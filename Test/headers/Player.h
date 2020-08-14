#pragma once
#include "Entity.h"
#include "Projectile.h"
#include <queue>

class Game;

class Player : public Entity
{
public:
	Player(sf::Texture& texture);
	void Update(float deltaTime, LevelReader& mapReader);

	//Lives Variables for each stage of processing the lives-|
	int GetLives() {
		return PlayerLives;
	}

	void SetLives(int playerLives) {
		PlayerLives = playerLives;
	}

	bool LivesChanged() {
		return ChangeLives;
	}

	void SetLivesChanged(bool changed) {
		ChangeLives = changed;
	}

	//Score Variables for each stage of processing the score-|
	int GetScore() {
		return PlayerScore;
	}

	void SetScore(int playerScore) {
		PlayerScore = playerScore;
		ChangeScore = true;
	}

	void AddScore(int playerScore) {
		PlayerScore += playerScore;
		ChangeScore = true;
	}

	bool ScoreChanged() {
		return ChangeScore;
	}

	void SetScoreChanged(bool changed) {
		ChangeScore = changed;
	}

	std::deque<Projectile>& GetProjectiles() {
		return Projectiles;
	}

	void Reset();
	void SubtractLife();

private:
	void DetectCollisionB(LevelReader& mapReader, sf::FloatRect boundingBox, int index);

private:
	//Added to avoid constant calling to the to_string every frame of the game-|
	bool ChangeLives;
	bool ChangeScore;
	bool PlayerDeath;

	int PlayerLives;
	int PlayerScore;

	float BulletCooldown;

	std::deque<Projectile> Projectiles;

	sf::Texture ProjectileTexture;
	sf::Clock ClockForCooldown;




};

