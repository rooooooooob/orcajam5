#ifndef OR5_GNOME_HPP
#define OR5_GNOME_HPP

#include <map>

#include "jam-engine/Core/Entity.hpp"
#include "jam-engine/Graphics/Animation.hpp"

namespace or5
{

class Gnome : public je::Entity
{
public:
	Gnome(je::Level *level, const sf::Vector2f& pos);

private:
	void onUpdate() override;

	void draw(sf::RenderTarget& target, const sf::RenderStates& states) const override;

	enum class State
	{
		Wander,
		Building
	};

	enum class AnimKey
	{
		Running,
		Building
	};

	enum class Thought
	{
		Nothing,
		Hunger
	};

	State state;
	AnimKey currentAnimation;
	std::map<AnimKey, je::Animation> animations;

	// wander
	int targetX;

	int countdown;

	Thought thought;
	std::map<Thought, je::Animation> thoughtAnimations;

	float hunger;
};

} // or5

#endif // OR5_GNOME_HPP
