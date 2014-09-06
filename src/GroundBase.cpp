#include "GroundBase.hpp"
#include "jam-engine/Core/Level.hpp"
#include "jam-engine/Core/Game.hpp"

namespace or5
{

GroundBase::GroundBase(je::Level *level, const sf::Vector2f& pos, const sf::Vector2i& dim)
	:je::Entity(level, "GroundBase", pos, dim)
	,grassTex(level->getGame().getTexManager().get("grass.png"))
	,grass(grassTex)
	,dirtTex(level->getGame().getTexManager().get("dirt.png"))
	,dirt(dirtTex)
{
	grass.setPosition(pos.x, pos.y - 4.f);
	grassTex.setRepeated(true);
	grass.setTextureRect(sf::IntRect(0.f, 0.f, dim.x, 16.f));

	dirt.setPosition(pos);
	dirtTex.setRepeated(true);
	dirt.setTextureRect(sf::IntRect(0.f, 0.f, dim.x, dim.y));

	setDepth(-10);
}


void GroundBase::onUpdate()
{
}

void GroundBase::draw(sf::RenderTarget& target, const sf::RenderStates& states) const
{
	target.draw(dirt, states);
	target.draw(grass, states);
}

} // or5
