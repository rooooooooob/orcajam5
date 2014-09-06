#ifndef OR5_GROWINGLIMB_HPP
#define OR5_GROWINGLIMB_HPP

#include <SFML/Graphics/VertexArray.hpp>

#include <vector>

#include "jam-engine/Core/Entity.hpp"

namespace or5
{

class GrowingLimb : public je::Entity
{
public:
	GrowingLimb(je::Level *level, const sf::Vector2f& pos);


	void subdivide();

	void grow(float amount);

	void updateBoneTransform(sf::Vector2f pos, sf::Vector2f scale, sf::Vector2f origin, float angle);

private:
	void onUpdate() override;

	void draw(sf::RenderTarget& target, const sf::RenderStates& states) const override;

	void recalculateBounds();


	std::vector<GrowingLimb*> children;
	sf::VertexArray vertices;
	float length;
	float angle;
	sf::Transformable limbTransform;
	GrowingLimb *parent;
	const float lengthAtWhichSubdivide;
};

} // or5

#endif // OR5_GROWINGLIMB_HPP
