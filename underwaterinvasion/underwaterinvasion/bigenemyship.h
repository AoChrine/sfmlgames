#pragma once
#include <SFML\Graphics.hpp>
using namespace std;

class bigEnemyShip {
private:

	sf::Vector2f eBigShipPosition;
	sf::Texture eBigShipTexture;
	sf::Sprite eBigShipSprite;
	bool noDraw = false;
public:

	bigEnemyShip(float x, float y);
	sf::FloatRect get_eBigShipCoord();
	sf::Sprite get_eBigShipSprite();

	void setTexture(string fileloc);
	void setNoDraw();
	void setColor();
	bool getNoDraw();

	void update();
};