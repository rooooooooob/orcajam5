#ifndef OR5_GROWINGLIMB_HPP
#define OR5_GROWINGLIMB_HPP

#include "jam-engine/Core/Entity.hpp"

namespace or5
{

class GrowingLimb : public je::Entity
{
public:
	GrowingLimb(je::Level *level, const sf::Vector2f& pos);

private:
	void onUpdate() override;
	void draw(sf::RenderTarget& target, const sf::RenderStates& states) const override;

	int length;
};

} // or5

#endif // OR5_GROWINGLIMB_HPP
