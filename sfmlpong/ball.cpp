#include "ball.h"
#include <cmath>
#include <chrono>
#include <thread>


Ball::Ball(float x, float y) {
	ballPosition.x = x;
	ballPosition.y = y;

	ballShape.setSize(sf::Vector2f(15, 15));
	ballShape.setFillColor(Color::Green);
	ballShape.setPosition(ballPosition);

}

FloatRect Ball::getBallCoord() {
	return ballShape.getGlobalBounds();
}

RectangleShape Ball::getBallShape() {
	return ballShape;
}

Vector2f Ball::getBallPos() {
	return ballPosition;
}

float Ball::getBallXSpd() {
	return xBallSpd;
}

float Ball::getBallYSpd() {
	return yBallSpd;
}

float Ball::checkFolTimer() {
	return folTimer;
}

void Ball::resetPosition() {
	ballPosition.x = 500;
	ballPosition.y = 400;
	xBallSpd = 0.5f;
	
}

void Ball::bounceTop() {
	shouldFollow = false;
	yBallSpd *= -1.0f;
}

void Ball::bounceBot() {
	shouldFollow = false;
	yBallSpd *= -1.0f;	
}

void Ball::bounceLeftPaddle() {
	xBallSpd *= -1.0f;
	if (xBallSpd < 0) {
		xBallSpd -= 0.1f;
	}else{
		xBallSpd += 0.1f;
	}
}

void Ball::bounceRightPaddle() {
	xBallSpd *= -1.0f;
	if (xBallSpd < 0) {
		xBallSpd -= 0.1f;
	}
	else {
		xBallSpd += 0.1f;
	}
}

void Ball::shouldFollowVortex(Vortex obs) {
	ballPosition.x = obs.vortexPosition.x+4;
	ballPosition.y = obs.vortexPosition.y+4;
	shouldFollow = true;
	startCount = true;
}

void Ball::SpinOff() {
	folTimer = 0.0f;
	shouldFollow = false;
	xBallSpd *= 1.2f;
	ballPosition.x = float(rand() % 400 + 300);
	ballPosition.y = float(rand() % 400 + 200);
}

bool Ball::getShouldFollow() {
	return shouldFollow;
}

bool Ball::getStartCount() {
	return startCount;
}

bool Ball::crossLeft(Ball ball, Vector2f wall) {
	if (ball.ballPosition.x < wall.x) {
		return true;
	}else{
		return false;
	}
}

bool Ball::crossRight(Ball ball, Vector2f wall) {
	if (ball.ballPosition.x > wall.x) {
		return true;
	}else{
		return false;
	}
}

void Ball::followVortexUp() {
	ballPosition.y += yFolSpd;
	ballShape.setPosition(ballPosition);
}

void Ball::followVortexDown() {
	ballPosition.y -= yFolSpd;
	ballShape.setPosition(ballPosition);

}

void Ball::startTimer() {
	folTimer += 1;
}

void Ball::update() {

	if (xBallSpd > 1.1f) {
		if (ballPosition.x < 500) ballPosition.x = 12.0f;
		if (ballPosition.x > 500) ballPosition.x = 988.0f;
		xBallSpd = 1.1f;
	}
	ballPosition.x += xBallSpd;
	ballPosition.y += yBallSpd;
	ballShape.setPosition(ballPosition);
}
