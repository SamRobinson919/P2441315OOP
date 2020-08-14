#include "headers/Menu.h"

Menu::Menu(sf::RenderWindow& window, std::string input) : Font(), BackgroundShape(), FirstLineText(), SecondLineText()
{
	//Put the all the texts in the correct places
	FirstLineText.setPosition((window.getView().getSize().x / 2.5f),
		(window.getView().getSize().y / 3.f));


	SecondLineText.setPosition((window.getView().getSize().x / 3.f),
		(window.getView().getSize().y / 2.f));

	//Make the backing of the menu Dark blue (SeeThrough)-------|
	BackgroundShape.setFillColor(sf::Color(12, 0, 127, 255));
	BackgroundShape.setSize(window.getView().getSize() * 10.0f);

	//Load and Set-----------|
	Font.loadFromFile(input);
	FirstLineText.setFont(Font);
	SecondLineText.setFont(Font);
}

//Setting the GameOver Screen Text-|
void Menu::SetGameOverScreen()
{
	//Added spaces below in text due to when dying text would always push to the far lefts off screen, due to the small size-|
	FirstLineText.setString("      Game Over Loser");
	SecondLineText.setString("       To play again Press Enter");
}

//Setting the Win Screen Text-|
void Menu::SetWinScreen()
{
	FirstLineText.setString("Well done Champ!");
	SecondLineText.setString("  To play again Press Enter");
}

//Drawing the Menus--------------------------|
void Menu::DrawMenu(sf::RenderWindow& window)
{
	window.draw(BackgroundShape);
	window.draw(FirstLineText);
	window.draw(SecondLineText);
}
