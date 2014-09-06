#include "GrowingLimb.hpp"
#include "Tree.hpp"

#include <initializer_list>
#include <iostream>

#include "jam-engine/Core/Level.hpp"
#include "jam-engine/Physics/PolygonMask.hpp"
#include "jam-engine/Utility/Random.hpp"
#include "jam-engine/Utility/Trig.hpp"

#define MaxLength 80
#define MinSubdivideLength 20

namespace or5
{

GrowingLimb::GrowingLimb(je::Level *level, const sf::Vector2f& pos, Tree* base, int capacity)
	:je::Entity(level, "GrowingLimb", pos, sf::Vector2i(32, 32))
	,children()
	,vertices(sf::PrimitiveType::Quads)
	,length(3.f)
	,angle(0.f)
	,limbTransform()
	,parent(nullptr)
	,tree(base)
	,limbCapacity(capacity)
{
	recalculateBounds();
}

void GrowingLimb::grow(float amount)
{
	const float rate = 0.1 + 0.9 * (1.f/length);
	length += amount * rate;
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
	int lengthPastSubdivide = length - MinSubdivideLength;
	if (lengthPastSubdivide < 0) lengthPastSubdivide = 0;

	if (children.size() < limbCapacity && je::randomf(1) < ((float)lengthPastSubdivide)/MaxLength)
	{
		GrowingLimb* child = tree->subdivide();

		if (child)
		{
			child->parent = this;
			//child->updateBoneTransform(sf::Vector2f(), sf::Vector2f(1.f, 1.f), sf::Vector2f(0.f, 0.f), 30.f - je::randomf(60.f));
			children.push_back(child);
		}
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
	const float upperThickness = length / 10.f + 1.f;
	const float lowerThickness = length / 8.f + 2.f;
	const std::initializer_list<sf::Vector2f> points = {
		sf::Vector2f(0.f, -lowerThickness),
		sf::Vector2f(0.f, lowerThickness),
		sf::Vector2f(length, upperThickness),
		sf::Vector2f(length, -upperThickness)
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
