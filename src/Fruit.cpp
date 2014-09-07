#include "Fruit.hpp"

#include "jam-engine/Core/Game.hpp"
#include "jam-engine/Core/Level.hpp"
#include "jam-engine/Physics/CircleMask.hpp"
#include "jam-engine/Utility/Trig.hpp"

namespace or5
{

Fruit::Fruit(je::Level * level, const sf::Vector2f& pos)
	:je::Entity(level, "Fruit", pos, je::DetailedMask::MaskRef(new je::CircleMask(4)))
	,sprite(level->getGame().getTexManager().get("fruit.png"), 8, 8, 300, false)
	,ripeness(0)
	,state(State::OnTree)
	,gravity(0.f)
{
	sprite.setOrigin(4.f, 4.f);
}


void Fruit::detatch()
{
	if (state == State::OnTree)
	{
		state = State::Falling;
	}
}

bool Fruit::isDetached() const
{
	return state != State::OnTree;
}

/*				private				*/
void Fruit::onUpdate()
{
	++ripeness;
	sprite.advanceFrame();

	switch (state)
	{
	case State::OnTree:
		if ((je::pointDistance(level->getCursorPos(), getPos()) < 100.f && level->getGame().getInput().isButtonPressed(sf::Mouse::Button::Left)) ||
		     ripeness > 1500) // falls off due to being ripe
		{
			state = State::Falling;
		}
		break;
	case State::Falling:
		gravity += 0.2f;
		transform().move(0.f, gravity);
		if (level->testCollision(this, "GroundBase") != nullptr)
		{
			gravity = 0.f;
			state = State::OnGround;
		}
		break;
	case State::OnGround:
		break;
	}
}

void Fruit::draw(sf::RenderTarget& target, const sf::RenderStates& states) const
{
	sf::RenderStates s = states;
	s.transform *= transform().getTransform();
	target.draw(sprite, s);
}

} // or5
