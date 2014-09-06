#include "World.hpp"
#include "GroundBase.hpp"

#include "Tree.hpp"

namespace or5
{

World::World(je::Game *game)
	:je::Level(game, 640, 480)
{
	addEntity(new GroundBase(this, sf::Vector2f(0, 400), sf::Vector2i(getWidth(), 80)));
	addEntity(new Tree(this, sf::Vector2f(320, 400)));

	const sf::Color top(36, 60, 96);
	const sf::Color bottom(57, 96, 153);
	background[0] = background[4] = sf::Vertex(sf::Vector2f(0.f, 0.f), top);
	background[1] = sf::Vertex(sf::Vector2f(getWidth(), 0.f), top);
	background[2] = sf::Vertex(sf::Vector2f(getWidth(), getHeight()), bottom);
	background[3] = sf::Vertex(sf::Vector2f(0.f, getHeight()), bottom);
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
	target.draw(background, 5, sf::PrimitiveType::Quads);
}


} // or5
