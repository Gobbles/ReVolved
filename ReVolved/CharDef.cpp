#include "CharDef.h"

//Constructor
CharDef::CharDef(std::string path)
{
	//increase this value to increase the number of animations to store
	animSize = 64;
	//increase this value to increase the number of frames
	frameSize = 512; // 512
	
	for(int i = 0; i < animSize; i++)
	{
		animations.push_back(Animations());
	}
	
	for(int i = 0; i < frameSize; i++)
	{
		frames.push_back(Frame());
	}

	Path = path;
	Read();
}

//Destructor
CharDef::~CharDef()
{	
}

//read the character definition for our character
void CharDef::Read()
{ 
	std::string tmp;
	std::ifstream myFile("skeleton.txt");
	if(myFile.is_open())
	{
		std::getline(myFile, Path);

		std::getline(myFile, tmp);
		headIndex = atof(tmp.c_str());

		std::getline(myFile, tmp);
		torsoIndex = atof(tmp.c_str());

		std::getline(myFile, tmp);
		legsIndex = atof(tmp.c_str());

		std::getline(myFile, tmp);
		armIndex = atof(tmp.c_str());
		
		for(int i = 0; i < animations.size(); i++)
		{
			std::getline(myFile, animations[i].name);

			for(int j = 0; j < animations[i].keyFrames.size(); j++)
			{
				KeyFrame& keyframe = animations[i].keyFrames[j];

				std::getline(myFile, tmp);
				keyframe.FrameRef = atof(tmp.c_str());

				std::getline(myFile, tmp);
				keyframe.Duration = atof(tmp.c_str());

				std::vector<ScriptLine> script = keyframe.scripts;
				for(int s = 0; s < script.size(); s++)
				{
					std::string line;

					std::getline(myFile, line);

					animations[i].keyFrames[j].scripts[s] = ScriptLine(line);
				}
			}
		}
			
		for(int i = 0; i < frames.size(); i++)
		{
			std::getline(myFile, frames[i].name);

			for(int j = 0; j < frames[i].parts.size(); j++)
			{
				Part& p = frames[i].parts[j];

				std::getline(myFile, tmp);
				p.Index = atof(tmp.c_str());

				std::getline(myFile, tmp);
				p.Location.x = atof(tmp.c_str());

				std::getline(myFile, tmp);
				p.Location.y = atof(tmp.c_str());

				std::getline(myFile, tmp);
				p.Rotation = atof(tmp.c_str());

				std::getline(myFile, tmp);
				p.Scaling.x = atof(tmp.c_str());

				std::getline(myFile, tmp);
				p.Scaling.y = atof(tmp.c_str());

				std::getline(myFile, tmp);
				p.Flip = atof(tmp.c_str());
			}
		}

		myFile.close();	
	}
}