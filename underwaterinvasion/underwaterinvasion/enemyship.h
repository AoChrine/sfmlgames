#pragma once
#include <SFML\Graphics.hpp>

using namespace std;

class enemyShip {
private:
	sf::Vector2f eShipPosition;
	sf::Texture eShipTexture;
	sf::Sprite eShipSprite;
	float moveUpSpeed = 0.5f;
	bool noDraw = false;


public:

	enemyShip(float x, float y);
	sf::FloatRect get_eShipCoord();
	sf::Sprite get_eShipSprite();

	void setTexture(string fileloc);
	void setNoDraw();
	void moveUp();
	void setColor();

	void update();

};