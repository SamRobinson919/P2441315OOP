#include "headers/Game.h"
#include "headers/Objective.h"
#include "headers/Player.h"

Objective::Objective(Type type, sf::Texture& texture) : Object(type, texture)
{
	switch (type)
	{
	case(Type::Pillar):
		SetUVRectLeft((int)Type::Pillar);
		break;

	case(Type::Bike):
		SetUVRectLeft((int)Type::Bike);
		break;
	}
}

void Objective::DetectCollision(Player& player, Game& game)
{
	//This enables the checking if theirs colliso if the player is near the objective---|
	if (abs(GetSprite().getPosition().x - player.GetPosition().x) < GetDetectDistance())
	{
		if (GetSprite().getGlobalBounds().intersects(player.GetBoundingBox()))
		{
			player.SetPosition(sf::Vector2f(128, 32));
			game.SetWin(true);
		}
	}

}
