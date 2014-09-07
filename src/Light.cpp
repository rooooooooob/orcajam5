#include "Light.hpp"
#include "jam-engine/Core/Level.hpp"

namespace or5
{

Light::Light(je::Level *level)
: Entity(level, "Light", sf::Vector2f(0, 0), sf::Vector2i(0, 0))
{
}

void Light::shine(sf::Vector2f initialPoint, sf::Vector2f endPoint)
{
	sf::Vector2f directionVector = endPoint - initialPoint;
	if (directionVector.x == 0)
	{

	}
	else
	{
		double slope = directionVector.y/directionVector.x;
		double b = (endPoint.x * slope) - endPoint.y;
		screenEdgePoint = sf::Vector2f((-1) * (b/slope), 0);
	}
}

void Light::onUpdate()
{
}

void Light::draw(sf::RenderTarget& target, const sf::RenderStates& states) const
{
	level->debugDrawRect(sf::Rect<int>(screenEdgePoint.x, screenEdgePoint.y, 5, 5), sf::Color::Red, sf::Color::Red);
}

} // or5
