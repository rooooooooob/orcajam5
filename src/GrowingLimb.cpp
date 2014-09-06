#include "GrowingLimb.hpp"

#include <initializer_list>

#include "jam-engine/Core/Level.hpp"
#include "jam-engine/Physics/PolygonMask.hpp"
#include "jam-engine/Utility/Random.hpp"
#include "jam-engine/Utility/Trig.hpp"

namespace or5
{

GrowingLimb::GrowingLimb(je::Level *level, const sf::Vector2f& pos)
	:je::Entity(level, "GrowingLimb", pos, sf::Vector2i(32, 32))
	,children()
	,vertices(sf::PrimitiveType::Quads)
	,length(3.f)
	,angle(0.f)
	,limbTransform()
	,parent(nullptr)
{
	recalculateBounds();
}


void GrowingLimb::subdivide()
{
	const int n = je::choose({2, 2, 3});

	const int minBudget = 20;
	std::vector<int> variances(n - 1, minBudget);
	int totalVariance = 0;
	for (int& variance : variances)
	{
		variance += je::randomf(10.f);
		totalVariance += variance;
	}

	float delta = je::randomf(30.f) - 15.f - totalVariance / 2.f;

	for (int i = 0; i < 2; ++i)
	{
		GrowingLimb *child = new GrowingLimb(level, sf::Vector2f(0.f, 0.f));//getPos() + je::lengthdir(length, angle));
		child->parent = this;
		//child->updateBoneTransform(sf::Vector2f(), sf::Vector2f(1.f, 1.f), sf::Vector2f(0.f, 0.f), 30.f - je::randomf(60.f));
		child->limbTransform.setRotation(delta);
		if (i < variances.size())
		{
			delta += variances[i];
		}
		children.push_back(child);
		level->addEntity(child);
	}
}

void GrowingLimb::grow(float amount)
{
	length += amount;
	recalculateBounds();
	for (GrowingLimb *child : children)
	{
		child->grow(amount);
	}
}

void GrowingLimb::updateBoneTransform(sf::Vector2f pos, sf::Vector2f scale, sf::Vector2f origin, float angle)
{
	//	boneTransform() overrides anything done to the regular Enity transform
	pos += limbTransform.getPosition();
	if (parent)
	{
		pos += je::lengthdir(scale.x * parent->length, -angle);
	}
	scale.x *= limbTransform.getScale().x;
	scale.y *= limbTransform.getScale().y;
	origin += limbTransform.getOrigin();
	angle += limbTransform.getRotation();

	transform().setPosition(pos);
	transform().setScale(scale);
	transform().setOrigin(origin);
	transform().setRotation(angle);

	for (GrowingLimb *child : children)
	{
		child->updateBoneTransform(pos, scale, origin, angle);
	}
}

/*			private			*/
void GrowingLimb::onUpdate()
{
	if (children.empty() && length > 32.f)
	{
		subdivide();
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
	const std::initializer_list<sf::Vector2f> points = {
		sf::Vector2f(0.f, -length / 3.f),
		sf::Vector2f(0.f, length / 3.f),
		sf::Vector2f(length, length / 4.f),
		sf::Vector2f(length, -length / 4.f)
	};

	setMask(je::DetailedMask::MaskRef(new je::PolygonMask(points)));

	vertices.clear();
	for (const sf::Vector2f& point : points)
	{
		vertices.append(sf::Vertex(point, sf::Color(158, 91, 24)));
	}
	vertices.append(vertices[0]);
}

} // or5
