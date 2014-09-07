#ifndef OR5_LIGHTNINGBOLT_HPP
#define OR5_LIGHTNINGBOLT_HPP

#include <SFML/Graphics/VertexArray.hpp>

#include <vector>

#include "jam-engine/Core/Entity.hpp"

namespace or5
{

class LightningBolt : public je::Entity
{
public:
	LightningBolt(je::Level *level, const sf::Vector2f& startPos, const sf::Vector2f& targetPos);


private:
	void onUpdate() override;

	void draw(sf::RenderTarget& target, const sf::RenderStates& states) const override;


	sf::Vector2f startPos;
	sf::Vector2f veloc;
	std::vector<sf::VertexArray> bolts;
};

} // or5

#endif // OR5_LIGHTNINGBOLT_HPP
