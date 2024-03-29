#ifndef ENTITY_MANAGER
#define ENTITY_MANAGER

//temp
#include <iostream>
//endtemp
#include <vector>
#include <memory>
#include <SFML\Graphics\RenderWindow.hpp>
#include "Map.h"
#include "ParticleManager.h"
#include "Character.h"
#include "Enemy.h"

class Entity;

class EntityManager
{
public:
	EntityManager();
	~EntityManager();
	void AddEntity(std::unique_ptr<Entity> entity);
	void RemoveEntity(int index);
	void UpdateEntities(float timePassed, ParticleManager& pMan, Map& map);
	void Draw(sf::RenderWindow& window);
	void CheckMovementHit();
	void CheckInput(bool keysPressed[]);
	void Clear();
	void CheckHit(sf::IntRect hitRect, Team team, int face);
	
	CharDir GetFaceFromTraj(sf::Vector2f trajectory);
	sf::Vector2f GetCharacterLocation();
	
private:
	std::vector<std::unique_ptr<Entity>> mEntities;

	//all entities non-character
	std::unique_ptr<CharDef> charDef;

	//character Information
	std::unique_ptr<Character> character;

	bool CheckHitBounds(sf::IntRect target, sf::IntRect source);
};

#endif