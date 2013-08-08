#ifndef SCRIPTLINE_H
#define SCRIPTLINE_H

#include <sstream>  //for std::istringstream
#include <iterator> //for std::istream_iterator
#include <vector>   //for std::vector
#include <map>		//for std::map
#include "ScriptEnums.h"

enum StringValue
{
	SETANIM,
    GOTO,
	IFUPGOTO,
	IFDOWNGOTO,
	FLOAT,
	UNFLOAT,
	SLIDE,
	BACKUP,
	SETJUMP,
	JOYMOVE,
	CLEARKEYS,
	SETUPPERGOTO,
	SETLOWERGOTO,
	SETATKGOTO,
	SETANYGOTO,
	SETSECUPGOTO,
	SETSECDOWNGOTO
};

class ScriptLine
{
private:
	
public:
	Commands command;
	std::string sParam;
	int iParam;

	typedef std::map<std::string, StringValue> StringMap;
	static StringMap stringMap;
	static StringMap InitMap();

	ScriptLine(std::string line);
};

#endif