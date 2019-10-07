#pragma once
#include <vector>

#include <SFML/Graphics.hpp>

#include "Config.hpp"

#define PLANETS_AMOUNT 3

struct Map
{
	static const int SIZE = 5;
	std::vector<std::vector<int>> field = 
	{
		//-2 as smth undefined
		{ -2, -2, -2, -2, -2},
		{ -2, -2, -2, -2, -2},
		{ -2, -2, -2, -2, -2},
		{ -2, -2, -2, -2, -2},
		{ -2, -2, -2, -2, -2}
	};
	//possible planets
	int planets[PLANETS_AMOUNT] = { MARS, MOON, EARTH };
};

void generatePlanetOrder(int* order);

void drawMap(sf::RenderWindow& window, sf::Sprite* sprites);

void createMap();

extern Map map;
