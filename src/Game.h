#pragma once
#include <SDL.h>
#include <SDL_image.h>

class Game
{
public:
	Game();
	~Game();

	void Init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);

	void HandleEvents();
	void Update();
	bool running() { return isRunning; };
	void Render();
	void Clean();

	static SDL_Renderer* renderer;
	static SDL_Event event;

private:
	int cnt = 0;
	bool isRunning;
	SDL_Window* window;
};

