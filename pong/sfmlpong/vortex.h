#pragma once
#include <SFML/Graphics.hpp>


using namespace sf;

class Vortex {
	friend class Ball;
private:
	Vector2f vortexPosition;
	CircleShape vortexShape;
	float yVortexSpd = 0.3f;
	bool hitBot = false;
	bool hitTop = false;

public:
	Vortex(float x, float y);
	FloatRect getVortexCoord();
	CircleShape getVortexShape();
	Vector2f getVortexPos();

	void bounceTop();
	void bounceBot();

	bool getHitUp();
	bool getHitDown();

	void update();


};