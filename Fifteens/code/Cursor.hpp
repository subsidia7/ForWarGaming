#pragma once
#include <SFML/Graphics.hpp>
#include "Config.hpp"
#include <utility>
#include "Map.hpp" 
class Cursor
{
public:
	Cursor();
	Cursor(
		const std::string filePath, 
		const float x, 
		const float y, 
		const float xLeft, 
		const float yLeft
	);
	void Draw(sf::RenderWindow& w) const;
	void Update(const int dx, const int dy);
	void Control(const sf::Event& event);
	bool is_open() const;
	~Cursor();
private:
	sf::Texture mTexture;
	sf::Sprite mSprite;
	sf::Sprite mSpriteSpaced;//when tile is chosen
	bool notChosen = true;
	float x, y, xLeft, yLeft, xRight, yRight;
	std::pair<int, int> chosenPoint;
	void ChooseTile();
	void ChangeTile();
	bool opened = false;
};

