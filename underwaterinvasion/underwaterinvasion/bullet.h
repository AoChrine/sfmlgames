#pragma once
#include <SFML\Graphics.hpp>

using namespace std;

class Bullet {
private:
	sf::Vector2f bulletPosition;
	sf::CircleShape bulletSprite;
	float moveRightSpd = 2.0f;
	float bulletLifeTime = 0.0f;
	bool noDraw = false;
public:

	Bullet(float x, float y);
	sf::FloatRect getBulletCoord();
	sf::CircleShape getBulletSprite();
	void setNoDraw();
	bool getNoDraw();
	void moveRight();
	void update();
}; 
