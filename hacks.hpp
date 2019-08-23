#include "include.hpp"
/*
The Purpose of this file is to have a place where I can put Game Specific Hacks.
The hope is that, one day, this file is not needed.
*/


int processHacks()
{
Title4[0] = memory[0x0134];
Title4[1] = memory[0x0135];
Title4[2] = memory[0x0136];
Title4[3] = memory[0x0137];


if (Title4[0] == 'T' && Title4[1] == 'I' && Title4[2] == 'C' && Title4[3] == '-') // Tic Tac Toe
{
    if(helperforHacks == false)
    {
        helperforHacks = true;
        printf("Tic-Tac-Toe Hack Enabled.\n");
    }
    if(pc == 0x2393)
    {
        pc = 0x2397;
    }
}
if (Title4[0] == 'D' && Title4[1] == 'R' && Title4[2] == '.' && Title4[3] == 'M') // Dr. Mario
{
    if(helperforHacks == false)
    {
        helperforHacks = true;
        printf("Dr. Mario Hack Enabled.\n");
    }
    if(pc == 0x0B7D)
    {
        pc = 0x0B81;
    }
}





}
