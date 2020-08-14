#pragma once
#include <SFML/Graphics.hpp>

class Menu
{
public:
	Menu(sf::RenderWindow& window, std::string input);
	void SetWinScreen();
	void SetGameOverScreen();
	void DrawMenu(sf::RenderWindow& window);

private:
	//Font & Text & Bakground-|
	sf::Font Font;
	sf::RectangleShape BackgroundShape;
	sf::Text FirstLineText;
	sf::Text SecondLineText;
};