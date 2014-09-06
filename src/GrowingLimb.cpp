#include "GrowingLimb.hpp"

namespace or5
{

GrowingLimb::GrowingLimb(je::Level *level, const sf::Vector2f& pos)
	:je::Entity(level, "GrowingLimb", pos, sf::Vector2i(32, 32))
	,length(0)
{
}


void GrowingLimb::onUpdate()
{
}

void GrowingLimb::draw(sf::RenderTarget& target, const sf::RenderStates& states) const
{
}

} // or5
