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
int8_t help0xC92;
std::bitset<1> help0x28;
std::bitset<1> help0xC0;
unsigned short help0x34;
unsigned short help0xE1;
char help0xD9[0x2];
char help0xEF;
char help0xEF2;
unsigned short backupPC0xEF;
// Variables that Store things like the Current Opcode being Executed
unsigned char opcode;
unsigned char previous_opcode;
unsigned char next_opcode;
int64_t cycles;
unsigned char opnn[2]; // JP
int16_t nn = 0x00000000;
// Variables that have Nothing to do with the Emulation of the Gameboy
int rom_size;
bool sdl_wanted;
char choice;
bool debugging_enabled;
bool advanced_debugging_enabled;
bool log_file_made;
int Operating_System;
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




// Other Functions
