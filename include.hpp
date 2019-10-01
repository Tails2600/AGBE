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
uint16_t membuffer;
uint8_t tem;
int64_t lyhelp1;
int64_t lyhelp2;
int64_t lyhelp3 = 1;
unsigned short hlbuffer2;
unsigned short hlbuffer3;
uint16_t spbuffer2;
uint8_t pcbuffer1;
uint8_t pcbuffer2;
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
std::bitset<8> FF0Fbitbuffer;
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
uint8_t C6help;
unsigned short help0xF0_2;
char help0xE2[0x2];
unsigned short help0xE2_2;
uint8_t help0xCD;
uint8_t help0xCD2;
uint8_t help0xCD3;
unsigned short help0xCD4;
uint8_t help0xC9;
uint8_t help0xC92;
unsigned char help0xC94;
std::bitset<1> help0x28;
std::bitset<1> help0xC0;
unsigned short help0x34;
unsigned short help0xE1;
uint8_t help0xD9[0x2];
uint8_t help0xEF;
uint8_t help0xEF2;
uint8_t help0xE8;
uint8_t help9E;
unsigned short backupPC0xEF;
std::bitset<1> help0x1F;
std::bitset<1> MSB_Helper;
std::bitset<1> Carry_Helper;
std::bitset<1> Carry_Helper2;
bool doBios;
bool VRAMRenderhelp;
bool cpuHALT;
int8_t Overflow_test;
uint8_t help0xFE;
bool helpOR = false;
int8_t bitcount;
unsigned short helpEA;
uint8_t helpEA2;
uint8_t helpEA3;
char help0x18;
int kirbyDEBUG = 0;
uint8_t help0xFA;
uint8_t help0xFA2;
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
std::string AGBE_version;
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
bool framerateCounter;
uint8_t OAMhelp;
unsigned short oamData;
unsigned char OAMx;
uint8_t currentxBuffer;
uint8_t currentyBuffer;
unsigned char OAMy;
unsigned char OAMtile;
unsigned char OAMflag;
uint8_t currentOAMxpixel;
uint8_t currentOAMypixel;
unsigned short oamdataloc2;
bool interruptEnable = false;
uint8_t oamCounter;
// SDL2 Color Palletes
int white[4] = {0xFF,0xFF,0xFF,0x00};
int lightgrey[4] = {0xC2,0xC2,0xC2,0x00};
int darkgrey[4] = {0x76,0x76,0x76,0x00};
int black[4] = {0x00,0x00,0x00,0x00};
char palletec[12];
SDL_Color color_black = {black[0],black[1],black[2],black[3]}; // Black (3)
SDL_Color color_darkgrey = {darkgrey[0], darkgrey[1], darkgrey[2], darkgrey[3]}; // Dark Gray (2)
SDL_Color color_lightgrey = {lightgrey[0], lightgrey[1], lightgrey[2], lightgrey[3]}; // Light Grey (1)
SDL_Color color_white = {white[0],white[1],white[2],white[3]}; // White (0)




// Other Functions
FILE * mem_dump;
FILE * error_log;
uint8_t helpF8;
std::bitset<4> before;
std::bitset<4> after;
std::bitset<4> before16;
std::bitset<4> after16;
std::bitset<4> before162;
std::bitset<4> after162;
std::bitset<8> halfcarrycheck16help;
uint8_t halfcarrycheck16help2;
unsigned char beforeHcheck;
unsigned short beforeHcheck16;

int halfcarrycheck(uint8_t a,uint8_t b)
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

int halfcarrycheckinv(uint8_t a,uint8_t b)
{
    before = a >> 4;
    after = b >> 4;
    if(before != after)
    {
        return 0; // Half Carry Happened.
    }
    if(before == after)
    {
        return 1; // Half Carry didn't happen.
    }
}

int halfcarrycheck16(uint16_t a,uint16_t b)
{
    halfcarrycheck16help = b >> 8;
    halfcarrycheck16help2 = halfcarrycheck16help.to_ulong();
    if(halfcarrycheck16help2 % 0x10 == 0x00 || halfcarrycheck16help2 == 0x00)
    {
        return 1; // Half Carry Happened.
    }
    if(halfcarrycheck16help2 % 0x10 != 0x00)
    {
        return 0; // Half Carry didn't happen.
    }
}

int overflowcheck(uint8_t a,uint8_t b)
{
    before = a;
    after = b;
    if(b >= a)
    {
    return 0;
    }
    if(b < a)
    {
    return 1;
    }
}

int overflowcheck16(uint16_t a,uint16_t b)
{
    if(b >= a)
    {
    return 0;
    }
    if(b < a)
    {
    return 1;
    }
}

int negativeoverflowcheck(uint8_t a,uint8_t b)
{
    before = a >> 4;
    after = b >> 4;
    if(b >= a)
    {
    return 1;
    }
    if(b < a)
    {
    return 0;
    }
}

int negativeoverflowcheck16(uint16_t a,uint16_t b)
{
    if(b >= a)
    {
    return 1;
    }
    if(b < a)
    {
    return 0;
    }
}

int breakpoint(unsigned short location)
{
    if(pc == location)
    {
        advanced_debugging_enabled = true;
    }
}
int antibreakpoint(unsigned short location)
{
    if(pc == location)
    {
        advanced_debugging_enabled = false;
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

unsigned short invRAM;
bool displayOn = true;
bool bgDisplaySelect = false;
bool bgDisplay = true;
bool spriteDisplay = true;

void otherThings() // Parts of code that I had no Idea where to put
{
    otherCounter++;
    // Prevents the Game from Writing to Rom?  Currently doesn't do it every opcode do to lag.
    if(mbcExist == true)
    {
        goto noromwrite;
    }
    if(otherCounter % 10 == 0x00 && doBios == false)
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
    Fbitbuffer = af[1];
    Fbitbuffer[3] = 0;
    Fbitbuffer[2] = 0;
    Fbitbuffer[1] = 0;
    Fbitbuffer[0] = 0;
    af[1] = Fbitbuffer.to_ulong();
    invRAM = 0xFEA0;
    againInvRAM:
    memory[invRAM] = 0x00;
    invRAM++;
    if(invRAM == 0xFF00)
    {
        goto doneInvRAM;
    }
    goto againInvRAM;
    doneInvRAM:
    // Handles FF40

    MEMbitbuffer = memory[0xFF40];
    //printf("bin: 0x%x\n",memory[0xFF40]);
    if(MEMbitbuffer[7] == 1)
    {
        displayOn = true;
    }
    if(MEMbitbuffer[7] == 0)
    {
        displayOn = false;
    }
    if(MEMbitbuffer[4] == 1)
    {
        mode0x8800 = false;
    }
    if(MEMbitbuffer[4] == 0)
    {
        mode0x8800 = true;
    }
    if(MEMbitbuffer[3] == 1)
    {
        bgDisplaySelect = true;
    }
    if(MEMbitbuffer[3] == 0)
    {
        bgDisplaySelect = false;
    }
    if(MEMbitbuffer[1] == 1)
    {
        spriteDisplay = true;
    }
    if(MEMbitbuffer[1] == 0)
    {
        spriteDisplay = false;
    }
    if(MEMbitbuffer[0] == 1)
    {
        bgDisplay = true;
    }
    if(MEMbitbuffer[0] == 0)
    {
        bgDisplay = false;
    }
    MEMbitbuffer = memory[0xFF02];
    if(MEMbitbuffer[7] == 0)
    {
        memory[0xFF02] = 0x7E;
    }
    MEMbitbuffer = memory[0xFF07];
    MEMbitbuffer[7] = 1;
    MEMbitbuffer[6] = 1;
    MEMbitbuffer[5] = 1;
    MEMbitbuffer[4] = 1;
    MEMbitbuffer[3] = 1;
    memory[0xFF07] = MEMbitbuffer.to_ulong();
    MEMbitbuffer = memory[0xFF0F];
    MEMbitbuffer[7] = 1;
    MEMbitbuffer[6] = 1;
    MEMbitbuffer[5] = 1;
    memory[0xFF0F] = MEMbitbuffer.to_ulong();
    MEMbitbuffer = memory[0xFF41];
    MEMbitbuffer[7] = 1;
    memory[0xFF41] = MEMbitbuffer.to_ulong();
    MEMbitbuffer = memory[0xFF10];
    MEMbitbuffer[7] = 1;
    memory[0xFF10] = MEMbitbuffer.to_ulong();
    MEMbitbuffer = memory[0xFF1A];
    MEMbitbuffer[6] = 1;
    MEMbitbuffer[5] = 1;
    MEMbitbuffer[4] = 1;
    MEMbitbuffer[3] = 1;
    MEMbitbuffer[2] = 1;
    MEMbitbuffer[1] = 1;
    MEMbitbuffer[0] = 1;
    memory[0xFF1A] = MEMbitbuffer.to_ulong();
    MEMbitbuffer = memory[0xFF1C];
    MEMbitbuffer[7] = 1;
    MEMbitbuffer[4] = 1;
    MEMbitbuffer[3] = 1;
    MEMbitbuffer[2] = 1;
    MEMbitbuffer[1] = 1;
    MEMbitbuffer[0] = 1;
    memory[0xFF1C] = MEMbitbuffer.to_ulong();
    MEMbitbuffer = memory[0xFF20];
    MEMbitbuffer[7] = 1;
    MEMbitbuffer[6] = 1;
    memory[0xFF20] = MEMbitbuffer.to_ulong();
    MEMbitbuffer = memory[0xFF23];
    MEMbitbuffer[5] = 1;
    MEMbitbuffer[4] = 1;
    MEMbitbuffer[3] = 1;
    MEMbitbuffer[2] = 1;
    MEMbitbuffer[1] = 1;
    MEMbitbuffer[0] = 1;
    memory[0xFF23] = MEMbitbuffer.to_ulong();
    MEMbitbuffer = memory[0xFF26];
    MEMbitbuffer[4] = 1;
    MEMbitbuffer[5] = 1;
    MEMbitbuffer[6] = 1;
    memory[0xFF26] = MEMbitbuffer.to_ulong();
    memory[0xFF03] = 0xFF;
    memory[0xFF08] = 0xFF;
    memory[0xFF09] = 0xFF;
    memory[0xFF0A] = 0xFF;
    memory[0xFF0B] = 0xFF;
    memory[0xFF0C] = 0xFF;
    memory[0xFF0D] = 0xFF;
    memory[0xFF0E] = 0xFF;
    memory[0xFF15] = 0xFF;
    memory[0xFF1F] = 0xFF;
    memory[0xFF27] = 0xFF;
    memory[0xFF28] = 0xFF;
    memory[0xFF29] = 0xFF;
    memory[0xFF2A] = 0xFF;
    memory[0xFF2B] = 0xFF;
    memory[0xFF2C] = 0xFF;
    memory[0xFF2D] = 0xFF;
    memory[0xFF2E] = 0xFF;
    memory[0xFF2F] = 0xFF;
    invRAM = 0xFF4C;
    invRAM2AGAIN: // 0xFF4C to 0xFF7F needs to always be 0xFF
    memory[invRAM] = 0xFF;
    invRAM++;
    if(invRAM == 0xFF80)
    {
        goto doneINVRAMLOOP;
    }
    goto invRAM2AGAIN;
    doneINVRAMLOOP:
    OAMhelp = memory[0xFF46];
    oamData = OAMhelp << 8 | 0x00;
    invRAM = 0xFE00;
    OAMwriteAgain:
    memory[invRAM] = memory[oamData];
    invRAM++;
    oamData++;
    if(invRAM == 0xFEA0)
    {
        goto doneOAMwrite;
    }
    goto OAMwriteAgain;
    doneOAMwrite:
    dummyvalue++;
}
int handleEchoRAM()
{

}
