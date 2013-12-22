#include <SFML/Graphics.hpp>
#include "Animations.h"
#include "Frame.h"
#include <fstream>
#include <vector>

class CharDef
{
public:
	//members
	std::vector<Animations> animations;
	std::vector<Frame> frames;

	std::string Path;
	int headIndex;
	int torsoIndex;
	int legsIndex;
	int armIndex;

	//public prototypes
	CharDef(std::string path);
	~CharDef();
	void Read();
private:
	int animSize;
	int frameSize;
};