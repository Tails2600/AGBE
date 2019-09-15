#include <SDL2/SDL.h>
#include "interupts.hpp"

int handle_controls3()
{
    switch( SDL_EVENT_HANDLING.key.keysym.sym )
        {
        case SDLK_o:
            mode0x8800 = false;
        break;

        case SDLK_p:
            mode0x8800 = true;
        break;


        case SDLK_SPACE: // This is currently being used as a way to exit the program.
            //memory[0xFF00] = memory[0xFF00] + 0x04;
            printf("\npc: 0x%X",pc);
            printf("\nop: 0x%X",opcode);
            printf("\naf: 0x%X%X",af[0],af[1]);
            printf("\nbc: 0x%X%X",bc[0],bc[1]);
            printf("\nde: 0x%X%X",de[0],de[1]);
            printf("\nhl: 0x%X%X",hl[0],hl[1]);
            printf("\nsp: 0x%X%X",sp[0],sp[1]);
            printf("\ncycles: %i",cycles);
            printf("\njoypad: 0x%X",memory[0xFF00]);
            close_program = true;
        break;

        }
}

int handle_controls2()
{
    MEMbitbuffer = memory[0xFF00];
    MEMbitbuffer[0] = 1;
    MEMbitbuffer[1] = 1;
    MEMbitbuffer[2] = 1;
    MEMbitbuffer[3] = 1;
    memory[0xFF00] = MEMbitbuffer.to_ulong();
}

int handle_controls()
{
    if(memory[0xFF00] == 0x10) // P14
    {
        memory[0xFF00] = 0xDF;
    }
    if(memory[0xFF00] == 0x20) // P15
    {
        memory[0xFF00] = 0xEF;
    }
    if(memory[0xFF00] == 0x30) // Disable P14 and P15
    {
        memory[0xFF00] = 0xCF;
    }
    //printf("FF00: 0x%X\n",(memory[0xFF00] - 0xFFFFFF00));
    MEMbitbuffer = memory[0xFF00];
    MEMbitbuffer[7] = 1;
    MEMbitbuffer[6] = 1;
    MEMbitbuffer[3] = 1;
    MEMbitbuffer[2] = 1;
    MEMbitbuffer[1] = 1;
    MEMbitbuffer[0] = 1;
    memory[0xFF00] = MEMbitbuffer.to_ulong();


        MEMbitbuffer = memory[0xFF00];
        switch( SDL_EVENT_HANDLING.key.keysym.sym )
        {

        case SDLK_UP: // Up

            if(MEMbitbuffer[4] == 0)
            {
                if(SDL_EVENT_HANDLING.type == SDL_KEYDOWN)
                {
                MEMbitbuffer[2] = 0;
                }
                if(SDL_EVENT_HANDLING.type == SDL_KEYUP)
                {
                MEMbitbuffer[2] = 1;
                }
            }
        break;

        case SDLK_DOWN:
            // Handle Down
            if(MEMbitbuffer[4] == 0)
            {
                if(SDL_EVENT_HANDLING.type == SDL_KEYDOWN)
                {
                MEMbitbuffer[3] = 0;
                }
                if(SDL_EVENT_HANDLING.type == SDL_KEYUP)
                {
                MEMbitbuffer[3] = 1;
                }
            }
        break;

        case SDLK_LEFT:
            // Handle Left
            if(MEMbitbuffer[4] == 0)
            {
                if(SDL_EVENT_HANDLING.type == SDL_KEYDOWN)
                {
                MEMbitbuffer[1] = 0;
                }
                if(SDL_EVENT_HANDLING.type == SDL_KEYUP)
                {
                MEMbitbuffer[1] = 1;
                }
            }
        break;

        case SDLK_RIGHT:
            // Handle Right
            if(MEMbitbuffer[4] == 0)
            {
                if(SDL_EVENT_HANDLING.type == SDL_KEYDOWN)
                {
                MEMbitbuffer[0] = 0;
                }
                if(SDL_EVENT_HANDLING.type == SDL_KEYUP)
                {
                MEMbitbuffer[0] = 1;
                }
            }
        break;

        case SDLK_LCTRL:
            // Handle B
            if(MEMbitbuffer[5] == 0)
            {
                if(SDL_EVENT_HANDLING.type == SDL_KEYDOWN)
                {
                MEMbitbuffer[1] = 0;
                }
                if(SDL_EVENT_HANDLING.type == SDL_KEYUP)
                {
                MEMbitbuffer[1] = 1;
                }
            }
        break;

        case SDLK_LALT:
            // Handle A
            if(MEMbitbuffer[5] == 0)
            {
                if(SDL_EVENT_HANDLING.type == SDL_KEYDOWN)
                {
                MEMbitbuffer[0] = 0;
                }
                if(SDL_EVENT_HANDLING.type == SDL_KEYUP)
                {
                MEMbitbuffer[0] = 1;
                }
            }
        break;

        case SDLK_RETURN:
            // Handle Start
            if(MEMbitbuffer[5] == 0)
            {
                if(SDL_EVENT_HANDLING.type == SDL_KEYDOWN)
                {
                MEMbitbuffer[3] = 0;
                }
                if(SDL_EVENT_HANDLING.type == SDL_KEYUP)
                {
                MEMbitbuffer[3] = 1;
                }
            }
        break;

        case SDLK_BACKSPACE:
            // Handle Select
            if(MEMbitbuffer[5] == 0)
            {
                if(SDL_EVENT_HANDLING.type == SDL_KEYDOWN)
                {
                MEMbitbuffer[2] = 0;
                }
                if(SDL_EVENT_HANDLING.type == SDL_KEYUP)
                {
                MEMbitbuffer[2] = 1;
                }
            }
        break;

        }// End of Switch Case

    memory[0xFF00] = MEMbitbuffer.to_ulong();
}
