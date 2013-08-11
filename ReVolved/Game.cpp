#include "Game.h"

Game::Game()
{
	screenSize = sf::Vector2f(1024,768);
	window = std::shared_ptr<sf::RenderWindow>(new sf::RenderWindow(sf::VideoMode(screenSize.x, screenSize.y), "Re:Volved ver 0.0.03a", sf::Style::Close));
	window->setFramerateLimit(60);
	MainCamera = std::make_shared<GameCamera>(sf::Vector2f(512,384),screenSize);
	window->setView(MainCamera->GameView());

	for(int i = 0; i < KEY_COUNT; i++)
	{
		keysPressed[i] = false;
	}

	if(!AppIcon.loadFromFile("Art/Generic/Icon.png"))
	{
		return;
	}



	window->setIcon(64,64,AppIcon.getPixelsPtr());

	LoadingTex = std::make_shared<sf::Texture>(sf::Texture());
	if(!LoadingTex->loadFromFile("Art/Screen/Loading.png"))
	{
		return;
	}
	LoadingSprite = std::shared_ptr<sf::Sprite>(new sf::Sprite());
	LoadingSprite->setTexture(*LoadingTex);
	LoadingSprite->setPosition(sf::Vector2f(0,0));

	mapsTex = std::make_shared<sf::Texture>(sf::Texture());
	if(!mapsTex->loadFromFile("Art/Map/PlatformTextures1.png"))
	{
		return;
	}
	mapSprite = std::make_shared<sf::Sprite>();
	mapSprite->setTexture(*mapsTex);

	mapBackTex = std::make_shared<sf::Texture>(sf::Texture());
	if(!mapBackTex->loadFromFile("Art/Map/Dark_Sky1.png"))
	{
		return;
	}
	mapBackSprite = std::make_shared<sf::Sprite>();
	mapBackSprite->setTexture(*mapBackTex);
	mapBackSprite->setPosition(0,0);
	Loaded = false;

	CharLoadThread = std::shared_ptr<sf::Thread>(new sf::Thread(&Game::LoadCharacter, this));
	CharLoadThread->launch();
}

Game::~Game()
{
}

void Game::LoadCharacter()
{
	groundMap = std::make_shared<Map>(MainCamera);
	groundMap->Read();

	charDef = std::make_shared<CharDef>(CharDef("skeleton"));
	character = std::make_shared<Character>(Character(sf::Vector2f(500.f, 100.f), charDef, 0));
	character->BodypartsInit();
	character->SetMap(groundMap);
	sf::Context context;
	Loaded = true;
}

void Game::Run()
{
	sf::Clock clock;
	sf::Event event;

	while (window->isOpen())
    {
        while (window->pollEvent(event))
        {
			CheckInput(event);
        }

		sf::Time elapsed = clock.restart();

		Logic((float)elapsed.asSeconds());
	}
}

void Game::CheckInput(sf::Event &event)
{
	//check for our Input Events
	switch(event.type)
	{
		case sf::Event::Closed:
		{
			window->close();
		}
		case sf::Event::KeyPressed:
		{
			switch(event.key.code)
			{
				case sf::Keyboard::A:
				{
					keysPressed[KEY_LEFT] = true;
					break;
				}
				case sf::Keyboard::D:
				{
					keysPressed[KEY_RIGHT] = true;
					break;
				}
				case sf::Keyboard::W:
				{
					keysPressed[KEY_UP] = true;
					break;
				}
				case sf::Keyboard::S:
				{
					MainCamera->GameView().move(0,-100);
					keysPressed[KEY_DOWN] = true;
					break;
				}
				case sf::Keyboard::Space:
				{
					keysPressed[KEY_JUMP] = true;
					break;
				}
				case sf::Keyboard::Q:
				{
					keysPressed[KEY_SECONDARY] = true;
					break;
				}
				case sf::Keyboard::E:
				{
					keysPressed[KEY_ATTACK] = true;
					break;
				}
			}
			break;
		}
	}
}

void Game::Logic(float time_passed)
{
	Update(time_passed);
	Draw();
}

void Game::DoInput()
{	
	character->Input(keysPressed);
	for(int i = 0; i < KEY_COUNT; i++)
	{
		keysPressed[i] = false;
	}
}

void Game::Update(float time_passed)
{
	if(Loaded)
	{
		DoInput();
		character->Update(time_passed);
		groundMap->Update();

		sf::View view = window->getView();
		sf::Vector2f pos = *character->Location;
		pos.y -= 200;
		if(pos.x - 512 < 0)
			pos.x = 512;
		if(pos.y - 384 < 0)
			pos.y = 384;

		view.setCenter(pos);
		window->setView(view);
	}
}

void Game::Draw()
{
	window->clear(sf::Color::Black);

	if(!Loaded)
	{
		window->draw(*LoadingSprite);
	}
	else
	{
		groundMap->Draw(window,mapsTex,mapBackTex,0,3);
		character->Draw(window);
	}

	//drawing code goes here
	//window->draw(//sprite goes in here");
    window->display();
}