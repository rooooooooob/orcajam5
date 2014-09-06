#include "Tree.hpp"

namespace or5
{

Tree::Tree(je::Level *level, const sf::Vector2f& pos)
	:je::Entity(level, "Tree", pos, sf::Vector2i(32, 32))
	,length(0)
{
}


void Tree::onUpdate()
{
}

void Tree::draw(sf::RenderTarget& target, const sf::RenderStates& states) const
{
}

} // or5
