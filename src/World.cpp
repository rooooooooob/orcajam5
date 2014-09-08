#include "World.hpp"

#include "jam-engine/Core/Game.hpp"
#include "jam-engine/Utility/Random.hpp"

#include "Building.hpp"
#include "Gnome.hpp"
#include "GroundBase.hpp"
#include "GrowingLimb.hpp"
#include "LightningBolt.hpp"
#include "Rain.hpp"
#include "Tree.hpp"
#include "Light.hpp"

namespace or5
{

World::World(je::Game *game)
	:je::Level(game, 1280, 640)
	, screen(this, 100, 50, sf::Rect<int>(0, 0, 640, 480))
	, groundHeight(128.f)
	, groundLevel(getHeight() - groundHeight)
	, currentlySelectedPower(Power::Rain)
	, tree(nullptr)
{
	addEntity(new GroundBase(this, sf::Vector2f(0.f, groundLevel), sf::Vector2i(getWidth(), groundHeight)));
	tree = new Tree(this, sf::Vector2f(getWidth() / 2.f, groundLevel));
	addEntity(tree);
	light = new Light(this);
	addEntity(light);

	const sf::Color top(36, 60, 96);
	const sf::Color bottom(57, 96, 153);
	background[0] = background[4] = sf::Vertex(sf::Vector2f(0.f, 0.f), top);
	background[1] = sf::Vertex(sf::Vector2f(getWidth(), 0.f), top);
	background[2] = sf::Vertex(sf::Vector2f(getWidth(), getHeight()), bottom);
	background[3] = sf::Vertex(sf::Vector2f(0.f, getHeight()), bottom);

	screen.snap(sf::Vector2f(getWidth()/2, getHeight()*(3.f/4)));
}


const je::Camera World::getCamera() const
{
	return screen;
}

/*				private				*/

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

	if (input.isButtonPressed(sf::Mouse::Button::Right))
	{
		switch (currentlySelectedPower)
		{
		case Power::Rain:
			{
				addEntity(new Rain(this, sf::Vector2f(getCursorPos().x, 0.f)));
			}
			break;
		case Power::Lightning:
			{
				// why the hell do I have to multiply getWidth() by 2?!
				const sf::Vector2f start(je::randomf(getWidth() * 2), 0.f);
				mouseClickPoint = this->getCursorPos();
				const sf::Vector2f end = mouseClickPoint;
				addEntity(new LightningBolt(this, start, end));
			}
			break;
		}
	}
	else if (input.isButtonReleased(sf::Mouse::Button::Left))
	{
		if (input.isKeyHeld(sf::Keyboard::Key::A))
			light->shine(mouseClickPoint, getCursorPos());
	}

	if (input.isKeyPressed(sf::Keyboard::Key::Q))
	{
		if (currentlySelectedPower == Power::Rain)
		{
			currentlySelectedPower = Power::Lightning;
		}
		else if (currentlySelectedPower == Power::Lightning)
		{
			currentlySelectedPower = Power::Rain;
		}
	}
	if (input.isKeyPressed(sf::Keyboard::Key::E))
	{
		if (currentlySelectedPower == Power::Rain)
		{
			currentlySelectedPower = Power::Lightning;
		}
		else if (currentlySelectedPower == Power::Lightning)
		{
			currentlySelectedPower = Power::Rain;
		}
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
		if (building.getBuildingType() != Building::Type::Bonfire)
		{
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
	}

	// spawn initial house
	if (entities["Building"].empty())
	{
		if (tree->getTrunk()->getMask().getHeight() > 32)
		{
			addEntity(new Building(this, sf::Vector2f(getWidth() / 2.f - 128 + je::randomf(256), groundLevel), Building::Type::BasicHouse));
		}
		else
		{
			tree->grow(0.5f);
		}
	}

	const int gnomeCount = entities["Gnome"].size();

	if (gnomeCount >= 3 && buildingCount[Building::Type::Bonfire] < gnomeCount / 9)
	{
		int count = 0;
		int x;
		bool bonfireHere = false;
		do
		{
			x = je::random(getWidth());
			++count;
			Building *b = static_cast<Building*>(testCollision(sf::Rect<int>(x, groundLevel - 32, 32, 32), "Building"));
			bonfireHere = b && b->getBuildingType() == Building::Type::Bonfire;
		}
		while (count < 32 && bonfireHere);
		if (count < 32)
		{
			addEntity(new Building(this, sf::Vector2f(x, groundLevel), Building::Type::Bonfire));
		}
	}
	else if (gnomeCount >= 15 && buildingCount[Building::Type::Church] < gnomeCount / 17)
	{
		const int variance = je::random(10) - 5;
		const int buildingX = minBuildingX - 32 < 0 ?
		                      maxBuildingX + 32  :
							  maxBuildingX > getWidth() + 32 ?
							  minBuildingX - 32 :
		                      je::choose({minBuildingX - 32, maxBuildingX + 32});
		addEntity(new Building(this, sf::Vector2f(buildingX + variance, groundLevel), Building::Type::Church));
	}
	else if (buildingCount[Building::Type::BasicHouse] < gnomeCount / 7)
	{
		const int variance = je::random(8) - 4;
		const int buildingX = minBuildingX < 0 ?
		                      maxBuildingX :
							  (maxBuildingX > getWidth() ?
							  minBuildingX:
		                      je::choose({minBuildingX, maxBuildingX}));
		addEntity(new Building(this, sf::Vector2f(buildingX + variance, groundLevel), Building::Type::BasicHouse));
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
