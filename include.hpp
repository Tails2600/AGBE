// This File just includes the declaration of most variables in the program.
#include <bits/stdc++.h>
#include <stdio.h>
#include <iostream>
#include <string>
#include <thread>
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
// MBC Stuff
char tempROM[0x4000];
FILE * tempROMfile;
int MBCcountHelp;
uint8_t bankSwitch = 0x01;
uint32_t romLocate;
char tempROM2[16000000]; // 16 MB
uint16_t MBCcount2;

// Helper Variables
int helpThing = 0x00;
char beforeFF01;
int64_t otherCounter;
char *filename;
unsigned short prev_pc;
char Title4[4];
unsigned int bcbuffer;
unsigned int debuffer;
unsigned int hlbuffer;
unsigned short nnbuffer;
unsigned int nbuffer;
unsigned int spbuffer;
short membuffer;
int8_t tem;
int64_t lyhelp1;
int64_t lyhelp2;
int64_t lyhelp3 = 1;
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
int8_t help0xE8;
unsigned short backupPC0xEF;
std::bitset<1> help0x1F;
std::bitset<1> MSB_Helper;
std::bitset<1> Carry_Helper;
std::bitset<1> Carry_Helper2;
bool doBios;
bool VRAMRenderhelp;
bool cpuHALT;
int8_t Overflow_test;
int8_t help0xFE;
bool helpOR = false;
int8_t bitcount;
uint16_t helpEA;
uint8_t helpEA2;
uint8_t helpEA3;
char help0x18;
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
bool gameHacks;
bool log_file_made;
int Operating_System;
char AGBE_version[30];
bool restartAGBE;
bool helperforHacks;
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
bool Interrupts_Enabled;
bool Interupt_thing;
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
short current_tile;
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
bool help0x9000Render;
bool mode0x8800;

int AGBEwinx = 160;
int AGBEwiny = 144;
int VRAMwinx = 128;
int VRAMwiny = 192;
bool helpThingWIN = false;

uint8_t OAMhelp;
unsigned short oamData;
unsigned char OAMx;
uint8_t currentxBuffer;
uint8_t currentyBuffer;
unsigned char OAMy;
unsigned char OAMtile;
uint8_t currentOAMxpixel;
uint8_t currentOAMypixel;
unsigned short oamdataloc2;
bool interruptEnable = false;
uint8_t oamCounter;
// SDL2 Color Palletes
SDL_Color color_black = {0,0,0,0}; // Black (3)
SDL_Color color_darkgrey = {0x76, 0x76, 0x76, 0}; // Dark Gray (2)
SDL_Color color_lightgrey = {0xC2, 0xC2, 0xC2, 0}; // Light Grey (1)
SDL_Color color_white = {255, 255, 255, 0}; // White (0)




// Other Functions
FILE * mem_dump;
FILE * error_log;
std::bitset<4> before;
std::bitset<4> after;
char beforeHcheck;

int halfcarrycheck(int8_t a,int8_t b)
{
    before = a >> 4;
    after = b >> 4;
    if(before != after)
    {
        return 1; // Half Carry Happened.
    }
    if(before == after)
    {
        return 0; // Half Carry didn't happen.
    }
}

int overflowcheck(int8_t a,int8_t b)
{
    if(b <= a)
    {
        return 1; // Overflow Happened.
    }
    if(b > a)
    {
        return 0; // Overflow Didn't Happen.
    }
}

int negativeoverflowcheck(int8_t a,int8_t b)
{
    if(b > a)
    {
    return 1;
    }
    if(b <= a)
    {
    return 0;
    }
}

int loopDetect() // Tries to detect if the game is in an Infinite Loop.  Not currently used because it causes lag?
{
    if(pc == prev_pc)
    {
    printf("In an Infinite Loop that Cannot be Exited?\nClosing Program...\n");
    close_program = true;
    }
}

bool mbcExist;

char compareArray(char a[],char b[],int size)	{
	int i;
	for(i=0;i<size;i++){
		if(a[i]!=b[i])
			return a[i];
	}
	return 0xFF;
}

uint8_t resultCompare;
std::string memoryString;
std::string tempROMString;


void otherThings() // Parts of code that I had no Idea where to put
{
    otherCounter++;
    // Prevents the Game from Writing to Rom?  Currently doesn't do it every opcode do to lag.
    if(mbcExist == true)
    {
        goto noromwrite;
    }
    if(otherCounter % 10 == 0x00)
    {
    FILE* rom = fopen(filename, "rb");
    fseek(rom,0,SEEK_END);
    rom_size = ftell(rom);
    rewind(rom);
    fread(memory,rom_size,1,rom);
    fclose(rom);
    }
    noromwrite:
    if(pc == 0xFFFF)
    {
        printf("PC HAS EXCEDED 0xFFFF.\nLOOPING TO BEGINNING.\n");
    }
    if(pc == 0x0038 && prev_pc == 0x0038)
    {
        printf("FF LOOP DETECTED.  \nTHIS LIKELY MEANS THE GAME HAS CRASHED.\n");
    }
    // Handles FF40
    /*
    MEMbitbuffer = memory[0xFF40];
    if(MEMbitbuffer[3] == 0)
    {
        mode0x8800 = false;
    }
    if(MEMbitbuffer[3] == 1)
    {
        mode0x8800 = true;
    }
    */

    dummyvalue++;
}

int handleEchoRAM()
{

}
