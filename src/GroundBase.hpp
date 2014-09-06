#ifndef OR5_GROUNDBASE_HPP
#define OR5_GROUNDBASE_HPP

#include <SFML/Graphics/Sprite.hpp>

#include "jam-engine/Core/Entity.hpp"

namespace or5
{

class GroundBase : public je::Entity
{
public:
	GroundBase(je::Level *level, const sf::Vector2f& pos, const sf::Vector2i& dim);

private:
	void onUpdate() override;
	void draw(sf::RenderTarget& target, const sf::RenderStates& states) const override;

	sf::Sprite grass;
	sf::Texture grassTex;
	sf::Sprite dirt;
	sf::Texture dirtTex;
};

} // or5

#endif // OR5_GROUNDBASE_HPP
