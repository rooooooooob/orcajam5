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
	trunk = new GrowingLimb(level, pos, this, capacity);
	level->addEntity(trunk);
	freeBranches += capacity;
}


void Tree::grow(float amount)
{
	trunk->grow(amount);
}

GrowingLimb* Tree::subdivide(bool lastBranch)
{
	if (lastBranch)
		freeBranches--;

	float delta = distribution(generator);// - totalVariance / 2.f;

	int branchCapacity = je::random(MaxBranchCapacity) + 1; // 1 to MaxBranches branchess;
	if (freeBranches > 1)
	{
		branchCapacity -= MaxBranchCapacity * (freeBranches/MaxBranches);
		if (branchCapacity < 0) branchCapacity = 0;
	}

	GrowingLimb *child = new GrowingLimb(level, sf::Vector2f(0.f, 0.f), this, branchCapacity);//getPos() + je::lengthdir(length, angle));
	freeBranches += branchCapacity;
	child->getLimbTransform().setRotation(delta);
	level->addEntity(child);
	branchCount++;
	return child;
}

/*				private				*/
void Tree::onUpdate()
{
	//if (je::random(4) == 1) // 9 is a cool number
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
