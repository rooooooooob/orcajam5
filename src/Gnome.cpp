#include "Gnome.hpp"

#include "jam-engine/Core/Game.hpp"
#include "jam-engine/Core/Level.hpp"
#include "jam-engine/Utility/Math.hpp"
#include "jam-engine/Utility/Random.hpp"
#include "jam-engine/Utility/Trig.hpp"

#include "Blood.hpp"
#include "Fruit.hpp"
#include "Tree.hpp"

namespace or5
{

Gnome::Gnome(je::Level *level, const sf::Vector2f& pos)
	:je::Entity(level, "Gnome", pos, sf::Vector2i(16, 16))
	,state(State::Wander)
	,currentAnimation(AnimKey::Running)
	,targetX(pos.x)
	,countdown(-1)
	,thought(Thought::Nothing)
	,hunger(0)
	,rage(0)
	,timesAlmostStarved(0)
{
	je::TexManager& texMan = level->getGame().getTexManager();
	animations.insert(std::make_pair(AnimKey::Running, je::Animation(texMan.get("gnome_running.png"), 16, 16, 6)));
	animations.insert(std::make_pair(AnimKey::Building, je::Animation(texMan.get("gnome_building.png"), 16, 16, 5)));
	animations.insert(std::make_pair(AnimKey::Chopping, je::Animation(texMan.get("gnome_chopping.png"), 16, 16, 5)));

	thoughtAnimations.insert(std::make_pair(Thought::Hunger, je::Animation(texMan.get("thinking_food.png"), 16, 16, {5, 10, 50})));
	thoughtAnimations.insert(std::make_pair(Thought::Chop, je::Animation(texMan.get("thinking_chop.png"), 16, 16, {5, 10, 50})));
	thoughtAnimations.insert(std::make_pair(Thought::Chop, je::Animation(texMan.get("thinking_tree.png"), 16, 16, {5, 10, 50})));
	thoughtAnimations.insert(std::make_pair(Thought::Chop, je::Animation(texMan.get("thinking_anti_tree.png"), 16, 16, {5, 10, 50})));

	for (auto& thoughtAnim : thoughtAnimations)
	{
		thoughtAnim.second.setOrigin(-8.f, 16.f);
	}

	transform().setOrigin(8.f, 16.f);
	transform().setPosition(pos);

	setDepth(-3);
}

/*				private				*/
void Gnome::onUpdate()
{
	if (countdown >= 0)
	{
		--countdown;
	}

	hunger += 0.03f;

	thought = Thought::Nothing;

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

			// get angry if almost starved a lot
			if (timesAlmostStarved > 1)
			{
				rage += 0.5f;
				thought = Thought::AntiTree;
			}
			else
			{
				if (rage > -100.f)
				{
					rage -= 0.05f;
				}
				else
				{
					thought = Thought::Tree;
				}
			}

			// hunger
			if (hunger > 50.f)
			{
				thought = Thought::Hunger;
				je::Entity *fruit = level->testCollision(this, "Fruit");
				if (fruit != nullptr)
				{
					if (hunger > 60.f)
					{
						++timesAlmostStarved;
					}
					fruit->destroy();
					hunger -= 50.f;
				}
			}
			if (hunger >= 100.f)
			{
				const int n = 9 + je::random(5);
				for (int i = 0; i < n; ++i)
				{
					const float bSpd = 2.f + je::randomf(3.f);
					const float bDir = je::randomf(180.f);
					level->addEntity(new Blood(level, getPos() - sf::Vector2f(0.f, 8.f), je::lengthdir(bSpd, bDir)));
				}
				destroy();
			}

			// GNOME RAGE
			if (rage > 100.f)
			{
				state = State::Rage;
			}
		}
		break;
	case State::Building:
		{

		}
		break;
	case State::Rage:
		{
			thought = Thought::Chop;
			Tree *tree = static_cast<Tree*>(level->testCollision(sf::Rect<int>(0, 0, level->getWidth(), level->getHeight()), "Tree"));

			transform().setScale(tree->getPos().x < getPos().x ? -1.f : 1.f, 1.f);

			if (tree->getPos().x > getPos().x + 32)
			{
				currentAnimation = AnimKey::Running;
				transform().move(1.f, 0.f);

				animations.at(currentAnimation).advanceFrame();
			}
			else if (tree->getPos().x < getPos().x - 32)
			{
				currentAnimation = AnimKey::Running;
				transform().move(-1.f, 0.f);

				animations.at(currentAnimation).advanceFrame();
			}
			else
			{
				currentAnimation = AnimKey::Chopping;

				animations.at(currentAnimation).advanceFrame();

				tree->chop();
			}
		}
		break;
	}

	if (thought != Thought::Nothing)
	{
		thoughtAnimations.at(thought).advanceFrame();
	}
}

void Gnome::draw(sf::RenderTarget& target, const sf::RenderStates& states) const
{
	sf::RenderStates s;
	s.transform *= transform().getTransform();
	target.draw(animations.at(currentAnimation), s);
	if (thought != Thought::Nothing)
	{
		target.draw(thoughtAnimations.at(thought), s);
	}
}

} // or5
