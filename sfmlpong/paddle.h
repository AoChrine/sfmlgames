#pragma once
#include "SFML\Graphics.hpp"

using namespace sf;

class Paddle {

private:

	Vector2f paddlePosition;
	RectangleShape paddleShape;
	float paddleSpd = 0.8f;

public:

	Paddle(float x, float y);

	FloatRect getPaddleCoord();

	RectangleShape getPaddleShape();

	float getPaddleSpd();

	void moveUp();

	void moveDown();


	void update();



};