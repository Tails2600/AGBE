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
}
if (MEMVRAMbitbuffer[bitset_id_counter] == 0 && MEMVRAMbitbuffer2[bitset_id_counter == 1])
{
setdrawcolor_lightgrey();
compare_pixels_result = 1;
}
if (MEMVRAMbitbuffer[bitset_id_counter] == 1 && MEMVRAMbitbuffer2[bitset_id_counter] == 0)
{
setdrawcolor_darkgrey();
compare_pixels_result = 2;
}
if (MEMVRAMbitbuffer[bitset_id_counter] == 1 && MEMVRAMbitbuffer2[bitset_id_counter] == 1)
{
setdrawcolor_black();
compare_pixels_result = 3;
}

}
void RenderTile(int xtile, int ytile)
{
current_x_pixel = 8 * xtile;
bitset_id_counter = 7;
current_y_pixel = 8 * ytile;
current_tile_location = (0x9800 + (xtile * 0x01) + (ytile * 0x20));
if
(
current_tile_location == 0x9814 ||
current_tile_location == 0x9834 ||
current_tile_location == 0x9854 ||
current_tile_location == 0x9874 ||
current_tile_location == 0x9894 ||
current_tile_location == 0x98B4 ||
current_tile_location == 0x98D4 ||
current_tile_location == 0x98F4 ||
current_tile_location == 0x9914 ||
current_tile_location == 0x9934 ||
current_tile_location == 0x9954 ||
current_tile_location == 0x9974 ||
current_tile_location == 0x9994 ||
current_tile_location == 0x99B4 ||
current_tile_location == 0x99D4 ||
current_tile_location == 0x99F4 ||
current_tile_location == 0x9A14 ||
current_tile_location == 0x9A34
)
{
current_tile_location == current_tile_location + 12;
}
current_tile = memory[current_tile_location];
if(current_tile > 0xFF)
{
help0x9000Render = true;
}
if(mode0x8800 == false)
{
goto no0x8800;
}
if(mode0x8800 == true)
{
    if(current_tile > 0x7F)
    {
    current_tile_data_location = (0x8000 + ((current_tile - 0xFFFFFF00) * 0x10));
    }
    if(current_tile <= 0x7F)
    {
    current_tile_data_location = (0x9000 + ((current_tile - 0xFFFFFF00) * 0x10));
    }
goto donetest0x8800;
}
no0x8800:
current_tile_data_location = (0x8000 + ((current_tile - 0xFFFFFF00) * 0x10));

donetest0x8800:
if(current_tile_data_location > 0x9000 && help0x9000Render == true)
{
current_tile_data_location -= 0x1000;
}
rendernewpixel:
MEMVRAMbitbuffer = memory[current_tile_data_location];
MEMVRAMbitbuffer2 = memory[current_tile_data_location + 1];
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
    goto donerenderingtile;
    }
}
goto rendernewpixel;
donerenderingtile:
dummyvalue++; // This is just here so the compiler doesn't complain about the last function being a goto related thing.
}

void RenderFrame()
{
current_x_tile = 0;
current_y_tile = 0;
renderNextTile:
if (current_x_tile < 21)
{
RenderTile(current_x_tile,current_y_tile);
current_x_tile++;
    if (current_y_tile == 19)
    {
    goto doneRenderingFrame;
    }
goto renderNextTile;
}
if (current_x_tile == 21)
{
current_y_tile++;
current_x_tile = 0;
goto renderNextTile;
}
doneRenderingFrame:
SDL_RenderPresent(renderer);
}

void setdrawcolor_VRAMwhite()
{
SDL_SetRenderDrawColor(VRAM_renderer,color_white.r,color_white.g,color_white.b,color_white.a);
}
void setdrawcolor_VRAMlightgrey()
{
SDL_SetRenderDrawColor(VRAM_renderer,color_lightgrey.r,color_lightgrey.g,color_lightgrey.b,color_lightgrey.a);
}
void setdrawcolor_VRAMdarkgrey()
{
SDL_SetRenderDrawColor(VRAM_renderer,color_darkgrey.r,color_darkgrey.g,color_darkgrey.b,color_darkgrey.a);
}
void setdrawcolor_VRAMblack()
{
SDL_SetRenderDrawColor(VRAM_renderer,color_black.r,color_black.g,color_black.b,color_black.a);
}

int compare_VRAMpixels() // MAKE SURE BITSET_ID_COUNTER IS SET CORRECTLY BEFORE USING THIS.
{
if (MEMVRAMbitbuffer[bitset_id_counter] == 0 && MEMVRAMbitbuffer2[bitset_id_counter] == 0)
{
setdrawcolor_VRAMwhite();
compare_pixels_result = 0;
}
if (MEMVRAMbitbuffer[bitset_id_counter] == 0 && MEMVRAMbitbuffer2[bitset_id_counter == 1])
{
setdrawcolor_VRAMlightgrey();
compare_pixels_result = 1;
}
if (MEMVRAMbitbuffer[bitset_id_counter] == 1 && MEMVRAMbitbuffer2[bitset_id_counter] == 0)
{
setdrawcolor_VRAMdarkgrey();
compare_pixels_result = 2;
}
if (MEMVRAMbitbuffer[bitset_id_counter] == 1 && MEMVRAMbitbuffer2[bitset_id_counter] == 1)
{
setdrawcolor_VRAMblack();
compare_pixels_result = 3;
}

}

void RenderVRAMTile(int xtile, int ytile)
{
current_x_pixel = 8 * xtile;
bitset_id_counter = 7;
current_y_pixel = 8 * ytile;

current_tile = 0x0000 + (xtile * 0x01) + (ytile * 0x10);
if(current_tile > 0xFF)
{
help0x9000Render = true;
}
current_tile_data_location = 0x8000 + ((current_tile - 0xFFFFFF00) * 0x10);
if (current_tile_data_location > 0x9000 && help0x9000Render == true)
{
current_tile_data_location -= 0x1000;
}
rendernewVRAMpixel:
MEMVRAMbitbuffer = memory[current_tile_data_location];
MEMVRAMbitbuffer2 = memory[current_tile_data_location + 1];
compare_VRAMpixels();
SDL_RenderDrawPoint(VRAM_renderer,current_x_pixel,current_y_pixel);
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
    goto donerenderingVRAMtile;
    }
}
goto rendernewVRAMpixel;
donerenderingVRAMtile:
dummyvalue++; // This is just here so the compiler doesn't complain about the last function being a goto related thing.
}

void RenderVRAMFrame()
{
current_x_tile = 0;
current_y_tile = 0;
renderNextVRAMTile:
if (current_x_tile < 17)
{
RenderVRAMTile(current_x_tile,current_y_tile);
current_x_tile++;
    if (current_y_tile == 25)
    {
    goto doneRenderingVRAMFrame;
    }
goto renderNextVRAMTile;
}
if (current_x_tile == 17)
{
current_y_tile++;
current_x_tile = 0;
goto renderNextVRAMTile;
}
doneRenderingVRAMFrame:
VRAMRenderhelp = false;
SDL_RenderPresent(VRAM_renderer);
}
