#pragma once
#include <SFML\Graphics.hpp>

using namespace std;

class Sub {

private:
	sf::Vector2f subPosition;
	sf::Vector2f fuelBarPosition;
	sf::Texture spriteTexture;
	sf::Sprite subSprite;
	sf::RectangleShape fuelBar;
	float fuelCount = 400.0f;
	float subLifeCount = 3.0f;
	float subRailSpd = 0.5f;
	float subMoveSpd = 1.0f;
	
public:

	Sub(float x, float y);
	sf::FloatRect getSubCoord();
	sf::RectangleShape getFuelBar();
	sf::Sprite getSprite();
	float getSubRailSpd();
	float getSubMoveSpd();
	float getSubFuelCount();
	float getSubLifeCount();

	void changeFuelBarSize(float x, float y);
	void changeFuelBarPosition(float x, float y);
	void resetSubPos();
	void addFuel();
	void moveUp();
	void moveDown();
	void moveLeft();
	void moveRight();
	void decreaseLife();
	void resetLife();
	void increaseFuel();
	void setTexture(string fileloc);

	void update();

};