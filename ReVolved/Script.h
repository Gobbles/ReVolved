#ifndef SCRIPT_H
#define SCRIPT_H

#include "ScriptLine.h"
#include "ScriptEnums.h"
class Character;

class Script
{
private:
	std::shared_ptr<Character> character;

public:
	Script(std::shared_ptr<Character> _character);
	~Script();
	void DoScript(int animIdx, int KeyFrameIdx);
};

#endif