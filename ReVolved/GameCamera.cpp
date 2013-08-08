#include "GameCamera.h"

GameCamera::GameCamera(sf::Vector2f center, sf::Vector2f size)
{
	gameView = sf::View(center, size);
}

sf::View GameCamera::GameView()
{
	return gameView;
}

sf::Vector2f GameCamera::GetPosition()
{
	sf::Vector2f viewCenter = gameView.getCenter();
    sf::Vector2f halfExtents = gameView.getSize() / 2.0f;
    sf::Vector2f translation = viewCenter - halfExtents;
	return translation;
}

void GameCamera::SetPosition(sf::Vector2f pos)
{
	gameView.move(pos);
	//gameView.setCenter(pos);
}