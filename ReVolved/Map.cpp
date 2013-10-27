#include "Map.h"

Map::Map(std::shared_ptr<GameCamera> camera)
{
	Camera = camera;
	//read in the map format
	ReadSegmentDefinitions();

	for( int i = 0; i < 16; i++)
	{
		ledge.push_back(std::make_shared<Ledge>());
	}
	for(int layer = 0; layer < 3; layer++)
	{
		mapSeg.push_back(std::vector<std::shared_ptr<MapSegment> >());
		for(int i = 0; i < 64; i++)
		{
			mapSeg[layer].push_back(std::shared_ptr<MapSegment>());
		}
	}
	for(int x = 0; x < 40; x++)
	{
		col.push_back(std::vector<int>());
		for(int y = 0; y < 20; y++)
		{
			col[x].push_back(-1);
		}
	}
}

void Map::Draw(std::shared_ptr<sf::RenderWindow> window, std::shared_ptr<sf::Texture> mapsTex,
			std::shared_ptr<sf::Texture> mapsBackTex, int startLayer, int endLayer)
{
	sf::IntRect sourceRect;
	sf::Vector2f destVec;

	if(startLayer == LAYER_BACK)
	{

		std::shared_ptr<sf::Sprite> backSprite(new sf::Sprite(*mapsBackTex));
		sf::Vector2f targ = sf::Vector2f(window->getView().getCenter() - window->getView().getSize() / 2.f);
		backSprite->setPosition(targ);

		window->draw(*backSprite);
	}

	for(int currentLayer = startLayer; currentLayer < endLayer; currentLayer++)
	{
		float scale = 1.0f;
		sf::Color color = sf::Color::White;
		if(currentLayer == 0)
		{
			color = sf::Color(190,190,190);
			scale = 0.75f;
		}
		else if(currentLayer == 2)
		{
			color = sf::Color(90,90,90);
			scale = 1.25f;
		}

		for(int i = 0; i < 64; i++)
		{
			if(mapSeg[currentLayer][i] != NULL)
			{
				std::shared_ptr<sf::Texture> tmp;

				sourceRect = segDef[mapSeg[currentLayer][i]->segmentIndex]->srcRect;

				tmp = mapsTex;
                                      
				std::shared_ptr<sf::Sprite> sprite(new sf::Sprite(*tmp,sourceRect));

				destVec.x = (int)(mapSeg[currentLayer][i]->Location.x /** 2.0f - (float)Camera->scroll.x*/ * scale);
				destVec.y = (int)(mapSeg[currentLayer][i]->Location.y /** 2.0f - (float)Camera->scroll.y*/ * scale);

				//mapsTex;//[segDef[mapSeg[currentLayer][i]->segmentIndex]->sourceIndex];
				sprite->setPosition(destVec);
				sprite->setScale(scale,scale);
				sprite->setColor(color);

				window->draw(*sprite);
			}
		}
	}
}

int Map::GetLedgeSec(int layer, float x)
{
	for (int i = 0; i < ledge[layer]->totalNodes - 1; i++)
	{
		if( x >= ledge[layer]->Nodes[i]->x &&
			x <= ledge[layer]->Nodes[i + 1]->x)
			return i;
	}
	return -1;
}

int Map::GetLedgeTotalNodes(int layer)
{
	return ledge[layer]->totalNodes;
}

int Map::GetLedgeFlags(int layer)
{
	return ledge[layer]->flags;
}

float Map::GetLedgeYLoc(int layer, int i, float x)
{
	return (ledge[layer]->Nodes[i + 1]->y - ledge[layer]->Nodes[i]->y) *
		((x - ledge[layer]->Nodes[i]->x) / (ledge[layer]->Nodes[i + 1]->x
		- ledge[layer]->Nodes[i]->x)) + ledge[layer]->Nodes[i]->y;
}

bool Map::CheckCol(sf::Vector2f loc)
{
	if(loc.x < 0.0f) return true;
	if(loc.y < 0.0f) return true;

	int x = (int)(loc.x / 32.0f);
	int y = (int)(loc.y / 32.0f);

	if(x >= 0 && y >= 0 && x < 40 && y < 20)
	{
		if(col[x][y] == 0) return false;
	}
  	return true;
}
bool Map::CheckParticleCol(sf::Vector2f loc)
{
	if(CheckCol(loc))
		return true;
	for(int i = 0; i < 16; i++)
	{
		if(ledge[i]->totalNodes > 1)
		{
			if(ledge[i]->flags == 1)
			{
				int s = GetLedgeSec(i, loc.x);

				if(s > -1)
					if(GetLedgeYLoc(i,s, loc.x) < loc.x)
						return true;
			}
		}
	}
	return false;
}
void Map::Update(ParticleManager& pMan)
{
	for(int i = 0; i < 64; i++)
	{
		if (mapSeg[1][i] != NULL)
		{
			if(segDef[mapSeg[1][i]->segmentIndex]->flags == Torch)
			{
				/*
				pMan.AddParticle(new Smoke(
                    mapSeg[1, i].Location * 2f + new Vector2(20f, 10f),
                    Rand.GetRandomVector2(-50.0f, 50.0f, -300.0f, -200.0f),
                    1.0f, 0.8f, 0.6f, 1.0f, Rand.GetRandomFloat(0.25f, 0.5f),
                    Rand.GetRandomInt(0, 4)), true);
                pMan.AddParticle(new Fire(
                    mapSeg[1, i].Location * 2f + new Vector2(20f, 20f),
                    Rand.GetRandomVector2(-30.0f, 30.0f, -250.0f, -200.0f),
                    Rand.GetRandomFloat(0.25f, 0.75f),
                    Rand.GetRandomInt(0, 4)), true);*/
				sf::Vector2f loc = mapSeg[1][i]->Location ;
				loc.x += 20.f;
				loc.y += 20.f;
				sf::Vector2f traj = GetRandomVector2(-30.f, 30.f, -250.f, -200.f);
				int icon = GetRandomFloat(0, 4);
                for(int i = 0; i < 10; i ++)
                {
                    loc.x += i * 20;
				    pMan.AddParticle(std::make_shared<Fire>(loc, traj,
					    GetRandomFloat(0.25f, 0.75f),
					    icon), true);
                }
			}
		}
	}
}

void Map::ReadSegmentDefinitions()
{
	std::string tmp;
	int n;
	int currentTex = 0;

	sf::IntRect tRect;
	std::ifstream myFile("mapFormat.txt");
	if(myFile.is_open())
	{
		std::getline(myFile, tmp);
		currentTex = atof(tmp.c_str());
		while(!myFile.eof())
		{
			std::string name;
			// get the name of the object
			std::getline(myFile, name);
			//grab all 4 rectangle positions and throw it into a IntRect
			//X
			std::getline(myFile, tmp);
			tRect.left = atof(tmp.c_str());
			//Y
			std::getline(myFile, tmp);
			tRect.top = atof(tmp.c_str());
			//Width
			std::getline(myFile, tmp);
			tRect.width = atof(tmp.c_str());
			tRect.width -= tRect.left;
			//Height
			std::getline(myFile, tmp);
			tRect.height = atof(tmp.c_str());
			tRect.height -= tRect.top;

			int flags;
			std::getline(myFile, tmp);
			flags = atof(tmp.c_str());

			segDef.push_back(std::make_shared<SegmentDefinition>(name, currentTex, tRect, flags));
		}
		myFile.close();
	}
}

void Map::Read()
{
	std::string tmp;
	std::ifstream myFile("map.txt");
	if(myFile.is_open())
	{
		for(int i = 0; i < ledge.size(); i++)
		{
			ledge[i] = std::make_shared<Ledge>();
			std::getline(myFile, tmp);
			ledge[i]->totalNodes = atof(tmp.c_str());
			for(int n = 0; n < ledge[i]->totalNodes; n++)
			{
				std::getline(myFile, tmp);
				float x = atof(tmp.c_str());
				std::getline(myFile, tmp);
				float y = atof(tmp.c_str());
				ledge[i]->Nodes.push_back(std::make_shared<sf::Vector2f>(x,y));
			}
			std::getline(myFile, tmp);
			ledge[i]->flags = atof(tmp.c_str());
		}
		for(int layer = 0; layer < 3; layer++)
		{
			for(int i = 0; i < 64; i++)
			{
				std::getline(myFile, tmp);
				int t = atof(tmp.c_str());
				if(t == -1)
					mapSeg[layer][i] = NULL;
				else
				{
					mapSeg[layer][i] = std::make_shared<MapSegment>();
					mapSeg[layer][i]->segmentIndex = t;
					std::getline(myFile, tmp);
					float x = atof(tmp.c_str());
					std::getline(myFile, tmp);
					float y = atof(tmp.c_str());
					mapSeg[layer][i]->Location = sf::Vector2f(x,y);
				}
			}
		}

		for(int x = 0; x < 40; x++)
		{
			for(int y = 0; y < 20; y++)
			{
				std::getline(myFile, tmp);
				col[x][y] = atof(tmp.c_str());
			}
		}
		myFile.close();
	}
}