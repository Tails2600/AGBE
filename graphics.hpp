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
int compare_pixels() // MAKE SURE BITSET_ID_COUNTER IS SET CORRECTLY BEFORE USING THIS.
{
if (MEMVRAMbitbuffer[bitset_id_counter] == 0 && MEMVRAMbitbuffer2[bitset_id_counter] == 0)
{
setdrawcolor_white();
compare_pixels_result = 0;
printf("white\n");
}
if (MEMVRAMbitbuffer[bitset_id_counter] == 0 && MEMVRAMbitbuffer2[bitset_id_counter == 1])
{
setdrawcolor_lightgrey();
compare_pixels_result = 1;
printf("lightgrey\n");
}
if (MEMVRAMbitbuffer[bitset_id_counter] == 1 && MEMVRAMbitbuffer2[bitset_id_counter] == 0)
{
setdrawcolor_darkgrey();
compare_pixels_result = 2;
printf("darkgrey\n");
}
if (MEMVRAMbitbuffer[bitset_id_counter] == 1 && MEMVRAMbitbuffer2[bitset_id_counter] == 1)
{
setdrawcolor_black();
compare_pixels_result = 3;
printf("black\n");
}

}

void RenderFrame()
{
current_x_pixel = 0;
current_y_pixel = 0;
bitset_id_counter = 7;
current_tile_data_location = 0x8270;




rendernewpixel:
MEMVRAMbitbuffer = memory[current_tile_data_location];
MEMVRAMbitbuffer2 = memory[current_tile_data_location + 1];
printf("memvram1: 0x%X",MEMVRAMbitbuffer);
printf("memvram2: 0x%X",MEMVRAMbitbuffer2);





compare_pixels();
SDL_RenderDrawPoint(renderer,current_x_pixel,current_y_pixel);
current_x_pixel++;
bitset_id_counter--;
if (current_x_pixel % 8 == 0) // Done Drawing Line
{
current_x_pixel -= 8;
bitset_id_counter = 7;
current_y_pixel++;
current_tile_data_location += 0x02;
    if (current_y_pixel % 8 == 0) // Done Drawing Tile
    {
    goto donerendering;
    }


}
SDL_RenderPresent(renderer);
goto rendernewpixel;





donerendering:
SDL_RenderPresent(renderer);
}
