#include <SFML/Graphics.hpp>
#include "Map.hpp"
#include "Cursor.hpp"
#include "Config.hpp"
#include "Background.hpp"
#include <iostream>
#include <ctime>
#include <Windows.h>

//load planets and black hole sprites
bool Setup(sf::Texture* tex, sf::Sprite* sprites)
{
	std::string paths[TILES_COUNT] = {
		"images/black_hole.png",
		"images/mars.png",
		"images/moon.png",
		"images/earth.png",
	};
	for (size_t i = 0; i < TILES_COUNT; i++)
	{
		if (!createSprite(sprites[i], tex[i], paths[i]))
			return false;
	}
	return true;
}

//return true if order is established
bool checkForEnd(const int* order)
{
	for (size_t i = 0; i < map.SIZE; i++)
	{
		if (!(
			map.field[i][0] == order[0] &&
			map.field[i][2] == order[1] &&
			map.field[i][4] == order[2]))
		{
			return false;
		}
	}
	return true;
}

void drawPlanetOrder(sf::RenderWindow& window, sf::Sprite* sprites, int* order)
{
	for (size_t i = 0; i < PLANETS_AMOUNT; i++)
	{
		sprites[order[i]].setPosition(X_FIELD + TILE_SIZE * 2 * i, Y_PLANET_ORDER);
		window.draw(sprites[order[i]]);
	}
}

void updateText(sf::Text& text, int score)
{
	text.setString("Score: " + std::to_string(score));
}

int main()
{
	HWND hConsole = GetConsoleWindow();//hide WindowConsole
	ShowWindow(hConsole, SW_HIDE);
	
	srand(time(NULL));

	Cursor pointer("images/cursor.png", X_FIELD, Y_FIELD, X_FIELD, Y_FIELD);
	if (!pointer.is_open())
		return -1;

	sf::Texture tex[TILES_COUNT];

	sf::Sprite sprites[TILES_COUNT];

	if (!Setup(tex, sprites))
		return -1;

	Background back("images/background.jpg", BACKGROUND_SPEED);
	if (!back.is_open())
		return -1;

	sf::RenderWindow window({ SCREEN_WIDTH, SCREEN_HEIGHT }, "Rofl Game");
	if (!window.isOpen())
		return -1;
	
	//load table
	sf::Texture texTable;
	sf::Sprite spTable;
	if (!createSprite(spTable, texTable, "images/table.png"))
		return false;
	spTable.setPosition(X_TABLE, Y_TABLE);

	float time;
	
	sf::Event event;

	sf::Clock clock;

	//load shuffle button
	sf::Texture texShuffle;
	sf::Sprite spShuffle;
	if (!createSprite(spShuffle, texShuffle, "images/shuffle.png", sf::Color::White))
		return -1;
	spShuffle.setPosition(X_SHUFFLE, Y_SHUFFLE);

	int score = 0;

	sf::Font font;
	font.loadFromFile("fonts/BebasNeue-Regular.ttf");

	sf::Text text;
	text.setFont(font);
	text.setCharacterSize(30);
	text.setStyle(sf::Text::Bold);
	text.setFillColor(sf::Color::Green);
	text.setPosition(X_SHUFFLE, Y_SHUFFLE + TILE_SIZE * 2);
	updateText(text, score);


	int order[PLANETS_AMOUNT];
	generatePlanetOrder(order);
	createMap();
	
	while (true)
	{
		time = clock.getElapsedTime().asSeconds();
		clock.restart();
		if (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
				break;
			}
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left) &&
				sf::IntRect(
					X_SHUFFLE, 
					Y_SHUFFLE, 
					SHUFFLE_WIDTH, 
					SHUFFLE_HEIGHT).contains(sf::Mouse::getPosition(window))
				)
			{
				generatePlanetOrder(order);
				createMap();
			}
			pointer.Control(event);
		}

		window.clear();

		back.draw(window);
		window.draw(spTable);
		drawPlanetOrder(window, sprites, order);
		drawMap(window, sprites);
		pointer.Draw(window);
		window.draw(spShuffle);
		window.draw(text);

		window.display();

		if (checkForEnd(order))
		{
			score++;
			updateText(text, score);
			createMap();
			generatePlanetOrder(order);
		}
		back.update(time);
	}
	return 0;
}