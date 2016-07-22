#pragma once
#include <SFML\Graphics.hpp>

using namespace std;

class Sub {

private:
	sf::Vector2f subPosition;
	sf::Texture spriteTexture;
	sf::Sprite subSprite;
	sf::RectangleShape fuelOutline;
	sf::RectangleShape fuelBar;
	float fuelCount = 1000.0f;
	float subLifeCount = 3.0f;
	float subRailSpd = 0.5f;
	float subMoveSpd = 1.0f;
	
public:

	Sub(float x, float y, sf::Texture subTexture);
	sf::FloatRect getSubCoord();
	sf::Sprite getSprite();
	float getSubRailSpd();
	float getSubMoveSpd();
	float getSubFuelCount();
	float getSubLifeCount();

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