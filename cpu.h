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

case 0x01:
bc[0] = memory[pc + 2];
bc[1] = memory[pc + 1];
pc += 3;
cycles += 12;
break;

case 0x02:
bcbuffer = bc[0] << 8 | bc[1];
memory[bcbuffer] = af[0];
pc++;
cycles += 8;
break;

case 0x03:
bc[1]++;
if (bc[1] == 0x00)
{
bc[0]++;
}
pc++;
cycles += 8;
break;

case 0x04:
bc[0]++;
if(bc[0] == 0x00)
{
af[1] = 0x80;
goto done0x04;
}
af[1] = 0x00;
done0x04:
cycles += 4;
pc++;
break;

case 0x05: // DEC B (Decrease B by 0x01)
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

case 0x06:
bc[0] = memory[pc + 1];
cycles += 8;
pc += 2;
break;

case 0x08:
nnbuffer = memory[pc + 2] << 8 | memory[pc + 1];
memory[(nnbuffer - 0xFFFF0000) + 1] = sp[0];
memory[(nnbuffer - 0xFFFF0000)] = sp[1];
pc += 3;
cycles += 20;
break;

case 0x09: // Flags need fixed on this opcode
hlbuffer2 = hl[0] << 8 | hl[1];
hlbuffer3 = bc[0] << 8 | bc[1];
hlbuffer2 = hlbuffer2 + hlbuffer3;
hl[0] = hlbuffer2 >> 8;
hl[1] = hlbuffer2;
pc++;
cycles += 8;
break;

case 0x0A:
bcbuffer = bc[0] << 8 | bc[1];
af[0] = memory[bcbuffer];
pc++;
cycles += 8;
break;

case 0x0B:
bc[1]--;
if(bc[1] == 0xFF)
{
bc[0]--;
}
pc++;
cycles += 8;
break;

case 0x0C:
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

case 0x0D:
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

case 0x0E:
bc[1] = memory[pc + 1];
cycles += 8;
pc += 2;
break;

case 0x11:
de[0] = memory[pc + 2];
de[1] = memory[pc + 1];
pc += 3;
cycles += 12;
break;

case 0x12:
debuffer = de[0] << 8 | de[1];
memory[debuffer] = af[0];
pc++;
cycles += 8;
break;

case 0x13:
de[1]++;
if (de[1] == 0x00)
{
de[0]++;
}
pc++;
cycles += 8;
break;

case 0x14:
de[0]++;
if(de[0] == 0x00)
{
af[1] = 0x80;
goto done0x14;
}
af[1] = 0x00;
done0x14:
cycles += 4;
pc++;
break;

case 0x16:
de[0] = memory[pc + 1];
pc += 2;
cycles += 8;
break;

case 0x18:
nbuffer = memory[pc + 1];
pc = pc + nbuffer;
cycles += 8;
pc += 2;
break;

case 0x19:
hl[0] = hl[0] + de[0];
hl[1] = hl[1] + de[1];
if(hl[1] < de[1])
{
hl[0]++;
}
af[1] = 0x00;
cycles += 8;
pc++;
break;

case 0x1A:
debuffer = de[0] << 8 | de[1];
af[0] = memory[debuffer];
pc++;
cycles += 8;
break;

case 0x1B:
de[1]--;
if(de[1] == 0xFF)
{
de[0]--;
}
pc++;
cycles += 8;
break;

case 0x1C:
de[1]++;
if(de[1] == 0x00)
{
af[1] = 0x80;
goto done0x1C;
}
af[1] = 0x00;
done0x1C:
cycles += 4;
pc++;
break;

case 0x1E:
de[1] = memory[pc + 1];
cycles += 8;
pc += 2;
break;

case 0x1F:
Abitbuffer = af[0];
help0x1F[0] = Abitbuffer[0];
Abitbuffer = Abitbuffer >> 1;
af[0] = Abitbuffer.to_ulong();
if(af[0] == 0x00)
{
Fbitbuffer = af[1];
Fbitbuffer[7] = 1;
Fbitbuffer[6] = 0;
Fbitbuffer[5] = 0;
Fbitbuffer[4] = help0x1F[0];
af[1] = Fbitbuffer.to_ulong();
}
if(af[0] != 0x00)
{
Fbitbuffer = af[1];
Fbitbuffer[7] = 0;
Fbitbuffer[6] = 0;
Fbitbuffer[5] = 0;
Fbitbuffer[4] = help0x1F[0];
af[1] = Fbitbuffer.to_ulong();
pc++;
cycles += 4;
}

break;

case 0x20:
pc +=2;
if(af[1] != 0x80 && af[1] != 0xC0 && af[1] != 0xA0 && af[1] != 0x90 && af[1] != 0xE0 && af[1] != 0xB0 && af[1] != 0xD0 && af[1] != 0xF0)
{
cycles += 8;
pc = pc + memory[pc - 1];
}
if(af[1] == 0x80 || af[1] == 0xC0 || af[1] == 0xA0 || af[1] == 0x90 || af[1] == 0xE0 || af[1] == 0xB0 || af[1] == 0xD0 || af[1] == 0xF0)
{
cycles += 8;
}
break;

case 0x21:
hl[0] = memory[pc + 2];
hl[1] = memory[pc + 1];
cycles += 12;
pc += 3;
break;

case 0x22:
hlbuffer = hl[0] << 8 | hl[1];
memory[hlbuffer] = af[0];
hl[1]++;
if (hl[1] == 0x00)
{
hl[0]++;
}
pc++;
cycles += 8;
break;

case 0x23:
hl[1]++;
if(hl[1] == 0x00)
{
hl[0]++;
}
pc++;
cycles += 8;
break;

case 0x24:
hl[0]++;
if(hl[0] == 0x00)
{
af[1] = 0x80;
goto done0x24;
}
af[1] = 0x00;
done0x24:
cycles += 4;
pc++;
break;

case 0x25:
hl[0]--;

if(hl[0] == 0x00)
{
af[1] = 0xC0;
}
if(hl[0] != 0x00)
{
af[1] = 0x40;
}
pc++;
cycles += 4;
break;

case 0x26:
hl[0] = memory[pc + 1];
cycles += 8;
pc += 2;
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

case 0x29: // Flags need fixed on this opcode
hlbuffer2 = hl[0] << 8 | hl[1];
hlbuffer3 = hl[0] << 8 | hl[1];
hlbuffer2 = hlbuffer2 + hlbuffer3;
hl[0] = hlbuffer2 >> 8;
hl[1] = hlbuffer2;
pc++;
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

case 0x2B:
hl[1]--;
if(hl[1] == 0xFF)
{
hl[0]--;
}
pc++;
cycles += 8;
break;

case 0x2C:
hl[1]++;
if(hl[1] == 0x00)
{
af[1] = 0x80;
goto done0x2C;
}
af[1] = 0x00;
done0x2C:
cycles += 4;
pc++;
break;

case 0x2D:
hl[1]--;

if(hl[1] == 0x00)
{
af[1] = 0xC0;
}
if(hl[1] != 0x00)
{
af[1] = 0x40;
}

pc++;
cycles += 4;
break;

case 0x2E:
hl[1] = memory[pc + 1];
cycles += 8;
pc += 2;
break;

case 0x2F:
af[0] = ~af[0];
af[1] = 0x60;
cycles += 4;
pc++;
break;

case 0x30:
Fbitbuffer = af[1];
if(Fbitbuffer[4] == 0)
{
pc = pc + memory[pc + 0x01];
}
pc += 2;
cycles += 8;
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

case 0x33:
sp[1]++;
if (sp[1] == 0x00)
{
sp[0]++;
}
pc++;
cycles += 8;
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

case 0x35:
nn = hl[0] << 8 | hl[1];
memory[(nn - 0xFFFF0000)]--;
Fbitbuffer = af[1];
if (memory[(nn - 0xFFFF0000)] == 0x00)
{
Fbitbuffer[7] = 1;
}
Fbitbuffer[6] = 1;
af[1] = Fbitbuffer.to_ulong();
pc++;
cycles += 12;
break;

case 0x36:
memory[hlbuffer] = memory[pc + 1];
cycles += 12;
pc += 2;
break;

case 0x37:
Fbitbuffer = af[1];
Fbitbuffer[6] = 0;
Fbitbuffer[5] = 0;
Fbitbuffer[4] = 1;
pc++;
cycles += 4;
break;

case 0x38:
Fbitbuffer = af[1];
if(Fbitbuffer[4] == 1)
{
pc = pc + memory[pc + 0x01];
}
pc += 2;
cycles += 8;
break;

case 0x39:
hlbuffer2 = hl[0] << 8 | hl[1];
spbuffer2 = sp[0] << 8 | sp[1];
hlbuffer2 = hlbuffer2 + spbuffer2;
hl[0] = hlbuffer2 >> 8;
hl[1] = hlbuffer2;
pc++;
cycles += 8;
break;

case 0x3A:
hlbuffer = hl[0] << 8 | hl[1];
af[0] = memory[hlbuffer];
hl[1]--;
if (hl[1] == 0xFF)
{
hl[0]--;
}
pc++;
cycles += 8;
break;

case 0x3B:
sp[1]--;
if(sp[1] == 0xFF)
{
sp[0]--;
}
pc++;
cycles += 8;
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

case 0x40:
bc[0] = bc[0];
pc++;
cycles += 4;;
break;

case 0x41:
bc[0] = bc[1];
pc++;
cycles += 4;
break;

case 0x42:
bc[0] = de[0];
pc++;
cycles += 4;
break;

case 0x43:
bc[0] = de[1];
pc++;
cycles += 4;
break;

case 0x44:
bc[0] = hl[0];
pc++;
cycles += 4;
break;

case 0x45:
bc[0] = hl[1];
pc++;
cycles += 4;
break;

case 0x46:
hlbuffer = hl[0] << 8 | hl[1];
bc[0] = memory[hlbuffer];
pc++;
cycles += 8;
break;

case 0x47:
bc[0] = af[0];
pc++;
cycles += 4;
break;

case 0x48:
bc[1] = bc[0];
pc++;
cycles += 4;
break;

case 0x49:
bc[1] = bc[1];
pc++;
cycles += 4;
break;

case 0x4A:
bc[1] = de[0];
pc++;
cycles += 4;
break;

case 0x4B:
bc[1] = de[1];
pc++;
cycles += 4;
break;

case 0x4C:
bc[1] = hl[0];
pc++;
cycles += 4;
break;

case 0x4D:
bc[1] = hl[1];
pc++;
cycles += 4;
break;

case 0x4E:
hlbuffer = hl[0] << 8 | hl[1];
bc[1] = memory[hlbuffer];
pc++;
cycles += 4;
break;

case 0x4F:
bc[1] = af[0];
pc++;
cycles += 4;
break;

case 0x50:
de[0] = bc[0];
pc++;
cycles += 4;
break;

case 0x51:
de[0] = bc[1];
pc++;
cycles += 4;
break;

case 0x52:
de[0] = de[0];
pc++;
cycles += 4;
break;

case 0x53:
de[0] = de[1];
pc++;
cycles += 4;
break;

case 0x54:
de[0] = hl[0];
pc++;
cycles += 4;
break;

case 0x55:
de[0] = hl[1];
pc++;
cycles += 4;
break;

case 0x56:
hlbuffer = hl[0] << 8 | hl[1];
de[0] = memory[hlbuffer];
cycles += 8;
pc++;
break;

case 0x57:
de[0] = af[0];
pc++;
cycles += 4;
break;

case 0x58:
de[1] = bc[0];
pc++;
cycles += 4;
break;

case 0x59:
de[1] = bc[1];
pc++;
cycles += 4;
break;

case 0x5A:
de[1] = de[0];
pc++;
cycles += 4;
break;

case 0x5B:
de[1] = de[1];
pc++;
cycles += 4;
break;

case 0x5C:
de[1] = hl[0];
pc++;
cycles += 4;
break;

case 0x5D:
de[1] = hl[1];
pc++;
cycles += 4;
break;

case 0x5E:
hlbuffer = hl[0] << 8 | hl[1];
de[1] = memory[hlbuffer];
cycles += 8;
pc++;
break;

case 0x5F:
de[1] = af[0];
pc++;
cycles += 4;
break;

case 0x60:
hl[0] = bc[0];
pc++;
cycles += 4;
break;

case 0x61:
hl[0] = bc[1];
pc++;
cycles += 4;
break;

case 0x62:
hl[0] = de[0];
pc++;
cycles += 4;
break;

case 0x63:
hl[0] = de[1];
pc++;
cycles += 4;
break;

case 0x64:
hl[0] = hl[0];
pc++;
cycles += 4;
break;

case 0x65:
hl[0] = hl[1];
pc++;
cycles += 4;
break;

case 0x66:
hlbuffer = hl[0] << 8 | hl[1];
hl[0] = memory[hlbuffer];
pc++;
cycles += 8;
break;

case 0x67:
hl[0] = af[0];
pc++;
cycles += 4;
break;

case 0x68:
hl[1] = bc[0];
pc++;
cycles += 4;
break;

case 0x69:
hl[1] = bc[1];
pc++;
cycles += 4;
break;

case 0x6A:
hl[1] = de[0];
pc++;
cycles += 4;
break;

case 0x6B:
hl[1] = de[1];
pc++;
cycles += 4;
break;

case 0x6C:
hl[1] = hl[0];
pc++;
cycles += 4;
break;

case 0x6D:
hl[1] = hl[1];
pc++;
cycles += 4;
break;

case 0x6E:
hlbuffer = hl[0] << 8 | hl[1];
hl[1] = memory[hlbuffer];
pc++;
cycles += 8;
break;

case 0x6F:
hl[1] = af[0];
pc++;
cycles += 4;
break;

case 0x70:
hlbuffer = hl[0] << 8 | hl[1];
memory[hlbuffer] = bc[0];
pc++;
cycles += 8;
break;

case 0x71:
hlbuffer = hl[0] << 8 | hl[1];
memory[hlbuffer] = bc[1];
pc++;
cycles += 8;
break;

case 0x72:
hlbuffer = hl[0] << 8 | hl[1];
memory[hlbuffer] = de[0];
pc++;
cycles += 8;
break;

case 0x73:
hlbuffer = hl[0] << 8 | hl[1];
memory[hlbuffer] = de[1];
pc++;
cycles += 8;
break;

case 0x74:
hlbuffer = hl[0] << 8 | hl[1];
memory[hlbuffer] = hl[0];
pc++;
cycles += 8;
break;

case 0x75:
hlbuffer = hl[0] << 8 | hl[1];
memory[hlbuffer] = hl[1];
pc++;
cycles += 8;
break;

case 0x77:
hlbuffer = hl[0] << 8 | hl[1];
memory[hlbuffer] = af[0];
pc++;
cycles += 8;
break;


case 0x78:
af[0] = bc[0];
pc++;
cycles += 4;
break;

case 0x79:
af[0] = bc[1];
pc++;
cycles += 4;
break;

case 0x7A:
af[0] = de[0];
pc++;
cycles += 4;
break;

case 0x7B:
af[0] = de[1];
pc++;
cycles += 4;
break;

case 0x7C:
af[0] = hl[0];
pc++;
cycles += 4;
break;

case 0x7D:
af[0] = hl[1];
pc++;
cycles += 4;
break;

case 0x7E:
hlbuffer = hl[0] << 8 | hl[1];
af[0] = memory[hlbuffer];
pc++;
cycles += 8;
break;

case 0x7F:
af[0] = af[0];
pc++;
cycles += 4;
break;

case 0x81:
af[0] = af[0] + bc[1];
if(af[0] == 0x00)
{
af[1] = 0x80;
}
if(af[0] != 0x00)
{
af[1] = 0x00;
}
pc++;
cycles += 4;
break;

case 0x83: // Flags need fixed
af[0] = af[0] + de[1];
if(af[0] == 0x00)
{
af[1] = 0x80;
}
if(af[0] != 0x00)
{
af[1] = 0x00;
}
pc++;
cycles += 4;
break;

case 0x87:
af[0] = af[0] + af[0];
if(af[0] == 0x00)
{
af[1] = 0x80;
}
if(af[0] != 0x00)
{
af[1] = 0x00;
}
pc++;
cycles += 4;
break;

case 0x91: // Flag Handling Needs Fixing.
af[0] = af[0] - bc[1];
Fbitbuffer = af[1];
if(af[0] == 0x00)
{
Fbitbuffer[7] = 1;
Fbitbuffer[6] = 1;
}
if(af[0] != 0x00)
{
Fbitbuffer[7] = 0;
Fbitbuffer[6] = 1;
}
pc++;
cycles += 4;
break;

case 0x95: // Flag Handling Needs Fixing.
af[0] = af[0] - hl[1];
Fbitbuffer = af[1];
if(af[0] == 0x00)
{
Fbitbuffer[7] = 1;
Fbitbuffer[6] = 1;
}
if(af[0] != 0x00)
{
Fbitbuffer[7] = 0;
Fbitbuffer[6] = 1;
}
pc++;
cycles += 4;
break;

case 0xA1:
af[0] = bc[1] && af[0];
if(af[0] == 0x00)
{
af[1] = 0xA0;
goto A1Done;
}
af[1] = 0x20;
A1Done:
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

case 0xA9:
af[0] = bc[1] ^ af[0];
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

case 0xAE:
hlbuffer = hl[0] << 8 | hl[1];
af[0] = memory[hlbuffer] ^ af[0];
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

case 0xB0:
if(bc[0] > af[0])
{
af[0] = bc[0];
goto done0xB0;
}
if(bc[0] < af[0])
{
af[0] = af[0];
}
done0xB0:
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

case 0xB7:
if(af[0] > af[0])
{
af[0] = af[0];
goto done0xB7;
}
if(af[0] < af[0])
{
af[0] = af[0];
}
done0xB7:
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

case 0xBE: // Flags need fixed.
hlbuffer = hl[0] << 8 | hl[1];
tem = af[0] - memory[hlbuffer];
Fbitbuffer = af[1];
if(tem == 0x00)
{
Fbitbuffer[7] = 1;
Fbitbuffer[6] = 1;
}
if(tem != 0x00)
{
Fbitbuffer[7] = 0;
Fbitbuffer[6] = 1;
}
pc++;
cycles += 8;
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

case 0xC2:
Fbitbuffer = af[1];
if (Fbitbuffer[7] == 0)
{
opnn[0] = memory[pc + 2];
opnn[1] = memory[pc + 1];
nn = opnn[0] << 8 | opnn[1];
pc = nn;
cycles += 12;
goto done0xC2;
}
if (Fbitbuffer[7] == 0)
{
pc += 3;
cycles += 12;
goto done0xC2;
}
done0xC2:
break;

case 0xC3:
opnn[0] = memory[pc + 2];
opnn[1] = memory[pc + 1];
nn = opnn[0] << 8 | opnn[1];
pc = nn;
cycles += 4;
break;

case 0xC4:
Abitbuffer = af[1];
if(Abitbuffer[7] == 0)
{
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
goto done0xC4;
}
pc += 3;
cycles += 12;


done0xC4:
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

case 0xC6:
af[0] = af[0] + memory[pc + 1];
if(af[0] == 0x00)
{
af[1] = 0x80;
}
if(af[0] != 0x00)
{
af[1] = 0x00;
}
pc += 2;
cycles += 8;
break;

case 0xC7:
// Note: 0xEF2 has the First bit, while 0xEF has the second.
pc++;
backupPC0xEF = pc;
help0xEF = pc; // to copy the first 8 bits.
pc = pc>>8; //push the other 8 bits to the right
help0xEF2 = pc;
pc = backupPC0xEF;
sp[1]--;
if(sp[1] == 0xFF)
{
sp[0]--;
}
spbuffer = sp[0] << 8 | sp[1];
memory[spbuffer] = (help0xEF2 - 0xFFFFFF00);
sp[1]--;
if(sp[1] == 0xFF)
{
sp[0]--;
}
spbuffer = sp[0] << 8 | sp[1];
memory[spbuffer] = (help0xEF - 0xFFFFFF00); // End of copying current PC to mem at SP
pc = 0x0000;
cycles += 32;
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
//printf("help0xC9: 0x%X\n", help0xC9);
//printf("help0xC92: 0x%X\n", help0xC92);
pc = help0xC9 << 8 | help0xC92;
//printf("pc: 0x%X\n",pc);
sp[1] += 0x02;
if(sp[1] == 0x00 || sp[1] == 0x01)
{
sp[0] += 0x01;
}
cycles += 8;
break;

case 0xCA:
Fbitbuffer = af[1];
if (Fbitbuffer[7] == 1)
{
opnn[0] = memory[pc + 2];
opnn[1] = memory[pc + 1];
nn = opnn[0] << 8 | opnn[1];
pc = nn;
cycles += 12;
goto done0xCA;
}
if (Fbitbuffer[7] == 0)
{
pc += 3;
cycles += 12;
goto done0xCA;
}
done0xCA:
break;

case 0xCB:
switch(next_opcode)
{

    case 0x19:
    Cbitbuffer = bc[1];
    Fbitbuffer = af[1];
    Carry_Helper[0] = Cbitbuffer[0];
    Carry_Helper2[0] = Fbitbuffer[4];
    Cbitbuffer = Cbitbuffer >> 1;
    Cbitbuffer[7] = Carry_Helper2[0];
    bc[1] = Cbitbuffer.to_ulong();
    if(bc[1] == 0x00)
    {
    Fbitbuffer[7] = 1;
    Fbitbuffer[6] = 0;
    Fbitbuffer[5] = 0;
    Fbitbuffer[4] = Carry_Helper[0];
    }
    if(bc[1] != 0x00)
    {
    Fbitbuffer[7] = 1;
    Fbitbuffer[6] = 0;
    Fbitbuffer[5] = 0;
    Fbitbuffer[4] = Carry_Helper[0];
    }
    af[1] = Fbitbuffer.to_ulong();
    pc += 2;
    cycles += 8;
    break;

    case 0x1A:
    Dbitbuffer = de[0];
    Fbitbuffer = af[1];
    Carry_Helper[0] = Dbitbuffer[0];
    Carry_Helper2[0] = Fbitbuffer[4];
    Dbitbuffer = Dbitbuffer >> 1;
    Dbitbuffer[7] = Carry_Helper2[0];
    de[0] = Dbitbuffer.to_ulong();
    if(de[0] == 0x00)
    {
    Fbitbuffer[7] = 1;
    Fbitbuffer[6] = 0;
    Fbitbuffer[5] = 0;
    Fbitbuffer[4] = Carry_Helper[0];
    }
    if(de[0] != 0x00)
    {
    Fbitbuffer[7] = 1;
    Fbitbuffer[6] = 0;
    Fbitbuffer[5] = 0;
    Fbitbuffer[4] = Carry_Helper[0];
    }
    af[1] = Fbitbuffer.to_ulong();
    pc += 2;
    cycles += 8;
    break;

    case 0x28:
    Bbitbuffer = bc[0];
    Fbitbuffer = af[1];
    MSB_Helper[0] = Bbitbuffer[7];
    Carry_Helper[0] = Bbitbuffer[0];
    Bbitbuffer = Bbitbuffer >> 1;
    Bbitbuffer[7] = MSB_Helper[0];
    bc[0] = Bbitbuffer.to_ulong();
    if(bc[0] == 0x00)
    {
    Fbitbuffer[7] = 1;
    Fbitbuffer[6] = 0;
    Fbitbuffer[5] = 0;
    Fbitbuffer[4] = Carry_Helper[0];
    }
    if(bc[0] != 0x00)
    {
    Fbitbuffer[6] = 0;
    Fbitbuffer[5] = 0;
    Fbitbuffer[4] = Carry_Helper[0];
    }
    af[1] = Fbitbuffer.to_ulong();
    pc += 2;
    cycles += 8;
    break;


    case 0x37:
    af[0] = ( (af[0] & 0x0F) << 4 | (af[0] & 0xF0) >> 4 );
    if (af[0] == 0x00)
    {
    af[1] = 0x80;
    }
    if (af[0] != 0x00)
    {
    af[1] = 0x00;
    }
    cycles += 8;
    pc += 2;
    break; // Ends 0xCB37 Case

    case 0x38:
    Bbitbuffer = bc[0];
    Fbitbuffer = af[1];
    MSB_Helper[0] = Bbitbuffer[7];
    Carry_Helper[0] = Bbitbuffer[0];
    Bbitbuffer = Bbitbuffer >> 1;
    MSB_Helper[0] = 0;
    Bbitbuffer[7] = MSB_Helper[0];
    bc[0] = Bbitbuffer.to_ulong();
    if(bc[0] == 0x00)
    {
    Fbitbuffer[7] = 1;
    Fbitbuffer[6] = 0;
    Fbitbuffer[5] = 0;
    Fbitbuffer[4] = Carry_Helper[0];
    }
    if(bc[0] != 0x00)
    {
    Fbitbuffer[6] = 0;
    Fbitbuffer[5] = 0;
    Fbitbuffer[4] = Carry_Helper[0];
    }
    af[1] = Fbitbuffer.to_ulong();
    pc += 2;
    cycles += 8;
    break;

    case 0x50:
    Bbitbuffer = bc[0];
    Fbitbuffer = af[1];
    if(Bbitbuffer[2] == 0)
    {
    Fbitbuffer[7] = 1;
    Fbitbuffer[6] = 0;
    Fbitbuffer[5] = 1;
    }
    if(Bbitbuffer[2] == 1)
    {
    Fbitbuffer[7] = 0;
    Fbitbuffer[6] = 0;
    Fbitbuffer[5] = 1;
    }
    af[1] = Fbitbuffer.to_ulong();
    pc += 2;
    cycles += 8;
    break;

    case 0x7C:
    Hbitbuffer = hl[0];
    Fbitbuffer = af[1];
    if(Hbitbuffer[7] == 0)
    {
    Fbitbuffer[7] = 1;
    Fbitbuffer[6] = 0;
    Fbitbuffer[5] = 1;
    }
    if(Hbitbuffer[7] == 1)
    {
    Fbitbuffer[7] = 0;
    Fbitbuffer[6] = 0;
    Fbitbuffer[5] = 1;
    }
    af[1] = Fbitbuffer.to_ulong();
    pc += 2;
    cycles += 8;
    break;

    case 0x7E:
    hlbuffer = hl[0] << 8 | hl[1];
    MEMbitbuffer = memory[hlbuffer];
    Fbitbuffer = af[1];
    if (MEMbitbuffer[7] == 0)
    {
    Fbitbuffer[7] = 1;
    Fbitbuffer[6] = 0;
    Fbitbuffer[5] = 1;
    af[1] = Fbitbuffer.to_ulong();
    }
    if (MEMbitbuffer[7] == 1)
    {
    Fbitbuffer[6] = 0;
    Fbitbuffer[5] = 1;
    af[1] = Fbitbuffer.to_ulong();
    }
    pc += 2;
    cycles += 16;
    break;

    case 0x7F: // Flags need fixing?
    Abitbuffer = af[0];
    Fbitbuffer = af[1];
    if(Abitbuffer[7] == 0)
    {
    Fbitbuffer[7] = 1;
    Fbitbuffer[6] = 0;
    Fbitbuffer[5] = 1;
    }
    if(Abitbuffer[7] == 1)
    {
    Fbitbuffer[7] = 0;
    Fbitbuffer[6] = 0;
    Fbitbuffer[5] = 1;
    }
    af[1] = Fbitbuffer.to_ulong();
    pc += 2;
    cycles += 8;
    break;

    case 0x80:
    Bbitbuffer = bc[0];
    Bbitbuffer.reset(0);
    bc[0] = Bbitbuffer.to_ulong();
    pc += 2;
    cycles += 8;
    break;

    case 0x81:
    Cbitbuffer = bc[1];
    Cbitbuffer.reset(0);
    bc[1] = Cbitbuffer.to_ulong();
    pc += 2;
    cycles += 8;
    break;

    case 0x82:
    Dbitbuffer = de[0];
    Dbitbuffer.reset(0);
    de[0] = Dbitbuffer.to_ulong();
    pc += 2;
    cycles += 8;
    break;

    case 0x83:
    Ebitbuffer = de[1];
    Ebitbuffer.reset(0);
    de[1] = Ebitbuffer.to_ulong();
    pc += 2;
    cycles += 8;
    break;

    case 0x84:
    Hbitbuffer = hl[0];
    Hbitbuffer.reset(0);
    hl[0] = Hbitbuffer.to_ulong();
    pc += 2;
    cycles += 8;
    break;

    case 0x85:
    Lbitbuffer = hl[1];
    Lbitbuffer.reset(0);
    hl[1] = Lbitbuffer.to_ulong();
    pc += 2;
    cycles += 8;
    break;

    case 0x86:
    hlbuffer = hl[0] << 8 | hl[1];
    MEMbitbuffer = memory[hlbuffer];
    MEMbitbuffer.reset(0);
    memory[hlbuffer] = MEMbitbuffer.to_ulong();
    pc += 2;
    cycles += 16;
    break;

    case 0x87:
    Abitbuffer = af[0];
    Abitbuffer.reset(0);
    af[0] = Abitbuffer.to_ulong();
    pc += 2;
    cycles += 8;
    break;

    case 0xBE:
    hlbuffer = hl[0] << 8 | hl[1];
    MEMbitbuffer = memory[hlbuffer];
    MEMbitbuffer.reset(7);
    memory[hlbuffer] = MEMbitbuffer.to_ulong();
    pc += 2;
    cycles += 16;
    break;

    case 0xBF:
    Abitbuffer = af[0];
    Abitbuffer[7] = 0;
    af[0] = Abitbuffer.to_ulong();
    pc += 2;
    cycles += 8;
    break;

    case 0xC7:
    Abitbuffer = af[0];
    Abitbuffer[0] = 1;
    af[0] = Abitbuffer.to_ulong();
    pc += 2;
    cycles += 8;
    break;

    case 0xE6:
    hlbuffer = hl[0] << 8 | hl[1];
    MEMbitbuffer = memory[hlbuffer];
    MEMbitbuffer.set(4);
    memory[hlbuffer] = MEMbitbuffer.to_ulong();
    pc += 2;
    cycles += 16;
    break;

    case 0xEE:
    hlbuffer = hl[0] << 8 | hl[1];
    MEMbitbuffer = memory[hlbuffer];
    MEMbitbuffer.set(5);
    memory[hlbuffer] = MEMbitbuffer.to_ulong();
    pc += 2;
    cycles += 16;
    break;

    case 0xF6:
    hlbuffer = hl[0] << 8 | hl[1];
    MEMbitbuffer = memory[hlbuffer];
    MEMbitbuffer.set(6);
    memory[hlbuffer] = MEMbitbuffer.to_ulong();
    pc += 2;
    cycles += 16;
    break;

    case 0xFE:
    hlbuffer = hl[0] << 8 | hl[1];
    MEMbitbuffer = memory[hlbuffer];
    MEMbitbuffer.set(7);
    memory[hlbuffer] = MEMbitbuffer.to_ulong();
    pc += 2;
    cycles += 16;
    break;

    case 0xFF:
    Abitbuffer = af[0];
    Abitbuffer[7] = 1;
    af[0] = Abitbuffer.to_ulong();
    pc += 2;
    cycles += 8;
    break;

    default:
    goto invalid_opcode_jump;
    break;
    }
    break; // Ends entire 0xCB Case


case 0xCC:
Abitbuffer = af[1];
if(Abitbuffer[7] == 1)
{
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
goto done0xCC;
}
pc += 3;
cycles += 12;

done0xCC:
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

case 0xCE: // Flags need fixed.
af[0] = af[0] + memory[pc + 0x01];
Fbitbuffer = af[1];
if (Fbitbuffer[4] == 1)
{
af[0]++;
}
if (Fbitbuffer[4] == 0)
{
}
if (af[0] == 0x00)
{
Fbitbuffer[7] = 1;
Fbitbuffer[6] = 0;
}
if (af[0] != 0x00)
{
Fbitbuffer[7] = 0;
Fbitbuffer[6] = 0;
}
pc += 2;
cycles += 8;
break;

case 0xCF:
// Note: 0xEF2 has the First bit, while 0xEF has the second.
pc++;
backupPC0xEF = pc;
help0xEF = pc; // to copy the first 8 bits.
pc = pc>>8; //push the other 8 bits to the right
help0xEF2 = pc;
pc = backupPC0xEF;
sp[1]--;
if(sp[1] == 0xFF)
{
sp[0]--;
}
spbuffer = sp[0] << 8 | sp[1];
memory[spbuffer] = (help0xEF2 - 0xFFFFFF00);
sp[1]--;
if(sp[1] == 0xFF)
{
sp[0]--;
}
spbuffer = sp[0] << 8 | sp[1];
memory[spbuffer] = (help0xEF - 0xFFFFFF00); // End of copying current PC to mem at SP
pc = 0x0008;
cycles += 32;
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

case 0xD6:
af[0] = af[0] - memory[pc + 1];
if(af[0] == 0x00)
{
af[1] = 0x80;
}
if(af[0] != 0x00)
{
af[1] = 0x00;
}
pc += 2;
cycles += 8;
break;

case 0xD9:
help0xE1 = sp[0] << 8 | sp[1];
help0xD9[0] = memory[help0xE1 + 1];
help0xD9[1] = memory[help0xE1];
pc = (help0xD9[0] - 0xFFFFFF00) << 8 | (help0xD9[1] - 0xFFFFFF00);
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
af[0] = af[0] && memory[pc + 0x01];
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

case 0xE9:
hlbuffer = hl[0] << 8 | hl[1];
pc = hlbuffer;
cycles += 4;
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

case 0xEE:
af[0] = memory[pc + 0x01] ^ af[0];
if(af[0] == 0x0)
{
af[1] = 0x80;
}
if(af[0] != 0x0)
{
af[1] = 0x00;
}
pc += 2;
cycles += 4;
break;

case 0xEF:
// Note: 0xEF2 has the First bit, while 0xEF has the second.
pc++;
backupPC0xEF = pc;
help0xEF = pc; // to copy the first 8 bits.
pc = pc>>8; //push the other 8 bits to the right
help0xEF2 = pc;
pc = backupPC0xEF;
sp[1]--;
if(sp[1] == 0xFF)
{
sp[0]--;
}
spbuffer = sp[0] << 8 | sp[1];
memory[spbuffer] = (help0xEF2 - 0xFFFFFF00);
sp[1]--;
if(sp[1] == 0xFF)
{
sp[0]--;
}
spbuffer = sp[0] << 8 | sp[1];
memory[spbuffer] = (help0xEF - 0xFFFFFF00); // End of copying current PC to mem at SP
pc = 0x0028;
cycles += 32;
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

case 0xF9:
sp[0] = hl[0];
sp[1] = hl[1];
pc++;
cycles += 8;
break;

case 0xFA:
nn = memory[pc + 2] << 8 | memory[pc + 1];
//printf("nn:0x%X\n",nn);
af[0] = memory[nn - 0xFFFF0000];
//printf("a:0x%X\n",af[0]);
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
if(af[0] == (memory[pc + 1] - 0xFFFFFF00))
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

case 0xFF:
// Note: 0xEF2 has the First bit, while 0xEF has the second.
pc++;
backupPC0xEF = pc;
help0xEF = pc; // to copy the first 8 bits.
pc = pc>>8; //push the other 8 bits to the right
help0xEF2 = pc;
pc = backupPC0xEF;
sp[1]--;
if(sp[1] == 0xFF)
{
sp[0]--;
}
spbuffer = sp[0] << 8 | sp[1];
memory[spbuffer] = (help0xEF2 - 0xFFFFFF00);
sp[1]--;
if(sp[1] == 0xFF)
{
sp[0]--;
}
spbuffer = sp[0] << 8 | sp[1];
memory[spbuffer] = (help0xEF - 0xFFFFFF00); // End of copying current PC to mem at SP
pc = 0x0038;
cycles += 32;
break;


default:
invalid_opcode_jump:
if (opcode != 0xCB)
{
printf("\nAn error has Occured\nUnknown Opcode: 0x%X", opcode);
}
if (opcode == 0xCB)
{
printf("\nAn error has Occured\nUnknown CB Opcode 0x%X", next_opcode);
}
printf("\nProgram Counter: 0x%X\n", pc);
printf("Stack Pointer: 0x%X%X\n", sp[0], sp[1]);
printf("Cycles: %i\n", cycles);
printf("Please see errorlog.txt for more details.\n");
printf("Please see memdump for a full Gameboy RAM Dump.\n");
printf("Type anything and press enter to close.");
std::cin>>dummychar;
if(sdl_wanted == true)
{
SDL_DestroyWindow(AGBE_window);
SDL_Quit();
}
close_program = true;
FILE * mem_dump;
mem_dump = fopen ("log/memdump", "w+");
fwrite (memory , sizeof(char), sizeof(memory), mem_dump);
fclose (mem_dump);
FILE * error_log;
error_log = fopen ("log/errorlog.txt", "w+");
fprintf (error_log, "An Unknown Opcode was Encountered.\n");
fprintf (error_log, "Opcode: 0x%X\n", opcode);
if (opcode == 0xCB)
{
fprintf (error_log, "CB Opcode: 0x%X\n",next_opcode);
}
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

if (doBios == true)
{
FILE* BIOS = fopen("BIOS/GB.BIOS", "rb");
fseek(BIOS,0,SEEK_END);
bios_size = ftell(BIOS);
rewind(BIOS);
fread(memory,bios_size,1,BIOS);
fclose(BIOS);
pc = 0x0000;
}
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
    if(debugmeminit >= 0xA000)
    {
    memory[debugmeminit] = 0xFF;
    }
    if(debugmeminit < 0xA000)
    {
    memory[debugmeminit] = 0x00;
    }
goto debug_mem_init_again;
}
if(debugmeminit == 0x10000)
{

}

}
