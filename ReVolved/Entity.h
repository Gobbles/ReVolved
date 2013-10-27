#ifndef ENTITY_H
#define ENTITY_H
#include <memory>
#include <SFML\Graphics\Transform.hpp>

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

	//public functions
	Entity(int id)
    {
        SetId(id);
    }

    int ID()const { return mId; }
};

#endif