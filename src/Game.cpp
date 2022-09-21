#include "Game.h"
#include "TextureManager.h"
#include "Map.h"
#include "ECS/Components.h"
#include "Collision.h"
#include <iostream>

Map* map;
Manager manager;

SDL_Renderer* Game::renderer = nullptr;
SDL_Event Game::event;

std::vector<ColliderComponent*> Game::colliders;

auto& player(manager.addEntity());
auto& wall(manager.addEntity());

Game::Game()
{}
Game::~Game()
{}

void Game::Init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen, bool splashScreen)
{
	int flags = 0;
	if (fullscreen)
	{
		flags = SDL_WINDOW_FULLSCREEN;
	}

	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
		renderer = SDL_CreateRenderer(window, -1, 0);
		if (renderer)
		{
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		}

		isRunning = true;

		// game object stuff

		map = new Map();

		Map::LoadMap("Assets/TileMaps/test.map", 16, 16);

		player.addComponent<TransformComponent>();
		player.addComponent<SpriteComponent>("Assets/Sprites/UI/biscuit.png");
		player.addComponent<KeyboardController>();
		player.addComponent<ColliderComponent>("Player");

		wall.addComponent<TransformComponent>(300.0f, 300.0f, 300, 20, 1);
		wall.addComponent<SpriteComponent>("Assets/Sprites/UI/zero.png");
		wall.addComponent<ColliderComponent>("wall");

		Game::SplashScreen(splashScreen);
	}
	else {
		isRunning = false;
	}
}

void Game::SplashScreen(bool show)
{
	if (show)
	{
		auto& StrifeLogo(manager.addEntity());
		StrifeLogo.addComponent<TransformComponent>(320.0f - 147.0f, 240.0f - 102.0f, 294.0f, 204.0f, 1);
		StrifeLogo.addComponent<SpriteComponent>("./StrifeEngineLogo.png");

	}
}

void Game::HandleEvents()
{
	SDL_PollEvent(&event);
	switch (event.type) {
		case SDL_QUIT:
			isRunning = false;
			break;

		default:
			break;
	}
}

void Game::Update()
{
	manager.refresh();
	manager.update();

	for (auto cc : colliders)
	{
		Collision::AABB(player.getComponent<ColliderComponent>(), *cc);
	}
	
}

void Game::Render()
{
	SDL_RenderClear(renderer);
	//map->DrawMap();
	manager.draw();
	SDL_RenderPresent(renderer);
}

void Game::Clean()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
}

void Game::AddTile(int id, int x, int y)
{
	auto& tile(manager.addEntity());
	tile.addComponent<TileComponent>(x, y, 32, 32, id);
}