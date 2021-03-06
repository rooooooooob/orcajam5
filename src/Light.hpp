#ifndef OR5_LIGHT_HPP
#define OR5_LIGHT_HPP

#include <SFML/Graphics/Vertex.hpp>

#include "jam-engine/Core/Entity.hpp"

namespace je
{
	class Level;
}

namespace or5
{

class Light : public je::Entity
{
public:
	Light(je::Level *level);
	void shine(sf::Vector2f initialPoint, sf::Vector2f endPoint);

private:
	void onUpdate();
	void draw(sf::RenderTarget& target, const sf::RenderStates& states) const;

	sf::Vertex      lightColour[5];
	sf::Vector2f    screenEdgePoint;
};

} // or5

#endif // OR5_LIGHT_HPP
