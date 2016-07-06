#pragma once

#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;

class Menu {
private:
	Font menuFont;
	Text restartLabels;
	Text menuLabels;
	Text playButton;
	Text quitButton;
	Text restartButton;
	bool playSelected = true;
	bool restartSelected = true;

public:

	Menu();

	Text getRestartLabels();
	Text getMenuLabels();
	Text getPlayButton();
	Text getQuitButton();
	Text getRestartButton();

	void setFont(String fontloc);
	void setString(String winText);

	bool getPlaySelected();
	bool getRestartSelected();
	bool hitPlayButton();
	bool hitQuitButton();
	bool hitRestartButton();


	void update();
	void restartUpdate();

};