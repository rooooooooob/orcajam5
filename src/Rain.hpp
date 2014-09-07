#ifndef OR5_RAIN_HPP
#define OR5_RAIN_HPP

#include <SFML/Graphics/VertexArray.hpp>

#include "jam-engine/Core/Entity.hpp"

namespace or5
{

class Rain : public je::Entity
{
public:
	Rain(je::Level *level, const sf::Vector2f& pos);

private:
	void onUpdate() override;

	void draw(sf::RenderTarget& target, const sf::RenderStates& states) const override;


	int duration;
	sf::VertexArray rain;
};

} // or5

#endif // OR5_RAIN_HPP
