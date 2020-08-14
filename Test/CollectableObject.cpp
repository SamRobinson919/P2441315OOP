#include "headers/CollectableObject.h"
#include "headers/Player.h"

CollectableObject::CollectableObject(Type type, sf::Texture& texture) : Object(type, texture), ScoreRecieved(0), Taken(false) {
	switch (type)
	{
	case(Type::Coin):
		SetUVRectLeft((int)Type::Coin);
		ScoreRecieved = 50;
		break;

	case(Type::Trophy):
		SetUVRectLeft((int)Type::Trophy);
		ScoreRecieved = 500;
		break;
	}
}

void CollectableObject::DetectCollision(Player& player, Game& game)
{
	//Enable the collison detection if the player is near the collectable---------------|
	if (abs(GetSprite().getPosition().x - player.GetPosition().x) < GetDetectDistance())
	{
		//Hide the collectable so that the player cannot interact with it multiple times-|
		if (GetSprite().getGlobalBounds().intersects(player.GetBoundingBox()))
		{
			SetPosition(sf::Vector2f(0, 0));
			player.AddScore(ScoreRecieved);
			Taken = true;
		}
	}

}
