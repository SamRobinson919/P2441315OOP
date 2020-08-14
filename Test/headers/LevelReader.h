#pragma once
#include <fstream>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <string>

#include "Object.h"
#include "ObjectTypes.h"


class Tile;

struct ObjectPos
{
	sf::Vector2f position;
	Type objectType;

	ObjectPos(sf::Vector2f position, Type type) : position(position), objectType(type) {}
};


class LevelReader : public sf::Transformable, public sf::Drawable
{
public:
	LevelReader(std::string levelTextFile);

	std::vector<Tile>& GetLevelTiles() {
		return TileMap;
	}

	int GetTileWidth() {
		return TileWidth;
	}

	int GetTileHeight() {
		return TileHeight;
	}

	sf::Vector2f& GetPlayerSpawnPosition() {
		return PlayerSpawnPosition;
	}

	std::vector<ObjectPos>& GetObjectSpawnPositions() {
		return ObjectPositions;
	}

	std::vector<sf::Vector2f>& GetEnemySpawnPositions() {
		return EnemySpawnPositions;
	}


private:

	void LoadFile(std::string levelTextFile);
	sf::VertexArray SetLevel();
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

private:
	std::vector<Tile> TileMap;
	std::ifstream levelFile;
	std::string level;
	sf::VertexArray vertices;
	sf::Texture tileset;
	const int levelWidth;
	const int levelHeight;
	const int TileHeight;
	const int TileWidth;

	sf::Vector2f PlayerSpawnPosition;
	std::vector<ObjectPos> ObjectPositions;
	std::vector<sf::Vector2f> EnemySpawnPositions;




};

