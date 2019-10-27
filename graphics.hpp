#include "sound.hpp"
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
int compare_bgp1pallete(uint8_t palthing)
{
    Palbitbuffer = memory[0xFF49];
    if (Palbitbuffer[palthing] == 0 && Palbitbuffer[palthing + 1] == 0)
    {
        setdrawcolor_white();
        return 0;
    }
    if (Palbitbuffer[palthing] == 0 && Palbitbuffer[palthing + 1] == 1)
    {
        setdrawcolor_lightgrey();
        return 1;
    }
    if (Palbitbuffer[palthing] == 1 && Palbitbuffer[palthing + 1] == 0)
    {
        setdrawcolor_darkgrey();
        return 2;
    }
    if (Palbitbuffer[palthing] == 1 && Palbitbuffer[palthing + 1] == 1)
    {
        setdrawcolor_black();
        return 3;
    }
}
int compare_bgp0pallete(uint8_t palthing)
{
    Palbitbuffer = memory[0xFF48];
    if (Palbitbuffer[palthing] == 0 && Palbitbuffer[palthing + 1] == 0)
    {
        setdrawcolor_white();
        return 0;
    }
    if (Palbitbuffer[palthing] == 0 && Palbitbuffer[palthing + 1] == 1)
    {
        setdrawcolor_lightgrey();
        return 1;
    }
    if (Palbitbuffer[palthing] == 1 && Palbitbuffer[palthing + 1] == 0)
    {
        setdrawcolor_darkgrey();
        return 2;
    }
    if (Palbitbuffer[palthing] == 1 && Palbitbuffer[palthing + 1] == 1)
    {
        setdrawcolor_black();
        return 3;
    }
}
int compare_pixels_2(uint8_t flags)
{
    MEMbitbuffer = flags;
    if (MEMVRAMbitbuffer[bitset_id_counter] == 0 && MEMVRAMbitbuffer2[bitset_id_counter] == 0)
    {
        if(MEMbitbuffer[4] == 0)
        {
           compare_bgp0pallete(0);
        }
        if(MEMbitbuffer[4] == 1)
        {
           compare_bgp1pallete(0);
        }
        compare_pixels_result = 0;
    }
    if (MEMVRAMbitbuffer[bitset_id_counter] == 0 && MEMVRAMbitbuffer2[bitset_id_counter] == 1)
    {
        if(MEMbitbuffer[4] == 0)
        {
           compare_bgp0pallete(2);
        }
        if(MEMbitbuffer[4] == 1)
        {
           compare_bgp1pallete(2);
        }
        compare_pixels_result = 1;
    }
    if (MEMVRAMbitbuffer[bitset_id_counter] == 1 && MEMVRAMbitbuffer2[bitset_id_counter] == 0)
    {
        if(MEMbitbuffer[4] == 0)
        {
           compare_bgp0pallete(4);
        }
        if(MEMbitbuffer[4] == 1)
        {
           compare_bgp1pallete(4);
        }
        compare_pixels_result = 2;
    }
    if (MEMVRAMbitbuffer[bitset_id_counter] == 1 && MEMVRAMbitbuffer2[bitset_id_counter] == 1)
    {
        if(MEMbitbuffer[4] == 0)
        {
           compare_bgp0pallete(6);
        }
        if(MEMbitbuffer[4] == 1)
        {
           compare_bgp1pallete(6);
        }
        compare_pixels_result = 3;
    }
}
int compare_pixels() // MAKE SURE BITSET_ID_COUNTER IS SET CORRECTLY BEFORE USING THIS.
{
    if (MEMVRAMbitbuffer[bitset_id_counter] == 0 && MEMVRAMbitbuffer2[bitset_id_counter] == 0)
    {
        setdrawcolor_white();
        compare_pixels_result = 0;
    }
    if (MEMVRAMbitbuffer[bitset_id_counter] == 0 && MEMVRAMbitbuffer2[bitset_id_counter] == 1)
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
    if(bgDisplaySelect == false)
    {
       current_tile_location = (0x9800 + (xtile * 0x01) + (ytile * 0x20));
    }
    if(bgDisplaySelect == true)
    {
        current_tile_location = (0x9C00 + (xtile * 0x01) + (ytile * 0x20));
    }
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
    if(current_tile_data_location >= 0x9000 && help0x9000Render == true)
    {
        current_tile_data_location -= 0x1000;
    }
    rendernewpixel:
    MEMVRAMbitbuffer = memory[current_tile_data_location];
    MEMVRAMbitbuffer2 = memory[current_tile_data_location + 1];
    compare_pixels();
    SDL_RenderDrawPoint(renderer,current_x_pixel - (memory[0xFF43]),current_y_pixel - memory[0xFF42]);
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

void RenderSprite2(uint8_t xcordi, uint8_t ycordi, uint16_t vramTile, uint8_t flags)
{
    currentOAMxpixel = xcordi;
    bitset_id_counter = 7;
    currentOAMypixel = ycordi;
    currentOAMxpixel = currentOAMxpixel - 0x08;
    currentOAMypixel = currentOAMypixel - 0x10;

    oamdataloc2 = (0x8000 + ((vramTile - 0xFFFFFF00) * 0x10));

    if(oamdataloc2 >= 0x9000)
    {
        oamdataloc2 -= 0x1000;
    }
    //printf("OAMDATALOC2: 0x%X\n",oamdataloc2);
    MEMbitbuffer = flags;
    if(MEMbitbuffer[5] == 1)
    {
        currentOAMxpixel = currentOAMxpixel + 0x07;
        currentxBuffer = currentOAMxpixel - 0x08;
    }
    if(MEMbitbuffer[5] == 0)
    {
        currentxBuffer = currentOAMxpixel + 0x08;
    }
    if(MEMbitbuffer[6] == 1)
    {
        currentOAMypixel = currentOAMypixel + 0x07;
        currentyBuffer = currentOAMypixel - 0x08;
    }
    if(MEMbitbuffer[6] == 0)
    {
        currentyBuffer = currentOAMypixel + 0x08;
    }
    rendernewpixel:
    MEMVRAMbitbuffer = memory[oamdataloc2];
    MEMVRAMbitbuffer2 = memory[oamdataloc2 + 1];
    compare_pixels_2(flags);

    if(compare_pixels_result == 0 && MEMbitbuffer[7] == 0)
    {
        goto dontRenderPix;
    }
    SDL_RenderDrawPoint(renderer,currentOAMxpixel,currentOAMypixel);

    dontRenderPix:
    if(MEMbitbuffer[5] == 1)
    {
        currentOAMxpixel--;
    }
    if(MEMbitbuffer[5] == 0)
    {
        currentOAMxpixel++;
    }
    bitset_id_counter--;

    if (currentOAMxpixel == currentxBuffer) // Done Drawing Line
    {
        if(MEMbitbuffer[5] == 1)
        {
            currentOAMxpixel += 8;
        }
        if(MEMbitbuffer[5] == 0)
        {
            currentOAMxpixel -= 8;
        }
        bitset_id_counter = 7;
        if(MEMbitbuffer[6] == 1)
        {
            currentOAMypixel--;
        }
        if(MEMbitbuffer[6] == 0)
        {
            currentOAMypixel++;
        }
        oamdataloc2 += 0x02;
        if (currentOAMypixel == currentyBuffer) // Done Drawing Tile
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
    if (current_x_tile < 32)
    {
        RenderTile(current_x_tile,current_y_tile);
        current_x_tile++;
        if (current_y_tile == 32)
        {
            goto doneRenderingFrame;
        }
    goto renderNextTile;
    }
    if (current_x_tile == 32)
    {
        current_y_tile++;
        current_x_tile = 0;
        goto renderNextTile;
    }
    doneRenderingFrame:
    OAMhelp = memory[0xFF46];
    oamData = OAMhelp << 8 | 0x00;
    oamCounter = 0xA0;
    againSprite:
    OAMy = memory[oamData];
    OAMx = memory[oamData + 0x01];
    OAMtile = memory[oamData + 0x02];
    OAMflag = memory[oamData + 0x03];
    RenderSprite2(OAMx,OAMy,OAMtile,OAMflag);
    if(doubleSprites == true)
    {
        RenderSprite2(OAMx,OAMy + 8,OAMtile + 1,OAMflag);
    }
    oamData += 0x04;
    oamCounter -= 0x04;
    if(oamCounter == 0x00)
    {
        goto doneSprite;
    }
    goto againSprite;
    doneSprite:
    /*
    RenderSprite(0xC004);
    RenderSprite(0xC008);
    RenderSprite(0xC00C);
    RenderSprite(0xC010);
    RenderSprite(0xC014);
    RenderSprite(0xC018);
    RenderSprite(0xC01C);
    RenderSprite(0xC020);
    RenderSprite(0xC024);
    RenderSprite(0xC028);
    RenderSprite(0xC02C);
    RenderSprite(0xC030);
    RenderSprite(0xC034);
    RenderSprite(0xC038);
    RenderSprite(0xC03C);
    RenderSprite(0xC040);
    RenderSprite(0xC044);
    RenderSprite(0xC048);
    RenderSprite(0xC04C);
    RenderSprite(0xC050);
    RenderSprite(0xC054);
    RenderSprite(0xC058);
    RenderSprite(0xC05C);
    RenderSprite(0xC060);
    */

    //SDL_RenderPresent(renderer);
    dummyvalue++;
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
    if (MEMVRAMbitbuffer[bitset_id_counter] == 0 && MEMVRAMbitbuffer2[bitset_id_counter] == 1)
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
    if (current_tile_data_location >= 0x9000 && help0x9000Render == true)
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

void renderThreadFrame()
{
    if(sdl_wanted == true) // Handles Rendering
    {
        SDL_RenderSetLogicalSize(renderer, 160,144);
        SDL_RenderSetLogicalSize(VRAM_renderer, 128,192);
        if(cycles % 10000 <= 0x02 && cycles % 10000 >= 0x00) // This is just set here so that things appear on the screen.
        {
        //printf("FF80: 0x%X\n",((memory[0xFF80] - 0xFFFFFF00) - 0x00000100));
        //if(displayOn == true)
        //{
            RenderFrame(); // Renders a frame
        //}
        if (VRAMdebugwanted == true)
            {
                RenderVRAMFrame(); // Renders a frame in the VRAM Debugger
            }
        }
    }
}
