#ifndef CHARACTER_H
#define CHARACTER_H

#include <SFML/Graphics.hpp>
#include <SFML\Window\Keyboard.hpp>
#include "ParticleManager.h"
#include "Entity.h"

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
class Character : public Entity
{
private:
	
public:	
	PressedKeys PressedKey;
	bool keyLeft, keyRight, keyUp, keyDown, keyJump, keyAttack, keySecondary;
	bool prevKeyState[KEY_COUNT];

	//public function prototypes
	Character(sf::Vector2f newLoc, std::shared_ptr<CharDef> newCharDef, int newId);

	void Update(float time_passed);
	void Draw(std::shared_ptr<sf::RenderWindow> window);
	void BodypartsInit();
	void Input(bool keysPressed[]);
	void SetSlide(float dinstance);
	void SetNewJump(float jump);
	void SetBodyPart(std::shared_ptr<BodyParts> newBodyPart, int bodyPartIndex);
	void SetMap(std::shared_ptr<Map> newMap);
	virtual void DoScript(int animIdx, int KeyFrameIdx);
};

#endif