#include "Game.h"

Game::Game() : screenSize(1024,768),
	window(sf::VideoMode(1024, 768), "Re:Volved ver 0.0.04a", sf::Style::Close)
{
	window.setKeyRepeatEnabled(false);
	MainCamera = std::make_shared<GameCamera>(sf::Vector2f(512,384),screenSize);
	window.setView(MainCamera->GameView());

	for(int i = 0; i < KEY_COUNT; i++)
	{
		keysPressed[i] = false;
	}

	if(!AppIcon.loadFromFile("Art/Generic/Icon.png"))
	{
		return;
	}

	window.setIcon(64,64,AppIcon.getPixelsPtr());

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

	if(!particleTex.loadFromFile("Art/Particles/particles.png"))
	{
		return;
	}
	particleSpr.setTexture(particleTex);

	if(!fpsFont.loadFromFile("Font/comic.ttf"))
	{
		return;
	}
	Loaded = false;

	pManager = std::unique_ptr<ParticleManager>(new ParticleManager());

	//LoadCharacter();
	CharLoadThread = std::unique_ptr<sf::Thread>(new sf::Thread(&Game::LoadCharacter, this));
	CharLoadThread->launch();
}

Game::~Game()
{
}

void Game::LoadCharacter()
{
	mEntityManager = std::unique_ptr<EntityManager>(new EntityManager());
	std::cout << "Start Loading\n";

	groundMap = std::make_shared<Map>(MainCamera);
	groundMap->Read();
    std::cout << "Map Read\n";

	//sf::Context context;
	Loaded = true;
}

void Game::Run()
{
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	static const sf::Time timePerFrame = sf::seconds(1.f / 60.f);

	fpsText.setFont(fpsFont);

	while (window.isOpen())
    {
		//ProcessEvents();
		timeSinceLastUpdate += clock.restart();

        //fps code
		fps = 1.f / timeSinceLastUpdate.asSeconds();
		std::stringstream ss (std::stringstream::in | std::stringstream::out);
		ss << fps;
		fpsStr = ss.str();
		fpsText.setString(fpsStr);
		fpsText.setColor(sf::Color::Red);
		
		while(timeSinceLastUpdate > timePerFrame)
		{
			timeSinceLastUpdate -= timePerFrame;
			ProcessEvents();
			Update(timePerFrame.asSeconds());
		}
		Draw();
	}
	mEntityManager->Clear();
}
void Game::ProcessEvents()
{
	sf::Event event;
	while (window.pollEvent(event))
    {
		CheckEvents(event);
    }
}
void Game::CheckEvents(sf::Event &event)
{
	//check for our Input Events
	switch(event.type)
	{
		case sf::Event::Closed:
		{
			window.close();
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
		case sf::Event::KeyReleased:
		{
			switch(event.key.code)
			{
				case sf::Keyboard::A:
				{
					keysPressed[KEY_LEFT] = false;
					break;
				}
				case sf::Keyboard::D:
				{
					keysPressed[KEY_RIGHT] = false;
					break;
				}
				case sf::Keyboard::W:
				{
					keysPressed[KEY_UP] = false;
					break;
				}
				case sf::Keyboard::S:
				{
					keysPressed[KEY_DOWN] = false;
					break;
				}
			}
			break;
		}
	}
}

void Game::DoInput()
{
	mEntityManager->CheckInput(keysPressed);
}

void Game::Update(float time_passed)
{
	if(Loaded)
	{
		DoInput();
		TestCollision(time_passed);
		mEntityManager->UpdateEntities(time_passed, *pManager, *groundMap);

		groundMap->Update(*pManager);
		pManager->UpdateParticles(time_passed);

        //we position the view around the character
		sf::View view = window.getView();
		sf::Vector2f pos = mEntityManager->GetCharacterLocation();//character->Location;

		if(pos.x - 512 < 0)
			pos.x = 512;
		if(pos.y - 384 < 0)
			pos.y = 384;

		view.setCenter(pos);
		window.setView(view);
	}
}

void Game::TestCollision(float time_passed)
{
	mEntityManager->CheckMovementHit();
}

void Game::Draw()
{
	window.clear(sf::Color::Black);

	if(!Loaded)
	{
		window.draw(*LoadingSprite);
	}
	else
	{
		groundMap->Draw(window, mapsTex, mapBackTex,0,3);
		pManager->DrawParticle(window, particleSpr, true);
		mEntityManager->Draw(window);

		pManager->DrawParticle(window, particleSpr, false);
		fpsText.setPosition(window.getView().getCenter() - window.getView().getSize() / 2.f);
	}
	window.draw(fpsText);
	//drawing code goes here
	//window->draw(//sprite goes in here");
    window.display();
}