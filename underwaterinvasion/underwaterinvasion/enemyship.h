#pragma once
#include <SFML\Graphics.hpp>

using namespace std;

class enemyShip {
private:
	sf::Vector2f eShipPosition;
	sf::Texture eShipTexture;
	sf::Sprite eShipSprite;
	float moveUpSpeed = 1.3f;
	bool moveUpVar = false;
	bool noDraw = false;


public:

	enemyShip(float x, float y);
	sf::FloatRect get_eShipCoord();
	sf::Sprite get_eShipSprite();

	sf::Vector2f getEShipPos();

	void setTexture(string fileloc);
	void setNoDraw();
	void moveUp();
	void setColor();
	void setMoveUp();
	bool getNoDraw();


	void update();

};