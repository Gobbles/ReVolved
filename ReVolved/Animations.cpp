#include "Animations.h"

Animations::Animations()
{
	name = "";
	size = 64;
	for(int i = 0; i < size; i++)
	{
		keyFrames.push_back(KeyFrame());
	}
}

Animations::~Animations()
{
	keyFrames.clear();
}