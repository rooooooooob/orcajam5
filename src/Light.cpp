#include "Light.hpp"
#include "jam-engine/Core/Level.hpp"

namespace or5
{

Light::Light(je::Level *level)
: Entity(level, "Light", sf::Vector2f(0, 0), sf::Vector2i(0, 0))
{
}

void Light::shine(sf::Vector2f directionVector)
{

}

void Light::onUpdate()
{
}

void Light::draw(sf::RenderTarget& target, const sf::RenderStates& states) const
{
}

} // or5
