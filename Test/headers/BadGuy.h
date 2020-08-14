#pragma once
#include "Entity.h"

class Player;

class BadGuy : public Entity
{
public:
	int GetPointsGiven() {
		return PointGiven;
	}

	BadGuy(sf::Texture& texture);

	void Update(float deltaTime, LevelReader& mapReader, Player& player);
	void Reset();
	void SetKilledState(bool killed) {
		Killed = killed;
	}

private:
	void Stop();

	//Collison detection with the player and the other objects-|
	void DetectPlayerCollision(Player& player);
	void DetectCollisionL(LevelReader& mapReader, sf::FloatRect boxBoundary, int index);
	void DetectCollisionR(LevelReader& mapReader, sf::FloatRect boxBoundary, int index);

private:
	const int PointGiven;
	float DistanceDetection;
	bool Killed;
};

