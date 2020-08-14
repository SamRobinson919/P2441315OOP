#pragma once
#include <SFML/Graphics.hpp>


class Animation
{
public:
	Animation(sf::Texture* texture, sf::Vector2u sizeOfSpriteSheet, float timeToSwitch);
	void Update(float deltaTime);

	void SwitchAnimation(int row, int frameCount, bool loop);
	sf::IntRect GetRect() { return UvRect; }

private:
	float TotalTime, TimeToSwitch;
	bool Looping, Replay;
	sf::IntRect UvRect;
	sf::Vector2u FrameCounter, CurrentFrame;

};

