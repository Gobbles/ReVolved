#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <sstream>
#include <cmath>
#include <iostream>
#include "EntityManager.h"
#include "Character.h"
#include "Enemy.h"
#include "Map.h"
#include "GameCamera.h"
#include "Commands.h"
class Game
{
public:
	Game();
	~Game();
	void Run();
	
	//member functions, getters/setters
	float FrameTime() { return frameTime; }
	void SetFrameTime( float value) { frameTime = value; }

	float SlowTime() {return slowTime; }
	void SetSlowTime( float value) {slowTime = value; }

	sf::Vector2f ScreenSize() { return screenSize; }
	void SetScreenSize(sf::Vector2f value) { screenSize = value; }

private:
	sf::RenderWindow window;
	std::unique_ptr<EntityManager> mEntityManager;
	//Loading Thread
	std::unique_ptr<sf::Thread> CharLoadThread;
	
	//static members
	sf::Vector2f screenSize;
	static float frameTime;
	static float slowTime;

	//Game Camera
	std::shared_ptr<GameCamera> MainCamera;

	//key input
	bool keysPressed[KEY_COUNT];

	//map information
	std::shared_ptr<Map> groundMap;
	std::shared_ptr<sf::Texture> mapsTex;
	std::shared_ptr<sf::Texture> mapBackTex;
	std::shared_ptr<sf::Sprite> mapSprite;
	std::shared_ptr<sf::Sprite> mapBackSprite;

	std::shared_ptr<sf::Texture> LoadingTex;
	std::shared_ptr<sf::Sprite> LoadingSprite;
	sf::Image AppIcon;

	//particle Image
	sf::Texture particleTex;
	sf::Sprite particleSpr;

	//FPS
	float fps;
	std::string fpsStr;
	sf::Text fpsText;
	sf::Font fpsFont;

	//content loaded
	bool Loaded;

	//Particle Engine
	std::unique_ptr<ParticleManager> pManager;

	//constants
	static const int gravity = 900;
	static const int friction = 1000;

	void LoadCharacter();

	//functions
	void Update(float time_passed);
	void DoInput();
	void CheckEvents(sf::Event &event);
	void Draw();
	void ProcessEvents();
	void TestCollision(float time_passed);

};