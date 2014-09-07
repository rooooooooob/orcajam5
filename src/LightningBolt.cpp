#include "LightningBolt.hpp"

#include "jam-engine/Utility/Random.hpp"
#include "jam-engine/Utility/Trig.hpp"

namespace or5
{

LightningBolt::LightningBolt(je::Level *level, const sf::Vector2f& startPos, const sf::Vector2f& targetPos)
	:je::Entity(level, "LightningBolt", startPos, sf::Vector2i(8, 8), sf::Vector2i(4, 4))
	,startPos(startPos)
	,veloc(je::lengthdir(12.f, je::pointDirection(startPos, targetPos)))
{
	const int n = 4 + je::random(5);
	for (int i = 0; i < n; ++i)
	{
		bolts.push_back(sf::VertexArray(sf::PrimitiveType::LinesStrip));
	}
}

void LightningBolt::onUpdate()
{
	const float dir = je::direction(veloc);

	if (getPos().y > 400.f)
	{
		this->destroy();
	}
	else
	{
		transform().move(veloc);

		const int boltJumpDist = 32;
		const int boltJumpVariance = 16;
		const int len = je::pointDistance(startPos, getPos());

		for (sf::VertexArray& bolt : bolts)
		{
			bolt.clear();

			const sf::Color color(0, 170, 255, 169);

			bolt.append(sf::Vertex(startPos, color));


			for (int i = je::random(boltJumpDist); i < len; i += je::random(boltJumpDist))
			{
				const sf::Vector2f pos = startPos // initial position
									   + je::lengthdir(i, dir) // how far we've traveled so far
									   + je::lengthdir(je::randomf(boltJumpVariance) * 2 - boltJumpVariance, dir + 90.f); // variance normal to the ray direction
				bolt.append(sf::Vertex(pos, color));
			}

			bolt.append(sf::Vertex(getPos(), color));
		}
	}
}

void LightningBolt::draw(sf::RenderTarget& target, const sf::RenderStates& states) const
{
	sf::RenderStates s = states;
	//s.transform *= transform().getTransform();
	for (const sf::VertexArray& bolt : bolts)
	{
		target.draw(bolt, s);
	}
}

} // or5
