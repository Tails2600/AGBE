#include "include.hpp"
void setdrawcolor_white()
{
SDL_SetRenderDrawColor(renderer,color_white.r,color_white.g,color_white.b,color_white.a);
}
void setdrawcolor_lightgrey()
{
SDL_SetRenderDrawColor(renderer,color_lightgrey.r,color_lightgrey.g,color_lightgrey.b,color_lightgrey.a);
}
void setdrawcolor_darkgrey()
{
SDL_SetRenderDrawColor(renderer,color_darkgrey.r,color_darkgrey.g,color_darkgrey.b,color_darkgrey.a);
}
void setdrawcolor_black()
{
SDL_SetRenderDrawColor(renderer,color_black.r,color_black.g,color_black.b,color_black.a);
}
int compare_pixels(int bitset_id)
{
    if (MEMVRAMbitbuffer[bitset_id] == 0 && MEMVRAMbitbuffer2[bitset_id] == 0)
    {
    compare_pixels_result = 0;
    setdrawcolor_white();
    }
    if (MEMVRAMbitbuffer[bitset_id] == 0 && MEMVRAMbitbuffer2[bitset_id] == 1)
    {
    compare_pixels_result = 1;
    setdrawcolor_lightgrey();
    }
    if (MEMVRAMbitbuffer[bitset_id] == 1 && MEMVRAMbitbuffer2[bitset_id] == 0)
    {
    compare_pixels_result = 2;
    setdrawcolor_darkgrey();
    }
    if (MEMVRAMbitbuffer[bitset_id] == 1 && MEMVRAMbitbuffer2[bitset_id] == 1)
    {
    compare_pixels_result = 3;
    setdrawcolor_black();
    }
}


void RenderFrame()
{
setdrawcolor_lightgrey();
SDL_RenderClear(renderer);
current_x_pixel = 0;
current_y_pixel = 0;
bitset_id_counter = 7;
current_tile_location = 0x97FF;
current_drawing_x_tile = 0x00;
current_drawing_y_tile = 0x00;


rendernextthing:
current_tile_location++;
current_tile = memory[current_tile_location];
current_tile_data_location = (0x8000 + (current_tile * 10));
MEMVRAMbitbuffer = memory[current_tile_data_location];
MEMVRAMbitbuffer2 = memory[current_tile_data_location + 1];
rendernextpixel:
compare_pixels(bitset_id_counter);
SDL_RenderDrawPoint(renderer,current_x_pixel,current_y_pixel);
current_x_pixel++;
bitset_id_counter--;
if (current_x_pixel > 7)
{
current_x_pixel = 0;
current_y_pixel++;
bitset_id_counter = 0x07;
if (current_y_pixel > 7)
{
current_drawing_x_tile++;
if (current_drawing_x_tile > 20)
{
current_drawing_x_tile = 0;
current_drawing_y_tile++;
if (current_drawing_y_tile > 18)
{
goto donerenderingframe;
}
goto rendernextthing;
}
goto rendernextthing;
}
goto rendernextpixel;

}


goto rendernextpixel;





donerenderingframe:
SDL_RenderPresent(renderer);
}
