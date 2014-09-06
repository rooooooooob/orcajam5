#include "World.hpp"

namespace or5
{

World::World(je::Game *game)
	:je::Level(game, 640, 480)
{
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
