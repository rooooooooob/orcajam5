#ifndef OR5_GROWINGLIMB_HPP
#define OR5_GROWINGLIMB_HPP

#include <SFML/Graphics/ConvexShape.hpp>

#include <vector>

#include "jam-engine/Core/Entity.hpp"

namespace or5
{

class Fruit;

class Tree;

class GrowingLimb : public je::Entity
{
public:
	GrowingLimb(je::Level *level, const sf::Vector2f& pos, Tree* base, int capacity);

	void grow(float amount);

	void updateBoneTransform(sf::Vector2f pos, sf::Vector2f scale, sf::Vector2f origin, float angle);

	sf::Transformable& getLimbTransform() { return limbTransform; }

	int getRemainingCapacity() { return limbCapacity - children.size(); }

private:
	void onUpdate() override;

	void draw(sf::RenderTarget& target, const sf::RenderStates& states) const override;

	void recalculateBounds();


	std::vector<GrowingLimb*> children;
	sf::ConvexShape vertices;
	float length;
	float angle;
	sf::Transformable limbTransform;
	int limbCapacity;
	GrowingLimb *parent;
	Tree* tree;
	Fruit *fruit;
};

} // or5

#endif // OR5_GROWINGLIMB_HPP
