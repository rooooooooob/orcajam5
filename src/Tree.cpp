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
	,distribution(0,15)
	,branchCount(1)
{
	trunk = new GrowingLimb(level, pos, this, 3);
	level->addEntity(trunk);
}


void Tree::grow(float amount)
{
	trunk->grow(amount);
}

GrowingLimb* Tree::subdivide()
{
	float delta = distribution(generator);// - totalVariance / 2.f;
	GrowingLimb *child = new GrowingLimb(level, sf::Vector2f(0.f, 0.f), this, 3);//getPos() + je::lengthdir(length, angle));
	child->getLimbTransform().setRotation(delta);
	level->addEntity(child);
	branchCount++;
	return child;
}

/*				private				*/
void Tree::onUpdate()
{
	//if (je::random(4) == 2) // 9 is a cool number
	{
		grow(je::randomf(4.f));
	}
	static float d = 0;
	d += je::randomf(0.01f);
	trunk->updateBoneTransform(getPos(), sf::Vector2f(1.f, 1.f), sf::Vector2f(0.f, 0.f), (sin(d) * 30.f / je::pi) - 90.f);
}

void Tree::draw(sf::RenderTarget& target, const sf::RenderStates& states) const
{
}

} // or5
