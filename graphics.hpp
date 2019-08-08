#include "include.hpp"
void RenderFrame()
{
SDL_SetRenderDrawColor(renderer,255,0,0,255);
SDL_RenderClear(renderer);
SDL_SetRenderDrawColor(renderer,0,255,0,255);
SDL_RenderDrawPoint(renderer,100,100);
SDL_RenderPresent(renderer);
}
