#include "render.h"
#define _USE_MATH_DEFINES
#include <cmath>
#include <vector>
#include "../util/env.h"

#if SDL_BYTEORDER == SDL_BIG_ENDIAN
Uint32 rmask = 0xff000000;
Uint32 gmask = 0x00ff0000;
Uint32 bmask = 0x0000ff00;
Uint32 amask = 0x000000ff;
#else
Uint32 rmask = 0x000000ff;
Uint32 gmask = 0x0000ff00;
Uint32 bmask = 0x00ff0000;
Uint32 amask = 0xff000000;
#endif

SDL_Texture* GenerateTextureLines(SDL_Renderer* renderer, SDL_Rect bounds, std::vector<SDL_Point> *points, SDL_Color fg , SDL_Colour bg)
{
    //Check if the Ship can be pre-rendered and saved as texture
    SDL_Surface* surface = SDL_CreateRGBSurface(0, bounds.w, bounds.h, 32,
                           rmask, gmask, bmask, amask);

    //Create a software Render with target of surface
    SDL_Renderer* swRender = SDL_CreateSoftwareRenderer(surface);

    //Set Render colour before cleaning
    SDL_SetRenderDrawColor ( swRender , bg.r , bg.g , bg.b , bg.a);

    //Clean the render target
    SDL_RenderClear ( swRender );

    //Set Ship Colour
    SDL_SetRenderDrawColor ( swRender , fg.r , fg.g , fg.b , fg.a);

    //Render to the Render target
    SDL_RenderDrawLines(swRender , &( (*points)[0]) , (*points).size());

    //Convert the surface to a texture, needs main renderer
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer , surface);

    //Delete render
    SDL_DestroyRenderer(swRender);

    //Free surface
    SDL_FreeSurface(surface);

    return texture;
}

SDL_Texture* GenerateTexturePoints(SDL_Renderer* renderer, SDL_Rect bounds, std::vector<SDL_Point> *points, SDL_Color fg , SDL_Colour bg)
{
    //Check if the Ship can be pre-rendered and saved as texture
    SDL_Surface* surface = SDL_CreateRGBSurface(0, bounds.w, bounds.h, 32,
                           rmask, gmask, bmask, amask);

    //Create a software Render with target of surface
    SDL_Renderer* swRender = SDL_CreateSoftwareRenderer(surface);

    //Set Render colour before cleaning
    SDL_SetRenderDrawColor ( swRender , bg.r , bg.g , bg.b , bg.a);

    //Clean the render target
    SDL_RenderClear ( swRender );

    //Set Ship Colour
    SDL_SetRenderDrawColor ( swRender , fg.r , fg.g , fg.b , fg.a);

    //Render to the Render target
    SDL_RenderDrawPoints(swRender , &( (*points)[0]) , (*points).size());

    //Convert the surface to a texture, needs main renderer
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer , surface);

    //Delete render
    SDL_DestroyRenderer(swRender);

    //Free surface
    SDL_FreeSurface(surface);

    return texture;
}
