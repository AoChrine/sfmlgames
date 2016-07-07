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
	bool playSelected = false;
	bool restartSelected = false;
public:

	Menu();

	void setFont(String fontLocation);
	void setString(String TitleString);
	
	void getMenuTitle();
	void getRestartTitle();
	void getPlayButton();
	void getQuitButton();
	void getRestartButoon();

	bool getPlaySelected();
	bool getRestartSelected();

	void update();
	void restartUpdate();

};

