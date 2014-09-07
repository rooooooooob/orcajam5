#ifndef OR5_BUILDING_HPP
#define OR5_BUILDING_HPP

#include "jam-engine/Core/Entity.hpp"
#include "jam-engine/Graphics/Animation.hpp"

namespace or5
{

class Building : public je::Entity
{
public:
	enum class Type
	{
		BasicHouse,
		Church,
		Bonfire
	};

	Building(je::Level *level, const sf::Vector2f& pos, Type type);


	Type getBuildingType() const;

	bool isBuilt() const;

	void build(int amount);

private:

	void onUpdate() override;

	void draw(sf::RenderTarget& target, const sf::RenderStates& states) const override;

	static const char* getFilename(Type type);

	static sf::Vector2i getSize(Type type);

	static int getConstructionNeeded(Type type);


	je::Animation sprite;
	Type type;
	int constructionDone;
	const int constructionNeeded;
};

} // or5

#endif // OR5_BUILDING_HPP
