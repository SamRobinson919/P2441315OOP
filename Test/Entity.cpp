#include "headers/Entity.h"
#include "headers/LevelReader.h"

Entity::Entity(sf::Texture& texture)
	: Sprite(texture, sf::IntRect(0, 0, Width, Height)),Width(32), Height(32),Texture(texture),
	  
	//Animation Variables---------------------------|
	TheAnimation(&texture, sf::Vector2u(6, 4), 6.f),
	IdleFrames(4),
	WalkingFrames(6),
	JumpingFrames(2),
	DamageFrames(1),

	//Entity Gravity & Speed Variables-|
	Velocity(sf::Vector2f(0, 0)),
	Acceleration(0.1f),
	Deceleration(0.50f),
	MaxLandSpeed(6.0f),
	MaxJumpSpeed(6.0f),
	MidAir(true),
	JumpForce(30.0f),
	Gravity(3.0f),

	//Collison Variables---|
	PlatformUpwards(false),
	FaceRight(true),
	moveRight(false),
	moveLeft(false),
	isJumping(false),
	jumpAnimCheck(false)

{
	//Load the entity texture--------|
	Sprite.setTexture(Texture, true);
	Sprite.setTextureRect(sf::IntRect(0, 0, Width, Height));

	//Position the pivot point around the center--------|
	sf::FloatRect localBounds = Sprite.getLocalBounds();
	Sprite.setOrigin(localBounds.width/2.0f, 0);

	//The enitiy starting position--|
	Sprite.setPosition(15*32, 27*32);

	//Set the animaiton to the idle state----------------------------|
	TheAnimation.SwitchAnimation(animStates::Idle, IdleFrames, true);
}

void Entity::Update(float deltaTime, LevelReader& levelReader)
{
	CalculateCollision(levelReader);
	Move(deltaTime);
	Sprite.move(Velocity.x * deltaTime, Velocity.y * deltaTime);

	//Apply the decelleration to the entity-|
	if (Velocity.x > 0)
	{
		Velocity.x -= Deceleration * deltaTime;

		//Stop the enities velocity from going all over the place after it goes near the value 0-|
		if (Velocity.x <= 0){
			TheAnimation.SwitchAnimation(animStates::Idle, IdleFrames, true);
			Velocity.x = 0;
		}
	}
	else if (Velocity.x < 0)
	{
		Velocity.x += Deceleration * deltaTime;

		//Stop the enities velocity from going all over the place after it goes near the value 0-|
		if (Velocity.x >= 0){
			TheAnimation.SwitchAnimation(animStates::Idle, IdleFrames, true);
			Velocity.x = 0;
		}
	}

	//Applies gravity to the entity-|
	if (MidAir)	{
		TheAnimation.SwitchAnimation(animStates::Jump, JumpingFrames, false);
		Velocity.y += (Gravity * deltaTime);
	}
	else if (!MidAir){
		if (jumpAnimCheck){
			TheAnimation.SwitchAnimation(animStates::Idle, IdleFrames, true);
			jumpAnimCheck = false;
		}
		Velocity.y = 0;
	}
	TheAnimation.Update(deltaTime);
	SetTextureRect(TheAnimation.GetRect());

}

void Entity::DrawSprite(sf::RenderWindow& window)
{
	window.draw(Sprite);
}


void Entity::CalculateCollision(LevelReader& levelReader)
{
	sf::FloatRect boundingBox = Sprite.getGlobalBounds();

	int xCoor = Sprite.getPosition().x / Width;
	int yCoor = Sprite.getPosition().y / Height;

	//The collison detection for the Left of the entity---------------------|
	DetectCollisionL(levelReader, boundingBox, (xCoor - 1) * Width + yCoor);
	//The collison detection for the Right of the entity--------------------|
	DetectCollisionR(levelReader, boundingBox, (xCoor + 1) * Width + yCoor);
	//The collison detection for the Bottom of the entity-------------------|
	DetectCollisionB(levelReader, boundingBox, xCoor * Width + (yCoor + 1));
	//The collison detection for the Top of the entity----------------------|
	DetectCollisionA(levelReader, boundingBox, xCoor * Width + (yCoor - 1));
}

void Entity::Move(float deltaTime)
{
	if (moveLeft)
	{
		TheAnimation.SwitchAnimation(animStates::Run, WalkingFrames, true);

		//If entity is facing right turn it left-|
		if (FaceRight){
			Sprite.scale(-1.f, 1.f);
			FaceRight = false;
		}
		Velocity.x -= Acceleration;
		if (Velocity.x < -MaxLandSpeed){
			Velocity.x = -MaxLandSpeed;
		}
	}
	else if (moveRight)
	{
		TheAnimation.SwitchAnimation(animStates::Run, WalkingFrames, true);
		//If entity is facing left turn it right-|
		if (!FaceRight){
			Sprite.scale(-1.f, 1.f);
			FaceRight = true;
		}
		Velocity.x += Acceleration;
		if (Velocity.x > MaxLandSpeed){
			Velocity.x = MaxLandSpeed;
		}
	}

	if (isJumping){
		jumpAnimCheck = true;

		if (!MidAir){
			TheAnimation.SwitchAnimation(animStates::Jump, JumpingFrames, false);
			Velocity.y -= JumpForce;
			MidAir = true;
		}
	}
}

void Entity::SetAnimationTexture(sf::Texture* texture, sf::Vector2u dimensions, int timeToSwitch)
{
	TheAnimation = Animation(texture, dimensions, timeToSwitch);
}

void Entity::DetectCollisionL(LevelReader& levelReader, sf::FloatRect boundingBox, int index)
{
	if (boundingBox.intersects(levelReader.GetLevelTiles()[index].collisionBox)){
		if (!levelReader.GetLevelTiles()[index].passable){
			TheAnimation.SwitchAnimation(animStates::Idle, IdleFrames, true);

			Sprite.setPosition(levelReader.GetLevelTiles()[index].tile.position.x + Width + boundingBox.width / 2 , Sprite.getPosition().y);
			Velocity.x = 0;
		}
	}
}

void Entity::DetectCollisionR(LevelReader& levelReader, sf::FloatRect boundingBox, int index)
{
	if (boundingBox.intersects(levelReader.GetLevelTiles()[index].collisionBox)){
		if (!levelReader.GetLevelTiles()[index].passable){
			TheAnimation.SwitchAnimation(animStates::Idle, IdleFrames, true);

			Sprite.setPosition(levelReader.GetLevelTiles()[index].tile.position.x - boundingBox.width / 2, Sprite.getPosition().y);
			Velocity.x = 0;

		}
	}
}

void Entity::DetectCollisionB(LevelReader &levelReader, sf::FloatRect boundingBox, int index)
{
	if (!levelReader.GetLevelTiles()[index].passable){
		Sprite.setPosition(Sprite.getPosition().x, levelReader.GetLevelTiles()[index].tile.position.y - Sprite.getLocalBounds().height);
		MidAir = false;
		PlatformUpwards = false;
	}else{
		MidAir = true;
	}
}

void Entity::DetectCollisionA(LevelReader& levelReader, sf::FloatRect boundingBox, int index){
	if (!levelReader.GetLevelTiles()[index].passable)	{
		if (!PlatformUpwards)		{
			Sprite.setPosition(Sprite.getPosition().x, levelReader.GetLevelTiles()[index].tile.position.y + Sprite.getLocalBounds().height);
			Velocity.y = 0;
			PlatformUpwards = true;
		}
	}
}








