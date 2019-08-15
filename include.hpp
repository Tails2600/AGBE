#include <bits/stdc++.h>
#include <stdio.h>
#include <iostream>
// The Gameboy RAM
char memory[0x10000];
// Registers and Flags
unsigned short pc = 0x0100;
unsigned char hl[2];
unsigned char af[2];
unsigned char bc[2];
unsigned char de[2];
unsigned char sp[2];
bool ime;
// Helper Variables
unsigned int bcbuffer;
unsigned int debuffer;
unsigned int hlbuffer;
unsigned int nnbuffer;
unsigned int nbuffer;
unsigned int spbuffer;
int8_t tem;
short hlbuffer2;
short hlbuffer3;
int16_t spbuffer2;
int8_t pcbuffer1;
int8_t pcbuffer2;
std::bitset<8> Abitbuffer;
std::bitset<8> Bbitbuffer;
std::bitset<8> Cbitbuffer;
std::bitset<8> Dbitbuffer;
std::bitset<8> Ebitbuffer;
std::bitset<8> Fbitbuffer;
std::bitset<8> Hbitbuffer;
std::bitset<8> Lbitbuffer;
std::bitset<8> MEMbitbuffer;
std::bitset<8> FFFFbitbuffer;
bool close_program;
char a;
char b;
char c;
char d;
char e;
char f;
char h;
char l;
char help0xE0[0x2];
unsigned short help0xE0_2;
char help0xF0[0x2];
unsigned short help0xF0_2;
char help0xE2[0x2];
unsigned short help0xE2_2;
int8_t help0xCD;
int8_t help0xCD2;
int8_t help0xCD3;
unsigned short help0xCD4;
int8_t help0xC9;
uint8_t help0xC92;
unsigned char help0xC94;
std::bitset<1> help0x28;
std::bitset<1> help0xC0;
unsigned short help0x34;
unsigned short help0xE1;
char help0xD9[0x2];
char help0xEF;
char help0xEF2;
unsigned short backupPC0xEF;
std::bitset<1> help0x1F;
std::bitset<1> MSB_Helper;
std::bitset<1> Carry_Helper;
std::bitset<1> Carry_Helper2;
bool doBios;
// Variables that Store things like the Current Opcode being Executed
unsigned char opcode;
unsigned char previous_opcode;
unsigned char next_opcode;
int64_t cycles;
unsigned char opnn[2]; // JP
int16_t nn = 0x00000000;
// Variables that have Nothing to do with the Emulation of the Gameboy
int rom_size;
int bios_size;
bool sdl_wanted;
char choice;
bool debugging_enabled;
bool advanced_debugging_enabled;
bool log_file_made;
int Operating_System;
char AGBE_version[30];
// Variables used for Logging
FILE * gamelog;
// Variables that help with Interupt Processing
std::bitset<1> FF0F_Interupt_Value;
int VBlank_Timer = 32860;
int helpEI;
std::bitset<1> bin_value_1 = 1;
std::bitset<1> bin_value_0 = 0;
bool VBlank_Interupt_Needs_Done;
std::bitset<8> FF0F_Interupt_Value2;
// Variables used for Testing
int testingn;
uint32_t pixeltestcounter;
int dummyvalue;
char dummychar;
// SDL2 Stuff
uint32_t* pixels = new uint32_t[160*144];
SDL_Event SDL_EVENT_HANDLING;
SDL_Window* AGBE_window = NULL;
SDL_Surface* screenSurface = NULL;
SDL_Renderer* renderer;
SDL_Window* AGBE_VRAM_DEBUG = NULL;
SDL_Renderer* VRAM_renderer;
SDL_Texture *texture;
int current_x_pixel;
int current_y_pixel;
std::bitset<8> MEMVRAMbitbuffer;
std::bitset<8> MEMVRAMbitbuffer2; // This should always hold the value after MEMVRAMbitbuffer.
unsigned char current_tile;
int current_x_tile;
int current_y_tile;
int current_tile_location;
int current_tile_data_location;
int current_tile_data_location_placeholder;
int compare_pixels_result;
int bitset_id_counter;
int current_drawing_x_tile;
int current_drawing_x_tile_plus1;
int current_drawing_y_tile;
int current_drawing_y_tile_plus1;
int tile_x_counter_for_pixelx;
int tile_y_counter_for_pixely;
int tile_x_counter_for_pixelx_plus1;
int tile_y_counter_for_pixely_plus1;
bool thingforSDL2render;
bool VRAMdebugwanted;
// SDL2 Color Palletes
SDL_Color color_black = {0,0,0,0}; // Black (3)
SDL_Color color_darkgrey = {0x76, 0x76, 0x76, 0}; // Dark Gray (2)
SDL_Color color_lightgrey = {0xC2, 0xC2, 0xC2, 0}; // Light Grey (1)
SDL_Color color_white = {255, 255, 255, 0}; // White (0)


// Other Functions
