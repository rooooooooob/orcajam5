#include "Building.hpp"

#include "jam-engine/Core/Game.hpp"
#include "jam-engine/Core/Level.hpp"
#include "jam-engine/Utility/Assert.hpp"
#include "jam-engine/Utility/Random.hpp"

#include "Gnome.hpp"

namespace or5
{

Building::Building(je::Level *level, const sf::Vector2f& pos, Type type)
	:je::Entity(level, "Building", pos, getSize(type))
	,sprite(level->getGame().getTexManager().get(getFilename(type)), getSize(type).x, getSize(type).y, 6)
	,type(type)
	,constructionDone(0)
	,constructionNeeded(getConstructionNeeded(type))
{
	transform().setOrigin(0.f, getSize(type).y);

	setDepth(-1);
	if (type == Type::Bonfire)
	{
		setDepth(-2);
	}
}


Building::Type Building::getBuildingType() const
{
	return type;
}

bool Building::isBuilt() const
{
	return constructionDone >= constructionNeeded;
}

void Building::build(int amount)
{
	constructionDone += amount;
	if (constructionDone > constructionNeeded)
	{
		constructionDone = constructionNeeded;
	}
}

/*				private				*/
void Building::onUpdate()
{
	if (isBuilt())
	{
		sprite.advanceFrame();
		switch (type)
		{
		case Type::BasicHouse:
			{
				if (je::random(69) == 0 && level->testCollision(this, "Gnome") == nullptr)
				{
					level->addEntity(new Gnome(level, getPos()));
				}
			}
			break;
		case Type::Church:
			{
			}
			break;
		}
	}
	else // remove later ?
	{
		build(1);
	}
}

void Building::draw(sf::RenderTarget& target, const sf::RenderStates& states) const
{
	sf::Transform t;
	const int y = (constructionNeeded - constructionDone) / (float) constructionNeeded * getSize(type).y;
	t.translate(0, y);
	sf::RenderStates s = states;
	s.transform *= t;
	s.transform *= transform().getTransform();
	target.draw(sprite, s);
}

/*static*/ const char* Building::getFilename(Type type)
{
	switch (type)
	{
	case Type::BasicHouse:
		return "gnome_house_basic.png";
	case Type::Church:
		return "gnome_church.png";
	case Type::Bonfire:
		return "bonfire.png";
	}
	JE_ERROR("Unhandled type");
	return "";
}

/*static*/ sf::Vector2i Building::getSize(Type type)
{
	switch (type)
	{
	case Type::BasicHouse:
		return sf::Vector2i(32, 32);
	case Type::Church:
		return sf::Vector2i(64, 64);
	case Type::Bonfire:
		return sf::Vector2i(32, 32);
	}
	JE_ERROR("Unhandled type");
	return sf::Vector2i(0, 0);
}

/*static*/ int Building::getConstructionNeeded(Type type)
{
	switch (type)
	{
	case Type::BasicHouse:
		return 100;
	case Type::Church:
		return 300;
	case Type::Bonfire:
		return 50;
	}
	JE_ERROR("Unhandled type");
	return 0;
}

} // or5
