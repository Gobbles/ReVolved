#ifndef GAME_CAMERA_H
#define GAME_CAMERA_H

#include <SFML\Graphics\View.hpp>

class GameCamera
{
public:	
	sf::View GameView();

	sf::Vector2f GetPosition();
	void SetPosition(sf::Vector2f pos);


	GameCamera(sf::Vector2f center, sf::Vector2f size);
private:
	sf::View gameView;
};

#endif
