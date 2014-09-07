#include "Gnome.hpp"

#include "jam-engine/Core/Game.hpp"
#include "jam-engine/Core/Level.hpp"
#include "jam-engine/Utility/Math.hpp"
#include "jam-engine/Utility/Random.hpp"

namespace or5
{

Gnome::Gnome(je::Level *level, const sf::Vector2f& pos)
	:je::Entity(level, "Gnome", pos, sf::Vector2i(16, 16))
	,state(State::Wander)
	,currentAnimation(AnimKey::Running)
	,targetX(pos.x)
	,countdown(-1)
{
	je::TexManager& texMan = level->getGame().getTexManager();
	animations.insert(std::make_pair(AnimKey::Running, je::Animation(texMan.get("gnome_running.png"), 16, 16, 6)));
	animations.insert(std::make_pair(AnimKey::Building, je::Animation(texMan.get("gnome_building.png"), 16, 16, 5)));

	transform().setOrigin(8.f, 16.f);
	transform().setPosition(pos);

	setDepth(-1);
}

/*				private				*/
void Gnome::onUpdate()
{
	if (countdown >= 0)
	{
		--countdown;
	}

	switch (state)
	{
	case State::Wander:
		{
			currentAnimation = AnimKey::Running;
			if (targetX > getPos().x + 16)
			{
				transform().move(1.f, 0.f);
				transform().setScale(1.f, 1.f);

				animations.at(currentAnimation).advanceFrame();
			}
			else if (targetX < getPos().x - 16)
			{
				transform().move(-1.f, 0.f);
				transform().setScale(-1.f, 1.f);

				animations.at(currentAnimation).advanceFrame();
			}
			else
			{
				targetX = je::random(level->getWidth());
			}
		}
		break;
	case State::Building:
		{

		}
		break;
	}
}

void Gnome::draw(sf::RenderTarget& target, const sf::RenderStates& states) const
{
	sf::RenderStates s;
	s.transform *= transform().getTransform();
	target.draw(animations.at(currentAnimation), s);
}

} // or5
