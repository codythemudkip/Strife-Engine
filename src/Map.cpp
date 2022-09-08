#include "Map.h"
#include "TextureManager.h"

int lvl1[5][10] = {
	{0,0,0,0,0},
	{0,0,0,0,0},
	{0,0,0,0,0},
	{0,0,0,0,0},
	{0,0,0,0,0},
};

Map::Map()
{
	dirt = TextureManager::LoadTexture("Assets/Sprites/Tiles/dirt.png");
	grass = TextureManager::LoadTexture("Assets/Sprites/Tiles/grass.png");
	water = TextureManager::LoadTexture("Assets/Sprites/Tiles/water.png");

	LoadMap(lvl1);

	src.x = src.y = 0;
	src.w = dest.w = 32;
	src.h = dest.h = 32;

	dest.x = dest.y = 0;
}

Map::~Map()
{
	SDL_DestroyTexture(grass);
	SDL_DestroyTexture(water);
	SDL_DestroyTexture(dirt);
}

void Map::LoadMap(int arr[5][10])
{
	for (int row = 4; row < 5; row++)
	{
		for (int column = 0; column < 10; column++)
		{
			map[row][column] = arr[row][column];
		}
	}
}

void Map::DrawMap()
{
	int type = 0;

	for (int row = 4; row < 5; row++)
	{
		for (int column = 0; column < 10; column++)
		{
			type = map[row][column];

			dest.x = column * 32;
			dest.y = row * 32;

			switch (type)
			{
			case 0:
				TextureManager::Draw(water, src, dest);
				break;
			case 1:
				TextureManager::Draw(grass, src, dest);
				break;
			case 2:
				TextureManager::Draw(dirt, src, dest);
				break;
			default:
				break;
			}
		}
	}
}