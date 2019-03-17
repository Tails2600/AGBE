#include "timers.hpp"

int handleInterupts()
{
switch(previous_opcode)
{
case 0x76:

break;

default:

break;
}
switch(ime)
{
case true:
if (helpEI == 0)
{
FF0F_Interupt_Value = memory[0xFF0F];
if (FF0F_Interupt_Value == bin_value_1)
{
VBlank_Interupt_Needs_Done = true;
}

}
if (helpEI == 1)
{
helpEI--;
}

break;

case false:
//goto done_processing_interupts; GOTO END OF FUNCTION
break;
}
if(VBlank_Interupt_Needs_Done == true)
{
// Do VBlank Interupt
ime = false;
help0xCD3 = sp[0];
nn = help0xCD3 << 8 | sp[1];
help0xCD = (pc + 0x3) >> 8;
help0xCD2 = (pc + 0x3);
memory[(nn - 0xFFFF0000) - 0x02] = help0xCD2;
memory[(nn - 0xFFFF0000) - 0x01] = help0xCD;
pc = 0x0040;
sp[1] -= 0x02;
if(sp[1] == 0xFF || sp[1] == 0xFE)
{
sp[0] -= 0x01;
}
memory[0xFF0F] = 0x00; // Note: if there is a bug where interupts are skipped, this is probably the line of code that would cause it.
VBlank_Interupt_Needs_Done = false;
advanced_debugging_enabled = true;
}


}
