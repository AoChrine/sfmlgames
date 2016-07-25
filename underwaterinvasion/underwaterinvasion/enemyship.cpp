#include "stdafx.h"
#include "enemyship.h"

enemyShip::enemyShip(float x, float y)
{

	eShipPosition.x = x;
	eShipPosition.y = y;

	eShipSprite.setPosition(eShipPosition);

}

sf::FloatRect enemyShip::get_eShipCoord()
{
	return eShipSprite.getGlobalBounds();
}

sf::Sprite enemyShip::get_eShipSprite()
{
	return eShipSprite;
}

void enemyShip::setTexture(string fileloc)
{
	eShipTexture.loadFromFile(fileloc);
	eShipTexture.setSmooth(true);
	eShipSprite.setTexture(eShipTexture);
}

void enemyShip::update()
{
	if (eShipPosition.y < 0) {
		noDraw = true;
	}

	eShipSprite.setPosition(eShipPosition);
}

void enemyShip::setNoDraw()
{
	noDraw = true;
}

void enemyShip::moveUp()
{
	eShipPosition.y -= moveUpSpeed;
}

void enemyShip::setColor()
{
	eShipSprite.setColor(sf::Color::Red);
}
