#ifndef OR5_TREE_HPP
#define OR5_TREE_HPP

#include "jam-engine/Core/Entity.hpp"
#include <random>

namespace or5
{

class GrowingLimb;

class Tree : public je::Entity
{
public:
	Tree(je::Level *level, const sf::Vector2f& pos);

	void grow(float amount);

	GrowingLimb* subdivide(const GrowingLimb* parent);

	void chop();

private:
	void onUpdate() override;

	void draw(sf::RenderTarget& target, const sf::RenderStates& states) const override;

	GrowingLimb *trunk;

	std::default_random_engine generator;
	std::normal_distribution<float> distribution;
	int branchCount;
	int freeBranches;
	const int maxHp;
	int hp;
};

} // or5

#endif // OR5_TREE_HPP
