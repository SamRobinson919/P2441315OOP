#include "headers/Projectile.h"
#include "headers/Entity.h"
#include "headers/LevelReader.h"
#include "headers/Tile.h"
#include "headers/Player.h"

Projectile::Projectile(sf::Vector2f position, int direction, sf::Texture& texture) : Sprite(texture), Velocity(sf::Vector2f(10.0f * direction, 0.0f)), Created(true)
{
	//Setting the origin of the projectile to the middle-|
	sf::FloatRect localBounds = Sprite.getLocalBounds();
	Sprite.setOrigin(localBounds.width / 2.0f, 0);

	Sprite.setPosition(position);
}


void Projectile::Update(float deltaTime, LevelReader& mr, std::vector<BadGuy>& entities, Player& player)
{
	//Moving the projectile across the game screen--------------|
	Sprite.move(Velocity.x * deltaTime, Velocity.y * deltaTime);
	//Checking the left collion of the projectile---------------------------------------------------------------|
	DetectCollision(mr, (Sprite.getPosition().x / 32 - 0) * 32 + Sprite.getPosition().y / 32, entities, player);
	//Checking the right collion of the projectile--------------------------------------------------------------|
	DetectCollision(mr, (Sprite.getPosition().x / 32 + 0) * 32 + Sprite.getPosition().y / 32, entities, player);
}

void Projectile::Draw(sf::RenderWindow& window)
{
	if (Created)
	{
		window.draw(Sprite);
	}
}

void Projectile::DetectCollision(LevelReader& levelReader, int index, std::vector<BadGuy>& entities, Player& player)
{
	//Checking the collison with the platforms-----------------------------------|
	if (Sprite.getGlobalBounds().intersects(levelReader.GetLevelTiles()[index].collisionBox))
	{
		if (!levelReader.GetLevelTiles()[index].passable)
		{
			Created = false;
		}
	}

	//Checking the collison with the enemies-|
	for (auto& enemy : entities)
	{
		if (Sprite.getGlobalBounds().intersects(enemy.GetBoundingBox()))
		{
			//Moves the projectile so that it does not hit the collison box on the enemies more than once-|
			Sprite.setPosition(64, 0);
			Created = false;
			enemy.SetKilledState(true);

			player.AddScore(enemy.GetPointsGiven());
		}
	}
}

