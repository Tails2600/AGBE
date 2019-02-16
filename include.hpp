
char memory[0x10000];
// Registers and Flags
int16_t pc = 0x100;
unsigned char hl[2];
unsigned char af[2];
unsigned char bc[2];
unsigned char de[2];
unsigned char sp[2];
bool ime;
// IF flag is at FF0F in memory
// Helper Variables
unsigned int hlbuffer;
bool close_program;
char a;
char b;
char c;
char d;
char e;
char f;
char h;
char l;

/*
00000000 = 0x00
10000000 = 0x80
01000000 = 0x40
00100000 = 0x20
00010000 = 0x10
11000000 = 0xC0
01100000 = 0x60
00110000 = 0x30
10100000 = 0xA0
01010000 = 0x50
10010000 = 0x90
11100000 = 0xE0
01110000 = 0x70
10110000 = 0xB0
11010000 = 0xD0
11110000 = 0xF0
*/

unsigned char opcode;
unsigned char previous_opcode;
int64_t cycles;
unsigned char opnn[2]; // JP
int16_t nn = 0x00000000;
char choice;
bool debugflagopcheck;
char help0xE0[0x2];
unsigned short help0xE0_2;
char help0xF0[0x2];
unsigned short help0xF0_2;
char help0xE2[0x2];
unsigned short help0xE2_2;
bool debugging_enabled;
bool advanced_debugging_enabled;
int8_t help0xCD;
int8_t help0xCD2;
int8_t help0xCD3;
int8_t help0xC9;
int8_t help0xC92;
