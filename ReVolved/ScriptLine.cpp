#include "ScriptLine.h"

ScriptLine::ScriptLine(std::string line)
{
	std::istringstream ss(line);
	std::istream_iterator<std::string> begin(ss), end;

	std::vector<std::string> split(begin,end);
	if(split.size() > 1)
	{
		switch(ScriptLine::stringMap[split[0]])
		{
			case SETANIM:
				command = SetAnim;
				sParam = split[1];
				break;
			case GOTO:
				command = Goto;
				iParam = atoi(split[1].c_str());
				break;
			case IFUPGOTO:
				command = IfUpGoto;
				iParam = atoi(split[1].c_str());
				break;
			case IFDOWNGOTO:
				command = IfDownGoto;
				iParam = atoi(split[1].c_str());
				break;
			case FLOAT:
				command = Float;
				break;
			case UNFLOAT:
				command = UnFloat;
				break;
			case SLIDE:
				command = Slide;
				iParam = atoi(split[1].c_str());
				break;
			case BACKUP:
				command = Backup;
				iParam = atoi(split[1].c_str());
				break;
			case SETJUMP:
				command = SetJump;
				iParam = atoi(split[1].c_str());
				break;
			case JOYMOVE:
				command = JoyMove;
				break;
			case CLEARKEYS:
				command = ClearKeys;
				break;
			case SETUPPERGOTO:
				command = SetUpperGoto;
				iParam = atoi(split[1].c_str());
				break;
			case SETLOWERGOTO:
				command = SetLowerGoto;
				iParam = atoi(split[1].c_str());
				break;
			case SETATKGOTO:
				command = SetAtkGoto;
				iParam = atoi(split[1].c_str());
				break;
			case SETANYGOTO:
				command = SetAnyGoto;
				iParam = atoi(split[1].c_str());
				break;
			case SETSECUPGOTO:
				command = SetSecUpGoto;
				iParam = atoi(split[1].c_str());
				break;
			case SETSECDOWNGOTO:
				command = SetSecDownGoto;
				iParam = atoi(split[1].c_str());
				break;
		}
	}
}

ScriptLine::StringMap ScriptLine::InitMap()
{
	StringMap m;
	m["setanim"] = SETANIM;
	m["goto"] = GOTO;
	m["ifupgoto"] = IFUPGOTO;
	m["ifdowngoto"] = IFDOWNGOTO;
	m["float"] = FLOAT;
	m["unfloat"] = UNFLOAT;
	m["slide"] = SLIDE;
	m["backup"] = BACKUP;
	m["setjump"] = SETJUMP;
	m["joymove"] = JOYMOVE;
	m["clearkeys"] = CLEARKEYS;
	m["setuppergoto"] = SETUPPERGOTO;
	m["setlowegoto"] = SETLOWERGOTO;
	m["setatkgoto"] = SETATKGOTO;
	m["setanygoto"] = SETANYGOTO;
	m["setsecupgoto"] = SETSECUPGOTO;
	m["setsecdowngoto"] = SETSECDOWNGOTO;
	
	return m;
}

ScriptLine::StringMap ScriptLine::stringMap(ScriptLine::InitMap());