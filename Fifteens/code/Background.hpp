#pragma once
#include <SFML/Graphics.hpp>
#include "Config.hpp"

class Background
{
public:
	Background();
	Background(const std::string filePath, float dx);
	void update(float time);
	void draw(sf::RenderWindow& win);
	bool is_open() const;
	void setSpeed(float speed);
	~Background();
private:
	float x, y;
	float dx;
	bool opened = false;
	sf::Texture mTex;
	sf::Sprite mSprite;
};

