#pragma once

#include <SFML\Graphics.hpp>

using namespace sf;
using namespace std;

class Menu {
private:
	Font menuFont;
	Text menuTitle;
	Text restartTitle;
	Text playButton;
	Text quitButton;
	Text restartButton;
	bool playSelected = true;
	bool restartSelected = true;
	Vector2f quitButtonPos;
	Vector2f restartTitlePos;
	Vector2f restartButtonPos;
public:

	Menu();

	void setFont(String fontLocation);
	void setString(String TitleString);
	void setQuitButtonPos(float x, float y);
	void setRestartButtonPos(float x, float y);
	void setRestartTitlePos(float x, float y);
	
	Text getMenuTitle();
	Text getRestartTitle();
	Text getPlayButton();
	Text getQuitButton();
	Text getRestartButton();

	bool getPlaySelected();
	bool getRestartSelected();

	void update();
	void restartUpdate();

};

