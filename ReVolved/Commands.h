#ifndef COMMANDS_H
#define COMMANDS_H

#include <SFML\System\Vector2.hpp>
#include <stdlib.h>
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

static double RadToDeg(float Rad)
{
	return Rad / PI * 180;
}

static float GetRandomFloat(float fMin, float fMax)
{
	float i = rand() / float(RAND_MAX);
	return i * (fMax - fMin) + fMin;
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

static double GetAngle(sf::Vector2f v1, sf::Vector2f v2)
{
	sf::Vector2f d = sf::Vector2f(v2.x - v1.x, v2.y - v1.y);
    if (d.x == 0.0f)
    {
        if (d.y < 0.0f)
            return PI * 0.5f;
        else if (d.y > 0.0f)
            return PI * 1.5f;
    }
    if (d.y == 0.0f)
    {
        if (d.x < 0.0f)
            return 0.0f;
        else if (d.x > 0.0f)
            return PI;
    }

    double a = (double)atan(abs(d.y) / abs(d.x));

    if ((d.x < 0.0f) || (d.y > 0.0f)) a = PI - a;
    if ((d.x < 0.0f) || (d.y < 0.0f)) a = PI + a;
    if ((d.x > 0.0f) || (d.y < 0.0f))
        a = PI * 2.0f - a;
    if (a < 0) a = a + PI * 2.0f;
    return a;
}

#endif