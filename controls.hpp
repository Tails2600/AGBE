#include <SDL2/SDL.h>
#include "interupts.hpp"

void handle_controls()
{

    switch( SDL_EVENT_HANDLING.key.keysym.sym )
    {
        case SDLK_UP:
            // Handle Up
            memory[0xFF00] = memory[0xFF00] + 0x40;
        break;

        case SDLK_DOWN:
            // Handle Down
            memory[0xFF00] = memory[0xFF00] + 0x80;
        break;

        case SDLK_LEFT:
            // Handle Left
            memory[0xFF00] = memory[0xFF00] + 0x20;
        break;

        case SDLK_RIGHT:
            // Handle Right
            memory[0xFF00] = memory[0xFF00] + 0x10;
        break;

        case SDLK_z:
            // Handle B
            memory[0xFF00] = memory[0xFF00] + 0x02;
        break;

        case SDLK_x:
            // Handle A
            memory[0xFF00] = memory[0xFF00] + 0x01;
        break;

        case SDLK_o:
            mode0x8800 = false;
        break;

        case SDLK_p:
            mode0x8800 = true;
        break;

        case SDLK_RETURN:
            // Handle Start
            memory[0xFF00] = memory[0xFF00] + 0x08;
        break;

        case SDLK_SPACE: // This is currently being used as a way to exit the program.
            // Handle Select
            //memory[0xFF00] = memory[0xFF00] + 0x04;
            printf("\npc: 0x%X",pc);
            printf("\nop: 0x%X",opcode);
            printf("\naf: 0x%X%X",af[0],af[1]);
            printf("\nbc: 0x%X%X",bc[0],bc[1]);
            printf("\nde: 0x%X%X",de[0],de[1]);
            printf("\nhl: 0x%X%X",hl[0],hl[1]);
            printf("\nsp: 0x%X%X",sp[0],sp[1]);
            printf("\ncycles: %i",cycles);
            close_program = true;
        break;

        case SDLK_l:
        break;
    } // End of Switch Case



}
