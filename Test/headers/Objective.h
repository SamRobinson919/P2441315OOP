#pragma once
#include "Object.h"

class Objective : public Object
{
public:
	Objective(Type type, sf::Texture& texture);
	void DetectCollision(Player& player, Game& game);
};