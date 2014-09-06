#include "Tree.hpp"

#include "jam-engine/Core/Level.hpp"
#include "jam-engine/Utility/Random.hpp"

#include "GrowingLimb.hpp"

namespace or5
{

Tree::Tree(je::Level *level, const sf::Vector2f& pos)
	:je::Entity(level, "Tree", pos, sf::Vector2i(32, 32))
	,trunk(nullptr)
{
	trunk = new GrowingLimb(level, pos);
	level->addEntity(trunk);
}


void Tree::grow(float amount)
{
	trunk->grow(amount);
}

/*				private				*/
void Tree::onUpdate()
{
	if (je::random(100) == 9) // 9 is a cool number
	{
		grow(je::randomf(2.f));
	}
}

void Tree::draw(sf::RenderTarget& target, const sf::RenderStates& states) const
{
}

} // or5
