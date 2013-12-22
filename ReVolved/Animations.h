#include <vector>
#include "KeyFrame.h"

class Animations
{
public:
	//members
	std::string name;
	std::vector<KeyFrame> keyFrames;
	int size;

	//Functions
	Animations();
	~Animations();
};