#pragma once
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "Player.h"
#include "BadGuy.h"
#include "Menu.h"

class LevelReader;
class Object;
class Player;

class Game
{
public:
	Game();
	void Run();
	void PlaySound(std::string input);
	void SetWin(bool result) {
		GameWin = result;
	}
	void SetLoss(bool result) {
		GameOver = result;
	}
private:
	//Updating & Checking & Initialising-|
	void Init();
	void Update(float deltaTime);
	void UpdateText();
	void UpdateCamera();
	void CheckGameState();

	//Drawing---|
	void Draw();
	void DrawPauseText(sf::RenderWindow& window);
	void Reset();
private:
	//Render & View---------|
	sf::RenderWindow Window;
	LevelReader LevelReader;
	sf::View Camera;

	//Player--------------------------|
	std::unique_ptr<Player> ThePlayer;
	sf::Texture PlayerTexture;

	//Enemies-------------------------------------|
	std::vector<BadGuy> Enemies;
	sf::Texture EnemyTexture;

	//Objects-------------------------------------|
	std::vector<std::unique_ptr<Object>> Objects;
	sf::Texture ObjectTexture;

	Menu Menu;
	//Text & Font------|
	sf::Font MainFont;
	sf::Text LivesText;
	sf::Text ScoreText;

	//States------|
	bool Paused;
	bool GameOver;
	bool GameWin;


};

