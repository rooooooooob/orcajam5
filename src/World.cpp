#include "World.hpp"
#include "GroundBase.hpp"

namespace or5
{

World::World(je::Game *game)
	:je::Level(game, 640, 480)
{
	GroundBase* grass = new GroundBase(this, sf::Vector2f(0, getHeight()*(2.f/3.f)), sf::Vector2i(getWidth(), getHeight()/3.f));
	addEntity(grass);
}


void World::onUpdate()
{
}

void World::onDraw(sf::RenderTarget& target) const
{
}

void World::drawGUI(sf::RenderTarget& target) const
{
}

void World::beforeDraw(sf::RenderTarget& target) const
{
}


} // or5
