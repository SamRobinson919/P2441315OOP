#include "headers/Player.h"
#include "headers/Game.h"
#include "headers/Projectile.h"

Player::Player(sf::Texture& texture) : Entity(texture),

//Player variables for lives/score/projectiles-|
ChangeLives(false), PlayerLives(3),
ChangeScore(false), PlayerScore(0),
Projectiles(), ProjectileTexture(),
BulletCooldown(1.0f), ClockForCooldown(),
PlayerDeath(false)
{
	SetAnimationTexture(&texture, sf::Vector2u(6, 4), 6.f);
	IdleFrames = 4;
	WalkingFrames = 6;
	JumpingFrames = 2;
	DamageFrames = 1;

	ProjectileTexture.loadFromFile("assets/images/bullet.png");
	ClockForCooldown.restart();
}

void Player::Update(float deltaTime, LevelReader& levelReader)
{
	//Dual keyboard inputs for player movemnt, walking and jumping------------------------------------|
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || (sf::Keyboard::isKeyPressed(sf::Keyboard::W)))
	{
		isJumping = true;
	}
	else
	{
		isJumping = false;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || (sf::Keyboard::isKeyPressed(sf::Keyboard::A)))
	{
		moveLeft = true;
	}
	else
	{
		moveLeft = false;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || (sf::Keyboard::isKeyPressed(sf::Keyboard::D)))
	{
		moveRight = true;
	}
	else
	{
		moveRight = false;
	}
	//Key to shoot the players bullet-------------------|
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		// shoot projectile
		if (ClockForCooldown.getElapsedTime().asSeconds() >= BulletCooldown)
		{
			Projectiles.push_back(Projectile(GetPosition(), GetSprite().getScale().x, ProjectileTexture));
			ClockForCooldown.restart();
		}
	}
	Entity::Update(deltaTime, levelReader);
}

void Player::Reset()
{
	SetLives(3);
	SetScore(0);

}

void Player::SubtractLife()
{
	if (!PlayerDeath)
	{
		SetScore(0);
		PlayerLives--;
		ChangeLives = true;
	}
}

void Player::DetectCollisionB(LevelReader& levelReader, sf::FloatRect boxBoundary, int index)
{
	//This helps detect the damage tiles that can kill the player-|
	Entity::DetectCollisionB(levelReader, boxBoundary, index);
	if (levelReader.GetLevelTiles()[index].killTile)
	{
		SubtractLife();
	}
}

