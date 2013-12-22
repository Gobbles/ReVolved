#include "ScriptLine.h"
#include <vector>

class KeyFrame
{
public:
	int FrameRef;
	int Duration;
	int size;

	std::vector<ScriptLine> scripts;

	KeyFrame();
	~KeyFrame();
};