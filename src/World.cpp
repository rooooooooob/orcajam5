#include "World.hpp"

#include "Tree.hpp"

namespace or5
{

World::World(je::Game *game)
	:je::Level(game, 640, 480)
{
	addEntity(new Tree(this, sf::Vector2f(320, 400)));
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
