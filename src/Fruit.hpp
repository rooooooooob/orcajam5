#ifndef OR5_FRUIT_HPP
#define OR5_FRUIT_HPP

#include "jam-engine/Graphics/Animation.hpp"
#include "jam-engine/Core/Entity.hpp"

namespace or5
{

class Fruit : public je::Entity
{
public:
	Fruit(je::Level * level, const sf::Vector2f& pos);


	void detatch();

	bool isDetached() const;

private:
	void onUpdate() override;

	void draw(sf::RenderTarget& target, const sf::RenderStates& states) const override;

	enum class State
	{
		OnTree,
		Falling,
		OnGround
	};

	je::Animation sprite;
	int ripeness;
	State state;
	float gravity;
};

} // or5

#endif // OR5_FRUIT_HPP
