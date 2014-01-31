#include "EntityManager.h"
#include "Entity.h"

EntityManager::EntityManager()
{
	mEntities = std::vector<std::unique_ptr<Entity>>();

	charDef = std::unique_ptr<CharDef>(new CharDef("skeleton"));
	std::cout << "CharDef Loaded\n";

	character = std::unique_ptr<Character>(new Character(sf::Vector2f(500.f, 100.f), *charDef, 0));
	std::cout << "Character Loaded\n";

	for(int i = 0; i < 5; ++i)
	{
		mEntities.emplace_back(new Enemy(sf::Vector2f(300*i + 100, 100.f), *charDef, 1));
	}

	std::cout << "Enemy Loaded\n";
}

EntityManager::~EntityManager()
{

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
	character->Update(timePassed, pMan, map, *this);
	//enemy->Update(timePassed, pMan, map);
	for(int i = 0; i < mEntities.size(); i++)
	{
		mEntities[i]->Update(timePassed, pMan, map, *this);
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
		for(int j = i+1; j < mEntities.size(); j++)
		{
			if(mEntities[i]->team == mEntities[j]->team)
				continue;
			if ( mEntities[i]->Location.x > mEntities[j]->Location.x - 45.0f &&
			 mEntities[i]->Location.x < mEntities[j]->Location.x + 45.0f &&
			 mEntities[i]->Location.y > mEntities[j]->Location.y - 60.0f &&
			 mEntities[i]->Location.y < mEntities[j]->Location.y + 5.0f)
			{
			float dif = (float)fabs( mEntities[i]->Location.x - mEntities[j]->Location.x);
			dif = 180.0f - dif;
			//dif *= 2.0f;
			if ( mEntities[i]->Location.x < mEntities[j]->Location.x)
			{
				 mEntities[i]->colMove = -dif;
				mEntities[j]->colMove = dif;
			}
			else
			{
				 mEntities[i]->colMove = dif;
				mEntities[j]->colMove = -dif;
			}
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

void EntityManager::Clear()
{
	
}

void EntityManager::CheckHit(sf::IntRect hitRect, Team team, int face)
{
	CharDir fFace = GetFaceFromTraj( sf::Vector2f(200.0f * (float)face - 100.0f, 0.0f));

	for(int i = 0; i < mEntities.size(); i++)
	{
		if(team != mEntities[i]->team)
		{
			bool hit = CheckHitBounds(mEntities[i]->GetHitBounds(), hitRect);
			if(hit)
			{
				//entity.Face = (fFace == Left) ? Right : Left;
				float tX = 1.0f;
				if(fFace == Left)
					tX = -1.0f;
				std::cout << "\nHit!\n";
				//entity.SetNewAnim("idle");
				//entity.SetNewAnim("hit");

				//if(entity.State == CharacterStates::Grounded)
				//	entity.SetSlide(-200.0f);
				//else
				//	entity.SetSlide(-50.0f);

				/*switch(particle.flag)
				{
					case 6://TRIG_HIT_DIAG_DOWN
						pMan.MakeBloodSplash(particle.location,
							sf::Vector2f(50.f * tX, 100.0f));
						break;
					case 5://TRIG_HIT_DIAG_DOWN
						pMan.MakeBloodSplash(particle.location,
							sf::Vector2f(-50.f * tX, -100.0f));
						break;
					case 3://TRIG_HIT_UP
						pMan.MakeBloodSplash(particle.location,
							sf::Vector2f(30.f * tX, -100.0f));
						break;
					case 4://TRIG_HIT_DOWN
						pMan.MakeBloodSplash(particle.location,
							sf::Vector2f(-50.f * tX, 100.0f));
						break;
					case 7://TRIG_HIT_UPPERCUT
						pMan.MakeBloodSplash(particle.location,
							sf::Vector2f(-50.f * tX, -150.0f));
						break;
					case 8://TRIG_HIT_SMACKDOWN
						pMan.MakeBloodSplash(particle.location,
							sf::Vector2f(-50.f * tX, 150.0f));
						break;
					case 9://TRIG_KICK
						pMan.MakeBloodSplash(particle.location,
							sf::Vector2f(300.f * tX, 0.0f));
						break;
				}*/
			}
		}
	}
}

CharDir EntityManager::GetFaceFromTraj(sf::Vector2f trajectory)
{
    return (trajectory.x <= 0) ? Left : Right;
}

bool EntityManager::CheckHitBounds(sf::IntRect target, sf::IntRect source)
{
	printf("target: %d, %d, %d, %d ",target.left, target.top, target.width, target.height);
	printf("source: %d, %d, %d, %d ",source.left, source.top, source.width, source.height);
	std::cout << "\n";
	if(target.intersects(source))
		return true;
	return false;
}