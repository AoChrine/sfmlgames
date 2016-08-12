#pragma once
#include <SFML\Graphics.hpp>

using namespace std;

class Bullet {
private:
	sf::Vector2f bulletPosition;
	sf::Sprite bulletSprite;
	sf::Texture bulletTexture;
	float moveRightSpd = 7.0f;
	float bulletLifeTime = 0.0f;
	bool noDraw = false;
public:

	Bullet(float x, float y);
	sf::FloatRect getBulletCoord();
	sf::Sprite getBulletSprite();
	void setNoDraw();
	bool getNoDraw();
	void moveRight();
	void update();
	void setTexture(sf::Texture texture);
}; 
