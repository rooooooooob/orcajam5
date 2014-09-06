#include "Tree.hpp"

#include "jam-engine/Core/Level.hpp"
#include "jam-engine/Utility/Random.hpp"
#include "jam-engine/Utility/Trig.hpp"

#include "GrowingLimb.hpp"
#include <cmath>
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
	if (je::random(4) == 2) // 9 is a cool number
	{
		grow(je::randomf(2.f));
	}
	static float d = 0;
	d += je::randomf(0.1f);
	trunk->updateBoneTransform(getPos(), sf::Vector2f(1.f, 1.f), sf::Vector2f(0.f, 0.f), (sin(d) * 30.f / je::pi) - 90.f);
}

void Tree::draw(sf::RenderTarget& target, const sf::RenderStates& states) const
{
}

} // or5
