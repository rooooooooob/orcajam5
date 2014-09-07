#include "LightningBolt.hpp"

#include "jam-engine/Core/Level.hpp"
#include "jam-engine/Utility/Random.hpp"
#include "jam-engine/Utility/Trig.hpp"

#include "Blood.hpp"

namespace or5
{

LightningBolt::LightningBolt(je::Level *level, const sf::Vector2f& startPos, const sf::Vector2f& targetPos)
	:je::Entity(level, "LightningBolt", startPos, sf::Vector2i(16, 16), sf::Vector2i(-8, -8))
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
	// destroy if off screen
	if (getPos().x < -16.f || getPos().x > level->getWidth() + 16.f || getPos().y < -16.f)
	{
		destroy();
	}

	std::vector<je::Entity*> poorLittleGnomes;
	level->findCollisions(poorLittleGnomes, this, "Gnome");
	for (je::Entity* poorLittleGnome : poorLittleGnomes)
	{
		const int n = 9 + je::random(5);
		for (int i = 0; i < n; ++i)
		{
			const float bSpd = 2.f + je::randomf(3.f);
			const float bDir = je::randomf(180.f);
			level->addEntity(new Blood(level, poorLittleGnome->getPos() - sf::Vector2f(0.f, 8.f), je::lengthdir(bSpd, bDir)));
		}
		poorLittleGnome->destroy();
	}

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
