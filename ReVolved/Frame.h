#include <vector>
#include "Part.h"

class Frame
{
public:
	std::vector<Part> parts;
	std::string name;
	int size;

	Frame();
	~Frame();
};