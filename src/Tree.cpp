#include "Tree.hpp"

#include "jam-engine/Core/Level.hpp"
#include "jam-engine/Utility/Random.hpp"
#include "jam-engine/Utility/Trig.hpp"

#include "GrowingLimb.hpp"
#include <cmath>

#define MaxBranchCapacity	4
#define MaxBranches 		160

namespace or5
{

Tree::Tree(je::Level *level, const sf::Vector2f& pos)
	:je::Entity(level, "Tree", pos, sf::Vector2i(32, 32))
	,trunk(nullptr)
	,distribution(0, 30)
	,branchCount(1)
	,freeBranches(1)
{
	int capacity = je::random(MaxBranchCapacity) + 1;
	trunk = new GrowingLimb(level, pos, this, capacity, 0);
	level->addEntity(trunk);
	freeBranches += capacity;
}


void Tree::grow(float amount)
{
	trunk->grow(amount);
}

GrowingLimb* Tree::subdivide(const GrowingLimb* parent)
{
	if (parent->getChildCount() == 1)
		freeBranches--;

	float delta = distribution(generator);// - totalVariance / 2.f;

	int branchCapacity = je::random(MaxBranchCapacity) + 1; // 1 to MaxBranches branchess;
	if (freeBranches > 1)
	{
		branchCapacity -= (MaxBranchCapacity * (freeBranches/MaxBranches)) ;
		if (branchCapacity < 0) branchCapacity = 0;
	}

	GrowingLimb *child = new GrowingLimb(level, sf::Vector2f(0.f, 0.f), this, branchCapacity, parent->getChainDepth());//getPos() + je::lengthdir(length, angle));
	freeBranches += branchCapacity;
	child->getLimbTransform().setRotation(delta);
	level->addEntity(child);
	branchCount++;
	return child;
}

/*				private				*/
void Tree::onUpdate()
{
	// natural growth
	if (je::random(30) == 9) // 9 is a cool number
	{
		grow(je::randomf(9.f));
	}

	// rain growth
	if (level->testCollision(this, "Rain") != nullptr)
	{
		grow(je::randomf(4.f));
	}

	// swaying in the "wind"
	static float d = 0;
	d += je::randomf(0.001f);
	trunk->updateBoneTransform(getPos(), sf::Vector2f(1.f, 1.f), sf::Vector2f(0.f, 0.f), (sin(d) * 30.f / je::pi) - 90.f);
}

void Tree::draw(sf::RenderTarget& target, const sf::RenderStates& states) const
{
}

} // or5
