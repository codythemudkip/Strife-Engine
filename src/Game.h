#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <vector>

class ColliderComponent;

class Game
{
public:
	Game();
	~Game();

	void Init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen, bool splashScreen = true);
	void SplashScreen(bool show);

	void HandleEvents();
	void Update();
	bool running() { return isRunning; };
	void Render();
	void Clean();

	static void AddTile(int id, int x, int y);

	static SDL_Renderer* renderer;
	static SDL_Event event;
	static std::vector<ColliderComponent*> colliders;

private:
	int cnt = 0;
	bool isRunning;
	SDL_Window* window;
};

