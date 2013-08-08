#include "KeyFrame.h"

KeyFrame::KeyFrame()
{
	FrameRef = 0;
	Duration = 0;
	size = 4;
	//scripts = std::vector<std::shared_ptr<ScriptLine> >(4, NULL);
	for(int i = 0; i < size; i++)
	{
		scripts.push_back(std::make_shared<ScriptLine>(""));
	}
}

KeyFrame::~KeyFrame()
{
	scripts.clear();
}