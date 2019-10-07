#pragma once
#include <SFML/Graphics.hpp>

bool createSprite(
	sf::Sprite& sp,
	sf::Texture& tex,
	const std::string fileName,
	const sf::Color color = sf::Color::Transparent
);