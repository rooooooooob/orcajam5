#include "World.hpp"

#include "jam-engine/Core/Game.hpp"
#include "jam-engine/Utility/Random.hpp"

#include "Building.hpp"
#include "Gnome.hpp"
#include "GroundBase.hpp"
#include "LightningBolt.hpp"
#include "Tree.hpp"

namespace or5
{

World::World(je::Game *game)
	:je::Level(game, 640, 480)
	, light(this)
	, screen(this, 100, 50, sf::Rect<int>(0, -240, 640, 480))
{
	addEntity(new GroundBase(this, sf::Vector2f(0, 400), sf::Vector2i(getWidth(), 80)));
	addEntity(new Tree(this, sf::Vector2f(320, 400)));
	addEntity(new Gnome(this, sf::Vector2f(100, 400)));
	addEntity(new Building(this, sf::Vector2f(500, 400), Building::Type::BasicHouse));
	addEntity(&light);

	const sf::Color top(36, 60, 96);
	const sf::Color bottom(57, 96, 153);
	background[0] = background[4] = sf::Vertex(sf::Vector2f(0.f, 0.f), top);
	background[1] = sf::Vertex(sf::Vector2f(getWidth(), 0.f), top);
	background[2] = sf::Vertex(sf::Vector2f(getWidth(), getHeight()), bottom);
	background[3] = sf::Vertex(sf::Vector2f(0.f, getHeight()), bottom);
}


void World::onUpdate()
{
	screenCenter = screen.getPosition();
	const je::Input input = getGame().getInput();

	if (input.isKeyHeld(sf::Keyboard::Key::Left))
	{
		screenCenter.x += -10;
	}
	if (input.isKeyHeld(sf::Keyboard::Key::Right))
	{
		screenCenter.x += 10;
	}
	if (input.isKeyHeld(sf::Keyboard::Key::Up))
	{
		screenCenter.y += -10;
	}
	if (input.isKeyHeld(sf::Keyboard::Key::Down))
	{
		screenCenter.y += 10;
	}

	if (input.isButtonPressed(sf::Mouse::Button::Left))
	{
		// why the hell do I have to multiply getWidth() by 2?!
		const sf::Vector2f start(je::randomf(getWidth() * 2), 0.f);
		mouseClickPoint = this->getCursorPos();
		const sf::Vector2f end = mouseClickPoint;
		addEntity(new LightningBolt(this, start, end));
	}
	else if (input.isButtonReleased(sf::Mouse::Button::Left))
	{
		if (input.isKeyHeld(sf::Keyboard::Key::A))
			light.shine(getCursorPos() - mouseClickPoint);
	}

	screen.update(screenCenter);

	// check for if you achieved some things
	int minBuildingX = getWidth();
	int maxBuildingX = 0;
	std::map<Building::Type, int> buildingCount;
	for (const je::Entity *entity : entities["Building"])
	{
		const Building& building = *static_cast<const Building*>(entity);
		++buildingCount[building.getBuildingType()];
		const int minX = building.getPos().x - building.getMask().getWidth();
		if (minX < minBuildingX)
		{
			minBuildingX = minX;
		}
		const int maxX = building.getPos().x + building.getMask().getWidth();
		if (maxX > maxBuildingX)
		{
			maxBuildingX = maxX;
		}

	}

	const int gnomeCount = entities["Gnome"].size();

	if (buildingCount[Building::Type::Bonfire] < 1 && gnomeCount >= 3)
	{
		const int buildingX = minBuildingX - 32 < 0 ?
		                      maxBuildingX + 32 :
							  maxBuildingX + 32 ?
							  minBuildingX - 32 :
		                      je::choose({minBuildingX - 32, maxBuildingX + 32});
		addEntity(new Building(this, sf::Vector2f(buildingX, 400.f), Building::Type::Bonfire));
	}
	else if (buildingCount[Building::Type::Church] < 1 && gnomeCount >= 15)
	{
		const int buildingX = minBuildingX - 64 < 0 ?
		                      maxBuildingX + 64 :
							  maxBuildingX + 64 ?
							  minBuildingX - 64 :
		                      je::choose({minBuildingX - 64, maxBuildingX + 64});
		addEntity(new Building(this, sf::Vector2f(buildingX, 400.f), Building::Type::Church));
	}
	else if (buildingCount[Building::Type::BasicHouse] < gnomeCount / 7)
	{
		const int buildingX = minBuildingX - 32 < 0 ?
		                      maxBuildingX + 32 :
							  maxBuildingX + 32 ?
							  minBuildingX - 32 :
		                      je::choose({minBuildingX - 32, maxBuildingX + 32});
		addEntity(new Building(this, sf::Vector2f(buildingX, 400.f), Building::Type::BasicHouse));
	}
}

void World::onDraw(sf::RenderTarget& target) const
{
}

void World::drawGUI(sf::RenderTarget& target) const
{
}

void World::beforeDraw(sf::RenderTarget& target) const
{
	target.draw(background, 5, sf::PrimitiveType::Quads);
}

} // or5
