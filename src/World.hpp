#ifndef OR5_WORLD_HPP
#define OR5_WORLD_HPP

#include <SFML/Graphics/Vertex.hpp>

#include "jam-engine/Core/Level.hpp"
#include "jam-engine/Core/Camera.hpp"

#include "Light.hpp"

namespace or5
{

class World : public je::Level
{
public:
	World(je::Game *game);


private:
	void onUpdate() override;

	void onDraw(sf::RenderTarget& target) const override;

	void drawGUI(sf::RenderTarget& target) const override;

	void beforeDraw(sf::RenderTarget& target) const override;

	//void loadEntities(const std::string& layerName, const std::vector<EntityPrototype>& prototypes) override;

	//void createTiles(const std::string& filename, int tileWidth, int tileHeight, int tilesAcross, int tilesHigh) override;

	//void transformTiles(const std::string& layerName, int tilesAcross, int tilesHigh, unsigned  **tiles) override;


	sf::Vertex		background[5];
	Light			light;
	sf::Vector2f	mouseClickPoint;
	je::Camera		screen;
	sf::Vector2f	screenCenter;

	const float groundHeight;
	const float groundLevel;
};

} // or5

#endif // OR5_WORLD_HPP
