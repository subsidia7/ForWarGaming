#include "CreateSprite.hpp"

bool createSprite(
	sf::Sprite& sp,
	sf::Texture& tex,
	const std::string fileName,
	const sf::Color color 
)
{
	sf::Image img;
	if (!img.loadFromFile(fileName))
		return false;
	img.createMaskFromColor(color);
	if (!tex.loadFromImage(img))
		return false;
	sp.setTexture(tex);
}