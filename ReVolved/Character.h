#ifndef CHARACTER_H
#define CHARACTER_H

#include <SFML/Graphics.hpp>
#include <SFML\Window\Keyboard.hpp>
#include "SideScrollEnt.h"

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
class Character : public SideScrollEnt
{
private:

public:	
	PressedKeys PressedKey;
	bool keyLeft, keyRight, keyUp, keyDown, keyJump, keyAttack, keySecondary;

	//public function prototypes
	Character();
	Character(sf::Vector2f newLoc, CharDef& newCharDef, int newId);

	virtual void Update(float time_passed, ParticleManager& pManager, Map& currentMap);
	void Input(bool keysPressed[]);
	
	virtual void DoScript(int animIdx, int KeyFrameIdx);
};

#endif