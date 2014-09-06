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
	,length(33.f)
{
	recalculateBounds();
}


void GrowingLimb::subdivide()
{
	const int n = 2;
	for (int i = 0; i < 2; ++i)
	{
		GrowingLimb *child = new GrowingLimb(level, getPos() + je::lengthdir(length, angle));
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

/*			private			*/
void GrowingLimb::onUpdate()
{
}

void GrowingLimb::draw(sf::RenderTarget& target, const sf::RenderStates& states) const
{
	target.draw(vertices, states);
}

void GrowingLimb::recalculateBounds()
{
	const std::initializer_list<sf::Vector2f> points = {
		sf::Vector2f(-length / 3.f, 0.f),
		sf::Vector2f(length / 3.f, 0.f),
		sf::Vector2f(length / 4.f, length),
		sf::Vector2f(-length / 4.f, length)
	};

	setMask(je::DetailedMask::MaskRef(new je::PolygonMask(points)));

	vertices.clear();
	for (const sf::Vector2f& point : points)
	{
		vertices.append(sf::Vertex(point + getPos(), sf::Color(158, 91, 24)));
	}
	vertices.append(vertices[0]);
}

} // or5
