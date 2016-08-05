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

sf::Vector2f enemyShip::getEShipPos()
{
	return eShipPosition;
}

void enemyShip::setTexture(string fileloc)
{
	eShipTexture.loadFromFile(fileloc);
	eShipTexture.setSmooth(true);
	eShipSprite.setTexture(eShipTexture);
}

void enemyShip::update()
{
	if (eShipPosition.y < -35) {
		
		noDraw = true;
		moveUpVar = false;
	}

	if (moveUpVar) {
		
		eShipPosition.y -= moveUpSpeed;
	}

	eShipSprite.setPosition(eShipPosition);
}

void enemyShip::setNoDraw()
{
	noDraw = true;
}

bool enemyShip::getNoDraw() {
	return noDraw;
}

void enemyShip::moveUp()
{
	eShipPosition.y -= moveUpSpeed;

}

void enemyShip::setColor()
{
	eShipSprite.setColor(sf::Color::Red);
}

void enemyShip::setMoveUp()
{
	moveUpVar = true;
}
