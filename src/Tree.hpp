#ifndef OR5_TREE_HPP
#define OR5_TREE_HPP

#include "jam-engine/Core/Entity.hpp"

namespace or5
{

class GrowingLimb;

class Tree : public je::Entity
{
public:
	Tree(je::Level *level, const sf::Vector2f& pos);

	void grow(float amount);

private:
	void onUpdate() override;

	void draw(sf::RenderTarget& target, const sf::RenderStates& states) const override;

	GrowingLimb *trunk;
};

} // or5

#endif // OR5_TREE_HPP
