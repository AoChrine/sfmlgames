#pragma once

#include "SFML\Graphics.hpp"
#include "vortex.h"

using namespace sf;
using namespace std;

class Ball {
private:
	Vector2f ballPosition;
	RectangleShape ballShape;
	float xBallSpd = 0.5f;
	float yBallSpd = 0.5f;
	float yFolSpd = 0.3f;
	float folTimer = 0.0f;
	bool shouldFollow = false;
	bool startCount = false;


public:
	Ball(float x, float y);
	FloatRect getBallCoord();
	RectangleShape getBallShape();
	Vector2f getBallPos();
	float getBallXSpd();
	float getBallYSpd();
	float checkFolTimer();

	void resetPosition();

	void bounceTop();
	void bounceBot();

	void bounceLeftPaddle();
	void bounceRightPaddle();

	void shouldFollowVortex(Vortex obs);
	void followVortexUp();
	void followVortexDown();
	void SpinOff();
	void startTimer();

	bool crossLeft(Ball ball, Vector2f wall);
	bool crossRight(Ball ball, Vector2f wall);
	bool getShouldFollow();
	bool getStartCount();

	void update();



};