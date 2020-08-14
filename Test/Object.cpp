#include "headers/Object.h"
#include "headers/Game.h"
#include "headers/Player.h"

Object::Object(Type type, sf::Texture& texture) :
	//Texture Variables--------------------------------------------------------------------------------------------------------|
	Texture(texture), numOfTextures(4), Sprite(texture), UvRect(0, 0, Texture.getSize().x / numOfTextures, Texture.getSize().y)
	, Collected(false), DistanceDetection(5.0f * 32)
{
}
//Drawing & rendering varibales------------------|
void Object::DrawSprite(sf::RenderWindow& window)
{
	if (!Collected)
	{
		window.draw(Sprite);
	}
}
//Allows me to set the texture variables to my prefered-|
void Object::SetUVRectLeft(int number)
{
	UvRect.left = UvRect.width * number;
	Sprite.setTextureRect(UvRect);
}
void Object::DetectCollision(Player& player, Game& game)
{
}


