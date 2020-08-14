#include "headers/LevelReader.h"
#include "headers/ObjectTypes.h"
#include "headers/Tile.h"


LevelReader::LevelReader(std::string levelTextFile) :
	TileMap({}), levelFile(), level(""), vertices(), tileset(),
	levelWidth(192), levelHeight(32), TileHeight(32), TileWidth(32),
	PlayerSpawnPosition(), ObjectPositions()
{
	LoadFile(levelTextFile);
}

void LevelReader::LoadFile(std::string levelTextFile)
{
	//Opening file----------------|
	levelFile.open(levelTextFile);

	if (levelFile.is_open())
	{
		// Get each character and write it to a string that will become the level-|
		char character;
		while (levelFile.get(character))
		{
			if (character != '\n')
			{
				level += character;
			}
		}
	}

	levelFile.close();
	SetLevel();
}

sf::VertexArray LevelReader::SetLevel()
{
	//Setting texture-|
	tileset.loadFromFile("assets/images/blocks.png");

	//Size the vertex array to fit all the quads into the array-|
	vertices.setPrimitiveType(sf::Quads);
	vertices.resize(levelWidth * levelHeight * 4);

	for (int i = 0; i < levelWidth; i++)
	{
		for (int j = 0; j < levelHeight; j++)
		{
			//Get the number/symbol representing the texture from the level string-|
			int tileNumber = level[i + j * levelWidth] - '0';

			switch (tileNumber)
			{
			case 5:
				PlayerSpawnPosition = sf::Vector2f(i * TileWidth, j * TileHeight);
				tileNumber = 2;
				break;
			case 6:
				ObjectPositions.push_back(ObjectPos(sf::Vector2f(i * TileWidth, j * TileHeight), Type::Coin));
				tileNumber = 2;
				break;
			case 7:
				ObjectPositions.push_back(ObjectPos(sf::Vector2f(i * TileWidth, j * TileHeight), Type::Trophy));
				tileNumber = 2;
				break;
			case 8:
				ObjectPositions.push_back(ObjectPos(sf::Vector2f(i * TileWidth, j * TileHeight), Type::Pillar));
				tileNumber = 2;
				break;
			case 9:
				ObjectPositions.push_back(ObjectPos(sf::Vector2f(i * TileWidth, j * TileHeight), Type::Bike));
				tileNumber = 2;
				break;
			case 72:
				EnemySpawnPositions.push_back(sf::Vector2f(i * TileWidth, j * TileHeight));
				tileNumber = 2;
				break;
			}



			// find the texture based off tileNumber in the tileset texture
			int tu = tileNumber % (tileset.getSize().x / TileWidth);
			int tv = tileNumber / (tileset.getSize().x / TileWidth);


			// Pointer to the current tile's quad
			sf::Vertex* quad = &vertices[(i + j * levelWidth) * 4];

			// define its 4 corners
			quad[0].position = sf::Vector2f(i * TileWidth, j * TileHeight);
			quad[1].position = sf::Vector2f((i + 1) * TileWidth, j * TileHeight);
			quad[2].position = sf::Vector2f((i + 1) * TileWidth, (j + 1) * TileHeight);
			quad[3].position = sf::Vector2f(i * TileWidth, (j + 1) * TileHeight);

			// define its 4 texture coordinates
			quad[0].texCoords = sf::Vector2f(tu * TileWidth, tv * TileHeight);
			quad[1].texCoords = sf::Vector2f((tu + 1) * TileWidth, tv * TileHeight);
			quad[2].texCoords = sf::Vector2f((tu + 1) * TileWidth, (tv + 1) * TileHeight);
			quad[3].texCoords = sf::Vector2f(tu * TileWidth, (tv + 1) * TileHeight);

			Tile tile;
			tile.tile = *quad;
			tile.type = tileNumber;

			tile.collisionBox = sf::FloatRect(tile.tile.position.x, tile.tile.position.y, TileWidth, TileHeight);

			if (tile.type == 0 || tile.type == 1)
			{
				tile.passable = false;
			}
			else if (tile.type == 3)
			{
				tile.passable = true;
				tile.killTile = true;
			}
			else
			{
				tile.passable = true;
			}

			TileMap.push_back(tile);

		}

	}
	return vertices;
}

void LevelReader::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	// apply the transform
	states.transform *= getTransform();

	// apply the tileset texture
	states.texture = &tileset;

	// draw the vertex array
	target.draw(vertices, states);
}

