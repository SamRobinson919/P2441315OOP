#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "ObjectTypes.h"

class Game;

class Player;

class Object
{
public:
	Object(Type type, sf::Texture& texture);

	sf::Sprite GetSprite() {
		return Sprite;
	}

	float GetDetectDistance() {
		return DistanceDetection;
	}

	void SetPosition(sf::Vector2f position) {
		Sprite.setPosition(position);
	}

	void SetTaken(bool collected) {
		Collected = collected;
	}
	void SetUVRectLeft(int number);

	void DrawSprite(sf::RenderWindow& window);

	virtual void DetectCollision(Player& player, Game& game);

private:
	sf::Texture Texture;
	int numOfTextures;

	sf::Sprite Sprite;
	sf::IntRect UvRect;

	bool Collected;
	float DistanceDetection;
};

