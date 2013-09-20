#ifndef H_RENDER_
#define H_RENDER_

#include "SDL2/SDL.h"
#include "../util/Point.h"
#include <vector>

SDL_Texture* GenerateTextureLines  (SDL_Renderer* renderer, SDL_Rect bounds, std::vector<SDL_Point> *points, SDL_Color fg , SDL_Colour bg);
SDL_Texture* GenerateTexturePoints (SDL_Renderer* renderer, SDL_Rect bounds, std::vector<SDL_Point> *points, SDL_Color fg , SDL_Colour bg);
#endif
