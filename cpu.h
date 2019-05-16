#include <stdio.h>
#include <iostream>
#include "controls.hpp"
#include <time.h>

int doOpcode()
{
switch(opcode)
{
case 0x00: // NOP (No Operation)
pc++;
cycles += 4;
break;

case 0x1:
bc[0] = memory[pc + 2];
bc[1] = memory[pc + 1];
pc += 3;
cycles += 12;
break;

case 0x5: // DEC B (Decrease B by 0x01)
bc[0]--;

if(bc[0] == 0x00)
{
af[1] = 0xC0;
}
if(bc[0] != 0x00)
{
af[1] = 0x40;
}

pc++;
cycles += 4;
break;

case 0x6: // LD B (Loads the value that is in front of the Current Opcode into B)
bc[0] = memory[pc + 1];
cycles += 8;
pc += 2;
break;

case 0xB:
bc[1] -= 0x01;
if(bc[1] == 0xFF)
{
bc[0] -= 0x01;
}
pc++;
cycles += 8;
break;

case 0xC:
bc[1] += 0x01;
if(bc[1] == 0x00)
{
af[1] = 0x80;
}
if(bc[1] != 0x00)
{
af[1] = 0x00;
}
pc++;
cycles += 4;
break;

case 0xD:
bc[1]--;
if(bc[1] == 0x00)
{
af[1] = 0xC0;
}
if(bc[1] != 0x00)
{
af[1] = 0x40;
}

pc++;
cycles += 4;
break;

case 0xE:
bc[1] = memory[pc + 1];
cycles += 8;
pc += 2;
break;

case 0x20:
if(af[1] != 0x80 && af[1] != 0xC0 && af[1] != 0xA0 && af[1] != 0x90 && af[1] != 0xE0 && af[1] != 0xB0 && af[1] != 0xD0 && af[1] != 0xF0)
{
cycles += 8;
pc = pc + memory[pc + 1];
}
if(af[1] == 0x80 || af[1] == 0xC0 || af[1] == 0xA0 || af[1] == 0x90 || af[1] == 0xE0 || af[1] == 0xB0 || af[1] == 0xD0 || af[1] == 0xF0)
{
cycles += 8;
}
pc +=2;
break;

case 0x21:
hl[0] = memory[pc + 2];
hl[1] = memory[pc + 1];
cycles += 12;
pc += 3;
break;

case 0x28:
help0x28 = af[1]>>7;
if(help0x28 == bin_value_1)
{
pc = pc + memory[pc + 0x01];
}
pc += 2;
cycles += 8;
break;

case 0x2A:
af[0] = memory[hlbuffer];
hl[1] += 0x01;
if(hl[1] == 0x00)
{
hl[0] += 0x01;
}
cycles += 8;
pc += 1;
break;

case 0x2F:
printf("a: %X\n", af[0]);
af[0] = ~af[0];
printf("a: %X\n", af[0]);
af[1] = 0x60;
cycles += 4;
pc++;
break;

case 0x31:
sp[0] = memory[pc + 2];
sp[1] = memory[pc + 1];
cycles += 12;
pc += 3;
break;

case 0x32:
memory[hlbuffer] = af[0];
if(hl[1] == 0x0)
{
hl[0] = (hl[0] - 0x01);
hl[1] = 0xFF;
goto done0x32;
}

if(hl[1] != 0x0)
{
hl[1] = (hl[1] - 0x01); // Does This Work?
goto done0x32;
}
done0x32:
cycles += 8;
pc++;
break;

case 0x34:
help0x34 = hl[0] << 8 | hl[1];
memory[help0x34]++;
if(memory[help0x34] == 0x00)
{
af[1] = 0x80;
goto done0x34;
}
af[1] = 0x00;
done0x34:
cycles += 12;
pc++;
break;

case 0x36:
memory[hlbuffer] = memory[pc + 1];
cycles += 12;
pc += 2;
break;

case 0x3C:
af[0]++;
if(af[0] == 0x00)
{
af[1] = 0x80;
goto done0x3C;
}
af[1] = 0x00;
done0x3C:
cycles += 4;
pc++;
break;

case 0x3D:
af[0] -= 0x01;
if(af[0] == 0x00)
{
af[1] = 0xC0;  //Note:  This is not the Exact behavior, however I dont have a way to write to specific bits right now so this will have to do.
goto done0x3D;
}
af[1] = 0x40;
done0x3D:
cycles += 4;
pc++;
break;

case 0x3E:
af[0] = memory[pc + 1];
cycles += 8;
pc += 2;
break;

case 0x78:
af[0] = bc[0];
pc++;
cycles += 4;
break;

case 0xA7:
af[0] = af[0] && af[0];
if(af[0] == 0x00)
{
af[1] = 0xA0;
goto A7Done;
}
af[1] = 0x20;
A7Done:
pc++;
cycles += 4;
break;

case 0xAF:
af[0] = af[0] ^ af[0];
if(af[0] == 0x0)
{
af[1] = 0x80;
}
if(af[0] != 0x0)
{
af[1] = 0x00;
}
pc++;
cycles += 4;
break;

case 0xB1:
if(bc[1] > af[0])
{
af[0] = bc[1];
goto done0xB1;
}
if(bc[1] < af[0])
{
af[0] = af[0];
}
done0xB1:
if(af[0] == 0x00)
{
af[1] = 0x80;
}
if(af[0] != 0x00)
{
af[1] = 0x00;
}
cycles += 4;
pc++;
break;

case 0xC0:
help0xC0 = af[1]>>7;
if(help0xC0 == bin_value_0)
{
nn = sp[0] << 8 | sp[1];
help0xC92 = memory[nn - 0xFFFF0000];
help0xC9 = memory[(nn - 0xFFFF0000) + 1];
pc = help0xC9 << 8 | help0xC92;
sp[1] += 0x02;
if(sp[1] == 0x00 || sp[1] == 0x01)
{
sp[0] += 0x01;
}
goto done0xC0;
}
pc++;
done0xC0:
cycles += 8;
break;

case 0xC1:
help0xE1 = sp[0] << 8 | sp[1];
bc[0] = memory[help0xE1 + 1];
bc[1] = memory[help0xE1];
sp[1] += 2;
if(sp[1] == 0x00 | sp[1] == 0x01)
{
sp[0]++;
}
cycles += 12;
pc++;
break;

case 0xC3:
opnn[0] = memory[pc + 2];
opnn[1] = memory[pc + 1];
nn = opnn[0] << 8 | opnn[1];
pc = nn;
cycles += 4;
break;

case 0xC5:
sp[1]--;
if(sp[1] == 0xFF)
{
sp[0]--;
}
spbuffer = sp[0] << 8 | sp[1];
memory[spbuffer] = bc[0];
sp[1]--;
if(sp[1] == 0xFF)
{
sp[0]--;
}
spbuffer = sp[0] << 8 | sp[1];
memory[spbuffer] = bc[1];
pc++;
cycles += 16;
break;

case 0xC8:
help0xC0 = af[1]>>7;
if(help0xC0 == bin_value_1)
{
nn = sp[0] << 8 | sp[1];
help0xC92 = memory[nn - 0xFFFF0000];
help0xC9 = memory[(nn - 0xFFFF0000) + 1];
pc = help0xC9 << 8 | help0xC92;
sp[1] += 0x02;
if(sp[1] == 0x00 || sp[1] == 0x01)
{
sp[0] += 0x01;
}
goto done0xC8;
}
pc++;
done0xC8:
cycles += 8;
break;

case 0xC9:
nn = sp[0] << 8 | sp[1];
help0xC92 = memory[nn - 0xFFFF0000];
help0xC9 = memory[(nn - 0xFFFF0000) + 1];
pc = help0xC9 << 8 | help0xC92;
sp[1] += 0x02;
if(sp[1] == 0x00 || sp[1] == 0x01)
{
sp[0] += 0x01;
}
cycles += 8;
break;

case 0xCD:
help0xCD3 = sp[0];
nn = help0xCD3 << 8 | sp[1];
help0xCD = (pc + 0x3) >> 8;
help0xCD2 = (pc + 0x3);
memory[(nn - 0xFFFF0000) - 0x02] = help0xCD2;
memory[(nn - 0xFFFF0000) - 0x01] = help0xCD;
opnn[0] = memory[pc + 2];
opnn[1] = memory[pc + 1];
nn = opnn[0] << 8 | opnn[1];
help0xCD4 = nn;
pc = help0xCD4;
sp[1] -= 0x02;
if(sp[1] == 0xFF || sp[1] == 0xFE)
{
sp[0] -= 0x01;
}
cycles += 12;
break;

case 0xD1:
help0xE1 = sp[0] << 8 | sp[1];
de[0] = memory[help0xE1 + 1];
de[1] = memory[help0xE1];
sp[1] += 2;
if(sp[1] == 0x00 | sp[1] == 0x01)
{
sp[0]++;
}
cycles += 12;
pc++;
break;

case 0xD5:
sp[1]--;
if(sp[1] == 0xFF)
{
sp[0]--;
}
spbuffer = sp[0] << 8 | sp[1];
memory[spbuffer] = de[0];
sp[1]--;
if(sp[1] == 0xFF)
{
sp[0]--;
}
spbuffer = sp[0] << 8 | sp[1];
memory[spbuffer] = de[1];
pc++;
cycles += 16;
break;

case 0xD9:
help0xE1 = sp[0] << 8 | sp[1];
help0xD9[0] = memory[help0xE1 + 1];
help0xD9[1] = memory[help0xE1];
pc = help0xD9[0] << 8 | help0xD9[1];
sp[1] += 2;
if(sp[1] == 0x00 | sp[1] == 0x01)
{
sp[0]++;
}
ime = true;
if (memory[0xFF0F] != 0x00)
{
helpEI = 1;
}
cycles += 8;
break;

case 0xE0:
help0xE0[0] = 0xFF;
help0xE0[1] = memory[pc + 1];
help0xE0_2 = help0xE0[0] << 8 | help0xE0[1];
memory[help0xE0_2] = af[0];
pc += 2;
cycles += 12;
break;

case 0xE1:
help0xE1 = sp[0] << 8 | sp[1];
hl[0] = memory[help0xE1 + 1];
hl[1] = memory[help0xE1];
sp[1] += 2;
if(sp[1] == 0x00 | sp[1] == 0x01)
{
sp[0]++;
}
cycles += 12;
pc++;
break;

case 0xE2:
help0xE2[0] = 0xFF;
help0xE2[1] = c;
help0xE2_2 = help0xE2[0] << 8 | help0xE2[1];
memory[help0xE2_2] = af[0];
pc++;
cycles += 8;
break;

case 0xE5:
sp[1]--;
if(sp[1] == 0xFF)
{
sp[0]--;
}
spbuffer = sp[0] << 8 | sp[1];
memory[spbuffer] = hl[0];
sp[1]--;
if(sp[1] == 0xFF)
{
sp[0]--;
}
spbuffer = sp[0] << 8 | sp[1];
memory[spbuffer] = hl[1];
pc++;
cycles += 16;
break;

case 0xE6:
printf("A: %X", af[0]);
af[0] = af[0] && memory[pc + 0x01];
printf("mem: %X", memory[pc + 0x01]);
printf("A: %X", af[0]);
if(af[0] == 0x00)
{
af[1] = 0xA0;
goto E6Done;
}
af[1] = 0x20;
E6Done:
pc += 2;
cycles += 8;
break;

case 0xEA:
opnn[0] = memory[pc + 2];
opnn[1] = memory[pc + 1];
nn = opnn[0] << 8 | opnn[1];
if(nn <= 0x7FFF)
{
goto done0xEA;
}
memory[nn] = af[0];
done0xEA:
cycles += 16;
pc += 3;
break;

case 0xF0:
help0xF0[0] = 0xFF;
help0xF0[1] = memory[pc + 1];
help0xF0_2 = help0xF0[0] << 8 | help0xF0[1];
af[0] = memory[help0xF0_2];
pc += 2;
cycles += 12;
break;

case 0xF1:
help0xE1 = sp[0] << 8 | sp[1];
af[0] = memory[help0xE1 + 1];
af[1] = memory[help0xE1];
sp[1] += 2;
if(sp[1] == 0x00 | sp[1] == 0x01)
{
sp[0]++;
}
cycles += 12;
pc++;
break;

case 0xF3: // DI (Disables Interupts)
ime = false;
cycles += 4;
pc++;
break;

case 0xF5: // PUSH AF (Pushes AF onto Stack)
sp[1]--;
if(sp[1] == 0xFF)
{
sp[0]--;
}
spbuffer = sp[0] << 8 | sp[1];
memory[spbuffer] = af[0];
sp[1]--;
if(sp[1] == 0xFF)
{
sp[0]--;
}
spbuffer = sp[0] << 8 | sp[1];
memory[spbuffer] = af[1];
pc++;
cycles += 16;
break;

case 0xFA:
nn = memory[pc + 2] << 8 | memory[pc + 1];
af[0] = memory[nn];
pc += 3;
cycles += 16;
break;

case 0xFB: // EI (Enables Interupts)
ime = true;
if (memory[0xFF0F] != 0x00)
{
helpEI = 1;
}
cycles += 4;
pc++;
break;

case 0xFE:
if(af[0] == memory[pc + 1])
{
af[1] = 0xC0;
goto done0xFE;
}
if(af[0] < memory[pc + 1])
{
af[1] = 0x50;
}
done0xFE:
cycles += 8;
pc += 2;
break;

default:
printf("\nAn error has Occured\nUnknown Opcode: 0x%X", opcode);
printf("\nProgram Counter: 0x%X\n", pc);
printf("Stack Pointer: 0x%X%X\n", sp[0], sp[1]);
printf("Cycles: %i\n", cycles);
printf("Please see errorlog.txt for more details.\n");
printf("Please see memdump for a full GB mem dump.\n");
SDL_DestroyWindow(AGBE_window);
SDL_Quit();
close_program = true;
FILE * mem_dump;
mem_dump = fopen ("log/memdump", "w+");
fwrite (memory , sizeof(char), sizeof(memory), mem_dump);
fclose (mem_dump);
FILE * error_log;
error_log = fopen ("log/errorlog.txt", "w+");
fprintf (error_log, "An Unknown Opcode was Encountered.\n");
fprintf (error_log, "Opcode: 0x%X\n", opcode);
fprintf (error_log, "Program Counter: 0x%X\n", pc);
fprintf (error_log, "Register A: 0x%X\n", af[0]);
fprintf (error_log, "Register F: 0x%X\n", af[1]);
fprintf (error_log, "Register B: 0x%X\n", bc[0]);
fprintf (error_log, "Register C: 0x%X\n", bc[1]);
fprintf (error_log, "Register D: 0x%X\n", de[0]);
fprintf (error_log, "Register E: 0x%X\n", de[1]);
fprintf (error_log, "Register H: 0x%X\n", hl[0]);
fprintf (error_log, "Register L: 0x%X\n", hl[1]);
fprintf (error_log, "Stack Pointer: 0x%X%X\n", sp[0], sp[1]);
fprintf (error_log, "CPU Cycles: %i", cycles);
fclose (error_log);
break;
}
return true;
}
int handleRegisters()
{
a = af[0];
f = af[1];
b = bc[0];
c = bc[1];
d = de[0];
e = de[1];
h = hl[0];
l = hl[1];
hlbuffer = hl[0] << 8 | hl[1];
return true;
}
int gbPowerOn()
{
hl[0] = 0x01;
hl[1] = 0x4D;
af[0] = 0x01;
af[1] = 0xB0;
bc[0] = 0x00;
bc[1] = 0x13;
de[0] = 0x00;
de[1] = 0xD8;
sp[0] = 0xFF;
sp[1] = 0xFE;
memory[0xFF00] = 0xCF;
memory[0xFF05] = 0x00;
memory[0xFF06] = 0x00;
memory[0xFF07] = 0x00;
memory[0xFF10] = 0x80;
memory[0xFF11] = 0xBF;
memory[0xFF12] = 0xF3;
memory[0xFF14] = 0xBF;
memory[0xFF16] = 0x3F;
memory[0xFF17] = 0x00;
memory[0xFF19] = 0xBF;
memory[0xFF1A] = 0x7F;
memory[0xFF1B] = 0xFF;
memory[0xFF1C] = 0x9F;
memory[0xFF1E] = 0xBF;
memory[0xFF20] = 0xFF;
memory[0xFF21] = 0x00;
memory[0xFF22] = 0x00;
memory[0xFF23] = 0xBF;
memory[0xFF24] = 0x77;
memory[0xFF25] = 0xF3;
memory[0xFF26] = 0xF1;
memory[0xFF40] = 0x91;
memory[0xFF42] = 0x00;
memory[0xFF43] = 0x00;
memory[0xFF45] = 0x00;
memory[0xFF47] = 0xFC;
memory[0xFF48] = 0xFF;
memory[0xFF49] = 0xFF;
memory[0xFF4A] = 0x00;
memory[0xFF4B] = 0x00;
memory[0xFFFF] = 0x00;
return true;
}

void init_memory()
{
int debugmeminit;
debugmeminit = 0x0000;
debug_mem_init_again:
debugmeminit++;
if(debugmeminit != 0x10000)
{
memory[debugmeminit] = 0xFF;
goto debug_mem_init_again;
}
if(debugmeminit == 0x10000)
{

}

}
