#include "mbc.hpp"
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

if (Title4[0] == 'D' && Title4[1] == 'R' && Title4[2] == '.' && Title4[3] == 'M') // Dr. Mario
{
    if(helperforHacks == false)
    {
        helperforHacks = true;
        printf("Dr. Mario Hack Enabled.\n");
    }
    memory[0xFFBF] = 0xC9;

    if(pc == 0x035B)
    {
        pc = 0x035E;
        //printf("VBLANK\n");
        ime = false;
        Interupt_thing = false;
        help0xCD3 = sp[0];
        nn = help0xCD3 << 8 | sp[1];
        help0xCD = (pc) >> 8;
        help0xCD2 = (pc);
        memory[(nn - 0xFFFF0000) - 0x02] = help0xCD2;
        memory[(nn - 0xFFFF0000) - 0x01] = help0xCD;
        pc = 0x0040;
        sp[1] -= 0x02;
        if(sp[1] == 0xFF || sp[1] == 0xFE)
        {
            sp[0] -= 0x01;
        }
        memory[0xFF0F] = 0x00; // Note: if there is a bug where interupts are skipped, this is probably the line of code that would cause it.
        memory[0xFFFF] = 0x00;
    }
}
if (Title4[0] == 'T' && Title4[1] == 'E' && Title4[2] == 'T' && Title4[3] == 'R') // Tetris
{
    memory[0xFFBF] = 0xC9;
    memory[0xFF85] = 0x91;
    int16_t tetrisCounter;
    if(helperforHacks == false)
    {
        helperforHacks = true;
        printf("Tetris Hack Enabled.\n");
    }
    tetrisCounter++;

    if(pc == 0x036E && 0 == 1)
    {
        pc = 0x0371;
        //printf("VBLANK\n");
        ime = false;
        Interupt_thing = false;
        help0xCD3 = sp[0];
        nn = help0xCD3 << 8 | sp[1];
        help0xCD = (pc) >> 8;
        help0xCD2 = (pc);
        memory[(nn - 0xFFFF0000) - 0x02] = help0xCD2;
        memory[(nn - 0xFFFF0000) - 0x01] = help0xCD;
        pc = 0x0040;
        sp[1] -= 0x02;
        if(sp[1] == 0xFF || sp[1] == 0xFE)
        {
            sp[0] -= 0x01;
        }
        memory[0xFF0F] = 0x00; // Note: if there is a bug where interupts are skipped, this is probably the line of code that would cause it.
        memory[0xFFFF] = 0x00;
    }

}
if (Title4[0] == 'T' && Title4[1] == 'E' && Title4[2] == 'N' && Title4[3] == 'N') // Tennis
{
    memory[0xFF80] = 0x3E;
    memory[0xFF81] = 0xDE;
    memory[0xFF82] = 0xE0;
    memory[0xFF83] = 0x46;
    memory[0xFF84] = 0x3E;
    memory[0xFF85] = 0x28;
    memory[0xFF86] = 0x3D;
    memory[0xFF87] = 0x20;
    memory[0xFF88] = 0xFD;
    memory[0xFF89] = 0xC9;
    if(helperforHacks == false)
    {
        helperforHacks = true;
        printf("Tennis Hack Enabled.\n");
    }
    if(pc == 0x02AE)
    {
        pc = 0x02AF;
        //printf("VBLANK\n");
        ime = false;
        Interupt_thing = false;
        help0xCD3 = sp[0];
        nn = help0xCD3 << 8 | sp[1];
        help0xCD = (pc) >> 8;
        help0xCD2 = (pc);
        memory[(nn - 0xFFFF0000) - 0x02] = help0xCD2;
        memory[(nn - 0xFFFF0000) - 0x01] = help0xCD;
        pc = 0x0040;
        sp[1] -= 0x02;
        if(sp[1] == 0xFF || sp[1] == 0xFE)
        {
            sp[0] -= 0x01;
        }
        memory[0xFF0F] = 0x00; // Note: if there is a bug where interupts are skipped, this is probably the line of code that would cause it.
        memory[0xFFFF] = 0x00;
    }
    if(pc == 0x02DD)
    {
        pc = 0x02DE;
        //printf("VBLANK\n");
        ime = false;
        Interupt_thing = false;
        help0xCD3 = sp[0];
        nn = help0xCD3 << 8 | sp[1];
        help0xCD = (pc) >> 8;
        help0xCD2 = (pc);
        memory[(nn - 0xFFFF0000) - 0x02] = help0xCD2;
        memory[(nn - 0xFFFF0000) - 0x01] = help0xCD;
        pc = 0x0040;
        sp[1] -= 0x02;
        if(sp[1] == 0xFF || sp[1] == 0xFE)
        {
            sp[0] -= 0x01;
        }
        memory[0xFF0F] = 0x00; // Note: if there is a bug where interupts are skipped, this is probably the line of code that would cause it.
        memory[0xFFFF] = 0x00;
    }
    if(pc == 0x03FF)
    {
        pc = 0x0400;
        //printf("VBLANK\n");
        ime = false;
        Interupt_thing = false;
        help0xCD3 = sp[0];
        nn = help0xCD3 << 8 | sp[1];
        help0xCD = (pc) >> 8;
        help0xCD2 = (pc);
        memory[(nn - 0xFFFF0000) - 0x02] = help0xCD2;
        memory[(nn - 0xFFFF0000) - 0x01] = help0xCD;
        pc = 0x0040;
        sp[1] -= 0x02;
        if(sp[1] == 0xFF || sp[1] == 0xFE)
        {
            sp[0] -= 0x01;
        }
        memory[0xFF0F] = 0x00; // Note: if there is a bug where interupts are skipped, this is probably the line of code that would cause it.
        memory[0xFFFF] = 0x00;
    }
    if(pc == 0x039D)
    {
        pc = 0x039E;
        //printf("VBLANK\n");
        ime = false;
        Interupt_thing = false;
        help0xCD3 = sp[0];
        nn = help0xCD3 << 8 | sp[1];
        help0xCD = (pc) >> 8;
        help0xCD2 = (pc);
        memory[(nn - 0xFFFF0000) - 0x02] = help0xCD2;
        memory[(nn - 0xFFFF0000) - 0x01] = help0xCD;
        pc = 0x0040;
        sp[1] -= 0x02;
        if(sp[1] == 0xFF || sp[1] == 0xFE)
        {
            sp[0] -= 0x01;
        }
        memory[0xFF0F] = 0x00; // Note: if there is a bug where interupts are skipped, this is probably the line of code that would cause it.
        memory[0xFFFF] = 0x00;
    }
}
if (Title4[0] == 'K' && Title4[1] == 'I' && Title4[2] == 'R' && Title4[3] == 'B') // Kirby Dream Land 1
{
    memory[0xFF91]++;
    memory[0xFF91]++;

    if(pc == 0x1DC9)
    {
        printf("VBlank\n");
                help0xCD3 = sp[0];
                nn = help0xCD3 << 8 | sp[1];
                help0xCD = (pc) >> 8;
                help0xCD2 = (pc);
                memory[(nn - 0xFFFF0000) - 0x02] = help0xCD2;
                memory[(nn - 0xFFFF0000) - 0x01] = help0xCD;
                pc = 0x0040;
                sp[1] -= 0x02;
                if(sp[1] == 0xFF || sp[1] == 0xFE)
                {
                    sp[0] -= 0x01;
                }
                MEMbitbuffer = memory[0xFFFF];
                MEMbitbuffer[0] = 0;
                memory[0xFFFF] = MEMbitbuffer.to_ulong();
                MEMbitbuffer = memory[0xFF0F];
                MEMbitbuffer[0] = 0;
                memory[0xFF0F] = MEMbitbuffer.to_ulong();
    }
    if(helperforHacks == false)
    {
        helperforHacks = true;
        printf("Kirby's Dream Land 1 Hack Enabled.\n");
    }
}
if (Title4[0] == 'Z' && Title4[1] == 'E' && Title4[2] == 'L' && Title4[3] == 'D') // Lozla
{
    memory[0xFFD1]++;
    if(helperforHacks == false)
    {
        helperforHacks = true;
        printf("Link Awakening Hack Enabled.\n");
    }
}
if (Title4[0] == 'M' && Title4[1] == 'A' && Title4[2] == 'R' && Title4[3] == 'I') // Mario Land
{
    /*
    if(pc == 0x0296)
    {
                //printf("VBlank\n");
                pc = 0x0297;
                help0xCD3 = sp[0];
                nn = help0xCD3 << 8 | sp[1];
                help0xCD = (pc) >> 8;
                help0xCD2 = (pc);
                memory[(nn - 0xFFFF0000) - 0x02] = help0xCD2;
                memory[(nn - 0xFFFF0000) - 0x01] = help0xCD;
                pc = 0x0040;
                sp[1] -= 0x02;
                if(sp[1] == 0xFF || sp[1] == 0xFE)
                {
                    sp[0] -= 0x01;
                }
                MEMbitbuffer = memory[0xFFFF];
                MEMbitbuffer[0] = 0;
                memory[0xFFFF] = MEMbitbuffer.to_ulong();
                MEMbitbuffer = memory[0xFF0F];
                MEMbitbuffer[0] = 0;
                memory[0xFF0F] = MEMbitbuffer.to_ulong();
    }
    */
    memory[0xFF82]++;
    if(helperforHacks == false)
    {
        helperforHacks = true;
        printf("Mario Land Hack Enabled.\n");
    }
}
if (Title4[0] == 'W' && Title4[1] == 'A' && Title4[2] == 'R' && Title4[3] == 'I') // Wario land (with modified title)
{
    if(pc == 0x02D3)
    {
        printf("VBlank\n");
                help0xCD3 = sp[0];
                nn = help0xCD3 << 8 | sp[1];
                help0xCD = (pc) >> 8;
                help0xCD2 = (pc);
                memory[(nn - 0xFFFF0000) - 0x02] = help0xCD2;
                memory[(nn - 0xFFFF0000) - 0x01] = help0xCD;
                pc = 0x0040;
                sp[1] -= 0x02;
                if(sp[1] == 0xFF || sp[1] == 0xFE)
                {
                    sp[0] -= 0x01;
                }
                MEMbitbuffer = memory[0xFFFF];
                MEMbitbuffer[0] = 0;
                memory[0xFFFF] = MEMbitbuffer.to_ulong();
                MEMbitbuffer = memory[0xFF0F];
                MEMbitbuffer[0] = 0;
                memory[0xFF0F] = MEMbitbuffer.to_ulong();
    }
    if(helperforHacks == false)
    {
        helperforHacks = true;
        printf("Wario.\n");
    }
}
if (Title4[0] == 'G' && Title4[1] == 'O' && Title4[2] == 'L' && Title4[3] == 'F') // Golf
{
    if(pc == 0x021E)
    {
        printf("VBlank\n");
                help0xCD3 = sp[0];
                nn = help0xCD3 << 8 | sp[1];
                help0xCD = (pc) >> 8;
                help0xCD2 = (pc);
                memory[(nn - 0xFFFF0000) - 0x02] = help0xCD2;
                memory[(nn - 0xFFFF0000) - 0x01] = help0xCD;
                pc = 0x0040;
                sp[1] -= 0x02;
                if(sp[1] == 0xFF || sp[1] == 0xFE)
                {
                    sp[0] -= 0x01;
                }
                MEMbitbuffer = memory[0xFFFF];
                MEMbitbuffer[0] = 0;
                memory[0xFFFF] = MEMbitbuffer.to_ulong();
                MEMbitbuffer = memory[0xFF0F];
                MEMbitbuffer[0] = 0;
                memory[0xFF0F] = MEMbitbuffer.to_ulong();
    }
    if(helperforHacks == false)
    {
        helperforHacks = true;
        printf("Wario.\n");
    }
}
if (Title4[0] == 'D' && Title4[1] == 'U' && Title4[2] == 'C' && Title4[3] == 'K') // Kirby Dream Land 1
{
    if(pc == 0x3731)
    {
        printf("VBlank\n");
                help0xCD3 = sp[0];
                nn = help0xCD3 << 8 | sp[1];
                help0xCD = (pc) >> 8;
                help0xCD2 = (pc);
                memory[(nn - 0xFFFF0000) - 0x02] = help0xCD2;
                memory[(nn - 0xFFFF0000) - 0x01] = help0xCD;
                pc = 0x0040;
                sp[1] -= 0x02;
                if(sp[1] == 0xFF || sp[1] == 0xFE)
                {
                    sp[0] -= 0x01;
                }
                MEMbitbuffer = memory[0xFFFF];
                MEMbitbuffer[0] = 0;
                memory[0xFFFF] = MEMbitbuffer.to_ulong();
                MEMbitbuffer = memory[0xFF0F];
                MEMbitbuffer[0] = 0;
                memory[0xFF0F] = MEMbitbuffer.to_ulong();
                memory[0xFF91]++;
    }
    if(helperforHacks == false)
    {
        helperforHacks = true;
        printf("Duck Hack Enabled.\n");
    }
}
if (Title4[0] == 'P' && Title4[1] == 'O' && Title4[2] == 'K' && Title4[3] == 'E') // Pokemon Blue
{
    if(pc == 0x20B4)
    {
        printf("VBlank\n");
                help0xCD3 = sp[0];
                nn = help0xCD3 << 8 | sp[1];
                help0xCD = (pc) >> 8;
                help0xCD2 = (pc);
                memory[(nn - 0xFFFF0000) - 0x02] = help0xCD2;
                memory[(nn - 0xFFFF0000) - 0x01] = help0xCD;
                pc = 0x0040;
                sp[1] -= 0x02;
                if(sp[1] == 0xFF || sp[1] == 0xFE)
                {
                    sp[0] -= 0x01;
                }
                MEMbitbuffer = memory[0xFFFF];
                MEMbitbuffer[0] = 0;
                memory[0xFFFF] = MEMbitbuffer.to_ulong();
                MEMbitbuffer = memory[0xFF0F];
                MEMbitbuffer[0] = 0;
                memory[0xFF0F] = MEMbitbuffer.to_ulong();
                memory[0xFF91]++;
    }
    if(helperforHacks == false)
    {
        helperforHacks = true;
        printf("Pokemon Blue Hack Enabled.\n");
    }
}
}
