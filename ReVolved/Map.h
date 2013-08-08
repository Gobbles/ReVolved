#ifndef MAP_H
#define MAP_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <fstream>
#include "Ledge.h"
#include "MapSegment.h"
#include "GameCamera.h"
#include "ParticleManager.h"

enum SegmentFlags
{
	None = 0,
	Torch
};

class Map
{
public:
	Map(std::shared_ptr<GameCamera> camera);
	const static int LAYER_BACK = 0;

	void Draw(std::shared_ptr<sf::RenderWindow> window, std::shared_ptr<sf::Texture> mapsTex,
			std::shared_ptr<sf::Texture> mapsBackTex, int startLayer, int endLayer);
	int GetLedgeSec(int layer, float x);
	int GetLedgeTotalNodes(int layer);
	int GetLedgeFlags(int layer);
	float GetLedgeYLoc(int layer, int i, float x);
	bool CheckCol(sf::Vector2f loc);
	bool CheckParticleCol(sf::Vector2f loc);
	void Update(/*std::shared_ptr<ParticleManager> pMan*/);

	void Read();

private:
	//map segments and information
	std::vector<std::shared_ptr<SegmentDefinition> > segDef;
	std::vector<std::shared_ptr<Ledge> > ledge;
	std::vector<std::vector<std::shared_ptr<MapSegment> > > mapSeg;

	std::vector<std::vector<int> > col;

	//file path
	std::string path;

	//camera
	std::shared_ptr<GameCamera> Camera;
	void ReadSegmentDefinitions();

};

#endif