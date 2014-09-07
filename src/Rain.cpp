#include "Rain.hpp"

#include "jam-engine/Core/Level.hpp"
#include "jam-engine/Utility/Assert.hpp"
#include "jam-engine/Utility/Random.hpp"

namespace or5
{

const int RAIN_WIDTH = 128;
const int RAIN_DURATION = 360;

Rain::Rain(je::Level *level, const sf::Vector2f& pos)
	:je::Entity(level, "Rain", pos, sf::Vector2i(RAIN_WIDTH, level->getWidth()), sf::Vector2i(-RAIN_WIDTH / 2, 0))
	,duration(RAIN_DURATION)
	,rain(sf::PrimitiveType::Lines)
{
	const int rainMinX = pos.x - RAIN_WIDTH / 2;
	const int rainMaxX = pos.x + RAIN_WIDTH / 2;
	const sf::Color rainColor(32, 64, 192, 128);
	for (int y = 0; y < level->getWidth(); y += 16)
	{
		for (int x = rainMinX; x < rainMaxX; x += je::random(4))
		{
			const int yVariance = je::randomf(16.f);
			rain.append(sf::Vertex(sf::Vector2f(x, y - je::randomf(3.f) + yVariance), rainColor));
			rain.append(sf::Vertex(sf::Vector2f(x - 2 + je::randomf(4.f), y + 9 + je::randomf(9.f) + yVariance), rainColor));
		}
	}

	setDepth(-3);
}

void Rain::onUpdate()
{
	if (--duration < 0)
	{
		destroy();
	}

	const int rainCount = rain.getVertexCount();
	JE_ASSERT(rainCount % 2 == 0);
	const int levelHeight = level->getHeight();
	for (int i = 0; i < rainCount; i += 2)
	{
		if (rain[i + 1].position.y < levelHeight)
		{
			rain[i].position.y += 4;
			rain[i + 1].position.y += 4;
		}
		else
		{
			rain[i].position.y -= levelHeight;
			rain[i + 1].position.y -= levelHeight;
		}
	}
}

void Rain::draw(sf::RenderTarget& target, const sf::RenderStates& states) const
{
	target.draw(rain, states);
}

} // or5
