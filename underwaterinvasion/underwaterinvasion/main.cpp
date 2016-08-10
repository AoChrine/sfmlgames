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
#include <thread>

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
	mainMenu.setQuitButtonPos(700, 300);
	Menu restartMenu;
	restartMenu.setFont("font.ttf");

	/*
	Load music, font, texture
	*/
	Music mainsong;
	if (!mainsong.openFromFile("chill.wav")) cout << "error loading main song" << endl;
	mainsong.setLoop(true);
	mainsong.play();

	SoundBuffer bufferShoot;
	if (!bufferShoot.loadFromFile("met.wav")) cout << "error loading shoot song" << endl;
	Sound shootSound;
	shootSound.setBuffer(bufferShoot);

	SoundBuffer bufferHit;
	if (!bufferHit.loadFromFile("jump.wav")) cout << "error loading hit song" << endl;;
	Sound hitSound;
	hitSound.setBuffer(bufferHit);


	Texture backgroundTex;
	backgroundTex.loadFromFile("background.png");
	backgroundTex.setRepeated(true);

	Sprite background;
	background.setTexture(backgroundTex);
	background.setPosition(0, 0);

	Texture* groundTex = new sf::Texture;
	groundTex->loadFromFile("ground.png");
	
	
	Font font;
	font.loadFromFile("font.ttf");

	Text labels;
	labels.setFont(font);
	labels.setCharacterSize(30);
	labels.setColor(sf::Color::White);

	int score = 0;

	String dieString = "Aw! You died. You noob.";
	stringstream restartString;
	restartString << "Well done. You win with " << score << " points!";

	//Texture bulletTexture;
	//if(!bulletTexture.loadFromFile("bullet.png")) return -1;

	/*
	Init obj. for game
	*/

	Sub mySub(50, 100);
	mySub.setTexture("subsprite.png");

	CircleShape lifeONE(50, 50); lifeONE.setRadius(10); lifeONE.setFillColor(sf::Color::Red);
	CircleShape lifeTWO(80, 50); lifeTWO.setRadius(10); lifeTWO.setFillColor(sf::Color::Red);
	CircleShape lifeTHREE(110, 50); lifeTHREE.setRadius(10); lifeTHREE.setFillColor(sf::Color::Red);

	vector<sf::CircleShape> lifeVec;
	lifeVec.push_back(lifeONE);
	lifeVec.push_back(lifeTWO);
	lifeVec.push_back(lifeTHREE);

	vector<sf::RectangleShape> groundVec;
	fillGroundVector(groundVec);

	vector<enemyShip> enemyShipVec;
	vector<bigEnemyShip> bigEnemyShipVec;
	vector<fuelTank> fuelVec;
	vector<Bullet*> bulletVec;
	vector<Missile*> missileVec;
	fillObjectVec(groundVec, enemyShipVec, bigEnemyShipVec, fuelVec);

	for (vector<sf::RectangleShape>::iterator it = groundVec.begin(); it != groundVec.end(); ++it) {
		it->setTexture(groundTex, true);
		it->setFillColor(Color::Green);
	}

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

	std::srand(1);
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

		mySub.changeFuelBarPosition(position.x + (windowWidth / 2) - 200, position.y+ 50);
		background.setPosition(position.x, position.y);

		if (lifeVec.size() == 3) {
			lifeVec[0].setPosition(sf::Vector2f(position.x + 100, position.y + 50));
			lifeVec[1].setPosition(sf::Vector2f(position.x + 150, position.y + 50));
			lifeVec[2].setPosition(sf::Vector2f(position.x + 200, position.y + 50));
		}
		else if (lifeVec.size() == 2) {
			lifeVec[0].setPosition(sf::Vector2f(position.x + 100, position.y + 50));
			lifeVec[1].setPosition(sf::Vector2f(position.x + 150, position.y + 50));
		}
		else if (lifeVec.size() == 1) {
			lifeVec[0].setPosition(sf::Vector2f(position.x + 100, position.y + 50));
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
					shootSound.play();
				}
				if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::K) {
					fillMissileVec(missileVec, mySub);
					shootSound.play();
				}
			}
		}
		
		stringstream scoreString;
		scoreString << "Score: " << score;
		labels.setPosition(position.x + 1300, position.y + 50);
		labels.setString(scoreString.str());

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
			//cout << "menu title pos: " << mainMenu.getMenuTitle().getPosition().x << ", " << mainMenu.getMenuTitle().getPosition().y << endl;
			//cout << "view pos: " << position.x << ", " << position.y << endl;
		}
		if (state == gameState::game) {
			
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
			//cout << "sub pos is " << mySub.getSprite().getPosition().x << ", " << mySub.getSprite().getPosition().y << endl;

			window.clear(Color::Black);
			window.draw(background);

			for (vector<sf::CircleShape>::iterator it = lifeVec.begin(); it != lifeVec.end(); ++it) {
				window.draw(*it);
			}

			window.draw(mySub.getFuelBar());
			window.draw(labels);
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
						lifeVec.pop_back();
						mySub.resetSubPos();
						hitSound.play();
						//sleep(sf::seconds (1));
						

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
							score += 100;
							hitSound.play();
						}
					}
					for (vector<Missile*>::iterator it = missileVec.begin(); it != missileVec.end(); ++it) {
						if (itE->get_eShipSprite().getGlobalBounds().intersects((*it)->getMissileSprite().getGlobalBounds())) {
							itE->setNoDraw();
							(*it)->setNoDraw();
							// add score for hitting enemy ship
							score += 100;
							hitSound.play();
						}
					}
					if (itE->get_eShipSprite().getGlobalBounds().intersects(mySub.getSprite().getGlobalBounds())) {
						// sub lose one life and move ship up to center
						itE->setNoDraw();
						lifeVec.pop_back();
						mySub.resetSubPos();
						//sleep(sf::seconds(1));
						hitSound.play();
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
							score += 500;
							hitSound.play();
						}
					}
					for (vector<Missile*>::iterator it = missileVec.begin(); it != missileVec.end(); ++it) {
						if (itBE->get_eBigShipSprite().getGlobalBounds().intersects((*it)->getMissileSprite().getGlobalBounds())) {
							itBE->setNoDraw();
							(*it)->setNoDraw();
							// add score for hitting enemy ship
							score += 500;
							hitSound.play();
						}
					}
					if (itBE->get_eBigShipSprite().getGlobalBounds().intersects(mySub.getSprite().getGlobalBounds())) {
						// sub lose one life and move ship up to center
						itBE->setNoDraw();
						lifeVec.pop_back();
						mySub.resetSubPos();
						//sleep(sf::seconds(1));
						hitSound.play();
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
							mySub.addFuel();
							hitSound.play();
						}
					}
					for (vector<Missile*>::iterator it = missileVec.begin(); it != missileVec.end(); ++it) {
						if (itF->getTankSprite().getGlobalBounds().intersects((*it)->getMissileSprite().getGlobalBounds())) {
							itF->setNoDraw();
							(*it)->setNoDraw();
							mySub.addFuel();
							// add score for hitting fuel
							hitSound.play();
						}
					}
					if (itF->getTankSprite().getGlobalBounds().intersects(mySub.getSprite().getGlobalBounds())) {
						// sub lose one life and move ship up to center
						// ..... maybe ship add a life if meele gas tank?
						itF->setNoDraw();
						mySub.resetSubPos();
						hitSound.play();
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
			
			if (lifeVec.empty()) {
				restartMenu.setString(dieString);
				mySub.hardResetPos();
				state = gameState::restartMenu;
			}
			// win condition sub goes past visible map

		}
		if (state == gameState::restartMenu) {

			restartMenu.setQuitButtonPos(position.x + (windowWidth / 2) - 100, position.y + 300);
			restartMenu.setRestartButtonPos(position.x + (windowWidth / 2) - 100, position.y + 200);
			restartMenu.setRestartTitlePos(position.x + (windowWidth / 2) - 300, position.y + 50);
			
			if (restartMenu.getRestartSelected() == true && Keyboard::isKeyPressed(Keyboard::Space)) {
				mySub.hardResetPos();
				mySub.changeFuelBarPosition(400, 20);
				score = 0;
				for (vector<sf::CircleShape>::iterator it = lifeVec.begin(); it != lifeVec.end(); ++it) {
					lifeVec.pop_back();
				}
				lifeVec.push_back(lifeONE);
				lifeVec.push_back(lifeTWO);
				lifeVec.push_back(lifeTHREE);

				groundVec.clear();
				enemyShipVec.clear();
				bigEnemyShipVec.clear();
				fuelVec.clear();

				fillGroundVector(groundVec);
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

				state = gameState::game;
			}
			if(restartMenu.getRestartSelected() == false && Keyboard::isKeyPressed(Keyboard::Space)) {
				window.close();

			}
			
			restartMenu.restartUpdate();

			window.clear(Color::Black);
			window.draw(restartMenu.getRestartTitle());
			window.draw(restartMenu.getRestartButton());
			window.draw(restartMenu.getQuitButton());
			
			//cout << "restart title pos: " << restartMenu.getRestartTitle().getPosition().x << ", " << restartMenu.getRestartTitle().getPosition().y << endl;
			//cout << "pos: " << position.x << ", " << position.y << endl;
		}
		// put text stuff here

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
		groundrecttoadd.setSize(sf::Vector2f(128, 10));
		groundrecttoadd.setPosition(sf::Vector2f(groundpos.x, groundpos.y));
		groundrecttoadd.setFillColor(Color::Black);

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
