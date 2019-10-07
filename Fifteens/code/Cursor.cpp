#include "Cursor.hpp"

Cursor::Cursor()
{
}

Cursor::Cursor(
	const std::string filePath, 
	const float x, 
	const float y, 
	const float xLeft, 
	const float yLeft
)
	:x(x), y(y), xLeft(xLeft), yLeft(yLeft), xRight(xLeft + (map.SIZE - 1) * TILE_SIZE), yRight(yLeft + (map.SIZE - 1) * TILE_SIZE)
{
	if (createSprite(mSprite, mTexture, filePath, sf::Color::White))
	{
		opened = true;
		mSpriteSpaced = mSprite;
		mSpriteSpaced.setColor(sf::Color::Red);
		mSprite.setPosition(x, y);
		mSpriteSpaced.setPosition(x, y);
	}
}

void Cursor::Draw(sf::RenderWindow& w) const
{
	if(!notChosen)
		w.draw(mSpriteSpaced);
	w.draw(mSprite);
}

bool Cursor::is_open() const
{
	return opened;
}

void Cursor::Update(const int dx, const int dy)
{
	float Y = y + dy, X = x + dx;
	if (X >= xLeft && X <= xRight && Y >= yLeft && Y <= yRight)
	{
		x = X;
		y = Y;
	}
	mSprite.setPosition(x, y);
}

void Cursor::Control(const sf::Event& event)
{
	if (event.type == sf::Event::KeyPressed)
	{
		switch (event.key.code)
		{
		case sf::Keyboard::Left:
			Update(-TILE_SIZE, 0);
			break;
		case sf::Keyboard::Right:
			Update(TILE_SIZE, 0);
			break;
		case sf::Keyboard::Up:
			Update(0, -TILE_SIZE);
			break;
		case sf::Keyboard::Down:
			Update(0, TILE_SIZE);
			break;
		case sf::Keyboard::Space:
			if (notChosen)
				ChooseTile();
			else
				ChangeTile();
			break;
		default:
			break;
		}
	}
}

void Cursor::ChooseTile()
{
	chosenPoint.first = (y - yLeft) / TILE_SIZE;
	chosenPoint.second = (x - xLeft) / TILE_SIZE;
	if (map.field[chosenPoint.first][chosenPoint.second] != EMPTINESS && 
		map.field[chosenPoint.first][chosenPoint.second] != BLACK_HOLE)
	{
		notChosen = false;
		mSpriteSpaced.setPosition(x, y);
	}
}

void Cursor::ChangeTile()
{
	std::pair<int, int> currentPoint;//row and col of current tile
	currentPoint.first = (y - yLeft) / TILE_SIZE;//row
	currentPoint.second = (x - xLeft) / TILE_SIZE;//col
	//we can move only to the emptiness 
	if (map.field[currentPoint.first][currentPoint.second] != EMPTINESS)
	{
		notChosen = true;
		return;
	}
	//this needs to check, is chosen tile a neighbour of current tile?
	int absOfDX = abs(currentPoint.first - chosenPoint.first);
	int absOfDY = abs(currentPoint.second - chosenPoint.second);
	if ( (absOfDX == 0) && (absOfDY == 0 || absOfDY == 1) || 
		 (absOfDX == 1 && absOfDY == 0) )
	{
		//swap tiles
		int swapped = map.field[currentPoint.first][currentPoint.second];
		map.field[currentPoint.first][currentPoint.second] = 
			map.field[chosenPoint.first][chosenPoint.second];
		map.field[chosenPoint.first][chosenPoint.second] = swapped;
	}
	notChosen = true;
}

Cursor::~Cursor()
{
}


