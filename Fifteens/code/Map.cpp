#include "Map.hpp"

#define EQUAL_PLANETS_AMOUNT 5

Map map;

void drawMap(sf::RenderWindow& window, sf::Sprite* sprites)
{
	int y;
	for (size_t i = 0; i < map.SIZE; i++)
	{
		y = Y_FIELD + i * TILE_SIZE;
		for (size_t j = 0; j < map.SIZE; j++)
		{
			if (map.field[i][j] == EMPTINESS) continue;
			sprites[map.field[i][j]].setPosition(X_FIELD + TILE_SIZE * j, y);
			window.draw(sprites[map.field[i][j]]);
		}
	}
}

//if all generated planets used return false
bool checkValid(int generated, const int* amount)
{
	if (amount[generated] == 0)
		return false;
	return true;
}

void generateValueFor(int &value, int* amount)
{
	int generated;
	bool randomIsValid = false;
	while (!randomIsValid)
	{
		generated = rand() % PLANETS_AMOUNT;
		randomIsValid = checkValid(generated, amount);
	}
	value = map.planets[generated];
	--amount[generated];
}

void setEmptinessAndBlackHoles()
{
	for (size_t i = 0; i < map.SIZE; i++)
	{
		for (size_t j = 1; j < map.SIZE; j += 2)
		{
			if (i % 2 == 0)
				map.field[i][j] = BLACK_HOLE;
			else
				map.field[i][j] = EMPTINESS;
		}
	}
}

void createMap()
{
	//max amounts of every possible planet
	int amount[PLANETS_AMOUNT] = 
	{ 
		EQUAL_PLANETS_AMOUNT, 
		EQUAL_PLANETS_AMOUNT, 
		EQUAL_PLANETS_AMOUNT
	};

	setEmptinessAndBlackHoles();

	//placing planets
	for (size_t i = 0; i < map.SIZE; i++)
	{
		for (size_t j = 0; j < map.SIZE; j++)
		{
			if (map.field[i][j] != BLACK_HOLE && map.field[i][j] != EMPTINESS)
			{
				generateValueFor(map.field[i][j], amount);//fill element with random planet
			}
		}
	}
}

void generatePlanetOrder(int* order)
{
	int amount[PLANETS_AMOUNT] = { 1, 1, 1 };
	for (size_t i = 0; i < PLANETS_AMOUNT; i++)
	{
		generateValueFor(order[i], amount);
	}
}
