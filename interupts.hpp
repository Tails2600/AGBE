#include "timers.hpp"

int checkInterrupts()
{
    if(Interrupts_Enabled == true)
    {
        if(cycles % 70000 == 0x00)
        {
            Interupt_thing = true;
        }
    }
    if(Interrupts_Enabled == false)
    {
        Interupt_thing = false;
    }
    if(Interupt_thing == true)
    {
        VBlank_Interupt_Needs_Done = true;
    }
}

int handleInterupts() // Handles Interupts (Not Finished at all)
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
            goto done_with_interupt_processing;
        break;
    }
    if(VBlank_Interupt_Needs_Done == true) // If the VBLank interupt Needs done, execute this.
    {
        // Do VBlank Interupt
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
        VBlank_Interupt_Needs_Done = false;
    }
    done_with_interupt_processing:
    return true;
}
