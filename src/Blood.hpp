#ifndef OR5_BLOOD_HPP
#define OR5_BLOOD_HPP

#include "jam-engine/Utility/Random.hpp"
#include "jam-engine/Core/Entity.hpp"

namespace or5
{

class Blood : public je::Entity
{
public:
	Blood(je::Level *level, const sf::Vector2f& pos, const sf::Vector2f& veloc, int type = je::random(3));


private:
	void onUpdate() override;

	void draw(sf::RenderTarget& target, const sf::RenderStates& states) const override;


	sf::Sprite sprite;
	sf::Vector2f veloc;
	int timer;
	bool isStuck;
};

}

#endif
