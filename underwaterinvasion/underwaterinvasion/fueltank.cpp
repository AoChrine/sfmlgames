#include "stdafx.h"
#include "fueltank.h"

fuelTank::fuelTank(float x, float y)
{
	tankPosition.x = x;
	tankPosition.y = y;

	tankSprite.setPosition(tankPosition);
}

sf::FloatRect fuelTank::getTankCoord()
{
	return tankSprite.getLocalBounds();
}

sf::Sprite fuelTank::getTankSprite()
{
	return tankSprite;
}

float fuelTank::getWidth()
{
	return width;
}

float fuelTank::getHeight()
{
	return height;
}

void fuelTank::setTexture(string fileloc)
{
	tankTexture.loadFromFile(fileloc);
	tankTexture.setSmooth(true);
	tankSprite.setTexture(tankTexture);
}

void fuelTank::setNoDraw()
{
	noDraw = true;
}

void fuelTank::setColor()
{
	tankSprite.setColor(sf::Color::Red);
}

void fuelTank::update()
{
}

void fuelTank::setRotation(float angle) {
	tankSprite.setRotation(angle);
}

void fuelTank::setPosition(float x, float y) {
	tankPosition.x = x;
	tankPosition.y = y;
	tankSprite.setPosition(tankPosition);
}

bool fuelTank::getNoDraw() {
	return noDraw;
}
