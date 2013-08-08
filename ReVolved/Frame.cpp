#include "Frame.h"

Frame::Frame()
{
	size = 16;
	//parts = std::vector<std::shared_ptr<Part> >(size, NULL);
	for(int i = 0; i < size; i++)
	{
		parts.push_back(std::make_shared<Part>());
	}
	name = "";
}

Frame::~Frame()
{
	parts.clear();
}