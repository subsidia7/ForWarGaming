#include "Background.hpp"

Background::Background()
{
}

Background::Background(const std::string filePath, float dx)
	: dx(dx), x(0), y(0)
{
	if (createSprite(mSprite, mTex, filePath))
		opened = true;
}

void Background::update(float time)
{
	x += dx * time;
	if (x + SCREEN_WIDTH <= 0)
		x = 0;
}

void Background::draw(sf::RenderWindow& win)
{
	mSprite.setPosition(x, y);
	win.draw(mSprite);
	mSprite.setPosition(x + SCREEN_WIDTH, y);
	win.draw(mSprite);
}

bool Background::is_open() const
{
	return opened;
}

void Background::setSpeed(float speed)
{
	dx = speed;
}

Background::~Background()
{
}
