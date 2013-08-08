#include "ScriptLine.h"
#include <vector>

class KeyFrame
{
public:
	int FrameRef;
	int Duration;
	int size;

	std::vector<std::shared_ptr<ScriptLine> > scripts;

	KeyFrame();
	~KeyFrame();
};