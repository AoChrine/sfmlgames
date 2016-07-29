#pragma once
#include <SFML\Graphics.hpp>

using namespace std;

class fuelTank {
private:

	sf::Vector2f tankPosition;
	sf::Texture tankTexture;
	sf::Sprite tankSprite;
	float width = 32.0f;
	float height = 32.0f;
	bool noDraw = false;
public:

	fuelTank(float x, float y);
	sf::FloatRect getTankCoord();
	sf::Sprite getTankSprite();
	
	float getWidth();
	float getHeight();

	void setTexture(string fileloc);
	void setNoDraw();
	void setColor();
	void setRotation(float angle);
	void setPosition(float x, float y);
	

	void update();
};