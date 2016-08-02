#include "stdafx.h"
#include "bigenemyship.h"

bigEnemyShip::bigEnemyShip(float x, float y)
{
	eBigShipPosition.x = x;
	eBigShipPosition.y = y;

	eBigShipSprite.setPosition(eBigShipPosition);

}

sf::FloatRect bigEnemyShip::get_eBigShipCoord()
{
	return eBigShipSprite.getGlobalBounds();
}

sf::Sprite bigEnemyShip::get_eBigShipSprite()
{
	return eBigShipSprite;
}

void bigEnemyShip::setTexture(string fileloc)
{
	eBigShipTexture.loadFromFile(fileloc);
	eBigShipTexture.setSmooth(true);
	eBigShipSprite.setTexture(eBigShipTexture);
}

void bigEnemyShip::setNoDraw()
{
	noDraw = true;
}

void bigEnemyShip::setColor()
{
	eBigShipSprite.setColor(sf::Color::Red);
}

bool bigEnemyShip::getNoDraw()
{
	return noDraw;
}

void bigEnemyShip::update()
{

}
