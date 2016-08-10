#include "stdafx.h"
#include "menu.h"

Menu::Menu() {
	
	menuTitle.setPosition(Vector2f(600, 50));
	menuTitle.setCharacterSize(50);
	menuTitle.setColor(Color::Cyan);
	menuTitle.setString("ScRaMbLe!");

	//restartTitle.setPosition(Vector2f(350, 100));
	restartTitle.setCharacterSize(40);
	restartTitle.setColor(Color::Red);

	playButton.setPosition(Vector2f(700, 200));
	playButton.setCharacterSize(35);
	playButton.setColor(Color::Yellow);
	playButton.setString("Play");

	//quitButton.setPosition(Vector2f(550, 300));
	quitButton.setCharacterSize(35);
	quitButton.setColor(Color::White);
	quitButton.setString("Quit");

	//restartButton.setPosition(Vector2f(550, 250));
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

void Menu::setQuitButtonPos(float x, float y)
{
	quitButtonPos.x = x;
	quitButtonPos.y = y;
}

void Menu::setRestartButtonPos(float x, float y)
{
	restartButtonPos.x = x;
	restartButtonPos.y = y;
}

void Menu::setRestartTitlePos(float x, float y)
{
	restartTitlePos.x = x;
	restartTitlePos.y = y;
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
	quitButton.setPosition(quitButtonPos.x, quitButtonPos.y);
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
	quitButton.setPosition(quitButtonPos.x, quitButtonPos.y);
	restartTitle.setPosition(restartTitlePos.x, restartTitlePos.y);
	restartButton.setPosition(restartButtonPos.x, restartButtonPos.y);

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