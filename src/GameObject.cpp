#include "GameObject.h"
#include "TextureManager.h"

GameObject::GameObject(const char* textureSheet, int x, int y, int imgH, int imgW)
{
	objectTexture = TextureManager::LoadTexture(textureSheet);

	xpos = x;
	ypos = y;
	srcRect.h = imgH;
	srcRect.w = imgW;
}

void GameObject::Update()
{
	xpos++;
	ypos++;

	//srcRect.h = 561;
	//srcRect.w = 560;
	srcRect.x = 0;
	srcRect.y = 0;

	destRect.x = xpos;
	destRect.y = ypos;
	destRect.w = 128;
	destRect.h = 128;
}

void GameObject::Render()
{
	SDL_RenderCopy(Game::renderer, objectTexture, &srcRect, &destRect);
}