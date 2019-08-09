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
int compare_pixels7()
{
    if (MEMVRAMbitbuffer[7] == 0 && MEMVRAMbitbuffer2[7] == 0)
    {
    compare_pixels_result = 0;
    setdrawcolor_white();
    printf("white\n");
    }
    if (MEMVRAMbitbuffer[7] == 0 && MEMVRAMbitbuffer2[7] == 1)
    {
    compare_pixels_result = 1;
    setdrawcolor_lightgrey();
    printf("lightgrey\n");

    }
    if (MEMVRAMbitbuffer[7] == 1 && MEMVRAMbitbuffer2[7] == 0)
    {
    compare_pixels_result = 2;
    setdrawcolor_darkgrey();
    printf("darkgrey\n");

    }
    if (MEMVRAMbitbuffer[7] == 1 && MEMVRAMbitbuffer2[7] == 1)
    {
    compare_pixels_result = 3;
    setdrawcolor_black();
    printf("black\n");

    }
}
int compare_pixels6()
{
    if (MEMVRAMbitbuffer[6] == 0 && MEMVRAMbitbuffer2[6] == 0)
    {
    compare_pixels_result = 0;
    setdrawcolor_white();
    printf("white\n");

    }
    if (MEMVRAMbitbuffer[6] == 0 && MEMVRAMbitbuffer2[6] == 1)
    {
    compare_pixels_result = 1;
    setdrawcolor_lightgrey();
    printf("lightgrey\n");

    }
    if (MEMVRAMbitbuffer[6] == 1 && MEMVRAMbitbuffer2[6] == 0)
    {
    compare_pixels_result = 2;
    setdrawcolor_darkgrey();
    printf("darkgrey\n");

    }
    if (MEMVRAMbitbuffer[6] == 1 && MEMVRAMbitbuffer2[6] == 1)
    {
    compare_pixels_result = 3;
    setdrawcolor_black();
    printf("black\n");

    }
}
int compare_pixels5()
{
    if (MEMVRAMbitbuffer[5] == 0 && MEMVRAMbitbuffer2[5] == 0)
    {
    compare_pixels_result = 0;
    setdrawcolor_white();
    printf("white\n");

    }
    if (MEMVRAMbitbuffer[5] == 0 && MEMVRAMbitbuffer2[5] == 1)
    {
    compare_pixels_result = 1;
    setdrawcolor_lightgrey();
    printf("lightgrey\n");

    }
    if (MEMVRAMbitbuffer[5] == 1 && MEMVRAMbitbuffer2[5] == 0)
    {
    compare_pixels_result = 2;
    setdrawcolor_darkgrey();
    printf("darkgrey\n");

    }
    if (MEMVRAMbitbuffer[5] == 1 && MEMVRAMbitbuffer2[5] == 1)
    {
    compare_pixels_result = 3;
    setdrawcolor_black();
    printf("black\n");

    }
}
int compare_pixels4()
{
    if (MEMVRAMbitbuffer[4] == 0 && MEMVRAMbitbuffer2[4] == 0)
    {
    compare_pixels_result = 0;
    setdrawcolor_white();
    printf("white\n");

    }
    if (MEMVRAMbitbuffer[4] == 0 && MEMVRAMbitbuffer2[4] == 1)
    {
    compare_pixels_result = 1;
    setdrawcolor_lightgrey();
    printf("lightgrey\n");

    }
    if (MEMVRAMbitbuffer[4] == 1 && MEMVRAMbitbuffer2[4] == 0)
    {
    compare_pixels_result = 2;
    setdrawcolor_darkgrey();
    printf("darkgrey\n");

    }
    if (MEMVRAMbitbuffer[4] == 1 && MEMVRAMbitbuffer2[4] == 1)
    {
    compare_pixels_result = 3;
    setdrawcolor_black();
    printf("black\n");

    }
}
int compare_pixels3()
{
    if (MEMVRAMbitbuffer[3] == 0 && MEMVRAMbitbuffer2[3] == 0)
    {
    compare_pixels_result = 0;
    setdrawcolor_white();
    printf("white\n");

    }
    if (MEMVRAMbitbuffer[3] == 0 && MEMVRAMbitbuffer2[3] == 1)
    {
    compare_pixels_result = 1;
    setdrawcolor_lightgrey();
    printf("lightgrey\n");

    }
    if (MEMVRAMbitbuffer[3] == 1 && MEMVRAMbitbuffer2[3] == 0)
    {
    compare_pixels_result = 2;
    setdrawcolor_darkgrey();
    printf("darkgrey\n");

    }
    if (MEMVRAMbitbuffer[3] == 1 && MEMVRAMbitbuffer2[3] == 1)
    {
    compare_pixels_result = 3;
    setdrawcolor_black();
    printf("black\n");

    }
}
int compare_pixels2()
{
    if (MEMVRAMbitbuffer[2] == 0 && MEMVRAMbitbuffer2[2] == 0)
    {
    compare_pixels_result = 0;
    setdrawcolor_white();
    printf("white\n");

    }
    if (MEMVRAMbitbuffer[2] == 0 && MEMVRAMbitbuffer2[2] == 1)
    {
    compare_pixels_result = 1;
    setdrawcolor_lightgrey();
    printf("lightgrey\n");

    }
    if (MEMVRAMbitbuffer[2] == 1 && MEMVRAMbitbuffer2[2] == 0)
    {
    compare_pixels_result = 2;
    setdrawcolor_darkgrey();
    printf("darkgrey\n");

    }
    if (MEMVRAMbitbuffer[2] == 1 && MEMVRAMbitbuffer2[2] == 1)
    {
    compare_pixels_result = 3;
    setdrawcolor_black();
    printf("black\n");

    }
}
int compare_pixels1()
{
    if (MEMVRAMbitbuffer[1] == 0 && MEMVRAMbitbuffer2[1] == 0)
    {
    compare_pixels_result = 0;
    setdrawcolor_white();
    printf("white\n");

    }
    if (MEMVRAMbitbuffer[1] == 0 && MEMVRAMbitbuffer2[1] == 1)
    {
    compare_pixels_result = 1;
    setdrawcolor_lightgrey();
    printf("lightgrey\n");

    }
    if (MEMVRAMbitbuffer[1] == 1 && MEMVRAMbitbuffer2[1] == 0)
    {
    compare_pixels_result = 2;
    setdrawcolor_darkgrey();
    printf("darkgrey\n");

    }
    if (MEMVRAMbitbuffer[1] == 1 && MEMVRAMbitbuffer2[1] == 1)
    {
    compare_pixels_result = 3;
    setdrawcolor_black();
    printf("black\n");

    }
}
int compare_pixels0()
{
    if (MEMVRAMbitbuffer[0] == 0 && MEMVRAMbitbuffer2[0] == 0)
    {
    compare_pixels_result = 0;
    setdrawcolor_white();
    printf("white\n");

    }
    if (MEMVRAMbitbuffer[0] == 0 && MEMVRAMbitbuffer2[0] == 1)
    {
    compare_pixels_result = 1;
    setdrawcolor_lightgrey();
    printf("lightgrey\n");

    }
    if (MEMVRAMbitbuffer[0] == 1 && MEMVRAMbitbuffer2[0] == 0)
    {
    compare_pixels_result = 2;
    setdrawcolor_darkgrey();
    printf("darkgrey\n");

    }
    if (MEMVRAMbitbuffer[0] == 1 && MEMVRAMbitbuffer2[0] == 1)
    {
    compare_pixels_result = 3;
    setdrawcolor_black();
    printf("black\n");

    }
}
int RenderTile(int xtile,int ytile)
{
current_x_pixel = 0;
current_y_pixel = 0;
bitset_id_counter = 7;
current_tile_location = 0x9800;
current_tile_location = (current_tile_location + ((1 * xtile) + (20 * ytile)));
current_tile = memory[current_tile_location];
//current_tile_data_location = (0x8000 + (current_tile * 10));
current_tile_data_location = 0x8000;


rendernextpixelgoto:
MEMVRAMbitbuffer = memory[current_tile_data_location];
MEMVRAMbitbuffer2 = memory[current_tile_data_location + 1];
printf("MEMVRAM1: 0x%X\n",MEMVRAMbitbuffer);
printf("MEMVRAM2: 0x%X\n",MEMVRAMbitbuffer2);
if(bitset_id_counter == 7)
{
compare_pixels7();
}
if(bitset_id_counter == 6)
{
compare_pixels6();
}
if(bitset_id_counter == 5)
{
compare_pixels5();
}
if(bitset_id_counter == 4)
{
compare_pixels4();
}
if(bitset_id_counter == 3)
{
compare_pixels3();
}
if(bitset_id_counter == 2)
{
compare_pixels2();
}
if(bitset_id_counter == 1)
{
compare_pixels1();
}
if(bitset_id_counter == 0)
{
compare_pixels0();
}
SDL_RenderDrawPoint(renderer,current_x_pixel,current_y_pixel);
current_x_pixel++;
bitset_id_counter--;
if(current_x_pixel > 7 )
{
current_y_pixel++;
current_x_pixel = xtile * 8;
current_tile_data_location += 2;
}
if(current_y_pixel > 7)
{
goto endofRenderTile;
}
goto rendernextpixelgoto;
endofRenderTile:
printf("ok");
}



void RenderFrame()
{
printf("print\n");
std::cout<<"out"<<std::endl;
setdrawcolor_lightgrey();
SDL_RenderClear(renderer);
//current_x_pixel = 0;
//current_y_pixel = 0;
//bitset_id_counter = 7;
//current_tile_location = 0x97FF;
current_drawing_x_tile = 0x00;
current_drawing_y_tile = 0x00;
RenderTile(0,0);
//RenderTile(1,0);
//RenderTile(2,0);
//RenderTile(0,1);

//current_tile_location++;
/*
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
*/
//current_tile = memory[current_tile_location];
//current_tile_data_location = (0x8000 + (current_tile * 10));
//MEMVRAMbitbuffer = memory[current_tile_data_location];
//MEMVRAMbitbuffer2 = memory[current_tile_data_location + 1];
//rendernextpixel:
//compare_pixels(bitset_id_counter);
//SDL_RenderDrawPoint(renderer,current_x_pixel,current_y_pixel);
//current_x_pixel++;
//bitset_id_counter--;
/*
if (current_x_pixel > 7)
{
if (current_drawing_x_tile == 0x00)
{
current_x_pixel = 0;
}
if (current_drawing_x_tile != 0x00)
{
current_x_pixel = current_drawing_x_tile * 8;
}
current_y_pixel++;
bitset_id_counter = 0x07;
if (current_y_pixel > 7)
{
current_drawing_x_tile++;
current_y_pixel = 0x00;
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
*/




donerenderingframe:
SDL_RenderPresent(renderer);
}
