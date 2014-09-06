#ifndef OR5_WORLD_HPP
#define OR5_WORLD_HPP

#include "jam-engine/Core/Level.hpp"

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


};

} // or5

#endif // OR5_WORLD_HPP
