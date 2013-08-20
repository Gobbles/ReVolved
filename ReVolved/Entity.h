#ifndef ENTITY_H
#define ENTITY_H
#include <memory>
#include <SFML\Graphics\Transform.hpp>
#include "CharDef.h"
#include "BodyParts.h"
#include "Commands.h"
#include "ScriptEnums.h"
#include "Map.h"
//enum for the states the entities can enter
enum CharState
{
	Grounded = 0,	//character is currently on the ground
	Air				//character is in the air either jumping or falling
};

//enum for the direction the character is facing
enum CharDir
{
	Left = 0,
	Right
};

class Entity
{
protected:
	//protected members
	std::shared_ptr<CharDef> charDef;
	CharDir Face;
	CharState State;
	
	std::shared_ptr<ParticleManager> pManager;
	std::vector<std::shared_ptr<BodyParts> > CharacterBodyParts;

	//int array for the key press combo system
	std::vector<int> GoToGoal;

	float Scale;
	float speed;
	float colMove;
	float frame;

	int AnimFrame;
	int Id;
	int Anim;

	bool floating;
	bool fire;

	std::string animName;	
	int ledgeAttach;
	std::shared_ptr<sf::Texture> SkellyTex;
	std::shared_ptr<Map> currentMap;

	//protected functions
	virtual void FallOff();
	virtual void Land();
	virtual void CheckXCol(std::shared_ptr<Map> map, std::shared_ptr<sf::Vector2f> pLoc);
	virtual void CheckTrig(std::shared_ptr<ParticleManager> pMan);
	virtual void FireTrig(int trig, std::shared_ptr<sf::Vector2f> loc, std::shared_ptr<ParticleManager> pMan);
public:
	//public members
	std::shared_ptr<sf::Vector2f> Location;
	std::shared_ptr<sf::Vector2f> Trajectory;

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

	//different types of hits possible by the character
	static const int TRIG_SHOOT_ACROSS = 0;
    static const int TRIG_SHOOT_UP = 1;
    static const int TRIG_SHOOT_DOWN = 2;
    static const int TRIG_HIT_UP = 3;
    static const int TRIG_HIT_DOWN = 4;
    static const int TRIG_HIT_DIAG_UP = 5;
    static const int TRIG_HIT_DIAG_DOWN = 6;
    static const int TRIG_HIT_UPPERCUT = 7;
    static const int TRIG_HIT_SMACKDOWN = 8;
    static const int TRIG_KICK = 9;
	//public functions
	Entity(){}
	virtual void Update(float time_passed);
	virtual void Draw(std::shared_ptr<sf::RenderWindow> window);
	virtual void BodypartsInit();
	virtual void SetBodyPart(std::shared_ptr<BodyParts> newBodyPart, int bodyPartIndex);
	virtual void SetNewAnim(std::string newAnim);
	virtual void DoScript(int animIdx, int KeyFrameIdx){}
	virtual void SetMap(std::shared_ptr<Map> newMap);
};

#endif