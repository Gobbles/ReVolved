#ifndef CHARACTER_H
#define CHARACTER_H

#include <SFML/Graphics.hpp>
#include <SFML\Window\Keyboard.hpp>
#include "ParticleManager.h"
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
	Character(sf::Vector2f newLoc, std::shared_ptr<CharDef> newCharDef, int newId, std::shared_ptr<ParticleManager> pMan);

	void Update(float time_passed);
	void Input(bool keysPressed[]);
	void SetSlide(float dinstance);
	void SetNewJump(float jump);
	
	virtual void DoScript(int animIdx, int KeyFrameIdx);
};

#endif