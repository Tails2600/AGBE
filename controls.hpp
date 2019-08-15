#include <SDL2/SDL.h>
#include "interupts.hpp"

void handle_controls()
{
memory[0xFF98] = 0x00;
switch( SDL_EVENT_HANDLING.key.keysym.sym )
{
case SDLK_UP:
// Handle Up
memory[0xFF98] = memory[0xFF98] + 0x40;
break;

case SDLK_DOWN:
// Handle Down
memory[0xFF98] = memory[0xFF98] + 0x80;
break;

case SDLK_LEFT:
// Handle Left
memory[0xFF98] = memory[0xFF98] + 0x20;
break;

case SDLK_RIGHT:
// Handle Right
memory[0xFF98] = memory[0xFF98] + 0x10;
break;

case SDLK_z:
// Handle B
memory[0xFF98] = memory[0xFF98] + 0x02;
break;

case SDLK_x:
// Handle A
memory[0xFF98] = memory[0xFF98] + 0x01;
break;

case SDLK_RETURN:
// Handle Start
memory[0xFF98] = memory[0xFF98] + 0x08;
break;

case SDLK_SPACE: // This is currently being used as a way to exit the program.
// Handle Select
//memory[0xFF98] = memory[0xFF98] + 0x04;
close_program = true;
break;

}



}
