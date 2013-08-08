#ifndef CHARACTER_H
#define CHARACTER_H

#include <SFML/Graphics.hpp>
#include <SFML\Window\Keyboard.hpp>
#include "ParticleManager.h"
#include "CharDef.h"
#include "BodyParts.h"
#include "Commands.h"
#include "ScriptEnums.h"
#include "Map.h"

//enum for the states our character can enter
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

//enum for controlling the keypresses
enum PressedKeys
{
	Nokey = 0,
	Upper,
	Lower,
	Attack,
	Secondary,
	SecUp,
	SecDown
};

//main character class, this is our hero.
class Character
{
private:
	bool fire;
	float frame;
	int ledgeAttach;
	std::shared_ptr<sf::Texture> SkellyTex;
	std::shared_ptr<Map> currentMap;

	//private function prototypes
	void FallOff();
	void Land();
	void CheckXCol(std::shared_ptr<Map> map, std::shared_ptr<sf::Vector2f> pLoc);
	void CheckTrig(std::shared_ptr<ParticleManager> pMan);
	void FireTrig(int trig, std::shared_ptr<sf::Vector2f> loc, std::shared_ptr<ParticleManager> pMan);

public:
	std::shared_ptr<sf::Vector2f> Location;
	std::shared_ptr<sf::Vector2f> Trajectory;

	std::shared_ptr<CharDef> charDef;
	CharDir Face;
	PressedKeys PressedKey;
	std::shared_ptr<ParticleManager> pManager;
	std::vector<std::shared_ptr<BodyParts> > CharacterBodyParts;
	std::vector<int> GoToGoal;

	float Scale;
	float speed;
	float colMove;
	int AnimFrame;
	int Id;
	int Anim;
	bool floating;
	bool keyLeft, keyRight, keyUp, keyDown, keyJump, keyAttack, keySecondary;
	bool prevKeyState[KEY_COUNT];
	std::string animName;
	CharState State;
	
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

	//public function prototypes
	Character(sf::Vector2f newLoc, std::shared_ptr<CharDef> newCharDef, int newId);
	~Character();

	void SetNewAnim(std::string newAnim);
	void Update(float time_passed);
	void Draw(std::shared_ptr<sf::RenderWindow> window);
	void BodypartsInit();
	void Input(bool keysPressed[]);
	void SetSlide(float dinstance);
	void SetNewJump(float jump);
	void SetBodyPart(std::shared_ptr<BodyParts> newBodyPart, int bodyPartIndex);
	void SetMap(std::shared_ptr<Map> newMap);
	void DoScript(int animIdx, int KeyFrameIdx);
};

#endif