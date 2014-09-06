#include "GroundBase.hpp"
#include "jam-engine/Core/Level.hpp"
#include "jam-engine/Core/Game.hpp"

namespace or5
{

GroundBase::GroundBase(je::Level *level, const sf::Vector2f& pos, const sf::Vector2i& dim)
	:je::Entity(level, "GroundBase", pos, dim)
	, length(0)
	, grass(level->getGame().getTexManager().get("grass.png"))
{
	grass.setPosition(pos);
}


void GroundBase::onUpdate()
{
}

void GroundBase::draw(sf::RenderTarget& target, const sf::RenderStates& states) const
{
	target.draw(grass, states);
}

} // or5
