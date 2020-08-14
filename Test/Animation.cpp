#include "headers/Animation.h"
#include <iostream>

Animation::Animation(sf::Texture* texture, sf::Vector2u numberOfImages, float timeToSwitch)
//Keeping track of the size of the texture and how many different animations there are-|
	: UvRect(0, 0,
		texture->getSize().x / float(numberOfImages.x),
		texture->getSize().y / float(numberOfImages.y)),

	//How many frames within and keept track of the frames-|
	FrameCounter(numberOfImages), CurrentFrame(0, 0),

	//Keeping the time of each frame and when to switch to naother frame-|
	TotalTime(0.0f), TimeToSwitch(timeToSwitch),
	//Keeps track of whether an animation should be looping or if it should be replayed-|
	Looping(true), Replay(true){}



void Animation::Update(float deltaTime)
{
	if (Replay)
	{
		TotalTime += deltaTime;

		//Go through the animation--|
		if (TotalTime >= TimeToSwitch) {
			TotalTime -= TimeToSwitch;
			CurrentFrame.x++;
		}


		//If the animation comes to an end. loop back to the beginnning-|
		if (CurrentFrame.x >= FrameCounter.x) {
			if (!Looping) {
				Replay = false;
			}
			CurrentFrame.x = 0;
		}
		UvRect.left = CurrentFrame.x * UvRect.width;
		UvRect.top = CurrentFrame.y * UvRect.height;
	}
}


void Animation::SwitchAnimation(int row, int imageCountX, bool loop)
{
	if (CurrentFrame.y != row) {
		Looping = loop;
		CurrentFrame.x = 0;
		CurrentFrame.y = row;
		Replay = true;
	}
	FrameCounter.x = imageCountX;
}
