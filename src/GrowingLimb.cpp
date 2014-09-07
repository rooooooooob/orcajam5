#include "GrowingLimb.hpp"
#include "Tree.hpp"

#include <initializer_list>

#include "jam-engine/Core/Game.hpp"
#include "jam-engine/Core/Level.hpp"
#include "jam-engine/Physics/PolygonMask.hpp"
#include "jam-engine/Utility/Random.hpp"
#include "jam-engine/Utility/Trig.hpp"

#include "Fruit.hpp"

#define TreeSize 0.5f

namespace or5
{

GrowingLimb::GrowingLimb(je::Level *level, const sf::Vector2f& pos, Tree* base, int capacity, int parentDepth)
	:je::Entity(level, "GrowingLimb", pos, sf::Vector2i(32, 32))
	,children()
	,vertices(4)
	,length(2.f)
	,angle(0.f)
	,MaxLength(200)
	,MinSubdivideLength(MaxLength/4)
	,limbTransform()
	,parent(nullptr)
	,tree(base)
	,limbCapacity(capacity)
	,chainDepth(++parentDepth)
	,fruit(nullptr)
{
	vertices.setTexture(&level->getGame().getTexManager().get("bark.png"));

	recalculateBounds();
}

void GrowingLimb::grow(float amount)
{
	if (length < float(MaxLength)/chainDepth)
	{
		const float rate = 0.1 * (MaxLength - length)/(MaxLength);
		length += amount * rate;
	}

	recalculateBounds();
	for (GrowingLimb *child : children)
	{
		child->grow(amount);
	}

	int lengthPastSubdivide = length - MinSubdivideLength;
	if (lengthPastSubdivide < 0) lengthPastSubdivide = 0;

	if (limbCapacity > children.size() && je::randomf(length * 100) < length/(children.size() + 1))
	{
		GrowingLimb* child = tree->subdivide(this);

		if (child)
		{
			child->parent = this;
			//child->updateBoneTransform(sf::Vector2f(), sf::Vector2f(1.f, 1.f), sf::Vector2f(0.f, 0.f), 30.f - je::randomf(60.f));
			children.push_back(child);
		}
	}
}

void GrowingLimb::updateBoneTransform(sf::Vector2f pos, sf::Vector2f scale, sf::Vector2f origin, float angle)
{
	//	boneTransform() overrides anything done to the regular Enity transform
	pos += limbTransform.getPosition();
	if (parent)
	{
		pos += je::lengthdir(scale.x * TreeSize * parent->length, -angle);
	}
	scale.x *= limbTransform.getScale().x;
	scale.y *= limbTransform.getScale().y;
	origin += limbTransform.getOrigin();
	angle += limbTransform.getRotation();

	transform().setPosition(pos);
	transform().setScale(scale);
	transform().setOrigin(origin);
	transform().setRotation(angle);

	updateMask();

	for (GrowingLimb *child : children)
	{
		child->updateBoneTransform(pos, scale, origin, angle);
	}
}

/*			private			*/
void GrowingLimb::onUpdate()
{
	if (fruit)
	{
		if (!fruit->isDetached())
		{
			fruit->transform().setPosition(getPos() + je::lengthdir(transform().getScale().x * TreeSize * length, -transform().getRotation()));
		}
		else
		{
			fruit = nullptr;
		}
	}
	else if (children.empty() && je::random(300) == 0)
	{
		fruit = new Fruit(level, getPos() + je::lengthdir(transform().getScale().x * TreeSize * length, -transform().getRotation()));
		level->addEntity(fruit);
	}
}

void GrowingLimb::draw(sf::RenderTarget& target, const sf::RenderStates& states) const
{
	sf::RenderStates s = states;
	s.transform *= transform().getTransform();
	target.draw(vertices, s);
}

void GrowingLimb::recalculateBounds()
{
	const float treeLength = length * TreeSize;
	const float upperThickness = treeLength / 10.f + 1.f;
	const float lowerThickness = treeLength / 8.f + 2.f;
	const std::initializer_list<sf::Vector2f> points = {
		sf::Vector2f(0.f, -lowerThickness),
		sf::Vector2f(0.f, lowerThickness),
		sf::Vector2f(treeLength, upperThickness),
		sf::Vector2f(treeLength, -upperThickness)
	};

	setMask(je::DetailedMask::MaskRef(new je::PolygonMask(points)));

	unsigned int index = 0;
	for (const sf::Vector2f& point : points)
	{
		vertices.setPoint(index++, point);
	}
}

} // or5
