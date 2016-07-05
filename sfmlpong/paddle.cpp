#include "paddle.h"


Paddle::Paddle(float x, float y) {
	paddlePosition.x = x;
	paddlePosition.y = y;

	paddleShape.setSize(sf::Vector2f(10,80));
	paddleShape.setPosition(paddlePosition);
}

FloatRect Paddle::getPaddleCoord() {
	return paddleShape.getGlobalBounds();
}

RectangleShape Paddle::getPaddleShape() {
	return paddleShape;
}

float Paddle::getPaddleSpd() {
	return paddleSpd;
}

void Paddle::moveUp() {
	paddlePosition.y -= paddleSpd;
}

void Paddle::moveDown() {
	paddlePosition.y += paddleSpd;
}


void Paddle::update() {
	if (paddlePosition.y < 0) {
		paddlePosition.y += paddleSpd;
	}

	if (paddlePosition.y + paddleShape.getGlobalBounds().height > 600) {
		paddlePosition.y -= paddleSpd;
	}
	paddleShape.setPosition(paddlePosition);
}
