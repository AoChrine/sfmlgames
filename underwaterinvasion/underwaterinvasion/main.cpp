#include "stdafx.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "bigenemyship.h"
#include "missile.h"
#include "bullet.h"
#include "enemyship.h"
#include "fueltank.h"
#include "menu.h"
#include "submarine.h"
#include <Windows.h>
#include <cstdlib>
#include <sstream>
#include "stdafx.h"
#include <iostream>
#include <vector>
#include <list>
#include <stdio.h>
#include <math.h>

using namespace std;

const float PI = 3.14159265f;


void fillGroundVector(vector<sf::RectangleShape> &groundVec);
void fillObjectVec(const vector<sf::RectangleShape> &groundvec, vector<enemyShip> &enemyShipVec, vector<bigEnemyShip> &bigEnemyShipVec, vector<fuelTank> &ftankVec);

int main()
{	
	Bullet testBul(500, 500);
	/*
	Init window
	*/

	unsigned int windowWidth = 1600;
	unsigned int windowHeight = 800;

	sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "Scramble Game");
	
	/*
	Setup game states
	*/
	enum class gameState { game, mainMenu, restartMenu };
	gameState state = gameState::mainMenu;

	/*
	Init main and restart menu
	*/
	Menu mainMenu;
	mainMenu.setFont("font.ttf");
	Menu restartMenu;
	mainMenu.setFont("font.ttf");

	/*
	Load music, font, texture
	*/
	Music mainsong;
	if (!mainsong.openFromFile("chill.wav")) return -1;
	mainsong.setLoop(true);
	//mainsong.play();

	Font font;
	font.loadFromFile("font.ttf");

	/*
	Init obj. for game
	*/

	Sub mySub(50, 100);
	mySub.setTexture("subsprite.png");

	vector<sf::RectangleShape> groundVec;
	fillGroundVector(groundVec);

	vector<enemyShip> enemyShipVec;
	vector<bigEnemyShip> bigEnemyShipVec;
	vector<fuelTank> fuelVec;
	list<Bullet> bulletList;
	fillObjectVec(groundVec, enemyShipVec, bigEnemyShipVec, fuelVec);

	for (vector<enemyShip>::iterator it = enemyShipVec.begin(); it != enemyShipVec.end(); ++it) {
		it->setTexture("enemyshipsprite.png");
	}
	for (vector<bigEnemyShip>::iterator it = bigEnemyShipVec.begin(); it != bigEnemyShipVec.end(); ++it) {
		it->setTexture("enemybigshipsprite.png");
	}
	for (vector<fuelTank>::iterator it = fuelVec.begin(); it != fuelVec.end(); ++it) {
		it->setTexture("fueltanksprite.png");
	}

	sf::View view;
	view.reset(sf::FloatRect(0.0f, 0.0f, (float)windowWidth, (float)windowHeight));
	view.setViewport(sf::FloatRect(0, 0, 1.0f, 1.0f));
	sf::Vector2f position(0, 0);



	while (window.isOpen())
	{

		/*
		Set up the scrolling view
		*/
		position.x = mySub.getSprite().getPosition().x - (windowWidth / 2);
		position.y = mySub.getSprite().getPosition().y - (windowHeight / 2);
		if (position.x < 0) {
			position.x = 0;
		}
		if (position.y < 0) {
			position.y = 0;
		}
	
		view.reset(sf::FloatRect(position.x, position.y, (float)windowWidth, (float)windowHeight));
		window.setView(view);
		


		// Close window
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		//Game state to control Main Menu
		if (state == gameState::mainMenu) {
			if (mainMenu.getPlaySelected() == true && Keyboard::isKeyPressed(Keyboard::Space)) {
				state = gameState::game;
			}
			if (mainMenu.getPlaySelected() == false && Keyboard::isKeyPressed(Keyboard::Space)) {
				window.close();
			}
			mainMenu.update();

			window.clear(Color::Black);
			window.draw(mainMenu.getMenuTitle());
			window.draw(mainMenu.getPlayButton());
			window.draw(mainMenu.getQuitButton());
		}

		//Game state to control Game
		if (state == gameState::game) {
			if (Keyboard::isKeyPressed(sf::Keyboard::Space)) {
				Bullet bullet(mySub.getSprite().getPosition().x + 64, mySub.getSprite().getPosition().y + 20);
				bulletList.push_back(bullet);

			}
			if (Keyboard::isKeyPressed(sf::Keyboard::D)) {
				mySub.moveRight();
			}
			if (Keyboard::isKeyPressed(sf::Keyboard::S)) {
				mySub.moveDown();
			}
			if (Keyboard::isKeyPressed(sf::Keyboard::A)) {
				mySub.moveLeft();
			}
			if (Keyboard::isKeyPressed(sf::Keyboard::W)) {
				mySub.moveUp();
			}
			for (vector<sf::RectangleShape>::iterator it = groundVec.begin(); it != groundVec.end(); ++it) {
				if (it->getGlobalBounds().intersects(mySub.getSprite().getGlobalBounds())) {
					cout << "colliding with ground" << endl;
				}
			}
			for (vector<enemyShip>::iterator it = enemyShipVec.begin(); it != enemyShipVec.end(); ++it) {
				

				if (abs(it->get_eShipSprite().getPosition().x - mySub.getSprite().getPosition().x) <= 200) {
					//cout << "true time to move up" << endl;
					it->setMoveUp();
				}

				if (it->get_eShipSprite().getGlobalBounds().intersects(mySub.getSprite().getGlobalBounds())) {
					cout << "collide with small ship" << endl;
				}

				it->update();
			}
			for (vector<bigEnemyShip>::iterator it = bigEnemyShipVec.begin(); it != bigEnemyShipVec.end(); ++it) {
				if (it->get_eBigShipSprite().getGlobalBounds().intersects(mySub.getSprite().getGlobalBounds())) {
					cout << "collide with big ship" << endl;
				}
			}
			for (vector<fuelTank>::iterator it = fuelVec.begin(); it != fuelVec.end(); ++it) {
				if (it->getTankSprite().getGlobalBounds().intersects(mySub.getSprite().getGlobalBounds())) {
					cout << "collide with fuel" << endl;
				}
			}
			list<Bullet>::iterator it = bulletList.begin();
			while (it != bulletList.end()) {
				if (it->getNoDraw() == true) {
					bulletList.erase(it++);
				}
				else {
					it->update();
					if (it->getBulletSprite().getPosition().x > mySub.getSprite().getPosition().x + 1200) {
						it->setNoDraw();
					}
				}
			}

			cout << "list size " << bulletList.size() << endl;

			
			mySub.update();
			//cout << mySub.getSprite().getPosition().x << ", " << mySub.getSprite().getPosition().y << endl;
			window.clear(Color::Black);

			window.draw(mySub.getSprite());

			for (vector<sf::RectangleShape>::iterator it = groundVec.begin(); it != groundVec.end(); ++it) {
				window.draw(*it);
			}
			for (vector<enemyShip>::iterator it = enemyShipVec.begin(); it != enemyShipVec.end(); ++it) {
				if (it->getNoDraw() == false) {
					window.draw(it->get_eShipSprite());
				}
			}
			for (vector<bigEnemyShip>::iterator it = bigEnemyShipVec.begin(); it != bigEnemyShipVec.end(); ++it) {
				window.draw(it->get_eBigShipSprite());
			}
			for (vector<fuelTank>::iterator it = fuelVec.begin(); it != fuelVec.end(); ++it) {
				window.draw(it->getTankSprite());
			}
			for (list<Bullet>::iterator it = bulletList.begin(); it != bulletList.end(); ++it) {
				window.draw(it->getBulletSprite());
			}
			
		
		}
		window.display();
	}

	return 0;
}

/*
Function to fill vector with rects to draw the ground
*/
void fillGroundVector(vector<sf::RectangleShape> &groundVec) {
	
	//DEFINE MAX GROUND HEIGHT
	sf::RectangleShape constraintRectTop(sf::Vector2f(30000, 10));
	constraintRectTop.setFillColor(Color::White);
	constraintRectTop.setPosition(sf::Vector2f(0, 500));

	
	//Define min ground height
	sf::RectangleShape constraintRectBot(sf::Vector2f(30000, 10));
	constraintRectBot.setFillColor(Color::White);
	constraintRectBot.setPosition(sf::Vector2f(0, 700));

	
	// Variables to make the ground
	float normOffset = 128.0f;
	float smallOffSet = 128 * cosf(PI / 4);
	bool hitbotconstraint = false;
	bool hittopconstraint = false;
	sf::Vector2f groundpos;
	groundpos.x = 0;
	groundpos.y = 550;

	// Seed rng so we have fixed field geometry
	srand(1);

	for (int i = 0; i < 400; i++) {
		sf::RectangleShape groundrecttoadd;
		groundrecttoadd.setSize(sf::Vector2f(128, 1));
		groundrecttoadd.setPosition(sf::Vector2f(groundpos.x, groundpos.y));
		groundrecttoadd.setFillColor(Color::Red);

		int randnum = (rand() % 4); // rand num between 0 and 3

		// Sets position for next rectangle if prev rec points down
		if (randnum == 0 && !hitbotconstraint) {
			groundrecttoadd.rotate(45);
			groundpos.x += smallOffSet;
			groundpos.y += smallOffSet;
			hittopconstraint = false;
		}
		// Sets	position for next rectangle if prev rec points up
		else if (randnum == 1 && !hittopconstraint) {
			groundrecttoadd.rotate(-45);
			groundpos.x += smallOffSet;
			groundpos.y -= smallOffSet;
			hitbotconstraint = false;
		}
		// Sets position for next rect if prev rect is flat
		else if (randnum == 2 || randnum == 3) {
			groundpos.x += normOffset;
		}
		// If next rect points down but is at min ground height, make next one point up	
		else if (randnum == 0 && hitbotconstraint) {
			groundrecttoadd.rotate(-45);
			groundpos.x += smallOffSet;
			groundpos.y -= smallOffSet;
			hitbotconstraint = false;
		}
		// If next rect points up but is at max ground height, make next one point down
		else if (randnum == 1 && hittopconstraint) {
			groundrecttoadd.rotate(45);
			groundpos.x += smallOffSet;
			groundpos.y += smallOffSet;
			hittopconstraint = false;
		}
		// If reached min ground height, set min ground height constraint to true
		if (groundrecttoadd.getGlobalBounds().intersects(constraintRectBot.getGlobalBounds())) {
			hitbotconstraint = true;
		}
		// If reached max ground height, set max ground height constraint to true
		if (groundrecttoadd.getGlobalBounds().intersects(constraintRectTop.getGlobalBounds())) {
			hittopconstraint = true;
		}
		// Push rect into vector
		groundVec.push_back(groundrecttoadd);
	}
}

/*
Function to fill vector with objects to draw on ground
*/
void fillObjectVec(const vector<sf::RectangleShape> &groundvec, vector<enemyShip> &enemyShipVec, vector<bigEnemyShip> &bigEnemyShipVec, vector<fuelTank> &ftankVec) {

	srand(1);

	for (vector<sf::RectangleShape>::const_iterator it = groundvec.begin(); it != groundvec.end(); ++it) {

		if (it->getRotation() == 0) {

			float recPosX = it->getPosition().x;
			float recPosY = it->getPosition().y;

			int randnum = (rand() % 5); // num between 0 and 4
			int randnum2 = (rand() % 5);

			if (randnum == 0 || randnum == 1 || randnum == 2) {
				enemyShip eShip(recPosX, recPosY - 32);
				enemyShipVec.push_back(eShip);
			}
			else if (randnum == 3) {
				bigEnemyShip bigEShip(recPosX, recPosY - 64);
				bigEnemyShipVec.push_back(bigEShip);
			}
			else if (randnum == 4) {
				fuelTank ftank(recPosX, recPosY - 32);
				ftankVec.push_back(ftank);
			}

			if (randnum2 == 0 || randnum2 == 1 || randnum2 == 2) {
				enemyShip eShip(recPosX+64, recPosY - 32);
				enemyShipVec.push_back(eShip);
			}
			else if (randnum2 == 3) {
				bigEnemyShip bigEShip(recPosX+64, recPosY - 64);
				bigEnemyShipVec.push_back(bigEShip);
			}
			else if (randnum2 == 4) {
				fuelTank ftank(recPosX+64, recPosY - 32);
				ftankVec.push_back(ftank);
			}
	

		}
	}
}