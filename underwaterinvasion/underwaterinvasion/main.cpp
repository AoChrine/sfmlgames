#include "stdafx.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "bigenemyship.h"
#include "enemyship.h"
#include "fueltank.h"
#include "menu.h"
#include "submarine.h"
#include "playground.h"
#include <Windows.h>
#include <cstdlib>
#include <sstream>
#include "stdafx.h"
#include <iostream>


int main()
{
	//sf::CircleShape shape(100.f);
	//shape.setFillColor(sf::Color::Green);
	unsigned int windowWidth = 1200;
	unsigned int windowHeight = 600;

	sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "Scramble Game");
	

	enum class gameState { game, mainMenu, restartMenu };
	gameState state = gameState::mainMenu;

	Menu mainMenu;
	mainMenu.setFont("font.ttf");
	Menu restartMenu;
	mainMenu.setFont("font.ttf");

	Music mainsong;
	if (!mainsong.openFromFile("chill.wav")) return -1;
	mainsong.setLoop(true);
	mainsong.play();

	Font font;
	font.loadFromFile("font.ttf");


	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}


		if (state == gameState::mainMenu) {
			if (mainMenu.getPlaySelected() == true && Keyboard::isKeyPressed(Keyboard::Space)) {
				state = gameState::game;
			}
			if (mainMenu.getPlaySelected() == false && Keyboard::isKeyPressed(Keyboard::Space)) {
				window.close();
			}
		}


		window.clear(Color::Blue);

		if (state == gameState::mainMenu) {
			mainMenu.update();
			window.draw(mainMenu.getMenuTitle());
			window.draw(mainMenu.getPlayButton());
			window.draw(mainMenu.getQuitButton());
		}
		//window.draw();
		window.display();
	}

	return 0;
}