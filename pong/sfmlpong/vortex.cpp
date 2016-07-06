#include "vortex.h"


Vortex::Vortex(float x, float y) {
	vortexPosition.x = x;
	vortexPosition.y = y;

	vortexShape.setPosition(vortexPosition);
	vortexShape.setRadius(12);
	vortexShape.setOutlineThickness(3);
	vortexShape.setOutlineColor(Color::Cyan);
	vortexShape.setFillColor(Color::Transparent);
}



FloatRect Vortex::getVortexCoord() {
	return vortexShape.getGlobalBounds();
}

CircleShape Vortex::getVortexShape() {
	return vortexShape;
}

Vector2f Vortex::getVortexPos() {
	return vortexPosition;
}

void Vortex::bounceTop() {
	hitBot = false;
	hitTop = true;
	yVortexSpd *= -1;
}

void Vortex::bounceBot() {
	hitTop = false;
	hitBot = true;
	yVortexSpd *= -1;
}

bool Vortex::getHitUp() {
	return hitTop;
}

bool Vortex::getHitDown() {
	return hitBot;
}

void Vortex::update() {
	vortexPosition.y += yVortexSpd;
	vortexShape.setPosition(vortexPosition);
}