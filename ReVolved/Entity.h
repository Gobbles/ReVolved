#ifndef ENTITY_H
#define ENTITY_H
#include <memory>
#include "Map.h"
#include <SFML/Graphics.hpp>

enum Team
{
	TEAM_GOOD_GUYS = 0,
	TEAM_BAD_GUYS,
	TEAM_NEUTRAL
};
class EntityManager;
class Entity
{
private:
    //Entity ID
    int mId;

    void SetId(int id)
    {
        mId = id;
    }
	
public:
	//public members
	sf::Vector2f Location;
    sf::Vector2f Trajectory;
	float colMove;
	//which team we one, the good, the bad, or the ugly?
	Team team;
	//public functions
	Entity(int id)
    {
        SetId(id);
    }
	virtual ~Entity(){}
	virtual void Update(float time_passed, ParticleManager& pMan, Map& currentMap, EntityManager& entityManager) = 0;
	virtual void Draw(sf::RenderWindow& window) = 0;
	virtual sf::IntRect GetHitBounds() = 0;

    int ID()const { return mId; }
};

#endif