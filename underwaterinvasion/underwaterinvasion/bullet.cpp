#include "stdafx.h"
#include "bullet.h"

Bullet::Bullet(float x, float y)
{
	bulletPosition.x = x;
	bulletPosition.y = y;

	bulletSprite.setRadius(5);
	bulletSprite.setFillColor(sf::Color::White);
	bulletSprite.setPosition(bulletPosition);
	
}

sf::FloatRect Bullet::getBulletCoord()
{
	return bulletSprite.getGlobalBounds();
}

sf::CircleShape Bullet::getBulletSprite()
{
	return bulletSprite;
}


void Bullet::setNoDraw()
{
	noDraw = true;
}

bool Bullet::getNoDraw()
{
	return noDraw;
}

void Bullet::moveRight()
{
	bulletPosition.x += moveRightSpd;
}

void Bullet::update()
{
	bulletPosition.x += moveRightSpd;

	bulletLifeTime += 1;
	if (bulletLifeTime > 40000) {
		noDraw = true;
	}

	bulletSprite.setPosition(bulletPosition);
}
