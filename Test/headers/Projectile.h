#pragma once
#include <SFML/Graphics.hpp>
#include "BadGuy.h"
class LevelReader;
class BadGuy;

class Projectile
{
public:
	Projectile(sf::Vector2f position, int direction, sf::Texture& texture);

	void Update(float dt, LevelReader& mapReader, std::vector<BadGuy>& entities, Player& player);
	void Draw(sf::RenderWindow& window);
	bool isCreated() {
		return Created;
	}
private:
	void DetectCollision(LevelReader& mapReader, int index, std::vector<BadGuy>& entities, Player& player);
private:
	sf::Sprite Sprite;
	const sf::Vector2f Velocity;
	bool Created;
};
