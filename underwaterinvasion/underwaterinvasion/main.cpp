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
#include <vector>
#include <stdio.h>
#include <math.h>

using namespace std;
//using namespace sf;

#define PI 3.14159265


int main()
{
	//sf::CircleShape shape(100.f);
	//shape.setFillColor(sf::Color::Green);
	unsigned int windowWidth = 1600;
	unsigned int windowHeight = 800;

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

	sf::RectangleShape bigRect(sf::Vector2f(10000, 600));
	bigRect.setFillColor(Color::Green);
	bigRect.setPosition(sf::Vector2f(0, 0));
	
	sf::RectangleShape constraintRectTop(sf::Vector2f(30000, 100));
	constraintRectTop.setFillColor(Color::White);
	constraintRectTop.setPosition(sf::Vector2f(0, 300));

	sf::RectangleShape constraintRectBot(sf::Vector2f(30000, 100));
	constraintRectBot.setFillColor(Color::White);
	constraintRectBot.setPosition(sf::Vector2f(0, 700));



	float normOffset = 100;
	float smallOffSet = 100 * cosf(PI / 4);
	

	

	bool hitbotconstraint = false;
	bool hittopconstraint = false;

	sf::Vector2f groundpos;
	groundpos.x = 0;
	groundpos.y = 550;

	srand(1);

	vector<sf::RectangleShape> groundVec;
	for (int i = 0; i < 300; i++) {
		sf::RectangleShape groundrecttoadd;
		groundrecttoadd.setSize(sf::Vector2f(100, 10));
		groundrecttoadd.setPosition(sf::Vector2f(groundpos.x, groundpos.y));
		groundrecttoadd.setFillColor(Color::Red);

		int randnum = (rand() % 3); // rand num between 0 and 2
		
		if (randnum == 0 && !hitbotconstraint) {
			groundrecttoadd.rotate(45);
			groundpos.x += smallOffSet;
			groundpos.y += smallOffSet;
			hittopconstraint = false;
			
		}else if (randnum == 1 && !hittopconstraint) {
			groundrecttoadd.rotate(-45);
			groundpos.x += smallOffSet;
			groundpos.y -= smallOffSet;
			hitbotconstraint = false;
			
		}
		else if (randnum == 2) {
			groundpos.x += normOffset;
			
		}

		if (groundrecttoadd.getGlobalBounds().intersects(constraintRectBot.getGlobalBounds())) {
			hitbotconstraint = true;
		}

		if (groundrecttoadd.getGlobalBounds().intersects(constraintRectTop.getGlobalBounds())) {
			hittopconstraint = true;
		}
		
		groundVec.push_back(groundrecttoadd);

	}




	sf::CircleShape myDot(25.0f);
	myDot.setFillColor(Color::Yellow);
	sf::Vector2f dotPosition;
	dotPosition.x = 50.0f;
	dotPosition.y = 100.0f;

	myDot.setPosition(dotPosition);

	float moveSpd = 1.5f;

	sf::View view;
	view.reset(sf::FloatRect(0, 0, windowWidth, windowHeight));
	view.setViewport(sf::FloatRect(0, 0, 1.0f, 1.0f));

	sf::Vector2f position(0, 0);

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
		if (state == gameState::game) {
			if (Keyboard::isKeyPressed(sf::Keyboard::D)) {
				dotPosition.x += moveSpd;
			}
			if (Keyboard::isKeyPressed(sf::Keyboard::S)) {
				dotPosition.y += 0.5;
			}
			if (Keyboard::isKeyPressed(sf::Keyboard::A)) {
				dotPosition.x -= moveSpd;
			}
			if (Keyboard::isKeyPressed(sf::Keyboard::W)) {
				dotPosition.y -= 0.5;
			}

		}


		window.clear(Color::Black);

		if (state == gameState::mainMenu) {
			mainMenu.update();
			window.draw(mainMenu.getMenuTitle());
			window.draw(mainMenu.getPlayButton());
			window.draw(mainMenu.getQuitButton());
		}
		if (state == gameState::game) {
			position.x = myDot.getPosition().x - (windowWidth / 2);
			position.y = myDot.getPosition().y - (windowHeight / 2);

			if (position.x < 0) {
				position.x = 0;
			}
			if (position.y < 0) {
				position.y = 0;
			}

			view.reset(sf::FloatRect(position.x, position.y, windowWidth, windowHeight));

			window.setView(view);

			myDot.setPosition(dotPosition);
			cout << dotPosition.x << ", " << dotPosition.y << endl;
			//window.draw(bigRect);
			//window.draw(ground);
			window.draw(constraintRectTop);
			window.draw(constraintRectBot);
			for (vector<sf::RectangleShape>::iterator it = groundVec.begin(); it != groundVec.end(); ++it) {
				window.draw(*it);
			}

			window.draw(myDot);

			
		}
		//window.draw();
		window.display();
	}

	return 0;
}