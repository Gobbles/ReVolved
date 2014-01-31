#ifndef _SIDESCROLLENT_H
#define _SIDESCROLLENT_H

#include "Entity.h"
#include "CharDef.h"
#include "BodyParts.h"
#include "ParticleManager.h"
#include "Commands.h"
#include "ScriptEnums.h"
#include "TextureHolder.h"
#include <iostream>

//enum for the states the entities can enter
namespace CharacterStates
{
	enum CharState
	{
		Grounded = 0,	//character is currently on the ground
		Air				//character is in the air either jumping or falling
	};
}
//enum for the direction the character is facing
enum CharDir
{
	Left = 0,
	Right
};

//different types of hits possible by the character
enum Triggers
{
	TRIG_SHOOT_ACROSS = 0,
    TRIG_SHOOT_UP,
	TRIG_SHOOT_DOWN,
    TRIG_HIT_UP,
    TRIG_HIT_DOWN,
    TRIG_HIT_DIAG_UP,
    TRIG_HIT_DIAG_DOWN,
    TRIG_HIT_UPPERCUT,
    TRIG_HIT_SMACKDOWN,
    TRIG_KICK
};

class EntityManager;

class SideScrollEnt : public Entity
 {
 protected:
     //protected members
	CharDef& charDef;

	std::vector<BodyParts> CharacterBodyParts;
	std::vector<sf::Sprite> CharacterBodySprites;

	//int array for the key press combo system
	std::vector<int> GoToGoal;

	//textures
	TextureHolder textures;

	float Scale;
	float speed;
	float jumpHeight;
	float frame;

	int AnimFrame;
	int Anim;

	bool floating;
	bool fire;
	
	int ledgeAttach;

	//protected virtual functions
	virtual void FallOff();
	virtual void Land();
	virtual void CheckXCol(Map& map, sf::Vector2f& pLoc);
	virtual void CheckTrig(ParticleManager& pMan, EntityManager& entityManager);
	virtual void FireTrig(int trig, sf::Vector2f loc, ParticleManager& pMan, EntityManager& entityManager);

 public:
     //animation constants
	std::string ANIMATION_IDLE;
    std::string ANIMATION_RUN;
    std::string ANIMATION_JUMP;
    std::string ANIMATION_FLY;
    std::string ANIMATION_ATTACK;
    std::string ANIMATION_SECODNARY;
    std::string ANIMATION_JHIT;
    std::string ANIMATION_JMID;
    std::string ANIMATION_JFALL;
    std::string ANIMATION_HITLAND;	

	//collision movement amount
	//float colMove;

	CharDir Face;
	CharacterStates::CharState State;

	std::string animName;

	sf::RectangleShape rectangle;

    //ctor
    SideScrollEnt(int id, CharDef& newCharDef);
	virtual ~SideScrollEnt(){}
    //virtuals
	virtual void Update(float time_passed, Map& currentMap, EntityManager& entityManager);
	virtual void SetNewJump(float jump);
	virtual void SetSlide(float dinstance);
	virtual void Draw(sf::RenderWindow& window);
	virtual void BodypartsInit();
	virtual void SetBodyPart(sf::IntRect rect, BodyPart::BodyPartTypes type);
	virtual void SetNewAnim(std::string newAnim);
	virtual void DoScript(int animIdx, int KeyFrameIdx){}
	virtual sf::IntRect GetHitBounds();
 };

#endif