#pragma once
#include <SFML\Graphics.hpp>

using namespace std;

class Missile {
private:
	sf::Vector2f missilePosition;
	sf::Sprite missileSprite;
	sf::Texture missileTexture;
	float moveDownSpd = 1.0f;
	bool noDraw = false;
public:

	Missile(float x, float y);
	sf::FloatRect getMissileCoord();
	sf::Sprite getMissileSprite();
	void setTexture(string fileloc);
	void setNoDraw();
	bool getNoDraw();
	void moveDown();
	void update();


};