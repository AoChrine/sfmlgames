#include "stdafx.h"
#include "submarine.h"





Sub::Sub(float x, float y, sf::Texture subTexture)
{
	subPosition.x = x;
	subPosition.y = y;

	subSprite.setTexture(subTexture);
	subSprite.setPosition(subPosition);
}

sf::FloatRect Sub::getSubCoord()
{
	return subSprite.getGlobalBounds();
}

sf::Sprite Sub::getSprite()
{
	return subSprite;
}

float Sub::getSubRailSpd()
{
	return subRailSpd;
}

float Sub::getSubMoveSpd()
{
	return subMoveSpd;
}

float Sub::getSubFuelCount()
{
	return fuelCount;
}

float Sub::getSubLifeCount()
{
	return subLifeCount;
}

void Sub::moveUp()
{
	subPosition.y -= subMoveSpd;
}

void Sub::moveDown()
{
	subPosition.y += subMoveSpd;
}

void Sub::moveLeft()
{
	subPosition.x -= subMoveSpd;
}

void Sub::moveRight()
{
	subPosition.x += subMoveSpd;
}

void Sub::decreaseLife()
{
	subLifeCount--;
}

void Sub::resetLife()
{
	subLifeCount = 3.0f;
}

void Sub::increaseFuel()
{
	fuelCount += 100.0f;
}

void Sub::setTexture(string fileloc)
{
	spriteTexture.loadFromFile(fileloc);
	spriteTexture.setSmooth(true);
	subSprite.setTexture(spriteTexture);
}

void Sub::update()
{
	if (subPosition.y < 0) {
		subPosition.y += subMoveSpd;
	}

	if (subPosition.x < 0) {
		subPosition.x += subMoveSpd;
	}

	if (!sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		subPosition.x += subRailSpd;
	}

	subSprite.setPosition(subPosition);

}
