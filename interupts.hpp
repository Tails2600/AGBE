#include "timers.hpp"

int joypadInterrupt()
{
    MEMbitbuffer = memory[0xFF00];
    if(MEMbitbuffer[0] == 0 || MEMbitbuffer[1] == 0 || MEMbitbuffer[2] == 0 || MEMbitbuffer[3] == 0)
    {
    MEMbitbuffer = memory[0xFF0F];
    MEMbitbuffer[4] == 1;
        if(MEMbitbuffer[4] == 1) // VBlank
        {
            MEMbitbuffer = memory[0xFFFF];
            if(MEMbitbuffer[4] == 1 && interruptEnable == true)
            {
                //advanced_debugging_enabled = true;
                printf("JoyPad\n");
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
        }
    }
}

int checkInterrupts()
{
    //if(interruptEnable == true)
    //{
        if(cycles % 65664 * 4 == 0x00) //65664
        {
            MEMbitbuffer = memory[0xFF0F];
            MEMbitbuffer[0] = 1;
            memory[0xFF0F] = MEMbitbuffer.to_ulong();
        }
        MEMbitbuffer = memory[0xFF0F];
        if(MEMbitbuffer[0] == 1) // VBlank
        {
            MEMbitbuffer = memory[0xFFFF];
            if(MEMbitbuffer[0] == 1 && interruptEnable == true)
            {
                //advanced_debugging_enabled = true;
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
        }
       // if(MEMbitbuffer[0] == 1)
        //{
        //    Interupt_thing = true;
       // }
    //}
    //if(Interrupts_Enabled == false)
    //{
    //    Interupt_thing = false;
    //}
    //if(Interupt_thing == true)
    //{
    //    VBlank_Interupt_Needs_Done = true;
    //}
    //}
}

int handleVblank()
{
    if(memory[0xFF44] == 0xFFFFFF91)
    {
        help0xFF44 = true;
    }
    if(memory[0xFF44] == 0xFFFFFF90 && help0xFF44 == true)
    {
        //MEMbitbuffer = memory[0xFF0F];
        //MEMbitbuffer[0] = 1; //
        //memory[0xFF0F] == MEMbitbuffer.to_ulong();
        help0xFF44 = false;
        memory[0xFF0F] = 0xE1;
    }
    if(cycles % 65664 == 0x00)
    {
        //MEMbitbuffer = memory[0xFF0F];
        //MEMbitbuffer[0] = 1; //
        //memory[0xFF0F] == MEMbitbuffer.to_ulong();
        memory[0xFF0F] = 0xE1;
    }
    FFFFbitbuffer = memory[0xFFFF];
    FF0Fbitbuffer = (memory[0xFF0F] - 0xFFFFFF00);
    if(FFFFbitbuffer[0] == 1 && memory[0xFF0F] == 0xFFFFFFE1 && interruptEnable == true)
    {
        interruptEnable = false;
        printf("VBLANK\n");
        spbuffer2 = sp[0] << 8 | sp[1];
        spbuffer2--;
        pcbuffer1 = pc >> 8;
        pcbuffer1 = pcbuffer1;
        pcbuffer2 = pc;
        memory[spbuffer2] = pcbuffer1;
        spbuffer2--;
        memory[spbuffer2] = pcbuffer2;
        pc = 0x0040;
        sp[1] -= 0x02;
        if(sp[1] == 0xFF || sp[1] == 0xFE)
        {
            sp[0]--;
        }
        MEMbitbuffer = memory[0xFF0F];
        MEMbitbuffer[0] = 0;
        memory[0xFF0F] = MEMbitbuffer.to_ulong();
        renderThreadFrame();
    }
}

int handleVblank2()
{
    if(memory[0xFF44] == 0xFFFFFF91)
    {
        help0xFF44 = true;
    }
    if(memory[0xFF44] == 0xFFFFFF90 && help0xFF44 == true)
    {
        //MEMbitbuffer = memory[0xFF0F];
        //MEMbitbuffer[0] = 1; //
        //memory[0xFF0F] == MEMbitbuffer.to_ulong();
        help0xFF44 = false;
        memory[0xFF0F] = 0xE1;
    }
    if(cycles % 65664 == 0x00)
    {
        //MEMbitbuffer = memory[0xFF0F];
        //MEMbitbuffer[0] = 1; //
        //memory[0xFF0F] == MEMbitbuffer.to_ulong();
        memory[0xFF0F] = 0xE1;
    }
    FFFFbitbuffer = memory[0xFFFF];
    FF0Fbitbuffer = (memory[0xFF0F] - 0xFFFFFF00);
    if(FFFFbitbuffer[0] == 1 && FF0Fbitbuffer[0] == 1 && interruptEnable == true)
    {
        interruptEnable = false;
        printf("VBLANK\n");
        spbuffer2 = sp[0] << 8 | sp[1];
        spbuffer2--;
        pcbuffer1 = pc >> 8;
        pcbuffer1 = pcbuffer1;
        pcbuffer2 = pc;
        memory[spbuffer2] = pcbuffer1;
        spbuffer2--;
        memory[spbuffer2] = pcbuffer2;
        pc = 0x0040;
        sp[1] -= 0x02;
        if(sp[1] == 0xFF || sp[1] == 0xFE)
        {
            sp[0]--;
        }
        MEMbitbuffer = memory[0xFF0F];
        MEMbitbuffer[0] = 0;
        memory[0xFF0F] = MEMbitbuffer.to_ulong();
        renderThreadFrame();
    }
}

int handleLCDInt()
{
    MEMbitbuffer = memory[0xFF41] - 0xFFFFFF00;
    if(MEMbitbuffer[6] == 1)
    {
        if(memory[0xFF44] == memory[0xFF45])
        {
            MEMbitbuffer[2] = 1;
        }
    }
    if(MEMbitbuffer[2] == 1)
    {
        FF0Fbitbuffer = memory[0xFF0F] - 0xFFFFFF00;
        FF0Fbitbuffer[1] = 1;
        memory[0xFF0F] = FF0Fbitbuffer.to_ulong();
    }
    FFFFbitbuffer = memory[0xFFFF];
    FF0Fbitbuffer = (memory[0xFF0F] - 0xFFFFFF00);
    if(FFFFbitbuffer[1] == 1 && FF0Fbitbuffer[1] == 1 && interruptEnable == true && memory[0xFF44] == memory[0xFF45] && MEMbitbuffer[6] == 1 && MEMbitbuffer[2] == 1)
    {
        interruptEnable = false;
        printf("LCD\n");
        spbuffer2 = sp[0] << 8 | sp[1];
        spbuffer2--;
        pcbuffer1 = pc >> 8;
        pcbuffer1 = pcbuffer1;
        pcbuffer2 = pc;
        memory[spbuffer2] = pcbuffer1;
        spbuffer2--;
        memory[spbuffer2] = pcbuffer2;
        pc = 0x0048;
        sp[1] -= 0x02;
        if(sp[1] == 0xFF || sp[1] == 0xFE)
        {
            sp[0]--;
        }
        MEMbitbuffer = memory[0xFF0F];
        MEMbitbuffer[1] = 0;
        memory[0xFF0F] = MEMbitbuffer.to_ulong();
    }
}


int handleInterupts2()
{
    handleLCDInt();
    handleVblank2();
}

int handleInterupts() // Handles Interupts (Not Finished at all)
{
    /*
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
            goto done_with_interupt_processing;
        break;
    }
    */
    if(VBlank_Interupt_Needs_Done == true) // If the VBLank interupt Needs done, execute this.
    {
        // Do VBlank Interupt
        VBlank_Interupt_Needs_Done = false;
        printf("VBLANK\n");
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
    done_with_interupt_processing:
    return true;
}
