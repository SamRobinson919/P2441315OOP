#pragma once
#include <SFML/Graphics.hpp>
#include "LevelReader.h"
#include "Tile.h"
#include "Animation.h"
#include <iostream>

class LevelReader;
class Animation;

class Entity
{
public:
	Entity(sf::Texture& texture);

	void Update(float deltaTime, LevelReader& levelReader);
	void DrawSprite(sf::RenderWindow& window);
	sf::Sprite GetSprite(){
		return Sprite; }

	sf::Vector2f GetPosition()
	{
		return Sprite.getPosition(); }
	void SetPosition(sf::Vector2f position) {
		Sprite.setPosition(position); }

	sf::FloatRect GetBoundingBox()			{
		return Sprite.getGlobalBounds(); }

	void SetTextureRect(sf::IntRect ir)		{
		Sprite.setTextureRect(ir); }
	void SetTexture(sf::Texture& texture)	{
		Sprite.setTexture(texture); }

private:
	void CalculateCollision(LevelReader& levelReader);
	void Move(float dt);

protected:
	virtual void DetectCollisionR(LevelReader& levelReader, sf::FloatRect boundingBox, int index);
	virtual void DetectCollisionL(LevelReader& levelReader, sf::FloatRect boundingBox, int index);
	virtual void DetectCollisionB(LevelReader& levelReader, sf::FloatRect boundingBox, int index);
	void DetectCollisionA(LevelReader& levelReader, sf::FloatRect boundingBox, int index);
	void SetAnimationTexture(sf::Texture* texture, sf::Vector2u dimensions, int switchTime);




private:
	sf::Sprite Sprite;
	sf::Texture Texture;

	Animation TheAnimation;
	enum animStates { Idle, Run, Jump, Hurt };

	const int Width;
	const int Height;

	sf::SoundBuffer SoundBuffer;
	sf::Sound Sound;

	sf::Vector2f Velocity;
	float Acceleration;
	float Deceleration;

	const float MaxLandSpeed;
	const float MaxJumpSpeed;

	bool MidAir;
	float JumpForce;

	const float Gravity;

	bool PlatformUpwards;
	bool FaceRight;

protected:
	bool moveRight;
	bool moveLeft;
	bool isJumping;
	bool jumpAnimCheck; // needed for animation checking

	int IdleFrames;
	int WalkingFrames;
	int JumpingFrames;
	int DamageFrames;

};

