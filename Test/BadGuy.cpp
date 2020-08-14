#include "headers/BadGuy.h"
#include "headers/Player.h"

BadGuy::BadGuy(sf::Texture& texture) : Entity(texture), Killed(false), PointGiven(150), DistanceDetection(5.0f * 32)
{
	SetTexture(texture);

	SetAnimationTexture(&texture, sf::Vector2u(4, 2), 15.0f);
	IdleFrames = 4;
	WalkingFrames = 4;

	moveLeft = false;
	moveRight = true;
}

void BadGuy::Update(float deltaTime, LevelReader& mr, Player& player)
{
	Entity::Update(deltaTime, mr);
	DetectPlayerCollision(player);

	if (Killed)
	{
		//Set the killed enemies position under the map so they can no longer be interacted with-|
		SetPosition(sf::Vector2f(32, 30 * 32));
		Stop();
	}
}

void BadGuy::Reset()
{
	moveLeft = false;
	moveRight = true;
	Killed = false;
}

void BadGuy::Stop()
{
	moveLeft = false;
	moveRight = false;
}

void BadGuy::DetectPlayerCollision(Player& player)
{
	if (abs(GetPosition().x - player.GetPosition().x) < DistanceDetection)
	{
		if (GetBoundingBox().intersects(player.GetBoundingBox()))
		{
			player.SubtractLife();
			player.SetPosition(sf::Vector2f(128, 32));
		}
	}
}

void BadGuy::DetectCollisionR(LevelReader& mapReader, sf::FloatRect boxBoundary, int index)
{
	if (boxBoundary.intersects(mapReader.GetLevelTiles()[index].collisionBox))
	{
		if (!mapReader.GetLevelTiles()[index].passable || mapReader.GetLevelTiles()[index].killTile)
		{
			moveRight = false;
			moveLeft = true;
		}
	}
}

void BadGuy::DetectCollisionL(LevelReader& mapReader, sf::FloatRect boxBoundary, int index)
{
	if (boxBoundary.intersects(mapReader.GetLevelTiles()[index].collisionBox))
	{
		if (!mapReader.GetLevelTiles()[index].passable || mapReader.GetLevelTiles()[index].killTile)
		{
			moveRight = true;
			moveLeft = false;
		}
	}
}

