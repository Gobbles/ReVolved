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
	std::shared_ptr<sf::Vector2f> Location;
	std::shared_ptr<sf::Vector2f> Trajectory;

	//public functions
	Entity(int id)
    {
        SetId(id);
    }

    int ID()const { return mId; }
};

#endif