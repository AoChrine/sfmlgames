#include "stdafx.h"
#include "menu.h"

Menu::Menu() {
	
	menuTitle.setPosition(Vector2f(400, 50));
	menuTitle.setCharacterSize(50);
	menuTitle.setColor(Color::Cyan);
	menuTitle.setString("OCEAN INVADER!");

	restartTitle.setPosition(Vector2f(350, 100));
	restartTitle.setCharacterSize(40);
	restartTitle.setColor(Color::Red);

	playButton.setPosition(Vector2f(550, 200));
	playButton.setCharacterSize(35);
	playButton.setColor(Color::Yellow);
	playButton.setString("Play");

	quitButton.setPosition(Vector2f(550, 300));
	quitButton.setCharacterSize(35);
	quitButton.setColor(Color::White);
	quitButton.setString("Quit");

	restartButton.setPosition(Vector2f(550, 250));
	restartButton.setCharacterSize(35);
	restartButton.setColor(Color::Yellow);
	restartButton.setString("Restart");

}

void Menu::setFont(String fileloc) {
	menuFont.loadFromFile(fileloc);
	menuTitle.setFont(menuFont);
	playButton.setFont(menuFont);
	quitButton.setFont(menuFont);
	restartButton.setFont(menuFont);
	restartTitle.setFont(menuFont);
}

void Menu::setString(String winText) {
	restartTitle.setString(winText);
}

Text Menu::getMenuTitle() {
	return menuTitle;
}

Text Menu::getRestartTitle() {
	return restartTitle;
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