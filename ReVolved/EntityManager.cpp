#include "EntityManager.h"
#include "Entity.h"

EntityManager::EntityManager()
{
	mEntities = std::vector<std::unique_ptr<Entity>>();

	charDef = std::unique_ptr<CharDef>(new CharDef("skeleton"));
	std::cout << "CharDef Loaded\n";

	character = std::unique_ptr<Character>(new Character(sf::Vector2f(500.f, 100.f), *charDef, 0));
	character->BodypartsInit();
	std::cout << "Character Loaded\n";

	enemy = std::unique_ptr<Enemy>(new Enemy(sf::Vector2f(800.f, 100.f), *charDef, 1));
	enemy->BodypartsInit();
	//mEntities.push_back(std::move(enemy));
	std::cout << "Enemy Loaded\n";
}

EntityManager::~EntityManager()
{
	//for(int i = mEntities.size()-1; i > 0; --i)
	//{
		//RemoveEntity(i);
	//}
}

void EntityManager::AddEntity(std::unique_ptr<Entity> entity)
{
	
}

void EntityManager::RemoveEntity(int index)
{
	mEntities.erase(mEntities.begin() + index);
}

void EntityManager::UpdateEntities(float timePassed, ParticleManager& pMan, Map& map)
{
	character->Update(timePassed, pMan, map);
	//enemy->Update(timePassed, pMan, map);
	for(int i = 0; i < mEntities.size(); i++)
	{
		mEntities[i]->Update(timePassed, pMan, map);
	}
}

void EntityManager::Draw(sf::RenderWindow& window)
{
	for(int i = 0; i < mEntities.size(); i++)
	{
		mEntities[i]->Draw(window);
	}
	//enemy->Draw(window);
	character->Draw(window);
}

void EntityManager::CheckMovementHit()
{
	for(int i = 0; i < mEntities.size(); i++)
	{
		if (character->Location.x > mEntities[i]->Location.x - 45.0f &&
		character->Location.x < mEntities[i]->Location.x + 45.0f &&
		character->Location.y > mEntities[i]->Location.y - 60.0f &&
		character->Location.y < mEntities[i]->Location.y + 5.0f)
		{
			float dif = (float)fabs(character->Location.x - mEntities[i]->Location.x);
			dif = 180.0f - dif;
			//dif *= 2.0f;
			if (character->Location.x < mEntities[i]->Location.x)
			{
				character->colMove = -dif;
				mEntities[i]->colMove = dif;
			}
			else
			{
				character->colMove = dif;
				mEntities[i]->colMove = -dif;
			}
		}
	}
}

void EntityManager::CheckInput(bool keysPressed[])
{
	character->Input(keysPressed);
}

sf::Vector2f EntityManager::GetCharacterLocation()
{
	return character->Location;
}