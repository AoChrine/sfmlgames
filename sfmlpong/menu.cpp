#include "menu.h"

Menu::Menu() {

	menuLabels.setPosition(Vector2f(350, 50));
	menuLabels.setCharacterSize(50);
	menuLabels.setColor(Color::White);
	menuLabels.setString("PONG GAME");

	restartLabels.setPosition(Vector2f(350, 100));
	restartLabels.setCharacterSize(40);
	restartLabels.setColor(Color::Red);
	//restartLabels.setString("Player 1 Wins!");

	playButton.setPosition(Vector2f(460, 200));
	playButton.setCharacterSize(35);
	playButton.setColor(Color::Yellow);
	playButton.setString("Play");

	quitButton.setPosition(Vector2f(460, 300));
	quitButton.setCharacterSize(35);
	quitButton.setColor(Color::White);
	quitButton.setString("Quit");

	restartButton.setPosition(Vector2f(440, 250));
	restartButton.setCharacterSize(35);
	restartButton.setColor(Color::Yellow);
	restartButton.setString("Restart");



}

Text Menu::getRestartLabels() {
	return restartLabels;
}

Text Menu::getMenuLabels() {
	return menuLabels;
}

Text Menu::getPlayButton() {
	return playButton;
}

Text Menu::getQuitButton() {
	return quitButton;
}

Text Menu::getRestartButton() {
	return restartButton;
}

bool Menu::getPlaySelected() {
	return playSelected;
}

bool Menu::getRestartSelected() {
	return restartSelected;
}

bool Menu::hitPlayButton() {
	return true;
}

bool Menu::hitQuitButton() {
	return true;
}

bool Menu::hitRestartButton() {
	return true;
}

void Menu::setFont(String fileloc) {
	menuFont.loadFromFile(fileloc);
	menuLabels.setFont(menuFont);
	playButton.setFont(menuFont);
	quitButton.setFont(menuFont);
	restartButton.setFont(menuFont);
	restartLabels.setFont(menuFont);
}

void Menu::setString(String winText) {
	restartLabels.setString(winText);
}

void Menu::update() {
	if (playSelected == true && Keyboard::isKeyPressed(Keyboard::Down)) {
		playSelected = false;
		quitButton.setColor(Color::Yellow);
		playButton.setColor(Color::White);
	}

	if (playSelected == false && Keyboard::isKeyPressed(Keyboard::Up)) {
		playSelected = true;
		playButton.setColor(Color::Yellow);
		quitButton.setColor(Color::White);
	}
}

void Menu::restartUpdate() {
	if (restartSelected == true && Keyboard::isKeyPressed(Keyboard::Down)) {
		restartSelected = false;
		restartButton.setColor(Color::White);
		quitButton.setColor(Color::Yellow);
	}

	if (restartSelected == false && Keyboard::isKeyPressed(Keyboard::Up)) {
		restartSelected = true;
		restartButton.setColor(Color::Yellow);
		quitButton.setColor(Color::White);
	}

}