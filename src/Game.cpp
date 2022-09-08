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

auto& player(manager.addEntity());
auto& wall(manager.addEntity());

Game::Game()
{}
Game::~Game()
{}

void Game::Init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen)
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
		
		player.addComponent<TransformComponent>();
		player.addComponent<SpriteComponent>("Assets/Sprites/UI/biscuit.png");
		player.addComponent<KeyboardController>();
		player.addComponent<ColliderComponent>("Player");

		wall.addComponent<TransformComponent>(300.0f, 300.0f, 300, 20, 1);
		wall.addComponent<SpriteComponent>("Assets/Sprites/UI/zero.png");
		wall.addComponent<ColliderComponent>("wall");
	}
	else {
		isRunning = false;
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

	if (Collision::AABB(player.getComponent<ColliderComponent>().collider, wall.getComponent<ColliderComponent>().collider))
	{
		player.getComponent<TransformComponent>().velocity * -1;
		std::cout << "Wall hit" << std::endl;
	}
}

void Game::Render()
{
	SDL_RenderClear(renderer);
	map->DrawMap();
	manager.draw();
	SDL_RenderPresent(renderer);
}

void Game::Clean()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
}