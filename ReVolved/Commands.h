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

float RadToDeg(float Rad);

float GetRandomFloat(float fMin, float fMax)
{
    return (float)rand() * (fMax - fMin) + fMin;
}

double GetRandomDouble(double dMin, double dMax)
{
    return rand() * (dMax - dMin) + dMin;
}

Vector2 GetRandomVector2(float xMin, float xMax, float yMin, float yMax)
{
    return sf::Vector2f(GetRandomFloat(xMin, xMax), GetRandomFloat(yMin, yMax));
}

int GetRandomInt(int iMin, int iMax)
{
    return rand() % (iMax - iMin) + iMin + 1;
}

#endif