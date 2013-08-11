#ifndef COMMANDS_H
#define COMMANDS_H

#include <SFML\System\Vector2.hpp>
#include <random>
enum KeyPress
{
	KEY_UP = 0,
	KEY_DOWN,
	KEY_LEFT,
	KEY_RIGHT,
	KEY_ATTACK,
	KEY_SECONDARY,
	KEY_JUMP,
	KEY_COUNT
};

const double PI = 3.14159265;


static float RadToDeg(float Rad)
{
	return Rad / PI * 180;
}

static float GetRandomFloat(float fMin, float fMax)
{
	return (float)rand() * (fMax - fMin) + fMin;
}

static double GetRandomDouble(double dMin, double dMax)
{
	return rand() * (dMax - dMin) + dMin;
}

static sf::Vector2f GetRandomVector2(float xMin, float xMax, float yMin, float yMax)
{
	return sf::Vector2f(GetRandomFloat(xMin, xMax), GetRandomFloat(yMin, yMax));
}

static int GetRandomInt(int iMin, int iMax)
{
	return rand() % (iMax - iMin) + iMin + 1;
}

#endif