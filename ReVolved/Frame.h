#include <vector>
#include "Part.h"

class Frame
{
public:
	std::vector<std::shared_ptr<Part> > parts;
	std::string name;
	int size;

	Frame();
	~Frame();
};