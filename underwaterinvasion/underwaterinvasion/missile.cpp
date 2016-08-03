#include "stdafx.h"
#include "missile.h"

Missile::Missile(float x, float y)
{
	missilePosition.x = x;
	missilePosition.y = y;


	missileTexture.loadFromFile("bomb.png");
	missileSprite.setTexture(missileTexture);
	missileSprite.setPosition(missilePosition);
}

sf::FloatRect Missile::getMissileCoord()
{
	return missileSprite.getGlobalBounds();
}

sf::Sprite Missile::getMissileSprite()
{
	return missileSprite;
}

void Missile::setTexture(sf::Texture texture)
{
	missileSprite.setTexture(texture);
}


void Missile::setNoDraw()
{
	noDraw = true;
}

bool Missile::getNoDraw()
{
	return noDraw;
}

void Missile::moveDown()
{
	missilePosition.y += moveDownSpd;
}

void Missile::update()
{
	missilePosition.y += moveDownSpd;

	missilePosition.y += moveDownSpd;
	if (missilePosition.y > 800) {
		noDraw = true;
	}

	missileSprite.setPosition(missilePosition);
}
