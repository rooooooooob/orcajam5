#ifndef OR5_GROWINGLIMB_HPP
#define OR5_GROWINGLIMB_HPP

#include <SFML/Graphics/ConvexShape.hpp>
#include <SFML/Graphics/Sprite.hpp>

#include <vector>

#include "jam-engine/Core/Entity.hpp"

namespace or5
{

class Fruit;

class Tree;

class GrowingLimb : public je::Entity
{
public:
	GrowingLimb(je::Level *level, const sf::Vector2f& pos, Tree* base, int capacity, int parentDepth);

	void grow(float amount);

	void updateBoneTransform(sf::Vector2f pos, sf::Vector2f scale, sf::Vector2f origin, float angle);

	sf::Transformable& getLimbTransform() { return limbTransform; }

	int getChildCount() const { return children.size(); }

	int getChainDepth() const { return chainDepth; }

	static const float MaxLengthLimit;
	static const float MinSubdivideLengthLimit;

private:
	void onUpdate() override;

	void draw(sf::RenderTarget& target, const sf::RenderStates& states) const override;

	void recalculateBounds();

	void spawnLeaves(int count);


	std::vector<GrowingLimb*> children;
	int chainDepth;
	sf::ConvexShape vertices;
	float length;
	float angle;
	float MaxLength;
	float MinSubdivideLength;
	sf::Transformable limbTransform;
	int limbCapacity;
	GrowingLimb *parent;
	Tree* tree;
	Fruit *fruit;
	std::vector<sf::Sprite> leaves;
};

} // or5

#endif // OR5_GROWINGLIMB_HPP
