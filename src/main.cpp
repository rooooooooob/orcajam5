#include "jam-engine/Core/Game.hpp"
#include "jam-engine/Graphics/TexManager.hpp"

#include "World.hpp"

int main()
{
	je::Game game(640, 480, 60);
	game.getTexManager().setPath("orcajam5/img/");

	game.setLevel(new or5::World(&game));

    return game.execute();
}
