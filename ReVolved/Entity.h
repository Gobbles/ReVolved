#ifndef ENTITY_H
#define ENTITY_H
#include <memory>
#include "Map.h"
#include <SFML/Graphics.hpp>

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
	//public functions
	Entity(int id)
    {
        SetId(id);
    }
	virtual ~Entity(){}
	virtual void Update(float time_passed, ParticleManager& pMan, Map& currentMap) = 0;
	virtual void Draw(sf::RenderWindow& window) = 0;

    int ID()const { return mId; }
};

#endif