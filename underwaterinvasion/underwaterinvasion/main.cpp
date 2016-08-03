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
void fillBulletVec(vector<Bullet*> &bulletVec, Sub mySub);
void fillMissileVec(vector<Missile*> &missileVec, Sub mySub);

int main()
{	
	
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

	//Texture bulletTexture;
	//if(!bulletTexture.loadFromFile("bullet.png")) return -1;

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
	vector<Bullet*> bulletVec;
	vector<Missile*> missileVec;
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
			if (state == gameState::game) {
				if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::J) {
					fillBulletVec(bulletVec, mySub);
				}
				if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::K) {
					fillMissileVec(missileVec, mySub);
				}
			}
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
			std::srand(1);
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
			mySub.update();

			window.clear(Color::Black);

			window.draw(mySub.getSprite());

			vector<sf::RectangleShape>::iterator itG = groundVec.begin();
			while (itG != groundVec.end()) {
				if (abs(itG->getPosition().x - mySub.getSprite().getPosition().x) <= 1200) {
					for (vector<Bullet*>::iterator it = bulletVec.begin(); it != bulletVec.end(); ++it) {
						if (itG->getGlobalBounds().intersects((*it)->getBulletSprite().getGlobalBounds())) {
							(*it)->setNoDraw();
						}
					}
					for (vector<Missile*>::iterator it = missileVec.begin(); it != missileVec.end(); ++it) {
						if (itG->getGlobalBounds().intersects((*it)->getMissileSprite().getGlobalBounds())) {
							(*it)->setNoDraw();
						}
					}
					if (itG->getGlobalBounds().intersects(mySub.getSprite().getGlobalBounds())) {
						// sub lose one life and move ship up to center
					}

				}
				if (itG->getPosition().x < mySub.getSprite().getPosition().x - 1200) {
					itG = groundVec.erase(itG);
				}
				else {
					//itBE->update();
					
					window.draw(*itG);
					itG++;
				}
			}


			vector<enemyShip>::iterator itE = enemyShipVec.begin();
			while (itE != enemyShipVec.end()) {
				if (abs(itE->getEShipPos().x - mySub.getSprite().getPosition().x) <= 1200) {
					// check collision with bullet and missile and if collide set nodraw
					for (vector<Bullet*>::iterator it = bulletVec.begin(); it != bulletVec.end(); ++it) {
						if (itE->get_eShipSprite().getGlobalBounds().intersects((*it)->getBulletSprite().getGlobalBounds())) {
							itE->setNoDraw();
							(*it)->setNoDraw();
							// add score for hitting enemy ship
						}
					}
					for (vector<Missile*>::iterator it = missileVec.begin(); it != missileVec.end(); ++it) {
						if (itE->get_eShipSprite().getGlobalBounds().intersects((*it)->getMissileSprite().getGlobalBounds())) {
							itE->setNoDraw();
							(*it)->setNoDraw();
							// add score for hitting enemy ship
						}
					}
					if (itE->get_eShipSprite().getGlobalBounds().intersects(mySub.getSprite().getGlobalBounds())) {
						// sub lose one life and move ship up to center
						itE->setNoDraw();
					}
				}
				if (itE->getNoDraw() == true) {
					itE = enemyShipVec.erase(itE);
				}
				else {
					if (itE->get_eShipSprite().getGlobalBounds().intersects(mySub.getSprite().getGlobalBounds())) {
						cout << "collide with small ship" << endl;
					}
					if (abs(itE->get_eShipSprite().getPosition().x - mySub.getSprite().getPosition().x) <= 200) {
						//cout << "true time to move up" << endl;
						int randnum = (rand() % 2);
						if (randnum == 0) {
							itE->setMoveUp();
						}
					}
					itE->update();
					window.draw(itE->get_eShipSprite());
					itE++;
				}
			}


			vector<bigEnemyShip>::iterator itBE = bigEnemyShipVec.begin();
			while (itBE != bigEnemyShipVec.end()) {
				if (abs(itBE->get_eBigShipSprite().getPosition().x - mySub.getSprite().getPosition().x) <= 1200) {
					// check collision with bullet and missile and if collide set nodraw
					for (vector<Bullet*>::iterator it = bulletVec.begin(); it != bulletVec.end(); ++it) {
						if (itBE->get_eBigShipSprite().getGlobalBounds().intersects((*it)->getBulletSprite().getGlobalBounds())) {
							itBE->setNoDraw();
							(*it)->setNoDraw();
							// add score for hitting enemy ship
						}
					}
					for (vector<Missile*>::iterator it = missileVec.begin(); it != missileVec.end(); ++it) {
						if (itBE->get_eBigShipSprite().getGlobalBounds().intersects((*it)->getMissileSprite().getGlobalBounds())) {
							itBE->setNoDraw();
							(*it)->setNoDraw();
							// add score for hitting enemy ship
						}
					}
					if (itBE->get_eBigShipSprite().getGlobalBounds().intersects(mySub.getSprite().getGlobalBounds())) {
						// sub lose one life and move ship up to center
						itBE->setNoDraw();
					}
				}

				if (itBE->getNoDraw() == true) {
					itBE = bigEnemyShipVec.erase(itBE);
				}
				else {
					//itBE->update();
					window.draw(itBE->get_eBigShipSprite());
					itBE++;
				}
			}


			vector<fuelTank>::iterator itF = fuelVec.begin();
			while (itF != fuelVec.end()) {
				if (abs(itF->getTankSprite().getPosition().x - mySub.getSprite().getPosition().x) <= 1200) {
					// check collision with bullet and missile and if collide set nodraw
					for (vector<Bullet*>::iterator it = bulletVec.begin(); it != bulletVec.end(); ++it) {
						if (itF->getTankSprite().getGlobalBounds().intersects((*it)->getBulletSprite().getGlobalBounds())) {
							itF->setNoDraw();
							(*it)->setNoDraw();
							// add score for hitting enemy ship
						}
					}
					for (vector<Missile*>::iterator it = missileVec.begin(); it != missileVec.end(); ++it) {
						if (itF->getTankSprite().getGlobalBounds().intersects((*it)->getMissileSprite().getGlobalBounds())) {
							itF->setNoDraw();
							(*it)->setNoDraw();
							// add score for hitting enemy ship
						}
					}
					if (itF->getTankSprite().getGlobalBounds().intersects(mySub.getSprite().getGlobalBounds())) {
						// sub lose one life and move ship up to center
						// ..... maybe ship add a life if meele gas tank?
						itF->setNoDraw();
					}
				}

				if (itF->getNoDraw() == true) {
					itF = fuelVec.erase(itF);
				}
				else {
					itF->update();
					// if collide wwith bullet set nodraw to true
					window.draw(itF->getTankSprite());
					itF++;
				}
			}

			vector<Bullet*>::iterator it = bulletVec.begin();
			while (it != bulletVec.end()) {
				if ((*it)->getNoDraw() == true) {
					delete *it;
					it = bulletVec.erase(it);
					
				}
				else {
					(*it)->update();
					if ((*it)->getBulletSprite().getPosition().x > mySub.getSprite().getPosition().x + 1200) {
						(*it)->setNoDraw();
					}
					window.draw((*it)->getBulletSprite());
					it++;
				}
			}

			vector<Missile*>::iterator itM = missileVec.begin();
			while (itM != missileVec.end()) {
				if ((*itM)->getNoDraw() == true) {
					delete *itM;
					itM = missileVec.erase(itM);

				}
				else {
					(*itM)->update();
					// nodraw is collide wtih ground
					window.draw((*itM)->getMissileSprite());
					itM++;
				}
			}

			cout << "bullet size " << bulletVec.size() << endl;	
			cout << "enemyship size " << enemyShipVec.size() << endl;
			cout << "ground size " << groundVec.size() << endl;
			cout << "missile size " << missileVec.size() << endl;
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
	std::srand(1);

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

	std::srand(1);

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

/*
Function to fill bulletList with bullet when we press J
*/
void fillBulletVec(vector<Bullet*> &bulletVec, Sub mySub) {
		float bulletPosX = mySub.getSprite().getPosition().x + 64;
		float bulletPosY = mySub.getSprite().getPosition().y + 20;
		Bullet* newBullet = new Bullet(bulletPosX, bulletPosY);
		bulletVec.push_back(newBullet);
}


/*
Function to fill missileVec with missile when we press K
*/
void fillMissileVec(vector<Missile*> &missileVec, Sub mySub) {
	float missilePosX = mySub.getSprite().getPosition().x + 32;
	float missilePosY = mySub.getSprite().getPosition().y + 30;
	Missile* newMissile = new Missile(missilePosX, missilePosY);
	missileVec.push_back(newMissile);
}
