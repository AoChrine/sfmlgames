#include "stdafx.h"
#include "bullet.h"

Bullet::Bullet(float x, float y)
{
	bulletPosition.x = x;
	bulletPosition.y = y;

	bulletTexture.loadFromFile("bullet.png");
	bulletSprite.setTexture(bulletTexture);
	bulletSprite.setPosition(bulletPosition);
}

sf::FloatRect Bullet::getBulletCoord()
{
	return bulletSprite.getGlobalBounds();
}

sf::Sprite Bullet::getBulletSprite()
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
	if (bulletLifeTime > 30000) {
		noDraw = true;
	}

	bulletSprite.setPosition(bulletPosition);
}

void Bullet::setTexture(sf::Texture texture)
{
	bulletSprite.setTexture(texture);
}
