#include "headers/CollectableObject.h"
#include "headers/Game.h"
#include "headers/LevelReader.h"
#include "headers/Object.h"
#include "headers/Objective.h"

Game::Game()
	: Window(sf::VideoMode(1000, 1000), "Jimmys Lost Bike - P2441315")
	//Load level from txt file-|
	, LevelReader("testlevel.txt")
	//Objects--------------------------------------------------------------|
	, Camera(), ThePlayer(nullptr), PlayerTexture(), Enemies(), Objects()
	//Font & Text---------------|
	, Menu(Window, "assets/fonts/Roboto.ttf"), MainFont(), LivesText(), ScoreText()
	//States-----------|
	, Paused(false), GameOver(false)
{
	//Initialise-|
	Init();
}
//Initialise the game functions
void Game::Init()
{
	//Load the textures and constructing the player class--|
	PlayerTexture.loadFromFile("assets/images/playerSprites.png");
	ThePlayer = std::make_unique<Player>(PlayerTexture);

	//Loading Enemy Texture----------------------|
	EnemyTexture.loadFromFile("assets/images/enemySprites.png");

	//Loading Enemy Textures------------------|
	ObjectTexture.loadFromFile("assets/images/interactables.png");

	//Load the objects into a list-----------------------|
	for (auto& obj : LevelReader.GetObjectSpawnPositions())
	{
		//If the number of the enum thats in the MapReader is after 1 and after 6, it is a goal object-|
		if ((int)obj.objectType > 1)
		{
			Objects.push_back(std::make_unique<Objective>(obj.objectType, ObjectTexture));
		}
		//Or else it is a point object------------------------------------------------------|
		else
		{
			Objects.push_back(std::make_unique<CollectableObject>(obj.objectType, ObjectTexture));
		}
	}

	//To load the enemys into a list------------------|
	for (auto& x : LevelReader.GetEnemySpawnPositions())
	{
		Enemies.push_back(BadGuy(EnemyTexture));
	}

	//Load the text for the Score and the Lives-|
	MainFont.loadFromFile("assets/fonts/Roboto.ttf");

	ScoreText.setFont(MainFont);
	LivesText.setFont(MainFont);


	LivesText.setString("Lives:" + std::to_string(ThePlayer->GetLives()));
	ScoreText.setString("Score:" + std::to_string(ThePlayer->GetScore()));


	Reset();
}
//Running functions-|
void Game::Run()
{
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	const sf::Time deltaTime = sf::seconds(1.0f / 90.0f);

	while (Window.isOpen())
	{
		sf::Event event;
		while (Window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				Window.close();
			}

			if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::Enter)
				{
					if (GameOver || GameWin)
					{
						Reset();
						GameOver = false;
						GameWin = false;
					}
				}
				//Pause Menu-------------------------------|
				if (event.key.code == sf::Keyboard::Escape)
				{
					if (!Paused)
					{
						Paused = true;
					}
					else
					{
						Paused = false;
					}
				}
			}
		}

		Update(deltaTime.asSeconds());

		Window.clear();
		Draw();

		Window.display();
	}
}

void Game::Update(float deltaTime)
{
	if (!Paused && !GameOver && !GameWin)
	{
		Window.setView(Camera);

		//Update thee player, projectiles, enemies and objects-|
		ThePlayer->Update(deltaTime, LevelReader);

		for (auto& prj : ThePlayer->GetProjectiles())
		{
			//If the projectile hits an object/enemy, it gets removed-|
			if (!prj.isCreated())
			{
				ThePlayer->GetProjectiles().pop_front();
			}
			prj.Update(deltaTime, LevelReader, Enemies, *ThePlayer);
		}

		for (auto& enemy : Enemies)
		{
			enemy.Update(deltaTime, LevelReader, *ThePlayer);
		}

		for (auto& obj : Objects)
		{
			obj->DetectCollision(*ThePlayer, *this);
		}


		UpdateText();
		UpdateCamera();
		CheckGameState();
	}
}

void Game::UpdateText()
{
	//Make sure the text is moving along with the camera while also setting thier position-|
	ScoreText.setPosition(Camera.getCenter().x - 475, Camera.getCenter().y - 475);
	LivesText.setPosition(Camera.getCenter().x - 475, Camera.getCenter().y - 425);

	//Changing the score text-----|
	if (ThePlayer->ScoreChanged())
	{
		ScoreText.setString("Score:" + std::to_string(ThePlayer->GetScore()));
		ThePlayer->SetScoreChanged(false);
	}

	//Changing the lives text-----|
	if (ThePlayer->LivesChanged())
	{
		if (ThePlayer->GetLives() == 0)
		{
			GameOver = true;
		}
		LivesText.setString("Lives:" + std::to_string(ThePlayer->GetLives()));
		ThePlayer->SetPosition(LevelReader.GetPlayerSpawnPosition());
		ThePlayer->SetLivesChanged(false);
		Reset();
	}


}

void Game::UpdateCamera()
{
	//Updating the camera--------------------|
	//The right out of bounds area-----------|
	if (ThePlayer->GetPosition().x >= 5500.f)
	{
		Camera.setCenter(5500.f, 512);
	}
	////The left out of bounds area-----------|
	else if (ThePlayer->GetPosition().x <= 530.f)
	{
		Camera.setCenter(530.f, 512);
	}
	//If the camera is not out of bounds, then follolw the player-------|
	else
	{
		Camera.setCenter(std::floor(ThePlayer->GetPosition().x), 512);
	}

}

void Game::CheckGameState()
{
	//Draw the GameOver menu is the player has died-|
	if (GameOver)
	{
		Menu.SetGameOverScreen();
	}
	//Draw the GameWin menu if the player has won-|
	else if (GameWin)
	{
		Menu.SetWinScreen();
	}
}

void Game::Draw()
{
	//Draw the map and the text-|
	Window.draw(LevelReader);

	Window.draw(LivesText);
	Window.draw(ScoreText);

	//Draw the player, the enemies and the objects-|
	ThePlayer->DrawSprite(Window);

	for (auto& objSprite : Objects)
	{
		objSprite->DrawSprite(Window);
	}

	for (auto& enemy : Enemies)
	{
		enemy.DrawSprite(Window);
	}

	for (auto& prj : ThePlayer->GetProjectiles())
	{
		prj.Draw(Window);
	}

	//Drawing the menus or the pause screens-|
	if (GameWin)
	{
		Window.setView(Camera);
		Menu.DrawMenu(Window);
	}
	else if (Paused)
	{
		DrawPauseText(Window);
	}
	if (GameOver)
	{
		Window.setView(Camera);
		Menu.DrawMenu(Window);
	}
	else if (Paused)
	{
		DrawPauseText(Window);
	}

}
//Drawing the Pause menu text---------------------|
void Game::DrawPauseText(sf::RenderWindow& window)
{
	sf::Text text;
	text.setFillColor(sf::Color::Black);
	text.setFont(MainFont);
	text.setPosition(Camera.getCenter().x - 100, Camera.getCenter().y - 50);
	text.setString("PAUSED");
	window.draw(text);
}

void Game::Reset()
{
	//Resetting the Object------------------|
	for (int i = 0; i < Objects.size(); i++)
	{
		Objects[i]->SetTaken(false);
		Objects[i]->SetPosition(LevelReader.GetObjectSpawnPositions()[i].position);
	}
	//Resetting the Enemy------------------|
	for (int i = 0; i < Enemies.size(); i++)
	{
		Enemies[i].Reset();
		Enemies[i].SetPosition(LevelReader.GetEnemySpawnPositions()[i]);
	}

	//Resetting the Player-|
	if (GameOver)
	{
		ThePlayer->Reset();
		LivesText.setString("Lives:" + std::to_string(ThePlayer->GetLives()));
		ScoreText.setString("Score:" + std::to_string(ThePlayer->GetScore()));
		ThePlayer->SetPosition(LevelReader.GetPlayerSpawnPosition());
	}
	//Resetting the Player-|
	if (GameWin)
	{
		ThePlayer->Reset();
		LivesText.setString("Lives:" + std::to_string(ThePlayer->GetLives()));
		ScoreText.setString("Score:" + std::to_string(ThePlayer->GetScore()));
		ThePlayer->SetPosition(LevelReader.GetPlayerSpawnPosition());
	}

}



