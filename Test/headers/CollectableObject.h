#pragma once
#include "Object.h"

class CollectableObject : public Object
{
public:
	CollectableObject(Type type, sf::Texture& texture);
	void DetectCollision(Player& player, Game& game);

private:
	int ScoreRecieved;
	bool Taken;

};

