#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "ball.h"
#include "menu.h"
#include "paddle.h"
#include "vortex.h"
#include <sstream>
#include <cstdlib>
#include <stdlib.h>
#include <iostream>
#include <Windows.h>


using namespace sf;
using namespace std;



int main()
{
	float i = 0.0f;

	float windowWidth = 1000.0f;
	float windowHeight = 600.0f;

	
	RenderWindow window(VideoMode(int(windowWidth), int(windowHeight)), "Coolest Pong Game!");

	enum class gameState {game, mainMenu, restartMenu};
	gameState state = gameState::mainMenu;
	
	Menu mainMenu;
	mainMenu.setFont("font.ttf");
	Menu restartMenu;
	restartMenu.setFont("font.ttf");

	Paddle paddle1(0.0f, windowHeight / 2);
	Paddle paddle2(windowWidth-10, windowHeight / 2);

	Ball birdie(windowWidth / 2, windowHeight / 2);

	Vortex obs(windowWidth / 2, 20);

	int p1score = 0;
	int p2score = 0;

	String p1win = "Player 1 Wins!";
	String p2win = "Player 2 Wins!";

	Music mainsong;
	if (!mainsong.openFromFile("chill.wav")) return -1;
	mainsong.setLoop(true);
	mainsong.play();
	

	SoundBuffer bufferscore;
	if (!bufferscore.loadFromFile("met.wav")) return -1;
	Sound scoresound;
	scoresound.setBuffer(bufferscore);

	SoundBuffer bufferpaddle;
	if (!bufferpaddle.loadFromFile("jump.wav")) return -1;
	Sound crosssound;
	crosssound.setBuffer(bufferpaddle);


	Font font;
	
	font.loadFromFile("font.ttf");

	
	Text labels;

	labels.setFont(font);
	labels.setCharacterSize(30);
	labels.setColor(Color::Green);

	
	while (window.isOpen())
	{
		
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
			//if (Keyboard::isKeyPressed(Keyboard::Escape)) {
			//	window.close();
			//}
		}

		if (state == gameState::game) {
			if (Keyboard::isKeyPressed(Keyboard::Down)) {
				paddle2.moveDown();
			}

			if (Keyboard::isKeyPressed(Keyboard::Up)) {

				paddle2.moveUp();

			}

			if (Keyboard::isKeyPressed(Keyboard::S)) {

				paddle1.moveDown();

			}

			if (Keyboard::isKeyPressed(Keyboard::W)) {


				paddle1.moveUp();

			}

			if (Keyboard::isKeyPressed(Keyboard::Escape)) {
				window.close();
			}
		}
		else if (state == gameState::mainMenu) {
			if (mainMenu.getPlaySelected() == true && Keyboard::isKeyPressed(Keyboard::Space)) {
				state = gameState::game;
			}
			if (mainMenu.getPlaySelected() == false && Keyboard::isKeyPressed(Keyboard::Space)) {
				window.close();
			}
		}
		else if (state == gameState::restartMenu) {
			if (restartMenu.getRestartSelected() == true && Keyboard::isKeyPressed(Keyboard::Space)) {
				birdie.resetPosition();
				p1score = 0;
				p2score = 0;
				state = gameState::game;
			}
			if (restartMenu.getRestartSelected() == false && Keyboard::isKeyPressed(Keyboard::Space)) {
				window.close();
			}
		}

		if (birdie.crossLeft(birdie, Vector2f(0,0)) == true) {
			p2score++;
			scoresound.play();
			birdie.resetPosition();
			
		}

		if (birdie.crossRight(birdie, Vector2f(windowWidth, 0)) == true) {
			p1score++;
			scoresound.play();
			birdie.resetPosition();
		}

		if (birdie.getBallCoord().top < 0) {
			birdie.bounceTop();
		}

		if (birdie.getBallCoord().top > windowHeight - 20) {
			birdie.bounceBot();
		}

		if (paddle1.getPaddleCoord().intersects(birdie.getBallCoord())) {
			birdie.bounceLeftPaddle();
			crosssound.play();
		}

		if (paddle2.getPaddleCoord().intersects(birdie.getBallCoord())) {
			birdie.bounceRightPaddle();
			crosssound.play();

		}

		if (obs.getVortexCoord().top > (windowHeight - 30)) {
			obs.bounceBot();
		}

		if (obs.getVortexCoord().top < 0) {
			obs.bounceTop();
		}

		if (birdie.getBallCoord().intersects(obs.getVortexCoord()) && birdie.getShouldFollow() == false) {
			birdie.shouldFollowVortex(obs);
			crosssound.play();
		}

		if (birdie.checkFolTimer() > 1500) {
			birdie.SpinOff();
			scoresound.play();
		}
		
		if (state == gameState::game) {

			paddle1.update();
			paddle2.update();

			if (birdie.getShouldFollow() == true) {
				birdie.startTimer();
				if (obs.getHitUp() == true) {
					birdie.followVortexUp();
				}
				else if (obs.getHitDown() == true) {
					birdie.followVortexDown();
				}
			}
			else {
				birdie.update();
			}
			obs.update();
			if (p1score >= 10 || p2score >= 10) {
				if (p1score >= 10) restartMenu.setString(p1win);
				if (p2score >= 10) restartMenu.setString(p2win);
				state = gameState::restartMenu;
			}
		}
		else if (state == gameState::mainMenu) {
			mainMenu.update();
		}
		else if (state == gameState::restartMenu) {
			restartMenu.restartUpdate();
		}

		stringstream scorestring;

		scorestring << "          Player 1 Score:     " << p1score << "                         Player 2 Score:     " << p2score;
		labels.setString(scorestring.str());


		window.clear();
		if (state == gameState::game) {
			window.draw(labels);
			window.draw(paddle1.getPaddleShape());
			window.draw(paddle2.getPaddleShape());
			window.draw(birdie.getBallShape());
			window.draw(obs.getVortexShape());
		}
		else if (state == gameState::mainMenu) {
			window.draw(mainMenu.getMenuLabels());
			window.draw(mainMenu.getPlayButton());
			window.draw(mainMenu.getQuitButton());

		}
		else if (state == gameState::restartMenu) {
			window.draw(restartMenu.getRestartLabels());
			window.draw(restartMenu.getRestartButton());
			window.draw(restartMenu.getQuitButton());
		}

		//window.draw(labels);
		window.display();

		i++;
		//cout << birdie.checkFolTimer() << endl;
		//cout << paddle1.getPaddleCoord().top << endl;
		//cout << birdie.getBallCoord().top << endl;
		//cout << birdie.getBallXSpd() << endl;
		//cout << paddle1.getPaddleSpd() << endl;
		//cout << mainMenu.getPlaySelected() << endl;
		cout << restartMenu.getRestartSelected() << endl;
	}

	return 0;
}

