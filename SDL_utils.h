#ifndef SDL_utils_h
#define SDL_utils_h

#include <iostream>
#include <string>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <windows.h>

using namespace std;

#define SCREEN_WIDTH 900 
#define SCREEN_HEIGHT 700

void initSDL(SDL_Window* &window, SDL_Renderer* &renderer);
void quitSDL(SDL_Window* win, SDL_Renderer* ren);
SDL_Texture* loadTexture(string path, SDL_Renderer* renderer);

#endif