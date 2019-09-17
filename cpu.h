#include "controls.hpp"
#include <time.h>
/* Finished Opcodes
Total:  499/500
Main Opcodes: 243/244
CB Opcodes 256/256
00 = 16/16   DONE
10 = 16/16   DONE
20 = 15/16   MISSING: 0x27
30 = 16/16   DONE
40 = 16/16   DONE
50 = 16/16   DONE
60 = 16/16   DONE
70 = 16/16   DONE
80 = 16/16   DONE
90 = 16/16   DONE
A0 = 16/16   DONE
B0 = 16/16   DONE
C0 = 15/15   DONE
CB00 = 16/16 DONE
CB10 = 16/16 DONE
CB20 = 16/16 DONE
CB30 = 16/16 DONE
CB40 = 16/16 DONE
CB50 = 16/16 DONE
CB60 = 16/16 DONE
CB70 = 16/16 DONE
CB80 = 16/16 DONE
CB90 = 16/16 DONE
CBA0 = 16/16 DONE
CBB0 = 16/16 DONE
CBC0 = 16/16 DONE
CBD0 = 16/16 DONE
CBE0 = 16/16 DONE
CBF0 = 16/16 DONE
D0 = 13/13   DONE
E0 = 11/11   DONE
F0 = 13/13   DONE
*/

int doOpcode()
{
    switch(opcode)
    {
        case 0x00: // Flag Checked
            pc++;
            cycles += 4;
        break;

        case 0x01: // Flag Checked
            bc[0] = memory[pc + 2];
            bc[1] = memory[pc + 1];
            pc += 3;
            cycles += 12;
        break;

        case 0x02: // Flag Checked
            bcbuffer = bc[0] << 8 | bc[1];
            memory[bcbuffer] = af[0];
            pc++;
            cycles += 8;
        break;

        case 0x03: // Flag Checked
            bc[1]++;
            if (bc[1] == 0x00)
            {
                bc[0]++;
            }
            pc++;
            cycles += 8;
        break;

        case 0x04: // Flag Checked
            beforeHcheck = bc[0];
            bc[0]++;
            Fbitbuffer = af[1];
            if(bc[0] == 0x00)
            {
                Fbitbuffer[7] = 1;
                Fbitbuffer[6] = 0;
                Fbitbuffer[5] = halfcarrycheck(beforeHcheck,bc[0]);
                goto done0x04;
            }
            Fbitbuffer[7] = 0;
            Fbitbuffer[6] = 0;
            Fbitbuffer[5] = halfcarrycheck(beforeHcheck,bc[0]);
            done0x04:
            af[1] = Fbitbuffer.to_ulong();
            cycles += 4;
            pc++;
        break;

        case 0x05: // Flag Checked
            Fbitbuffer = af[1];
            beforeHcheck = bc[0];
            bc[0]--;
            if(bc[0] == 0x00)
            {
                Fbitbuffer[7] = 1;
                Fbitbuffer[6] = 1;
                Fbitbuffer[5] = halfcarrycheck(beforeHcheck,bc[0]);
            }
            if(bc[0] != 0x00)
            {
                Fbitbuffer[7] = 0;
                Fbitbuffer[6] = 1;
                Fbitbuffer[5] = halfcarrycheck(beforeHcheck,bc[0]);
            }
            af[1] = Fbitbuffer.to_ulong();
            pc++;
            cycles += 4;
        break;

        case 0x06: // Flag Checked
            bc[0] = memory[pc + 1];
            cycles += 8;
            pc += 2;
        break;

        case 0x07:  // Flag Checked
            Abitbuffer = af[0];
            Carry_Helper[0] = Abitbuffer[7];
            Abitbuffer = Abitbuffer << 1;
            af[0] = Abitbuffer.to_ulong();
            Fbitbuffer = af[1];
            if(af[0] == 0x00)
            {
                Fbitbuffer[7] = 1;
                Fbitbuffer[6] = 0;
                Fbitbuffer[5] = 0;
                Fbitbuffer[4] = Carry_Helper[0];
            }
            if(af[0] != 0x00)
            {
                Fbitbuffer[7] = 0;
                Fbitbuffer[6] = 0;
                Fbitbuffer[5] = 0;
                Fbitbuffer[4] = Carry_Helper[0];
            }
            af[1] = Fbitbuffer.to_ulong();
            pc++;
            cycles += 4;
        break;

        case 0x08: // Flag Checked
            membuffer = memory[pc + 2] << 8 | memory[pc + 1];
            memory[membuffer] = sp[1];
            memory[membuffer + 1] = sp[0];
            pc += 3;
            cycles += 20;
        break;

        case 0x09: // Flags NOT CHECKED
            hlbuffer2 = hl[0] << 8 | hl[1];
            hlbuffer3 = bc[0] << 8 | bc[1];
            hlbuffer2 = hlbuffer2 + hlbuffer3;
            hl[0] = hlbuffer2 >> 8;
            hl[1] = hlbuffer2;
            pc++;
            cycles += 8;
        break;

        case 0x0A: // Flag Checked
            bcbuffer = bc[0] << 8 | bc[1];
            af[0] = memory[bcbuffer];
            pc++;
            cycles += 8;
        break;

        case 0x0B: // Flag Checked
            bc[1]--;
            if(bc[1] == 0xFF)
            {
                bc[0]--;
            }
            pc++;
            cycles += 8;
        break;

        case 0x0C: // Flag Checked
            Fbitbuffer = af[1];
            beforeHcheck = bc[1];
            bc[1]++;
            if(bc[1] == 0x00)
            {
                Fbitbuffer[7] = 1;
                Fbitbuffer[6] = 0;
                Fbitbuffer[5] = halfcarrycheck(beforeHcheck,bc[1]);
            }
            if(bc[1] != 0x00)
            {
                Fbitbuffer[7] = 0;
                Fbitbuffer[6] = 0;
                Fbitbuffer[5] = halfcarrycheck(beforeHcheck,bc[1]);
            }
            af[1] = Fbitbuffer.to_ulong();
            pc++;
            cycles += 4;
        break;

        case 0x0D: // Flag Checked
            Fbitbuffer = af[1];
            beforeHcheck = bc[1];
            bc[1]--;
            if(bc[1] == 0x00)
            {
                Fbitbuffer[7] = 1;
                Fbitbuffer[6] = 1;
                Fbitbuffer[5] = halfcarrycheck(beforeHcheck,bc[1]);
            }
            if(bc[1] != 0x00)
            {
                Fbitbuffer[7] = 0;
                Fbitbuffer[6] = 1;
                Fbitbuffer[5] = halfcarrycheck(beforeHcheck,bc[1]);
            }
            af[1] = Fbitbuffer.to_ulong();
            pc++;
            cycles += 4;
        break;

        case 0x0E: // Flag Checked
            bc[1] = memory[pc + 1];
            cycles += 8;
            pc += 2;
        break;

        case 0x0F: // Flag Checked
            Abitbuffer = af[0];
            Carry_Helper[0] = Abitbuffer[0];
            Abitbuffer = Abitbuffer >> 1;
            af[0] = Abitbuffer.to_ulong();
            Fbitbuffer = af[1];
            if(af[0] == 0x00)
            {
                Fbitbuffer[7] = 1;
                Fbitbuffer[6] = 0;
                Fbitbuffer[5] = 0;
                Fbitbuffer[4] = Carry_Helper[0];
            }
            if(af[0] != 0x00)
            {
                Fbitbuffer[7] = 0;
                Fbitbuffer[6] = 0;
                Fbitbuffer[5] = 0;
                Fbitbuffer[4] = Carry_Helper[0];
            }
            af[1] = Fbitbuffer.to_ulong();
            pc++;
            cycles += 4;
        break;

        case 0x10: // Flag Checked
            printf("\nSTOP Opcode 0x10 Encountered!\nThis likely means that the Emulated Software Encountered an Error!");
            printf("\nProgram Counter: 0x%X\n", pc);
            printf("Stack Pointer: 0x%X%X\n", sp[0], sp[1]);
            printf("Cycles: %i\n", cycles);
            printf("Please see errorlog.txt for more details.\n");
            printf("Please see memdump for a full Gameboy RAM Dump.\n");
            if(sdl_wanted == true)
            {
                SDL_DestroyWindow(AGBE_window);
                SDL_Quit();
            }
            close_program = true;
            mem_dump = fopen ("log/memdump", "w+");
            fwrite (memory , sizeof(char), sizeof(memory), mem_dump);
            fclose (mem_dump);
            error_log = fopen ("log/errorlog.txt", "w+");
            fprintf (error_log, "An STOP Opcode was Encountered.\n");
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

        case 0x11: // Flag Checked
            de[0] = memory[pc + 2];
            de[1] = memory[pc + 1];
            pc += 3;
            cycles += 12;
        break;

        case 0x12: // Flag Checked
            debuffer = de[0] << 8 | de[1];
            memory[debuffer] = af[0];
            pc++;
            cycles += 8;
        break;

        case 0x13: // Flag Checked
            de[1]++;
            if (de[1] == 0x00)
            {
                de[0]++;
            }
            pc++;
            cycles += 8;
        break;

        case 0x14: // Flag Checked
            Fbitbuffer = af[1];
            beforeHcheck = de[0];
            de[0]++;
            if(de[0] == 0x00)
            {
                Fbitbuffer[7] = 1;
                Fbitbuffer[6] = 0;
                Fbitbuffer[5] = halfcarrycheck(beforeHcheck,de[0]);
            }
            if(de[0] != 0x00)
            {
                Fbitbuffer[7] = 0;
                Fbitbuffer[6] = 0;
                Fbitbuffer[5] = halfcarrycheck(beforeHcheck,de[0]);
            }
            af[1] = Fbitbuffer.to_ulong();
            cycles += 4;
            pc++;
        break;

        case 0x15: // Flag Checked
            Fbitbuffer = af[1];
            beforeHcheck = de[0];
            de[0]--;
            if(de[0] == 0x00)
            {
                Fbitbuffer[7] = 1;
                Fbitbuffer[6] = 1;
                Fbitbuffer[5] = halfcarrycheck(beforeHcheck,de[0]);
            }
            if(de[0] != 0x00)
            {
                Fbitbuffer[7] = 0;
                Fbitbuffer[6] = 1;
                Fbitbuffer[5] = halfcarrycheck(beforeHcheck,de[0]);
            }
            af[1] = Fbitbuffer.to_ulong();
            pc++;
            cycles += 4;
        break;

        case 0x16: // Flag Checked
            de[0] = memory[pc + 1];
            pc += 2;
            cycles += 8;
        break;

        case 0x17: // Flag Checked
            Fbitbuffer = af[1];
            Abitbuffer = af[0];
            Carry_Helper[0] = Fbitbuffer[4];
            Carry_Helper2[0] = Abitbuffer[7];
            af[0] = af[0] << 1;
            Abitbuffer = af[0];
            Abitbuffer[0] = Carry_Helper[0];
            Fbitbuffer[4] = Carry_Helper2[0];
            Fbitbuffer[5] = 0;
            Fbitbuffer[6] = 0;
            af[0] = Abitbuffer.to_ulong();
            if(af[0] == 0x00)
            {
                Fbitbuffer[7] = 1;
            }
            if(af[0] != 0x00)
            {
                Fbitbuffer[7] = 0;
            }
            af[1] = Fbitbuffer.to_ulong();
            pc++;
            cycles += 4;
        break;

        case 0x18: // Flag Checked
            help0x18 = memory[pc + 1];
            if(help0x18 <= 0x7F)
            {
            pc = pc + help0x18;
            }
            if(help0x18 >= 0x80)
            {
            pc = pc + help0x18;
            pc = pc - 0x0100;
            }
            cycles += 8;
            pc += 2;
        break;

        case 0x19: // Flags Need Fixed
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

        case 0x1A: // Flag Checked
            debuffer = de[0] << 8 | de[1];
            af[0] = memory[debuffer];
            pc++;
            cycles += 8;
        break;

        case 0x1B: // Flag Checked
            de[1]--;
            if(de[1] == 0xFF)
            {
                de[0]--;
            }
            pc++;
            cycles += 8;
        break;

        case 0x1C: // Flag Checked
            Fbitbuffer = af[1];
            beforeHcheck = de[1];
            de[1]++;
            if(de[1] == 0x00)
            {
                Fbitbuffer[7] = 1;
                Fbitbuffer[6] = 0;
                Fbitbuffer[5] = halfcarrycheck(beforeHcheck,de[1]);
            }
            if(de[1] != 0x00)
            {
                Fbitbuffer[7] = 0;
                Fbitbuffer[6] = 0;
                Fbitbuffer[5] = halfcarrycheck(beforeHcheck,de[1]);
            }
            af[1] = Fbitbuffer.to_ulong();
            cycles += 4;
            pc++;
        break;

        case 0x1D: // Flag Checked
            beforeHcheck = de[1];
            Fbitbuffer = af[1];
            de[1]--;
            if(de[1] == 0x00)
            {
                Fbitbuffer[7] = 1;
                Fbitbuffer[6] = 0;
                Fbitbuffer[5] = halfcarrycheck(beforeHcheck,de[1]);
            }
            if(de[1] != 0x00)
            {
                Fbitbuffer[7] = 0;
                Fbitbuffer[6] = 0;
                Fbitbuffer[5] = halfcarrycheck(beforeHcheck,de[1]);
            }
            Fbitbuffer = af[1];
            pc++;
            cycles += 4;
        break;

        case 0x1E: // Flag Checked
            de[1] = memory[pc + 1];
            cycles += 8;
            pc += 2;
        break;

        case 0x1F: // Flag Checked
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
            }
            pc++;
            cycles += 4;
        break;

        case 0x20: // Flag Checked
            Fbitbuffer = af[1];
            if(Fbitbuffer[7] == 0)
            {
                cycles += 8;
                if(memory[pc + 1] <= 0x7F)
                {
                pc = pc + memory[pc + 1];
                }
                if(memory[pc + 1] >= 0x80)
                {
                pc = pc + memory[pc + 1];
                pc = pc - 0x100;
                }
            }
            if(Fbitbuffer[7] == 1)
            {
                cycles += 8;
            }
            pc +=2;
        break;

        case 0x21: // Flag Checked
            hl[0] = memory[pc + 2];
            hl[1] = memory[pc + 1];
            cycles += 12;
            pc += 3;
        break;

        case 0x22: // Flag Checked
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

        case 0x23: // Flag Cheked
            hl[1]++;
            if(hl[1] == 0x00)
            {
                hl[0]++;
            }
            pc++;
            cycles += 8;
        break;

        case 0x24: // Flag Checked
            beforeHcheck = hl[0];
            Fbitbuffer = af[1];
            hl[0]++;
            if(hl[0] == 0x00)
            {
                Fbitbuffer[7] = 1;
                Fbitbuffer[6] = 0;
                Fbitbuffer[5] = halfcarrycheck(beforeHcheck,hl[0]);
            }
            if(hl[0] != 0x00)
            {
                Fbitbuffer[7] = 0;
                Fbitbuffer[6] = 0;
                Fbitbuffer[5] = halfcarrycheck(beforeHcheck,hl[0]);
            }
            af[1] = Fbitbuffer.to_ulong();
            cycles += 4;
            pc++;
        break;

        case 0x25: // Flag Checked
            beforeHcheck = hl[0];
            Fbitbuffer = af[1];
            hl[0]--;
            if(hl[0] == 0x00)
            {
                Fbitbuffer[7] = 1;
                Fbitbuffer[6] = 0;
                Fbitbuffer[5] = halfcarrycheck(beforeHcheck,hl[0]);
            }
            if(hl[0] != 0x00)
            {
                Fbitbuffer[7] = 0;
                Fbitbuffer[6] = 0;
                Fbitbuffer[5] = halfcarrycheck(beforeHcheck,hl[0]);
            }
            af[1] = Fbitbuffer.to_ulong();
            pc++;
            cycles += 4;
        break;

        case 0x26: // Flag Checked
            hl[0] = memory[pc + 1];
            cycles += 8;
            pc += 2;
        break;

        case 0x27: // DAA.  No idea if this works.
            pc++;
            beforeHcheck = af[0];
            Fbitbuffer = af[1];
            // note: assumes a is a uint8_t and wraps from 0xff to 0
            if (Fbitbuffer[6] == 0)
            {  // after an addition, adjust if (half-)carry occurred or if result is out of bounds
                if (Fbitbuffer[4] == 1 || af[0] > 0x99) { af[0] += 0x60; Fbitbuffer[4] = 1; }
                if (Fbitbuffer[5] == 1 || (af[0] & 0x0f) > 0x09) { af[0] += 0x6; }
            }
            else
            {  // after a subtraction, only adjust if (half-)carry occurred
                if (Fbitbuffer[4] == 1) { af[0] -= 0x60; }
                if (Fbitbuffer[5] == 1) { af[0] -= 0x6; }
            }
            // these flags are always updated
            if(af[0] == 0x00)
            {
                Fbitbuffer[7] = 1; // the usual z flag
            }
            if(af[0] != 0x00)
            {
                Fbitbuffer[7] = 0; // the usual z flag
            }
            Fbitbuffer[5] = 0; // h flag is always cleared
            Fbitbuffer[4] = overflowcheck(beforeHcheck,af[0]);
            af[1] = Fbitbuffer.to_ulong();
        break;

        case 0x28: // Flag Checked
            Fbitbuffer = af[1];
            if(Fbitbuffer[7] == 1)
            {
                cycles += 8;
                if(memory[pc + 1] <= 0x7F)
                {
                pc = pc + memory[pc + 1];
                }
                if(memory[pc + 1] >= 0x80)
                {
                pc = pc + memory[pc + 1];
                pc = pc - 0x100;
                }
            }
            if(Fbitbuffer[7] == 0)
            {
                cycles += 8;
            }
            pc += 2;
        break;

        case 0x29: // Flags need fixed
            hlbuffer2 = hl[0] << 8 | hl[1];
            hlbuffer3 = hl[0] << 8 | hl[1];
            hlbuffer2 = hlbuffer2 + hlbuffer3;
            hl[0] = hlbuffer2 >> 8;
            hl[1] = hlbuffer2;
            pc++;
            cycles += 8;
        break;

        case 0x2A: // Flag Checked
            af[0] = memory[hlbuffer];
            hl[1] += 0x01;
            if(hl[1] == 0x00)
            {
                hl[0] += 0x01;
            }
            cycles += 8;
            pc += 1;
        break;

        case 0x2B: // Flag Checked
            hl[1]--;
            if(hl[1] == 0xFF)
            {
                hl[0]--;
            }
            pc++;
            cycles += 8;
        break;

        case 0x2C: // Flag Checked
            beforeHcheck = hl[1];
            Fbitbuffer = af[1];
            hl[1]++;
            if(hl[1] == 0x00)
            {
                Fbitbuffer[7] = 1;
                Fbitbuffer[6] = 0;
                Fbitbuffer[5] = halfcarrycheck(beforeHcheck,hl[1]);
            }
            if(hl[1] != 0x00)
            {
                Fbitbuffer[7] = 0;
                Fbitbuffer[6] = 0;
                Fbitbuffer[5] = halfcarrycheck(beforeHcheck,hl[1]);
            }
            af[1] = Fbitbuffer.to_ulong();
            cycles += 4;
            pc++;
        break;

        case 0x2D: // Flags Need Fixed
            beforeHcheck = hl[1];
            Fbitbuffer = af[1];
            hl[1]--;
            if(hl[1] == 0x00)
            {
                Fbitbuffer[7] = 1;
                Fbitbuffer[6] = 1;
                Fbitbuffer[5] = halfcarrycheck(beforeHcheck,hl[1]);
            }
            if(hl[1] != 0x00)
            {
                Fbitbuffer[7] = 0;
                Fbitbuffer[6] = 1;
                Fbitbuffer[5] = halfcarrycheck(beforeHcheck,hl[1]);
            }
            af[1] = Fbitbuffer.to_ulong();
            pc++;
            cycles += 4;
        break;

        case 0x2E: // Flag Checked
            hl[1] = memory[pc + 1];
            cycles += 8;
            pc += 2;
        break;

        case 0x2F: // Flag Checked
            Abitbuffer = af[0];
            Abitbuffer.flip();
            af[0] = Abitbuffer.to_ulong();
            Fbitbuffer = af[1];
            Fbitbuffer[6] = 1;
            Fbitbuffer[5] = 1;
            af[1] = Fbitbuffer.to_ulong();
            cycles += 4;
            pc++;
        break;

        case 0x30: // Flag Checked
            Fbitbuffer = af[1];
            if(Fbitbuffer[4] == 0)
            {
                cycles += 8;
                if(memory[pc + 1] <= 0x7F)
                {
                pc = pc + memory[pc + 1];
                }
                if(memory[pc + 1] >= 0x80)
                {
                pc = pc + memory[pc + 1];
                pc = pc - 0x100;
                }
            }
            if(Fbitbuffer[4] == 1)
            {
                cycles += 8;
            }
            pc += 2;
        break;

        case 0x31: // Flag Checked
            sp[0] = memory[pc + 2];
            sp[1] = memory[pc + 1];
            cycles += 12;
            pc += 3;
        break;

        case 0x32: // Flag Checked
            hlbuffer = hl[0] << 8 | hl[1];
            memory[hlbuffer] = af[0];
            hl[1]--;
            if(hl[1] == 0xFF)
            {
            hl[0]--;
            }
            pc++;
            cycles += 8;
        break;

        case 0x33: // Flag Checked
            sp[1]++;
            if (sp[1] == 0x00)
            {
                sp[0]++;
            }
            pc++;
            cycles += 8;
        break;

        case 0x34: // Flags Need Fixed
            Fbitbuffer = af[1];
            hlbuffer = hl[0] << 8 | hl[1];
            beforeHcheck = memory[hlbuffer];
            memory[hlbuffer]++;
            if(memory[hlbuffer] == 0x00)
            {
                Fbitbuffer[7] = 1;
                Fbitbuffer[6] = 0;
                Fbitbuffer[5] = halfcarrycheck(beforeHcheck,memory[hlbuffer]);
            }
            if(memory[hlbuffer] != 0x00)
            {
                Fbitbuffer[7] = 0;
                Fbitbuffer[6] = 0;
                Fbitbuffer[5] = halfcarrycheck(beforeHcheck,memory[hlbuffer]);
            }
            af[1] = Fbitbuffer.to_ulong();
            cycles += 12;
            pc++;
        break;

        case 0x35: // Flag Checked
            nn = hl[0] << 8 | hl[1];
            beforeHcheck = memory[(nn - 0xFFFF0000)];
            memory[(nn - 0xFFFF0000)]--;
            Fbitbuffer = af[1];
            if (memory[(nn - 0xFFFF0000)] == 0x00)
            {
                Fbitbuffer[7] = 1;
            }
            if (memory[(nn - 0xFFFF0000)] != 0x00)
            {
                Fbitbuffer[7] = 0;
            }
            Fbitbuffer[6] = 1;
            Fbitbuffer[5] = halfcarrycheck(beforeHcheck,memory[(nn - 0xFFFF0000)]);
            af[1] = Fbitbuffer.to_ulong();
            pc++;
            cycles += 12;
        break;

        case 0x36: // Flag Checked
            memory[hlbuffer] = memory[pc + 1];
            cycles += 12;
            pc += 2;
        break;

        case 0x37: // Flag Checked
            Fbitbuffer = af[1];
            Fbitbuffer[6] = 0;
            Fbitbuffer[5] = 0;
            Fbitbuffer[4] = 1;
            af[1] = Fbitbuffer.to_ulong();
            pc++;
            cycles += 4;
        break;

        case 0x38: // Flag Checked
            Fbitbuffer = af[1];
            if(Fbitbuffer[4] == 1)
            {
                if(memory[pc + 1] <= 0x7F)
                {
                pc = pc + memory[pc + 1];
                }
                if(memory[pc + 1] >= 0x80)
                {
                pc = pc + memory[pc + 1];
                pc = pc - 0x100;
                }
            }
            pc += 2;
            cycles += 8;
        break;

        case 0x39: // Flag Needs Fixed
            hlbuffer2 = hl[0] << 8 | hl[1];
            spbuffer2 = sp[0] << 8 | sp[1];
            hlbuffer2 = hlbuffer2 + spbuffer2;
            hl[0] = hlbuffer2 >> 8;
            hl[1] = hlbuffer2;
            pc++;
            cycles += 8;
        break;

        case 0x3A: // Flag Checked
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

        case 0x3B: // Flag Checked
            sp[1]--;
            if(sp[1] == 0xFF)
            {
                sp[0]--;
            }
            pc++;
            cycles += 8;
        break;

        case 0x3C: // Flag Checked
            Fbitbuffer = af[1];
            beforeHcheck = af[0];
            af[0]++;
            if(af[0] == 0x00)
            {
                Fbitbuffer[7] = 1;
                Fbitbuffer[6] = 0;
                Fbitbuffer[5] = halfcarrycheck(beforeHcheck,af[0]);
            }
            if(af[0] != 0x00)
            {
                Fbitbuffer[7] = 0;
                Fbitbuffer[6] = 0;
                Fbitbuffer[5] = halfcarrycheck(beforeHcheck,af[0]);
            }
            af[1] = Fbitbuffer.to_ulong();
            cycles += 4;
            pc++;
        break;

        case 0x3D: // Flag Checked
            Fbitbuffer = af[1];
            beforeHcheck = af[0];
            af[0] -= 0x01;
            if(af[0] == 0x00)
            {
                Fbitbuffer[7] = 1;
                Fbitbuffer[6] = 1;
                Fbitbuffer[5] = halfcarrycheck(beforeHcheck,af[0]);
            }
            if(af[0] != 0x00)
            {
                Fbitbuffer[7] = 0;
                Fbitbuffer[6] = 1;
                Fbitbuffer[5] = halfcarrycheck(beforeHcheck,af[0]);
            }
            af[1] = Fbitbuffer.to_ulong();
            cycles += 4;
            pc++;
        break;

        case 0x3E: // Flag Checked
            af[0] = (memory[pc + 1] - 0xFFFFFF00);
            cycles += 8;
            pc += 2;
        break;

        case 0x3F: // Flag Checked
        Fbitbuffer = af[1];
        Fbitbuffer[6] = 0;
        Fbitbuffer[5] = 0;
        Fbitbuffer.flip(4);
        af[1] = Fbitbuffer.to_ulong();
        pc++;
        cycles += 4;
        break;

        case 0x40: // Flag Checked
            bc[0] = bc[0];
            pc++;
            cycles += 4;;
        break;

        case 0x41: // Flag Checked
            bc[0] = bc[1];
            pc++;
            cycles += 4;
        break;

        case 0x42: // Flag Checked
            bc[0] = de[0];
            pc++;
            cycles += 4;
        break;

        case 0x43: // Flag Checked
            bc[0] = de[1];
            pc++;
            cycles += 4;
        break;

        case 0x44: // Flag Checked
            bc[0] = hl[0];
            pc++;
            cycles += 4;
        break;

        case 0x45: // Flag Checked
            bc[0] = hl[1];
            pc++;
            cycles += 4;
        break;

        case 0x46: // Flag Checked
            hlbuffer = hl[0] << 8 | hl[1];
            bc[0] = memory[hlbuffer];
            pc++;
            cycles += 8;
        break;

        case 0x47: // Flag Checked
            bc[0] = af[0];
            pc++;
            cycles += 4;
        break;

        case 0x48: // Flag Checked
            bc[1] = bc[0];
            pc++;
            cycles += 4;
        break;

        case 0x49: // Flag Checked
            bc[1] = bc[1];
            pc++;
            cycles += 4;
        break;

        case 0x4A: // Flag Checked
            bc[1] = de[0];
            pc++;
            cycles += 4;
        break;

        case 0x4B: // Flag Checked
            bc[1] = de[1];
            pc++;
            cycles += 4;
        break;

        case 0x4C: // Flag Checked
            bc[1] = hl[0];
            pc++;
            cycles += 4;
        break;

        case 0x4D: // Flag Checked
            bc[1] = hl[1];
            pc++;
            cycles += 4;
        break;

        case 0x4E: // Flag Checked
            hlbuffer = hl[0] << 8 | hl[1];
            bc[1] = memory[hlbuffer];
            pc++;
            cycles += 4;
        break;

        case 0x4F: // Flag Checked
            bc[1] = af[0];
            pc++;
            cycles += 4;
        break;

        case 0x50: // Flag Checked
            de[0] = bc[0];
            pc++;
            cycles += 4;
        break;

        case 0x51: // Flag Checked
            de[0] = bc[1];
            pc++;
            cycles += 4;
        break;

        case 0x52: // Flag Checked
            de[0] = de[0];
            pc++;
            cycles += 4;
        break;

        case 0x53: // Flag Checked
            de[0] = de[1];
            pc++;
            cycles += 4;
        break;

        case 0x54: // Flag Checked
            de[0] = hl[0];
            pc++;
            cycles += 4;
        break;

        case 0x55: // Flag Checked
            de[0] = hl[1];
            pc++;
            cycles += 4;
        break;

        case 0x56: // Flag Checked
            hlbuffer = hl[0] << 8 | hl[1];
            de[0] = memory[hlbuffer];
            cycles += 8;
            pc++;
        break;

        case 0x57: // Flag Checked
            de[0] = af[0];
            pc++;
            cycles += 4;
        break;

        case 0x58: // Flag Checked
            de[1] = bc[0];
            pc++;
            cycles += 4;
        break;

        case 0x59: // Flag Checked
            de[1] = bc[1];
            pc++;
            cycles += 4;
        break;

        case 0x5A: // Flag Checked
            de[1] = de[0];
            pc++;
            cycles += 4;
        break;

        case 0x5B: // Flag Checked
            de[1] = de[1];
            pc++;
            cycles += 4;
        break;

        case 0x5C: // Flag Checked
            de[1] = hl[0];
            pc++;
            cycles += 4;
        break;

        case 0x5D: // Flag Checked
            de[1] = hl[1];
            pc++;
            cycles += 4;
        break;

        case 0x5E: // Flag Checked
            hlbuffer = hl[0] << 8 | hl[1];
            de[1] = memory[hlbuffer];
            cycles += 8;
            pc++;
        break;

        case 0x5F: // Flag Checked
            de[1] = af[0];
            pc++;
            cycles += 4;
        break;

        case 0x60: // Flag Checked
            hl[0] = bc[0];
            pc++;
            cycles += 4;
        break;

        case 0x61: // Flag Checked
            hl[0] = bc[1];
            pc++;
            cycles += 4;
        break;

        case 0x62: // Flag Checked
            hl[0] = de[0];
            pc++;
            cycles += 4;
        break;

        case 0x63: // Flag Checked
            hl[0] = de[1];
            pc++;
            cycles += 4;
        break;

        case 0x64: // Flag Checked
            hl[0] = hl[0];
            pc++;
            cycles += 4;
        break;

        case 0x65: // Flag Checked
            hl[0] = hl[1];
            pc++;
            cycles += 4;
        break;

        case 0x66: // Flag Checked
            hlbuffer = hl[0] << 8 | hl[1];
            hl[0] = memory[hlbuffer];
            pc++;
            cycles += 8;
        break;

        case 0x67: // Flag Checked
            hl[0] = af[0];
            pc++;
            cycles += 4;
        break;

        case 0x68: // Flag Checked
            hl[1] = bc[0];
            pc++;
            cycles += 4;
        break;

        case 0x69: // Flag Checked
            hl[1] = bc[1];
            pc++;
            cycles += 4;
        break;

        case 0x6A: // Flag Checked
            hl[1] = de[0];
            pc++;
            cycles += 4;
        break;

        case 0x6B: // Flag Checked
            hl[1] = de[1];
            pc++;
            cycles += 4;
        break;

        case 0x6C: // Flag Checked
            hl[1] = hl[0];
            pc++;
            cycles += 4;
        break;

        case 0x6D: // Flag Checked
            hl[1] = hl[1];
            pc++;
            cycles += 4;
        break;

        case 0x6E: // Flag Checked
            hlbuffer = hl[0] << 8 | hl[1];
            hl[1] = memory[hlbuffer];
            pc++;
            cycles += 8;
        break;

        case 0x6F: // Flag Checked
            hl[1] = af[0];
            pc++;
            cycles += 4;
        break;

        case 0x70: // Flag Checked
            hlbuffer = hl[0] << 8 | hl[1];
            memory[hlbuffer] = bc[0];
            pc++;
            cycles += 8;
        break;

        case 0x71: // Flag Checked
            hlbuffer = hl[0] << 8 | hl[1];
            memory[hlbuffer] = bc[1];
            pc++;
            cycles += 8;
        break;

        case 0x72: // Flag Checked
            hlbuffer = hl[0] << 8 | hl[1];
            memory[hlbuffer] = de[0];
            pc++;
            cycles += 8;
        break;

        case 0x73: // Flag Checked
            hlbuffer = hl[0] << 8 | hl[1];
            memory[hlbuffer] = de[1];
            pc++;
            cycles += 8;
        break;

        case 0x74: // Flag Checked
            hlbuffer = hl[0] << 8 | hl[1];
            memory[hlbuffer] = hl[0];
            pc++;
            cycles += 8;
        break;

        case 0x75: // Flag Checked
            hlbuffer = hl[0] << 8 | hl[1];
            memory[hlbuffer] = hl[1];
            pc++;
            cycles += 8;
        break;

        case 0x76: // Probably Broken
            pc++;
            cycles += 4;
        break;

        case 0x77: // Flag Checked
            hlbuffer = hl[0] << 8 | hl[1];
            memory[hlbuffer] = af[0];
            pc++;
            cycles += 8;
        break;

        case 0x78: // Flag Checked
            af[0] = bc[0];
            pc++;
            cycles += 4;
        break;

        case 0x79: // Flag Checked
            af[0] = bc[1];
            pc++;
            cycles += 4;
        break;

        case 0x7A: // Flag Checked
            af[0] = de[0];
            pc++;
            cycles += 4;
        break;

        case 0x7B: // Flag Checked
            af[0] = de[1];
            pc++;
            cycles += 4;
        break;

        case 0x7C: // Flag Checked
            af[0] = hl[0];
            pc++;
            cycles += 4;
        break;

        case 0x7D: // Flag Checked
            af[0] = hl[1];
            pc++;
            cycles += 4;
        break;

        case 0x7E: // Flag Checked
            hlbuffer = hl[0] << 8 | hl[1];
            af[0] = memory[hlbuffer];
            pc++;
            cycles += 8;
        break;

        case 0x7F: // Flag Checked
            af[0] = af[0];
            pc++;
            cycles += 4;
        break;

        case 0x80: // Flag Checked
            beforeHcheck = af[0];
            Fbitbuffer = af[1];
            af[0] = af[0] + bc[0];
            if(af[0] == 0x00)
            {
                Fbitbuffer[7] = 1;
                Fbitbuffer[6] = 0;
                Fbitbuffer[5] = halfcarrycheck(beforeHcheck,af[0]);
                Fbitbuffer[4] = overflowcheck(beforeHcheck,af[0]);  // Here, we are using beforeHcheck because there is no reason to use another variable when this one already has the value I want.
            }
            if(af[0] != 0x00)
            {
                Fbitbuffer[7] = 0;
                Fbitbuffer[6] = 0;
                Fbitbuffer[5] = halfcarrycheck(beforeHcheck,af[0]);
                Fbitbuffer[4] = overflowcheck(beforeHcheck,af[0]);
            }
            af[1] = Fbitbuffer.to_ulong();
            pc++;
            cycles += 4;
        break;

        case 0x81: // Flag Checked
            beforeHcheck = af[0];
            Fbitbuffer = af[1];
            af[0] = af[0] + bc[1];
            if(af[0] == 0x00)
            {
                Fbitbuffer[7] = 1;
                Fbitbuffer[6] = 0;
                Fbitbuffer[5] = halfcarrycheck(beforeHcheck,af[0]);
                Fbitbuffer[4] = overflowcheck(beforeHcheck,af[0]);  // Here, we are using beforeHcheck because there is no reason to use another variable when this one already has the value I want.
            }
            if(af[0] != 0x00)
            {
                Fbitbuffer[7] = 0;
                Fbitbuffer[6] = 0;
                Fbitbuffer[5] = halfcarrycheck(beforeHcheck,af[0]);
                Fbitbuffer[4] = overflowcheck(beforeHcheck,af[0]);
            }
            af[1] = Fbitbuffer.to_ulong();
            pc++;
            cycles += 4;
        break;

        case 0x82: // Flag Checked
            beforeHcheck = af[0];
            Fbitbuffer = af[1];
            af[0] = af[0] + de[0];
            if(af[0] == 0x00)
            {
                Fbitbuffer[7] = 1;
                Fbitbuffer[6] = 0;
                Fbitbuffer[5] = halfcarrycheck(beforeHcheck,af[0]);
                Fbitbuffer[4] = overflowcheck(beforeHcheck,af[0]);  // Here, we are using beforeHcheck because there is no reason to use another variable when this one already has the value I want.
            }
            if(af[0] != 0x00)
            {
                Fbitbuffer[7] = 0;
                Fbitbuffer[6] = 0;
                Fbitbuffer[5] = halfcarrycheck(beforeHcheck,af[0]);
                Fbitbuffer[4] = overflowcheck(beforeHcheck,af[0]);
            }
            af[1] = Fbitbuffer.to_ulong();
            pc++;
            cycles += 4;
        break;

        case 0x83: // Flag Checked
            beforeHcheck = af[0];
            Fbitbuffer = af[1];
            af[0] = af[0] + de[1];
            if(af[0] == 0x00)
            {
                Fbitbuffer[7] = 1;
                Fbitbuffer[6] = 0;
                Fbitbuffer[5] = halfcarrycheck(beforeHcheck,af[0]);
                Fbitbuffer[4] = overflowcheck(beforeHcheck,af[0]);  // Here, we are using beforeHcheck because there is no reason to use another variable when this one already has the value I want.
            }
            if(af[0] != 0x00)
            {
                Fbitbuffer[7] = 0;
                Fbitbuffer[6] = 0;
                Fbitbuffer[5] = halfcarrycheck(beforeHcheck,af[0]);
                Fbitbuffer[4] = overflowcheck(beforeHcheck,af[0]);
            }
            af[1] = Fbitbuffer.to_ulong();
            pc++;
            cycles += 4;
        break;

        case 0x84: // Flag Checked
            beforeHcheck = af[0];
            Fbitbuffer = af[1];
            af[0] = af[0] + hl[0];
            if(af[0] == 0x00)
            {
                Fbitbuffer[7] = 1;
                Fbitbuffer[6] = 0;
                Fbitbuffer[5] = halfcarrycheck(beforeHcheck,af[0]);
                Fbitbuffer[4] = overflowcheck(beforeHcheck,af[0]);  // Here, we are using beforeHcheck because there is no reason to use another variable when this one already has the value I want.
            }
            if(af[0] != 0x00)
            {
                Fbitbuffer[7] = 0;
                Fbitbuffer[6] = 0;
                Fbitbuffer[5] = halfcarrycheck(beforeHcheck,af[0]);
                Fbitbuffer[4] = overflowcheck(beforeHcheck,af[0]);
            }
            af[1] = Fbitbuffer.to_ulong();
            pc++;
            cycles += 4;

        case 0x85: // Flag Checked
            beforeHcheck = af[0];
            Fbitbuffer = af[1];
            af[0] = af[0] + hl[1];
            if(af[0] == 0x00)
            {
                Fbitbuffer[7] = 1;
                Fbitbuffer[6] = 0;
                Fbitbuffer[5] = halfcarrycheck(beforeHcheck,af[0]);
                Fbitbuffer[4] = overflowcheck(beforeHcheck,af[0]);  // Here, we are using beforeHcheck because there is no reason to use another variable when this one already has the value I want.
            }
            if(af[0] != 0x00)
            {
                Fbitbuffer[7] = 0;
                Fbitbuffer[6] = 0;
                Fbitbuffer[5] = halfcarrycheck(beforeHcheck,af[0]);
                Fbitbuffer[4] = overflowcheck(beforeHcheck,af[0]);
            }
            af[1] = Fbitbuffer.to_ulong();
            pc++;
            cycles += 4;
        break;

        case 0x86: // Flag Checked
            hlbuffer = hl[0] << 8 | hl[1];
            beforeHcheck = af[0];
            Fbitbuffer = af[1];
            af[0] = af[0] + memory[hlbuffer];
            if(af[0] == 0x00)
            {
                Fbitbuffer[7] = 1;
                Fbitbuffer[6] = 0;
                Fbitbuffer[5] = halfcarrycheck(beforeHcheck,af[0]);
                Fbitbuffer[4] = overflowcheck(beforeHcheck,af[0]);  // Here, we are using beforeHcheck because there is no reason to use another variable when this one already has the value I want.
            }
            if(af[0] != 0x00)
            {
                Fbitbuffer[7] = 0;
                Fbitbuffer[6] = 0;
                Fbitbuffer[5] = halfcarrycheck(beforeHcheck,af[0]);
                Fbitbuffer[4] = overflowcheck(beforeHcheck,af[0]);
            }
            af[1] = Fbitbuffer.to_ulong();
            pc++;
            cycles += 4;
        break;

        case 0x87: // Flag Checked
            beforeHcheck = af[0];
            Fbitbuffer = af[1];
            af[0] = af[0] + af[0];
            if(af[0] == 0x00)
            {
                Fbitbuffer[7] = 1;
                Fbitbuffer[6] = 0;
                Fbitbuffer[5] = halfcarrycheck(beforeHcheck,af[0]);
                Fbitbuffer[4] = overflowcheck(beforeHcheck,af[0]);  // Here, we are using beforeHcheck because there is no reason to use another variable when this one already has the value I want.
            }
            if(af[0] != 0x00)
            {
                Fbitbuffer[7] = 0;
                Fbitbuffer[6] = 0;
                Fbitbuffer[5] = halfcarrycheck(beforeHcheck,af[0]);
                Fbitbuffer[4] = overflowcheck(beforeHcheck,af[0]);
            }
            af[1] = Fbitbuffer.to_ulong();
            pc++;
            cycles += 4;
        break;

        case 0x88: // Flag Checked
            beforeHcheck = af[0];
            af[0] = af[0] + bc[0];
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
                Fbitbuffer[5] = halfcarrycheck(beforeHcheck,af[0]);
                Fbitbuffer[4] = overflowcheck(beforeHcheck,af[0]);
            }
            if (af[0] != 0x00)
            {
                Fbitbuffer[7] = 0;
                Fbitbuffer[6] = 0;
                Fbitbuffer[5] = halfcarrycheck(beforeHcheck,af[0]);
                Fbitbuffer[4] = overflowcheck(beforeHcheck,af[0]);
            }
            af[1] = Fbitbuffer.to_ulong();
            pc += 1;
            cycles += 4;
        break;

        case 0x89: // Flag Checked
            beforeHcheck = af[0];
            af[0] = af[0] + bc[1];
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
                Fbitbuffer[5] = halfcarrycheck(beforeHcheck,af[0]);
                Fbitbuffer[4] = overflowcheck(beforeHcheck,af[0]);
            }
            if (af[0] != 0x00)
            {
                Fbitbuffer[7] = 0;
                Fbitbuffer[6] = 0;
                Fbitbuffer[5] = halfcarrycheck(beforeHcheck,af[0]);
                Fbitbuffer[4] = overflowcheck(beforeHcheck,af[0]);
            }
            af[1] = Fbitbuffer.to_ulong();
            pc += 1;
            cycles += 4;
        break;

        case 0x8A: // Flag Checked
            beforeHcheck = af[0];
            af[0] = af[0] + de[0];
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
                Fbitbuffer[5] = halfcarrycheck(beforeHcheck,af[0]);
                Fbitbuffer[4] = overflowcheck(beforeHcheck,af[0]);
            }
            if (af[0] != 0x00)
            {
                Fbitbuffer[7] = 0;
                Fbitbuffer[6] = 0;
                Fbitbuffer[5] = halfcarrycheck(beforeHcheck,af[0]);
                Fbitbuffer[4] = overflowcheck(beforeHcheck,af[0]);
            }
            af[1] = Fbitbuffer.to_ulong();
            pc += 1;
            cycles += 4;
        break;

        case 0x8B: // Flag Checked
            beforeHcheck = af[0];
            af[0] = af[0] + de[1];
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
                Fbitbuffer[5] = halfcarrycheck(beforeHcheck,af[0]);
                Fbitbuffer[4] = overflowcheck(beforeHcheck,af[0]);
            }
            if (af[0] != 0x00)
            {
                Fbitbuffer[7] = 0;
                Fbitbuffer[6] = 0;
                Fbitbuffer[5] = halfcarrycheck(beforeHcheck,af[0]);
                Fbitbuffer[4] = overflowcheck(beforeHcheck,af[0]);
            }
            af[1] = Fbitbuffer.to_ulong();
            pc += 1;
            cycles += 4;
        break;

        case 0x8C: // Flag Checked
            beforeHcheck = af[0];
            af[0] = af[0] + hl[0];
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
                Fbitbuffer[5] = halfcarrycheck(beforeHcheck,af[0]);
                Fbitbuffer[4] = overflowcheck(beforeHcheck,af[0]);
            }
            if (af[0] != 0x00)
            {
                Fbitbuffer[7] = 0;
                Fbitbuffer[6] = 0;
                Fbitbuffer[5] = halfcarrycheck(beforeHcheck,af[0]);
                Fbitbuffer[4] = overflowcheck(beforeHcheck,af[0]);
            }
            af[1] = Fbitbuffer.to_ulong();
            pc += 1;
            cycles += 4;
        break;

        case 0x8D: // Flag Checked
            beforeHcheck = af[0];
            af[0] = af[0] + hl[1];
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
                Fbitbuffer[5] = halfcarrycheck(beforeHcheck,af[0]);
                Fbitbuffer[4] = overflowcheck(beforeHcheck,af[0]);
            }
            if (af[0] != 0x00)
            {
                Fbitbuffer[7] = 0;
                Fbitbuffer[6] = 0;
                Fbitbuffer[5] = halfcarrycheck(beforeHcheck,af[0]);
                Fbitbuffer[4] = overflowcheck(beforeHcheck,af[0]);
            }
            af[1] = Fbitbuffer.to_ulong();
            pc += 1;
            cycles += 4;
        break;

        case 0x8E: // Flag Checked
            hlbuffer = hl[0] << 8 | hl[1];
            beforeHcheck = af[0];
            af[0] = af[0] + memory[hlbuffer];
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
                Fbitbuffer[5] = halfcarrycheck(beforeHcheck,af[0]);
                Fbitbuffer[4] = overflowcheck(beforeHcheck,af[0]);
            }
            if (af[0] != 0x00)
            {
                Fbitbuffer[7] = 0;
                Fbitbuffer[6] = 0;
                Fbitbuffer[5] = halfcarrycheck(beforeHcheck,af[0]);
                Fbitbuffer[4] = overflowcheck(beforeHcheck,af[0]);
            }
            af[1] = Fbitbuffer.to_ulong();
            pc += 1;
            cycles += 8;
        break;

        case 0x8F: // Flag Checked
            beforeHcheck = af[0];
            af[0] = af[0] + af[0];
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
                Fbitbuffer[5] = halfcarrycheck(beforeHcheck,af[0]);
                Fbitbuffer[4] = overflowcheck(beforeHcheck,af[0]);
            }
            if (af[0] != 0x00)
            {
                Fbitbuffer[7] = 0;
                Fbitbuffer[6] = 0;
                Fbitbuffer[5] = halfcarrycheck(beforeHcheck,af[0]);
                Fbitbuffer[4] = overflowcheck(beforeHcheck,af[0]);
            }
            af[1] = Fbitbuffer.to_ulong();
            pc += 1;
            cycles += 4;
        break;

        case 0x90: // Flag Checked
            beforeHcheck = af[0];
            af[0] = af[0] - bc[0];
            Fbitbuffer = af[1];
            if(af[0] == 0x00)
            {
                Fbitbuffer[7] = 1;
                Fbitbuffer[6] = 1;
                Fbitbuffer[5] = halfcarrycheck(beforeHcheck,af[0]);
                Fbitbuffer[4] = negativeoverflowcheck(beforeHcheck,af[0]);
            }
            if(af[0] != 0x00)
            {
                Fbitbuffer[7] = 0;
                Fbitbuffer[6] = 1;
                Fbitbuffer[5] = halfcarrycheck(beforeHcheck,af[0]);
                Fbitbuffer[4] = negativeoverflowcheck(beforeHcheck,af[0]);
            }
            af[1] = Fbitbuffer.to_ulong();
            pc++;
            cycles += 4;
        break;

        case 0x91: // Flag Checked
            beforeHcheck = af[0];
            af[0] = af[0] - bc[1];
            Fbitbuffer = af[1];
            if(af[0] == 0x00)
            {
                Fbitbuffer[7] = 1;
                Fbitbuffer[6] = 1;
                Fbitbuffer[5] = halfcarrycheck(beforeHcheck,af[0]);
                Fbitbuffer[4] = negativeoverflowcheck(beforeHcheck,af[0]);
            }
            if(af[0] != 0x00)
            {
                Fbitbuffer[7] = 0;
                Fbitbuffer[6] = 1;
                Fbitbuffer[5] = halfcarrycheck(beforeHcheck,af[0]);
                Fbitbuffer[4] = negativeoverflowcheck(beforeHcheck,af[0]);
            }
            af[1] = Fbitbuffer.to_ulong();
            pc++;
            cycles += 4;
        break;

        case 0x92: // Flag Checked
            beforeHcheck = af[0];
            af[0] = af[0] - de[0];
            Fbitbuffer = af[1];
            if(af[0] == 0x00)
            {
                Fbitbuffer[7] = 1;
                Fbitbuffer[6] = 1;
                Fbitbuffer[5] = halfcarrycheck(beforeHcheck,af[0]);
                Fbitbuffer[4] = negativeoverflowcheck(beforeHcheck,af[0]);
            }
            if(af[0] != 0x00)
            {
                Fbitbuffer[7] = 0;
                Fbitbuffer[6] = 1;
                Fbitbuffer[5] = halfcarrycheck(beforeHcheck,af[0]);
                Fbitbuffer[4] = negativeoverflowcheck(beforeHcheck,af[0]);
            }
            af[1] = Fbitbuffer.to_ulong();
            pc++;
            cycles += 4;
        break;

        case 0x93: // Flag Checked
            beforeHcheck = af[0];
            af[0] = af[0] - de[1];
            Fbitbuffer = af[1];
            if(af[0] == 0x00)
            {
                Fbitbuffer[7] = 1;
                Fbitbuffer[6] = 1;
                Fbitbuffer[5] = halfcarrycheck(beforeHcheck,af[0]);
                Fbitbuffer[4] = negativeoverflowcheck(beforeHcheck,af[0]);
            }
            if(af[0] != 0x00)
            {
                Fbitbuffer[7] = 0;
                Fbitbuffer[6] = 1;
                Fbitbuffer[5] = halfcarrycheck(beforeHcheck,af[0]);
                Fbitbuffer[4] = negativeoverflowcheck(beforeHcheck,af[0]);
            }
            af[1] = Fbitbuffer.to_ulong();
            pc++;
            cycles += 4;
        break;

        case 0x94: // Flag Checked
            beforeHcheck = af[0];
            af[0] = af[0] - hl[0];
            Fbitbuffer = af[1];
            if(af[0] == 0x00)
            {
                Fbitbuffer[7] = 1;
                Fbitbuffer[6] = 1;
                Fbitbuffer[5] = halfcarrycheck(beforeHcheck,af[0]);
                Fbitbuffer[4] = negativeoverflowcheck(beforeHcheck,af[0]);
            }
            if(af[0] != 0x00)
            {
                Fbitbuffer[7] = 0;
                Fbitbuffer[6] = 1;
                Fbitbuffer[5] = halfcarrycheck(beforeHcheck,af[0]);
                Fbitbuffer[4] = negativeoverflowcheck(beforeHcheck,af[0]);
            }
            af[1] = Fbitbuffer.to_ulong();
            pc++;
            cycles += 4;
        break;

        case 0x95: // Flag Checked
            beforeHcheck = af[0];
            af[0] = af[0] - hl[1];
            Fbitbuffer = af[1];
            if(af[0] == 0x00)
            {
                Fbitbuffer[7] = 1;
                Fbitbuffer[6] = 1;
                Fbitbuffer[5] = halfcarrycheck(beforeHcheck,af[0]);
                Fbitbuffer[4] = negativeoverflowcheck(beforeHcheck,af[0]);
            }
            if(af[0] != 0x00)
            {
                Fbitbuffer[7] = 0;
                Fbitbuffer[6] = 1;
                Fbitbuffer[5] = halfcarrycheck(beforeHcheck,af[0]);
                Fbitbuffer[4] = negativeoverflowcheck(beforeHcheck,af[0]);
            }
            af[1] = Fbitbuffer.to_ulong();
            pc++;
            cycles += 4;
        break;

        case 0x96: // Flag Checked
            hlbuffer = hl[0] << 8 | hl[1];
            beforeHcheck = af[0];
            af[0] = af[0] - memory[hlbuffer];
            Fbitbuffer = af[1];
            if(af[0] == 0x00)
            {
                Fbitbuffer[7] = 1;
                Fbitbuffer[6] = 1;
                Fbitbuffer[5] = halfcarrycheck(beforeHcheck,af[0]);
                Fbitbuffer[4] = negativeoverflowcheck(beforeHcheck,af[0]);
            }
            if(af[0] != 0x00)
            {
                Fbitbuffer[7] = 0;
                Fbitbuffer[6] = 1;
                Fbitbuffer[5] = halfcarrycheck(beforeHcheck,af[0]);
                Fbitbuffer[4] = negativeoverflowcheck(beforeHcheck,af[0]);
            }
            af[1] = Fbitbuffer.to_ulong();
            pc++;
            cycles += 8;
        break;

        case 0x97: // Flag Checked
            beforeHcheck = af[0];
            af[0] = af[0] - af[0];
            Fbitbuffer = af[1];
            if(af[0] == 0x00)
            {
                Fbitbuffer[7] = 1;
                Fbitbuffer[6] = 1;
                Fbitbuffer[5] = halfcarrycheck(beforeHcheck,af[0]);
                Fbitbuffer[4] = negativeoverflowcheck(beforeHcheck,af[0]);
            }
            if(af[0] != 0x00)
            {
                Fbitbuffer[7] = 0;
                Fbitbuffer[6] = 1;
                Fbitbuffer[5] = halfcarrycheck(beforeHcheck,af[0]);
                Fbitbuffer[4] = negativeoverflowcheck(beforeHcheck,af[0]);
            }
            af[1] = Fbitbuffer.to_ulong();
            pc++;
            cycles += 4;
        break;

        case 0x98: // Flag Checked
        beforeHcheck = af[0];
        Fbitbuffer = af[1];
        if(Fbitbuffer[4] == 1)
        {
            af[0] = af[0] - (bc[0] + 0x01);
        }
        if(Fbitbuffer[4] == 0)
        {
            af[0] = af[0] - (bc[0]);
        }
        if(af[0] == 0x00)
        {
            Fbitbuffer[7] = 1;
            Fbitbuffer[6] = 1;
            Fbitbuffer[5] = halfcarrycheck(beforeHcheck,af[0]);
            Fbitbuffer[4] = negativeoverflowcheck(beforeHcheck,af[0]);
        }
        if(af[0] != 0x00)
        {
            Fbitbuffer[7] = 0;
            Fbitbuffer[6] = 1;
            Fbitbuffer[5] = halfcarrycheck(beforeHcheck,af[0]);
            Fbitbuffer[4] = negativeoverflowcheck(beforeHcheck,af[0]);
        }
        af[1] = Fbitbuffer.to_ulong();
        pc++;
        cycles += 4;
        break;

        case 0x99: // Flag Checked
        beforeHcheck = af[0];
        Fbitbuffer = af[1];
        if(Fbitbuffer[4] == 1)
        {
            af[0] = af[0] - (bc[1] + 0x01);
        }
        if(Fbitbuffer[4] == 0)
        {
            af[0] = af[0] - (bc[1]);
        }
        if(af[0] == 0x00)
        {
            Fbitbuffer[7] = 1;
            Fbitbuffer[6] = 1;
            Fbitbuffer[5] = halfcarrycheck(beforeHcheck,af[0]);
            Fbitbuffer[4] = negativeoverflowcheck(beforeHcheck,af[0]);
        }
        if(af[0] != 0x00)
        {
            Fbitbuffer[7] = 0;
            Fbitbuffer[6] = 1;
            Fbitbuffer[5] = halfcarrycheck(beforeHcheck,af[0]);
            Fbitbuffer[4] = negativeoverflowcheck(beforeHcheck,af[0]);
        }
        af[1] = Fbitbuffer.to_ulong();
        pc++;
        cycles += 4;
        break;

        case 0x9A: // Flag Checked
        beforeHcheck = af[0];
        Fbitbuffer = af[1];
        if(Fbitbuffer[4] == 1)
        {
            af[0] = af[0] - (de[0] + 0x01);
        }
        if(Fbitbuffer[4] == 0)
        {
            af[0] = af[0] - (de[0]);
        }
        if(af[0] == 0x00)
        {
            Fbitbuffer[7] = 1;
            Fbitbuffer[6] = 1;
            Fbitbuffer[5] = halfcarrycheck(beforeHcheck,af[0]);
            Fbitbuffer[4] = negativeoverflowcheck(beforeHcheck,af[0]);
        }
        if(af[0] != 0x00)
        {
            Fbitbuffer[7] = 0;
            Fbitbuffer[6] = 1;
            Fbitbuffer[5] = halfcarrycheck(beforeHcheck,af[0]);
            Fbitbuffer[4] = negativeoverflowcheck(beforeHcheck,af[0]);
        }
        af[1] = Fbitbuffer.to_ulong();
        pc++;
        cycles += 4;
        break;

        case 0x9B: // Flag Checked
        beforeHcheck = af[0];
        Fbitbuffer = af[1];
        if(Fbitbuffer[4] == 1)
        {
            af[0] = af[0] - (de[1] + 0x01);
        }
        if(Fbitbuffer[4] == 0)
        {
            af[0] = af[0] - (de[1]);
        }
        if(af[0] == 0x00)
        {
            Fbitbuffer[7] = 1;
            Fbitbuffer[6] = 1;
            Fbitbuffer[5] = halfcarrycheck(beforeHcheck,af[0]);
            Fbitbuffer[4] = negativeoverflowcheck(beforeHcheck,af[0]);
        }
        if(af[0] != 0x00)
        {
            Fbitbuffer[7] = 0;
            Fbitbuffer[6] = 1;
            Fbitbuffer[5] = halfcarrycheck(beforeHcheck,af[0]);
            Fbitbuffer[4] = negativeoverflowcheck(beforeHcheck,af[0]);
        }
        af[1] = Fbitbuffer.to_ulong();
        pc++;
        cycles += 4;
        break;

        case 0x9C: // Flag Checked
        beforeHcheck = af[0];
        Fbitbuffer = af[1];
        if(Fbitbuffer[4] == 1)
        {
            af[0] = af[0] - (hl[0] + 0x01);
        }
        if(Fbitbuffer[4] == 0)
        {
            af[0] = af[0] - (hl[0]);
        }
        if(af[0] == 0x00)
        {
            Fbitbuffer[7] = 1;
            Fbitbuffer[6] = 1;
            Fbitbuffer[5] = halfcarrycheck(beforeHcheck,af[0]);
            Fbitbuffer[4] = negativeoverflowcheck(beforeHcheck,af[0]);
        }
        if(af[0] != 0x00)
        {
            Fbitbuffer[7] = 0;
            Fbitbuffer[6] = 1;
            Fbitbuffer[5] = halfcarrycheck(beforeHcheck,af[0]);
            Fbitbuffer[4] = negativeoverflowcheck(beforeHcheck,af[0]);
        }
        af[1] = Fbitbuffer.to_ulong();
        pc++;
        cycles += 4;
        break;

        case 0x9D: // Flag Checked
        beforeHcheck = af[0];
        Fbitbuffer = af[1];
        if(Fbitbuffer[4] == 1)
        {
            af[0] = af[0] - (hl[1] + 0x01);
        }
        if(Fbitbuffer[4] == 0)
        {
            af[0] = af[0] - (hl[1]);
        }
        if(af[0] == 0x00)
        {
            Fbitbuffer[7] = 1;
            Fbitbuffer[6] = 1;
            Fbitbuffer[5] = halfcarrycheck(beforeHcheck,af[0]);
            Fbitbuffer[4] = negativeoverflowcheck(beforeHcheck,af[0]);
        }
        if(af[0] != 0x00)
        {
            Fbitbuffer[7] = 0;
            Fbitbuffer[6] = 1;
            Fbitbuffer[5] = halfcarrycheck(beforeHcheck,af[0]);
            Fbitbuffer[4] = negativeoverflowcheck(beforeHcheck,af[0]);
        }
        af[1] = Fbitbuffer.to_ulong();
        pc++;
        cycles += 4;
        break;

        case 0x9E: // Flag Checked
        hlbuffer = hl[0] << 8 | hl[1];
        beforeHcheck = af[0];
        Fbitbuffer = af[1];
        if(Fbitbuffer[4] == 1)
        {
            af[0] = af[0] - (memory[hlbuffer] + 0x01);
        }
        if(Fbitbuffer[4] == 0)
        {
            af[0] = af[0] - (memory[hlbuffer]);
        }
        if(af[0] == 0x00)
        {
            Fbitbuffer[7] = 1;
            Fbitbuffer[6] = 1;
            Fbitbuffer[5] = halfcarrycheck(beforeHcheck,af[0]);
            Fbitbuffer[4] = negativeoverflowcheck(beforeHcheck,af[0]);
        }
        if(af[0] != 0x00)
        {
            Fbitbuffer[7] = 0;
            Fbitbuffer[6] = 1;
            Fbitbuffer[5] = halfcarrycheck(beforeHcheck,af[0]);
            Fbitbuffer[4] = negativeoverflowcheck(beforeHcheck,af[0]);
        }
        af[1] = Fbitbuffer.to_ulong();
        pc++;
        cycles += 8;
        break;

        case 0x9F: // Flag Checked
        beforeHcheck = af[0];
        Fbitbuffer = af[1];
        if(Fbitbuffer[4] == 1)
        {
            af[0] = af[0] - (af[0] + 0x01);
        }
        if(Fbitbuffer[4] == 0)
        {
            af[0] = af[0] - (af[0]);
        }
        if(af[0] == 0x00)
        {
            Fbitbuffer[7] = 1;
            Fbitbuffer[6] = 1;
            Fbitbuffer[5] = halfcarrycheck(beforeHcheck,af[0]);
            Fbitbuffer[4] = negativeoverflowcheck(beforeHcheck,af[0]);
        }
        if(af[0] != 0x00)
        {
            Fbitbuffer[7] = 0;
            Fbitbuffer[6] = 1;
            Fbitbuffer[5] = halfcarrycheck(beforeHcheck,af[0]);
            Fbitbuffer[4] = negativeoverflowcheck(beforeHcheck,af[0]);
        }
        af[1] = Fbitbuffer.to_ulong();
        pc++;
        cycles += 4;
        break;

        case 0xA0: // Flag Checked
            Fbitbuffer = af[1];
            af[0] = bc[0] & af[0];
            if(af[0] == 0x00)
            {
                Fbitbuffer[7] = 1;
                Fbitbuffer[6] = 0;
                Fbitbuffer[5] = 1;
                Fbitbuffer[4] = 0;
            }
            if(af[0] != 0x00)
            {
                Fbitbuffer[7] = 0;
                Fbitbuffer[6] = 0;
                Fbitbuffer[5] = 1;
                Fbitbuffer[4] = 0;
            }
            af[1] = Fbitbuffer.to_ulong();
            pc++;
            cycles += 4;
        break;

        case 0xA1: // Flags Need Fixed
            Fbitbuffer = af[1];
            af[0] = bc[1] & af[0];
            if(af[0] == 0x00)
            {
                Fbitbuffer[7] = 1;
                Fbitbuffer[6] = 0;
                Fbitbuffer[5] = 1;
                Fbitbuffer[4] = 0;
            }
            if(af[0] != 0x00)
            {
                Fbitbuffer[7] = 0;
                Fbitbuffer[6] = 0;
                Fbitbuffer[5] = 1;
                Fbitbuffer[4] = 0;
            }
            af[1] = Fbitbuffer.to_ulong();
            pc++;
            cycles += 4;
        break;

        case 0xA2: // Flag Checked
            Fbitbuffer = af[1];
            af[0] = de[0] & af[0];
            if(af[0] == 0x00)
            {
                Fbitbuffer[7] = 1;
                Fbitbuffer[6] = 0;
                Fbitbuffer[5] = 1;
                Fbitbuffer[4] = 0;
            }
            if(af[0] != 0x00)
            {
                Fbitbuffer[7] = 0;
                Fbitbuffer[6] = 0;
                Fbitbuffer[5] = 1;
                Fbitbuffer[4] = 0;
            }
            af[1] = Fbitbuffer.to_ulong();
            pc++;
            cycles += 4;
        break;

        case 0xA3: // Flag Checked
            Fbitbuffer = af[1];
            af[0] = de[1] & af[0];
            if(af[0] == 0x00)
            {
                Fbitbuffer[7] = 1;
                Fbitbuffer[6] = 0;
                Fbitbuffer[5] = 1;
                Fbitbuffer[4] = 0;
            }
            if(af[0] != 0x00)
            {
                Fbitbuffer[7] = 0;
                Fbitbuffer[6] = 0;
                Fbitbuffer[5] = 1;
                Fbitbuffer[4] = 0;
            }
            af[1] = Fbitbuffer.to_ulong();
            pc++;
            cycles += 4;
        break;

        case 0xA4: // Flag Checked
            Fbitbuffer = af[1];
            af[0] = hl[0] & af[0];
            if(af[0] == 0x00)
            {
                Fbitbuffer[7] = 1;
                Fbitbuffer[6] = 0;
                Fbitbuffer[5] = 1;
                Fbitbuffer[4] = 0;
            }
            if(af[0] != 0x00)
            {
                Fbitbuffer[7] = 0;
                Fbitbuffer[6] = 0;
                Fbitbuffer[5] = 1;
                Fbitbuffer[4] = 0;
            }
            af[1] = Fbitbuffer.to_ulong();
            pc++;
            cycles += 4;
        break;

        case 0xA5: // Flag Checked
            Fbitbuffer = af[1];
            af[0] = hl[1] & af[0];
            if(af[0] == 0x00)
            {
                Fbitbuffer[7] = 1;
                Fbitbuffer[6] = 0;
                Fbitbuffer[5] = 1;
                Fbitbuffer[4] = 0;
            }
            if(af[0] != 0x00)
            {
                Fbitbuffer[7] = 0;
                Fbitbuffer[6] = 0;
                Fbitbuffer[5] = 1;
                Fbitbuffer[4] = 0;
            }
            af[1] = Fbitbuffer.to_ulong();
            pc++;
            cycles += 4;
        break;

        case 0xA6: // Flag Checked
            hlbuffer = hl[0] << 8 | hl[1];
            af[0] = memory[hlbuffer] & af[0];
            Fbitbuffer = af[1];
            if(af[0] == 0x00)
            {
                Fbitbuffer[7] = 1;
                Fbitbuffer[6] = 0;
                Fbitbuffer[5] = 1;
                Fbitbuffer[4] = 0;
            }
            if(af[0] != 0x00)
            {
                Fbitbuffer[7] = 0;
                Fbitbuffer[6] = 0;
                Fbitbuffer[5] = 1;
                Fbitbuffer[4] = 0;
            }
            af[1] = Fbitbuffer.to_ulong();
            pc++;
            cycles += 8;
        break;

        case 0xA7: // Flag Checked
            Fbitbuffer = af[1];
            af[0] = af[0] & af[0];
            if(af[0] == 0x00)
            {
                Fbitbuffer[7] = 1;
                Fbitbuffer[6] = 0;
                Fbitbuffer[5] = 1;
                Fbitbuffer[4] = 0;
            }
            if(af[0] != 0x00)
            {
                Fbitbuffer[7] = 0;
                Fbitbuffer[6] = 0;
                Fbitbuffer[5] = 1;
                Fbitbuffer[4] = 0;
            }
            af[1] = Fbitbuffer.to_ulong();
            pc++;
            cycles += 4;
        break;

        case 0xA8: // Flag Checked
            af[0] = bc[0] ^ af[0];
            Fbitbuffer = af[1];
            if(af[0] == 0x0)
            {
                Fbitbuffer[7] = 1;
                Fbitbuffer[6] = 0;
                Fbitbuffer[5] = 0;
                Fbitbuffer[4] = 0;
            }
            if(af[0] != 0x0)
            {
                Fbitbuffer[7] = 1;
                Fbitbuffer[6] = 0;
                Fbitbuffer[5] = 0;
                Fbitbuffer[4] = 0;
            }
            af[1] = Fbitbuffer.to_ulong();
            pc++;
            cycles += 4;
        break;

        case 0xA9: // Flag Checked
            af[0] = bc[1] ^ af[0];
            Fbitbuffer = af[1];
            if(af[0] == 0x0)
            {
                Fbitbuffer[7] = 1;
                Fbitbuffer[6] = 0;
                Fbitbuffer[5] = 0;
                Fbitbuffer[4] = 0;
            }
            if(af[0] != 0x0)
            {
                Fbitbuffer[7] = 1;
                Fbitbuffer[6] = 0;
                Fbitbuffer[5] = 0;
                Fbitbuffer[4] = 0;
            }
            af[1] = Fbitbuffer.to_ulong();
            pc++;
            cycles += 4;
        break;

        case 0xAA: // Flag Checked
            af[0] = de[0] ^ af[0];
            Fbitbuffer = af[1];
            if(af[0] == 0x0)
            {
                Fbitbuffer[7] = 1;
                Fbitbuffer[6] = 0;
                Fbitbuffer[5] = 0;
                Fbitbuffer[4] = 0;
            }
            if(af[0] != 0x0)
            {
                Fbitbuffer[7] = 1;
                Fbitbuffer[6] = 0;
                Fbitbuffer[5] = 0;
                Fbitbuffer[4] = 0;
            }
            af[1] = Fbitbuffer.to_ulong();
            pc++;
            cycles += 4;
        break;

        case 0xAB: // Flag Checked
            af[0] = de[1] ^ af[0];
            Fbitbuffer = af[1];
            if(af[0] == 0x0)
            {
                Fbitbuffer[7] = 1;
                Fbitbuffer[6] = 0;
                Fbitbuffer[5] = 0;
                Fbitbuffer[4] = 0;
            }
            if(af[0] != 0x0)
            {
                Fbitbuffer[7] = 1;
                Fbitbuffer[6] = 0;
                Fbitbuffer[5] = 0;
                Fbitbuffer[4] = 0;
            }
            af[1] = Fbitbuffer.to_ulong();
            pc++;
            cycles += 4;
        break;

        case 0xAC: // Flag Checked
            af[0] = hl[0] ^ af[0];
            Fbitbuffer = af[1];
            if(af[0] == 0x0)
            {
                Fbitbuffer[7] = 1;
                Fbitbuffer[6] = 0;
                Fbitbuffer[5] = 0;
                Fbitbuffer[4] = 0;
            }
            if(af[0] != 0x0)
            {
                Fbitbuffer[7] = 1;
                Fbitbuffer[6] = 0;
                Fbitbuffer[5] = 0;
                Fbitbuffer[4] = 0;
            }
            af[1] = Fbitbuffer.to_ulong();
            pc++;
            cycles += 4;
        break;

        case 0xAD: // Flag Checked
            af[0] = hl[1] ^ af[0];
            Fbitbuffer = af[1];
            if(af[0] == 0x0)
            {
                Fbitbuffer[7] = 1;
                Fbitbuffer[6] = 0;
                Fbitbuffer[5] = 0;
                Fbitbuffer[4] = 0;
            }
            if(af[0] != 0x0)
            {
                Fbitbuffer[7] = 1;
                Fbitbuffer[6] = 0;
                Fbitbuffer[5] = 0;
                Fbitbuffer[4] = 0;
            }
            af[1] = Fbitbuffer.to_ulong();
            pc++;
            cycles += 4;
        break;

        case 0xAE: // Flag Checked
            hlbuffer = hl[0] << 8 | hl[1];
            af[0] = memory[hlbuffer] ^ af[0];
            Fbitbuffer = af[1];
            if(af[0] == 0x0)
            {
                Fbitbuffer[7] = 1;
                Fbitbuffer[6] = 0;
                Fbitbuffer[5] = 0;
                Fbitbuffer[4] = 0;
            }
            if(af[0] != 0x0)
            {
                Fbitbuffer[7] = 1;
                Fbitbuffer[6] = 0;
                Fbitbuffer[5] = 0;
                Fbitbuffer[4] = 0;
            }
            af[1] = Fbitbuffer.to_ulong();
            pc++;
            cycles += 4;
        break;

        case 0xAF: // Flag Checked
            af[0] = af[0] ^ af[0];
            Fbitbuffer = af[1];
            if(af[0] == 0x0)
            {
                Fbitbuffer[7] = 1;
                Fbitbuffer[6] = 0;
                Fbitbuffer[5] = 0;
                Fbitbuffer[4] = 0;
            }
            if(af[0] != 0x0)
            {
                Fbitbuffer[7] = 1;
                Fbitbuffer[6] = 0;
                Fbitbuffer[5] = 0;
                Fbitbuffer[4] = 0;
            }
            af[1] = Fbitbuffer.to_ulong();
            pc++;
            cycles += 4;
        break;

        case 0xB0: // Flag Checked
            Abitbuffer = af[0];
            Bbitbuffer = bc[0];
            Fbitbuffer = af[1];
            bitcount = 7;
            while (helpOR == false)
            {
                if(Abitbuffer[bitcount] == 0 && Bbitbuffer[bitcount] == 1)
                {
                    Abitbuffer[bitcount] = 1;
                }
                bitcount--;
                if(bitcount == 0xFFFFFFFF)
                {
                    break;
                }
            }
            af[0] = Abitbuffer.to_ulong();
            if(af[0] == 0x00)
            {
                Fbitbuffer[7] = 1;
                Fbitbuffer[6] = 0;
                Fbitbuffer[5] = 0;
                Fbitbuffer[4] = 0;
            }
            if(af[0] != 0x00)
            {
                Fbitbuffer[7] = 0;
                Fbitbuffer[6] = 0;
                Fbitbuffer[5] = 0;
                Fbitbuffer[4] = 0;
            }
            af[1] = Fbitbuffer.to_ulong();
            pc++;
            cycles += 4;
        break;

        case 0xB1: // Flag Checked
            Abitbuffer = af[0];
            Bbitbuffer = bc[1];
            Fbitbuffer = af[1];
            bitcount = 7;
            while (helpOR == false)
            {
                if(Abitbuffer[bitcount] == 0 && Bbitbuffer[bitcount] == 1)
                {
                    Abitbuffer[bitcount] = 1;
                }
                bitcount--;
                if(bitcount == 0xFFFFFFFF)
                {
                    break;
                }
            }
            af[0] = Abitbuffer.to_ulong();
            if(af[0] == 0x00)
            {
                Fbitbuffer[7] = 1;
                Fbitbuffer[6] = 0;
                Fbitbuffer[5] = 0;
                Fbitbuffer[4] = 0;
            }
            if(af[0] != 0x00)
            {
                Fbitbuffer[7] = 0;
                Fbitbuffer[6] = 0;
                Fbitbuffer[5] = 0;
                Fbitbuffer[4] = 0;
            }
            af[1] = Fbitbuffer.to_ulong();
            pc++;
            cycles += 4;
        break;

        case 0xB2: // Flag Checked
            Abitbuffer = af[0];
            Bbitbuffer = de[0];
            Fbitbuffer = af[1];
            bitcount = 7;
            while (helpOR == false)
            {
                if(Abitbuffer[bitcount] == 0 && Bbitbuffer[bitcount] == 1)
                {
                    Abitbuffer[bitcount] = 1;
                }
                bitcount--;
                if(bitcount == 0xFFFFFFFF)
                {
                    break;
                }
            }
            af[0] = Abitbuffer.to_ulong();
            if(af[0] == 0x00)
            {
                Fbitbuffer[7] = 1;
                Fbitbuffer[6] = 0;
                Fbitbuffer[5] = 0;
                Fbitbuffer[4] = 0;
            }
            if(af[0] != 0x00)
            {
                Fbitbuffer[7] = 0;
                Fbitbuffer[6] = 0;
                Fbitbuffer[5] = 0;
                Fbitbuffer[4] = 0;
            }
            af[1] = Fbitbuffer.to_ulong();
            pc++;
            cycles += 4;
        break;

        case 0xB3: // Flag Checked
            Abitbuffer = af[0];
            Bbitbuffer = de[1];
            Fbitbuffer = af[1];
            bitcount = 7;
            while (helpOR == false)
            {
                if(Abitbuffer[bitcount] == 0 && Bbitbuffer[bitcount] == 1)
                {
                    Abitbuffer[bitcount] = 1;
                }
                bitcount--;
                if(bitcount == 0xFFFFFFFF)
                {
                    break;
                }
            }
            af[0] = Abitbuffer.to_ulong();
            if(af[0] == 0x00)
            {
                Fbitbuffer[7] = 1;
                Fbitbuffer[6] = 0;
                Fbitbuffer[5] = 0;
                Fbitbuffer[4] = 0;
            }
            if(af[0] != 0x00)
            {
                Fbitbuffer[7] = 0;
                Fbitbuffer[6] = 0;
                Fbitbuffer[5] = 0;
                Fbitbuffer[4] = 0;
            }
            af[1] = Fbitbuffer.to_ulong();
            pc++;
            cycles += 4;
        break;

        case 0xB4: // Flag Checked
            Abitbuffer = af[0];
            Bbitbuffer = hl[0];
            Fbitbuffer = af[1];
            bitcount = 7;
            while (helpOR == false)
            {
                if(Abitbuffer[bitcount] == 0 && Bbitbuffer[bitcount] == 1)
                {
                    Abitbuffer[bitcount] = 1;
                }
                bitcount--;
                if(bitcount == 0xFFFFFFFF)
                {
                    break;
                }
            }
            af[0] = Abitbuffer.to_ulong();
            if(af[0] == 0x00)
            {
                Fbitbuffer[7] = 1;
                Fbitbuffer[6] = 0;
                Fbitbuffer[5] = 0;
                Fbitbuffer[4] = 0;
            }
            if(af[0] != 0x00)
            {
                Fbitbuffer[7] = 0;
                Fbitbuffer[6] = 0;
                Fbitbuffer[5] = 0;
                Fbitbuffer[4] = 0;
            }
            af[1] = Fbitbuffer.to_ulong();
            pc++;
            cycles += 4;
        break;

        case 0xB5: // Flag Checked
            Abitbuffer = af[0];
            Bbitbuffer = hl[1];
            Fbitbuffer = af[1];
            bitcount = 7;
            while (helpOR == false)
            {
                if(Abitbuffer[bitcount] == 0 && Bbitbuffer[bitcount] == 1)
                {
                    Abitbuffer[bitcount] = 1;
                }
                bitcount--;
                if(bitcount == 0xFFFFFFFF)
                {
                    break;
                }
            }
            af[0] = Abitbuffer.to_ulong();
            if(af[0] == 0x00)
            {
                Fbitbuffer[7] = 1;
                Fbitbuffer[6] = 0;
                Fbitbuffer[5] = 0;
                Fbitbuffer[4] = 0;
            }
            if(af[0] != 0x00)
            {
                Fbitbuffer[7] = 0;
                Fbitbuffer[6] = 0;
                Fbitbuffer[5] = 0;
                Fbitbuffer[4] = 0;
            }
            af[1] = Fbitbuffer.to_ulong();
            pc++;
            cycles += 4;
        break;

        case 0xB6: // Flag Checked
            hlbuffer = hl[0] << 8 | hl[1];
            Abitbuffer = af[0];
            Bbitbuffer = memory[hlbuffer];
            Fbitbuffer = af[1];
            bitcount = 7;
            while (helpOR == false)
            {
                if(Abitbuffer[bitcount] == 0 && Bbitbuffer[bitcount] == 1)
                {
                    Abitbuffer[bitcount] = 1;
                }
                bitcount--;
                if(bitcount == 0xFFFFFFFF)
                {
                    break;
                }
            }
            af[0] = Abitbuffer.to_ulong();
            if(af[0] == 0x00)
            {
                Fbitbuffer[7] = 1;
                Fbitbuffer[6] = 0;
                Fbitbuffer[5] = 0;
                Fbitbuffer[4] = 0;
            }
            if(af[0] != 0x00)
            {
                Fbitbuffer[7] = 0;
                Fbitbuffer[6] = 0;
                Fbitbuffer[5] = 0;
                Fbitbuffer[4] = 0;
            }
            af[1] = Fbitbuffer.to_ulong();
            pc++;
            cycles += 8;
        break;

        case 0xB7: // Flag Checked
            Abitbuffer = af[0];
            Bbitbuffer = af[0];
            Fbitbuffer = af[1];
            bitcount = 7;
            while (helpOR == false)
            {
                if(Abitbuffer[bitcount] == 0 && Bbitbuffer[bitcount] == 1)
                {
                    Abitbuffer[bitcount] = 1;
                }
                bitcount--;
                if(bitcount == 0xFFFFFFFF)
                {
                    break;
                }
            }
            af[0] = Abitbuffer.to_ulong();
            if(af[0] == 0x00)
            {
                Fbitbuffer[7] = 1;
                Fbitbuffer[6] = 0;
                Fbitbuffer[5] = 0;
                Fbitbuffer[4] = 0;
            }
            if(af[0] != 0x00)
            {
                Fbitbuffer[7] = 0;
                Fbitbuffer[6] = 0;
                Fbitbuffer[5] = 0;
                Fbitbuffer[4] = 0;
            }
            af[1] = Fbitbuffer.to_ulong();
            pc++;
            cycles += 4;
        break;

        case 0xB8: // Flag Checked
            tem = af[0] - bc[0];
            Fbitbuffer = af[1];
            if(tem == 0x00)
            {
                Fbitbuffer[7] = 1;
                Fbitbuffer[6] = 1;
                Fbitbuffer[5] = halfcarrycheck(af[0],tem);
                Fbitbuffer[4] = negativeoverflowcheck(af[0],tem);
            }
            if(tem != 0x00)
            {
                Fbitbuffer[7] = 0;
                Fbitbuffer[6] = 1;
                Fbitbuffer[5] = halfcarrycheck(af[0],tem);
                Fbitbuffer[4] = negativeoverflowcheck(af[0],tem);
            }
            af[1] = Fbitbuffer.to_ulong();
            pc++;
            cycles += 8;
        break;

        case 0xB9: // Flag Checked
            tem = af[0] - bc[1];
            Fbitbuffer = af[1];
            if(tem == 0x00)
            {
                Fbitbuffer[7] = 1;
                Fbitbuffer[6] = 1;
                Fbitbuffer[5] = halfcarrycheck(af[0],tem);
                Fbitbuffer[4] = negativeoverflowcheck(af[0],tem);
            }
            if(tem != 0x00)
            {
                Fbitbuffer[7] = 0;
                Fbitbuffer[6] = 1;
                Fbitbuffer[5] = halfcarrycheck(af[0],tem);
                Fbitbuffer[4] = negativeoverflowcheck(af[0],tem);
            }
            af[1] = Fbitbuffer.to_ulong();
            pc++;
            cycles += 8;
        break;

        case 0xBA: // Flag Checked
            tem = af[0] - de[0];
            Fbitbuffer = af[1];
            if(tem == 0x00)
            {
                Fbitbuffer[7] = 1;
                Fbitbuffer[6] = 1;
                Fbitbuffer[5] = halfcarrycheck(af[0],tem);
                Fbitbuffer[4] = negativeoverflowcheck(af[0],tem);
            }
            if(tem != 0x00)
            {
                Fbitbuffer[7] = 0;
                Fbitbuffer[6] = 1;
                Fbitbuffer[5] = halfcarrycheck(af[0],tem);
                Fbitbuffer[4] = negativeoverflowcheck(af[0],tem);
            }
            af[1] = Fbitbuffer.to_ulong();
            pc++;
            cycles += 8;
        break;

        case 0xBB: // Flag Checked
            tem = af[0] - de[1];
            Fbitbuffer = af[1];
            if(tem == 0x00)
            {
                Fbitbuffer[7] = 1;
                Fbitbuffer[6] = 1;
                Fbitbuffer[5] = halfcarrycheck(af[0],tem);
                Fbitbuffer[4] = negativeoverflowcheck(af[0],tem);
            }
            if(tem != 0x00)
            {
                Fbitbuffer[7] = 0;
                Fbitbuffer[6] = 1;
                Fbitbuffer[5] = halfcarrycheck(af[0],tem);
                Fbitbuffer[4] = negativeoverflowcheck(af[0],tem);
            }
            af[1] = Fbitbuffer.to_ulong();
            pc++;
            cycles += 8;
        break;

        case 0xBC: // Flag Checked
            tem = af[0] - hl[0];
            Fbitbuffer = af[1];
            if(tem == 0x00)
            {
                Fbitbuffer[7] = 1;
                Fbitbuffer[6] = 1;
                Fbitbuffer[5] = halfcarrycheck(af[0],tem);
                Fbitbuffer[4] = negativeoverflowcheck(af[0],tem);
            }
            if(tem != 0x00)
            {
                Fbitbuffer[7] = 0;
                Fbitbuffer[6] = 1;
                Fbitbuffer[5] = halfcarrycheck(af[0],tem);
                Fbitbuffer[4] = negativeoverflowcheck(af[0],tem);
            }
            af[1] = Fbitbuffer.to_ulong();
            pc++;
            cycles += 8;
        break;

        case 0xBD: // Flag Checked
            tem = af[0] - hl[1];
            Fbitbuffer = af[1];
            if(tem == 0x00)
            {
                Fbitbuffer[7] = 1;
                Fbitbuffer[6] = 1;
                Fbitbuffer[5] = halfcarrycheck(af[0],tem);
                Fbitbuffer[4] = negativeoverflowcheck(af[0],tem);
            }
            if(tem != 0x00)
            {
                Fbitbuffer[7] = 0;
                Fbitbuffer[6] = 1;
                Fbitbuffer[5] = halfcarrycheck(af[0],tem);
                Fbitbuffer[4] = negativeoverflowcheck(af[0],tem);
            }
            af[1] = Fbitbuffer.to_ulong();
            pc++;
            cycles += 8;
        break;

        case 0xBE: // Flag Checked
            hlbuffer = hl[0] << 8 | hl[1];
            tem = af[0] - memory[hlbuffer];
            Fbitbuffer = af[1];
            if(tem == 0x00)
            {
                Fbitbuffer[7] = 1;
                Fbitbuffer[6] = 1;
                Fbitbuffer[5] = halfcarrycheck(af[0],tem);
                Fbitbuffer[4] = negativeoverflowcheck(af[0],tem);
            }
            if(tem != 0x00)
            {
                Fbitbuffer[7] = 0;
                Fbitbuffer[6] = 1;
                Fbitbuffer[5] = halfcarrycheck(af[0],tem);
                Fbitbuffer[4] = negativeoverflowcheck(af[0],tem);
            }
            af[1] = Fbitbuffer.to_ulong();
            cycles += 8;
            pc += 2;
        break;

        case 0xBF: // Flag Checked
            tem = af[0] - af[0];
            Fbitbuffer = af[1];
            if(tem == 0x00)
            {
                Fbitbuffer[7] = 1;
                Fbitbuffer[6] = 1;
                Fbitbuffer[5] = halfcarrycheck(af[0],tem);
                Fbitbuffer[4] = negativeoverflowcheck(af[0],tem);
            }
            if(tem != 0x00)
            {
                Fbitbuffer[7] = 0;
                Fbitbuffer[6] = 1;
                Fbitbuffer[5] = halfcarrycheck(af[0],tem);
                Fbitbuffer[4] = negativeoverflowcheck(af[0],tem);
            }
            af[1] = Fbitbuffer.to_ulong();
            pc++;
            cycles += 8;
        break;

        case 0xC0: // Flag Checked
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

        case 0xC1: // Flag Checked
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

        case 0xC2: // Flag Checked
            Fbitbuffer = af[1];
            if (Fbitbuffer[7] == 0)
            {
                opnn[0] = memory[pc + 2];
                opnn[1] = memory[pc + 1];
                nn = opnn[0] << 8 | opnn[1];
                pc = nn;
                cycles += 12;
            }
            if (Fbitbuffer[7] == 1)
            {
            pc += 3;
            cycles += 12;
            }
        break;

        case 0xC3: // Flag Checked
            opnn[0] = memory[pc + 2];
            opnn[1] = memory[pc + 1];
            nn = opnn[0] << 8 | opnn[1];
            pc = nn;
            cycles += 4;
        break;

        case 0xC4: // Flag Checked
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
            }
            if(Fbitbuffer[7] == 1)
            {
                pc += 3;
                cycles += 12;
            }
        break;

        case 0xC5: // Flag Checked
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

        case 0xC6: // Flag Checked
            beforeHcheck = af[0];
            Fbitbuffer = af[1];
            af[0] = af[0] + memory[pc + 1];
            if(af[0] == 0x00)
            {
                Fbitbuffer[7] = 1;
                Fbitbuffer[6] = 0;
                Fbitbuffer[5] = halfcarrycheck(beforeHcheck,af[0]);
                Fbitbuffer[4] = overflowcheck(beforeHcheck,af[0]);  // Here, we are using beforeHcheck because there is no reason to use another variable when this one already has the value I want.
            }
            if(af[0] != 0x00)
            {
                Fbitbuffer[7] = 0;
                Fbitbuffer[6] = 0;
                Fbitbuffer[5] = halfcarrycheck(beforeHcheck,af[0]);
                Fbitbuffer[4] = overflowcheck(beforeHcheck,af[0]);
            }
            af[1] = Fbitbuffer.to_ulong();
            pc += 2;
            cycles += 8;
        break;

        case 0xC7: // Flag Checked
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

        case 0xC8: // Flag Checked
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

        case 0xC9: // Flag Checked
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

        case 0xCA: // Flag Checked
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

                case 0x00:
                    Bbitbuffer = bc[0];
                    Fbitbuffer = af[1];
                    Carry_Helper[0] = Bbitbuffer[7];
                    Bbitbuffer = Bbitbuffer << 1;
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
                        Fbitbuffer[7] = 0;
                        Fbitbuffer[6] = 0;
                        Fbitbuffer[5] = 0;
                        Fbitbuffer[4] = Carry_Helper[0];
                    }
                    af[1] = Fbitbuffer.to_ulong();
                    pc += 2;
                    cycles += 8;
                break;

                case 0x01:
                    Bbitbuffer = bc[1];
                    Fbitbuffer = af[1];
                    Carry_Helper[0] = Bbitbuffer[7];
                    Bbitbuffer = Bbitbuffer << 1;
                    bc[1] = Bbitbuffer.to_ulong();
                    if(bc[1] == 0x00)
                    {
                        Fbitbuffer[7] = 1;
                        Fbitbuffer[6] = 0;
                        Fbitbuffer[5] = 0;
                        Fbitbuffer[4] = Carry_Helper[0];
                    }
                    if(bc[1] != 0x00)
                    {
                        Fbitbuffer[7] = 0;
                        Fbitbuffer[6] = 0;
                        Fbitbuffer[5] = 0;
                        Fbitbuffer[4] = Carry_Helper[0];
                    }
                    af[1] = Fbitbuffer.to_ulong();
                    pc += 2;
                    cycles += 8;
                break;

                case 0x02:
                    Bbitbuffer = de[0];
                    Fbitbuffer = af[1];
                    Carry_Helper[0] = Bbitbuffer[7];
                    Bbitbuffer = Bbitbuffer << 1;
                    de[0] = Bbitbuffer.to_ulong();
                    if(de[0] == 0x00)
                    {
                        Fbitbuffer[7] = 1;
                        Fbitbuffer[6] = 0;
                        Fbitbuffer[5] = 0;
                        Fbitbuffer[4] = Carry_Helper[0];
                    }
                    if(de[0] != 0x00)
                    {
                        Fbitbuffer[7] = 0;
                        Fbitbuffer[6] = 0;
                        Fbitbuffer[5] = 0;
                        Fbitbuffer[4] = Carry_Helper[0];
                    }
                    af[1] = Fbitbuffer.to_ulong();
                    pc += 2;
                    cycles += 8;
                break;

                case 0x03:
                    Bbitbuffer = de[1];
                    Fbitbuffer = af[1];
                    Carry_Helper[0] = Bbitbuffer[7];
                    Bbitbuffer = Bbitbuffer << 1;
                    de[1] = Bbitbuffer.to_ulong();
                    if(de[1] == 0x00)
                    {
                        Fbitbuffer[7] = 1;
                        Fbitbuffer[6] = 0;
                        Fbitbuffer[5] = 0;
                        Fbitbuffer[4] = Carry_Helper[0];
                    }
                    if(de[1] != 0x00)
                    {
                        Fbitbuffer[7] = 0;
                        Fbitbuffer[6] = 0;
                        Fbitbuffer[5] = 0;
                        Fbitbuffer[4] = Carry_Helper[0];
                    }
                    af[1] = Fbitbuffer.to_ulong();
                    pc += 2;
                    cycles += 8;
                break;

                case 0x04:
                    Bbitbuffer = hl[0];
                    Fbitbuffer = af[1];
                    Carry_Helper[0] = Bbitbuffer[7];
                    Bbitbuffer = Bbitbuffer << 1;
                    hl[0] = Bbitbuffer.to_ulong();
                    if(hl[0] == 0x00)
                    {
                        Fbitbuffer[7] = 1;
                        Fbitbuffer[6] = 0;
                        Fbitbuffer[5] = 0;
                        Fbitbuffer[4] = Carry_Helper[0];
                    }
                    if(hl[0] != 0x00)
                    {
                        Fbitbuffer[7] = 0;
                        Fbitbuffer[6] = 0;
                        Fbitbuffer[5] = 0;
                        Fbitbuffer[4] = Carry_Helper[0];
                    }
                    af[1] = Fbitbuffer.to_ulong();
                    pc += 2;
                    cycles += 8;
                break;

                case 0x05:
                    Bbitbuffer = hl[1];
                    Fbitbuffer = af[1];
                    Carry_Helper[0] = Bbitbuffer[7];
                    Bbitbuffer = Bbitbuffer << 1;
                    hl[1] = Bbitbuffer.to_ulong();
                    if(hl[1] == 0x00)
                    {
                        Fbitbuffer[7] = 1;
                        Fbitbuffer[6] = 0;
                        Fbitbuffer[5] = 0;
                        Fbitbuffer[4] = Carry_Helper[0];
                    }
                    if(hl[1] != 0x00)
                    {
                        Fbitbuffer[7] = 0;
                        Fbitbuffer[6] = 0;
                        Fbitbuffer[5] = 0;
                        Fbitbuffer[4] = Carry_Helper[0];
                    }
                    af[1] = Fbitbuffer.to_ulong();
                    pc += 2;
                    cycles += 8;
                break;

                case 0x06:
                    hlbuffer = hl[0] << 8 | hl[1];
                    Bbitbuffer = memory[hlbuffer];
                    Fbitbuffer = af[1];
                    Carry_Helper[0] = Bbitbuffer[7];
                    Bbitbuffer = Bbitbuffer << 1;
                    memory[hlbuffer] = Bbitbuffer.to_ulong();
                    if(memory[hlbuffer] == 0x00)
                    {
                        Fbitbuffer[7] = 1;
                        Fbitbuffer[6] = 0;
                        Fbitbuffer[5] = 0;
                        Fbitbuffer[4] = Carry_Helper[0];
                    }
                    if(memory[hlbuffer] != 0x00)
                    {
                        Fbitbuffer[7] = 0;
                        Fbitbuffer[6] = 0;
                        Fbitbuffer[5] = 0;
                        Fbitbuffer[4] = Carry_Helper[0];
                    }
                    af[1] = Fbitbuffer.to_ulong();
                    pc += 2;
                    cycles += 8;
                break;

                case 0x07:
                    Bbitbuffer = af[0];
                    Fbitbuffer = af[1];
                    Carry_Helper[0] = Bbitbuffer[7];
                    Bbitbuffer = Bbitbuffer << 1;
                    af[0] = Bbitbuffer.to_ulong();
                    if(af[0] == 0x00)
                    {
                        Fbitbuffer[7] = 1;
                        Fbitbuffer[6] = 0;
                        Fbitbuffer[5] = 0;
                        Fbitbuffer[4] = Carry_Helper[0];
                    }
                    if(af[0] != 0x00)
                    {
                        Fbitbuffer[7] = 0;
                        Fbitbuffer[6] = 0;
                        Fbitbuffer[5] = 0;
                        Fbitbuffer[4] = Carry_Helper[0];
                    }
                    af[1] = Fbitbuffer.to_ulong();
                    pc += 2;
                    cycles += 8;
                break;

                case 0x08:
                    Bbitbuffer = bc[0];
                    Fbitbuffer = af[1];
                    Carry_Helper[0] = Bbitbuffer[0];
                    Bbitbuffer = Bbitbuffer >> 1;
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
                        Fbitbuffer[7] = 0;
                        Fbitbuffer[6] = 0;
                        Fbitbuffer[5] = 0;
                        Fbitbuffer[4] = Carry_Helper[0];
                    }
                    af[1] = Fbitbuffer.to_ulong();
                    pc += 2;
                    cycles += 8;
                break;

                case 0x09:
                    Bbitbuffer = bc[1];
                    Fbitbuffer = af[1];
                    Carry_Helper[0] = Bbitbuffer[0];
                    Bbitbuffer = Bbitbuffer >> 1;
                    bc[1] = Bbitbuffer.to_ulong();
                    if(bc[1] == 0x00)
                    {
                        Fbitbuffer[7] = 1;
                        Fbitbuffer[6] = 0;
                        Fbitbuffer[5] = 0;
                        Fbitbuffer[4] = Carry_Helper[0];
                    }
                    if(bc[1] != 0x00)
                    {
                        Fbitbuffer[7] = 0;
                        Fbitbuffer[6] = 0;
                        Fbitbuffer[5] = 0;
                        Fbitbuffer[4] = Carry_Helper[0];
                    }
                    af[1] = Fbitbuffer.to_ulong();
                    pc += 2;
                    cycles += 8;
                break;

                case 0x0A:
                    Bbitbuffer = de[0];
                    Fbitbuffer = af[1];
                    Carry_Helper[0] = Bbitbuffer[0];
                    Bbitbuffer = Bbitbuffer >> 1;
                    de[0] = Bbitbuffer.to_ulong();
                    if(de[0] == 0x00)
                    {
                        Fbitbuffer[7] = 1;
                        Fbitbuffer[6] = 0;
                        Fbitbuffer[5] = 0;
                        Fbitbuffer[4] = Carry_Helper[0];
                    }
                    if(de[0] != 0x00)
                    {
                        Fbitbuffer[7] = 0;
                        Fbitbuffer[6] = 0;
                        Fbitbuffer[5] = 0;
                        Fbitbuffer[4] = Carry_Helper[0];
                    }
                    af[1] = Fbitbuffer.to_ulong();
                    pc += 2;
                    cycles += 8;
                break;

                case 0x0B:
                    Bbitbuffer = de[1];
                    Fbitbuffer = af[1];
                    Carry_Helper[0] = Bbitbuffer[0];
                    Bbitbuffer = Bbitbuffer >> 1;
                    de[1] = Bbitbuffer.to_ulong();
                    if(de[1] == 0x00)
                    {
                        Fbitbuffer[7] = 1;
                        Fbitbuffer[6] = 0;
                        Fbitbuffer[5] = 0;
                        Fbitbuffer[4] = Carry_Helper[0];
                    }
                    if(de[1] != 0x00)
                    {
                        Fbitbuffer[7] = 0;
                        Fbitbuffer[6] = 0;
                        Fbitbuffer[5] = 0;
                        Fbitbuffer[4] = Carry_Helper[0];
                    }
                    af[1] = Fbitbuffer.to_ulong();
                    pc += 2;
                    cycles += 8;
                break;

                case 0x0C:
                    Bbitbuffer = hl[0];
                    Fbitbuffer = af[1];
                    Carry_Helper[0] = Bbitbuffer[0];
                    Bbitbuffer = Bbitbuffer >> 1;
                    hl[0] = Bbitbuffer.to_ulong();
                    if(hl[0] == 0x00)
                    {
                        Fbitbuffer[7] = 1;
                        Fbitbuffer[6] = 0;
                        Fbitbuffer[5] = 0;
                        Fbitbuffer[4] = Carry_Helper[0];
                    }
                    if(hl[0] != 0x00)
                    {
                        Fbitbuffer[7] = 0;
                        Fbitbuffer[6] = 0;
                        Fbitbuffer[5] = 0;
                        Fbitbuffer[4] = Carry_Helper[0];
                    }
                    af[1] = Fbitbuffer.to_ulong();
                    pc += 2;
                    cycles += 8;
                break;

                case 0x0D:
                    Bbitbuffer = hl[1];
                    Fbitbuffer = af[1];
                    Carry_Helper[0] = Bbitbuffer[0];
                    Bbitbuffer = Bbitbuffer >> 1;
                    hl[1] = Bbitbuffer.to_ulong();
                    if(hl[1] == 0x00)
                    {
                        Fbitbuffer[7] = 1;
                        Fbitbuffer[6] = 0;
                        Fbitbuffer[5] = 0;
                        Fbitbuffer[4] = Carry_Helper[0];
                    }
                    if(hl[1] != 0x00)
                    {
                        Fbitbuffer[7] = 0;
                        Fbitbuffer[6] = 0;
                        Fbitbuffer[5] = 0;
                        Fbitbuffer[4] = Carry_Helper[0];
                    }
                    af[1] = Fbitbuffer.to_ulong();
                    pc += 2;
                    cycles += 8;
                break;

                case 0x0E:
                    hlbuffer = hl[0] << 8 | hl[1];
                    Bbitbuffer = memory[hlbuffer];
                    Fbitbuffer = af[1];
                    Carry_Helper[0] = Bbitbuffer[0];
                    Bbitbuffer = Bbitbuffer >> 1;
                    memory[hlbuffer] = Bbitbuffer.to_ulong();
                    if(memory[hlbuffer] == 0x00)
                    {
                        Fbitbuffer[7] = 1;
                        Fbitbuffer[6] = 0;
                        Fbitbuffer[5] = 0;
                        Fbitbuffer[4] = Carry_Helper[0];
                    }
                    if(memory[hlbuffer] != 0x00)
                    {
                        Fbitbuffer[7] = 0;
                        Fbitbuffer[6] = 0;
                        Fbitbuffer[5] = 0;
                        Fbitbuffer[4] = Carry_Helper[0];
                    }
                    af[1] = Fbitbuffer.to_ulong();
                    pc += 2;
                    cycles += 8;
                break;

                case 0x0F:
                    Bbitbuffer = af[0];
                    Fbitbuffer = af[1];
                    Carry_Helper[0] = Bbitbuffer[0];
                    Bbitbuffer = Bbitbuffer >> 1;
                    af[0] = Bbitbuffer.to_ulong();
                    if(af[0] == 0x00)
                    {
                        Fbitbuffer[7] = 1;
                        Fbitbuffer[6] = 0;
                        Fbitbuffer[5] = 0;
                        Fbitbuffer[4] = Carry_Helper[0];
                    }
                    if(af[0] != 0x00)
                    {
                        Fbitbuffer[7] = 0;
                        Fbitbuffer[6] = 0;
                        Fbitbuffer[5] = 0;
                        Fbitbuffer[4] = Carry_Helper[0];
                    }
                    af[1] = Fbitbuffer.to_ulong();
                    pc += 2;
                    cycles += 8;
                break;

                case 0x10:
                    Bbitbuffer = bc[0];
                    Fbitbuffer = af[1];
                    Carry_Helper[0] = Bbitbuffer[7];
                    Carry_Helper2[0] = Fbitbuffer[4];
                    Bbitbuffer = Bbitbuffer << 1;
                    Bbitbuffer[0] = Carry_Helper2[0];
                    Fbitbuffer[4] = Carry_Helper[0];
                    bc[0] = Bbitbuffer.to_ulong();
                    if(bc[0] == 0x00)
                    {
                    Fbitbuffer[7] = 1;
                    Fbitbuffer[6] = 0;
                    Fbitbuffer[5] = 0;
                    }
                    if(bc[0] != 0x00)
                    {
                    Fbitbuffer[7] = 0;
                    Fbitbuffer[6] = 0;
                    Fbitbuffer[5] = 0;
                    }
                    af[1] = Fbitbuffer.to_ulong();
                    pc += 2;
                    cycles += 8;
                break;

                case 0x11:
                    Bbitbuffer = bc[1];
                    Fbitbuffer = af[1];
                    Carry_Helper[0] = Bbitbuffer[7];
                    Carry_Helper2[0] = Fbitbuffer[4];
                    Bbitbuffer = Bbitbuffer << 1;
                    Bbitbuffer[0] = Carry_Helper2[0];
                    Fbitbuffer[4] = Carry_Helper[0];
                    bc[1] = Bbitbuffer.to_ulong();
                    if(bc[1] == 0x00)
                    {
                    Fbitbuffer[7] = 1;
                    Fbitbuffer[6] = 0;
                    Fbitbuffer[5] = 0;
                    }
                    if(bc[1] != 0x00)
                    {
                    Fbitbuffer[7] = 0;
                    Fbitbuffer[6] = 0;
                    Fbitbuffer[5] = 0;
                    }
                    af[1] = Fbitbuffer.to_ulong();
                    pc += 2;
                    cycles += 8;
                break;

                case 0x12:
                    Bbitbuffer = de[0];
                    Fbitbuffer = af[1];
                    Carry_Helper[0] = Bbitbuffer[7];
                    Carry_Helper2[0] = Fbitbuffer[4];
                    Bbitbuffer = Bbitbuffer << 1;
                    Bbitbuffer[0] = Carry_Helper2[0];
                    Fbitbuffer[4] = Carry_Helper[0];
                    de[0] = Bbitbuffer.to_ulong();
                    if(de[0] == 0x00)
                    {
                    Fbitbuffer[7] = 1;
                    Fbitbuffer[6] = 0;
                    Fbitbuffer[5] = 0;
                    }
                    if(de[0] != 0x00)
                    {
                    Fbitbuffer[7] = 0;
                    Fbitbuffer[6] = 0;
                    Fbitbuffer[5] = 0;
                    }
                    af[1] = Fbitbuffer.to_ulong();
                    pc += 2;
                    cycles += 8;
                break;

                case 0x13:
                    Bbitbuffer = de[1];
                    Fbitbuffer = af[1];
                    Carry_Helper[0] = Bbitbuffer[7];
                    Carry_Helper2[0] = Fbitbuffer[4];
                    Bbitbuffer = Bbitbuffer << 1;
                    Bbitbuffer[0] = Carry_Helper2[0];
                    Fbitbuffer[4] = Carry_Helper[0];
                    de[1] = Bbitbuffer.to_ulong();
                    if(de[1] == 0x00)
                    {
                    Fbitbuffer[7] = 1;
                    Fbitbuffer[6] = 0;
                    Fbitbuffer[5] = 0;
                    }
                    if(de[1] != 0x00)
                    {
                    Fbitbuffer[7] = 0;
                    Fbitbuffer[6] = 0;
                    Fbitbuffer[5] = 0;
                    }
                    af[1] = Fbitbuffer.to_ulong();
                    pc += 2;
                    cycles += 8;
                break;

                case 0x14:
                    Bbitbuffer = hl[0];
                    Fbitbuffer = af[1];
                    Carry_Helper[0] = Bbitbuffer[7];
                    Carry_Helper2[0] = Fbitbuffer[4];
                    Bbitbuffer = Bbitbuffer << 1;
                    Bbitbuffer[0] = Carry_Helper2[0];
                    Fbitbuffer[4] = Carry_Helper[0];
                    hl[0] = Bbitbuffer.to_ulong();
                    if(hl[0] == 0x00)
                    {
                    Fbitbuffer[7] = 1;
                    Fbitbuffer[6] = 0;
                    Fbitbuffer[5] = 0;
                    }
                    if(hl[0] != 0x00)
                    {
                    Fbitbuffer[7] = 0;
                    Fbitbuffer[6] = 0;
                    Fbitbuffer[5] = 0;
                    }
                    af[1] = Fbitbuffer.to_ulong();
                    pc += 2;
                    cycles += 8;
                break;

                case 0x15:
                    Bbitbuffer = hl[1];
                    Fbitbuffer = af[1];
                    Carry_Helper[0] = Bbitbuffer[7];
                    Carry_Helper2[0] = Fbitbuffer[4];
                    Bbitbuffer = Bbitbuffer << 1;
                    Bbitbuffer[0] = Carry_Helper2[0];
                    Fbitbuffer[4] = Carry_Helper[0];
                    hl[1] = Bbitbuffer.to_ulong();
                    if(hl[1] == 0x00)
                    {
                        Fbitbuffer[7] = 1;
                        Fbitbuffer[6] = 0;
                        Fbitbuffer[5] = 0;
                    }
                    if(hl[1] != 0x00)
                    {
                        Fbitbuffer[7] = 0;
                        Fbitbuffer[6] = 0;
                        Fbitbuffer[5] = 0;
                    }
                    af[1] = Fbitbuffer.to_ulong();
                    pc += 2;
                    cycles += 8;
                break;

                case 0x16:
                    hlbuffer = hl[0] << 8 | hl[1];
                    Bbitbuffer = memory[hlbuffer];
                    Fbitbuffer = af[1];
                    Carry_Helper[0] = Bbitbuffer[7];
                    Carry_Helper2[0] = Fbitbuffer[4];
                    Bbitbuffer = Bbitbuffer << 1;
                    Bbitbuffer[0] = Carry_Helper2[0];
                    Fbitbuffer[4] = Carry_Helper[0];
                    memory[hlbuffer] = Bbitbuffer.to_ulong();
                    if(memory[hlbuffer] == 0x00)
                    {
                    Fbitbuffer[7] = 1;
                    Fbitbuffer[6] = 0;
                    Fbitbuffer[5] = 0;
                    }
                    if(memory[hlbuffer] != 0x00)
                    {
                    Fbitbuffer[7] = 0;
                    Fbitbuffer[6] = 0;
                    Fbitbuffer[5] = 0;
                    }
                    af[1] = Fbitbuffer.to_ulong();
                    pc += 2;
                    cycles += 8;
                break;

                case 0x17:
                    Bbitbuffer = af[0];
                    Fbitbuffer = af[1];
                    Carry_Helper[0] = Bbitbuffer[7];
                    Carry_Helper2[0] = Fbitbuffer[4];
                    Bbitbuffer = Bbitbuffer << 1;
                    Bbitbuffer[0] = Carry_Helper2[0];
                    Fbitbuffer[4] = Carry_Helper[0];
                    af[0] = Bbitbuffer.to_ulong();
                    if(af[0] == 0x00)
                    {
                    Fbitbuffer[7] = 1;
                    Fbitbuffer[6] = 0;
                    Fbitbuffer[5] = 0;
                    }
                    if(af[0] != 0x00)
                    {
                    Fbitbuffer[7] = 0;
                    Fbitbuffer[6] = 0;
                    Fbitbuffer[5] = 0;
                    }
                    af[1] = Fbitbuffer.to_ulong();
                    pc += 2;
                    cycles += 8;
                break;

                case 0x18: // Flags Need Fixed
                    Cbitbuffer = bc[0];
                    Fbitbuffer = af[1];
                    Carry_Helper[0] = Cbitbuffer[0];
                    Carry_Helper2[0] = Fbitbuffer[4];
                    Cbitbuffer = Cbitbuffer >> 1;
                    Cbitbuffer[7] = Carry_Helper2[0];
                    bc[0] = Cbitbuffer.to_ulong();
                    if(bc[0] == 0x00)
                    {
                        Fbitbuffer[7] = 1;
                        Fbitbuffer[6] = 0;
                        Fbitbuffer[5] = 0;
                        Fbitbuffer[4] = Carry_Helper[0];
                    }
                    if(bc[0] != 0x00)
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

                case 0x19: // Flags Need Fixed
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

                case 0x1A: // Flags Need Fixed
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

                case 0x1B: // Flags Need Fixed
                    Cbitbuffer = de[1];
                    Fbitbuffer = af[1];
                    Carry_Helper[0] = Cbitbuffer[0];
                    Carry_Helper2[0] = Fbitbuffer[4];
                    Cbitbuffer = Cbitbuffer >> 1;
                    Cbitbuffer[7] = Carry_Helper2[0];
                    de[1] = Cbitbuffer.to_ulong();
                    if(de[1] == 0x00)
                    {
                        Fbitbuffer[7] = 1;
                        Fbitbuffer[6] = 0;
                        Fbitbuffer[5] = 0;
                        Fbitbuffer[4] = Carry_Helper[0];
                    }
                    if(de[1] != 0x00)
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

                case 0x1C: // Flags Need Fixed
                    Cbitbuffer = hl[0];
                    Fbitbuffer = af[1];
                    Carry_Helper[0] = Cbitbuffer[0];
                    Carry_Helper2[0] = Fbitbuffer[4];
                    Cbitbuffer = Cbitbuffer >> 1;
                    Cbitbuffer[7] = Carry_Helper2[0];
                    hl[0] = Cbitbuffer.to_ulong();
                    if(hl[0] == 0x00)
                    {
                        Fbitbuffer[7] = 1;
                        Fbitbuffer[6] = 0;
                        Fbitbuffer[5] = 0;
                        Fbitbuffer[4] = Carry_Helper[0];
                    }
                    if(hl[0] != 0x00)
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

                case 0x1D: // Flags Need Fixed
                    Cbitbuffer = hl[1];
                    Fbitbuffer = af[1];
                    Carry_Helper[0] = Cbitbuffer[0];
                    Carry_Helper2[0] = Fbitbuffer[4];
                    Cbitbuffer = Cbitbuffer >> 1;
                    Cbitbuffer[7] = Carry_Helper2[0];
                    hl[1] = Cbitbuffer.to_ulong();
                    if(hl[1] == 0x00)
                    {
                        Fbitbuffer[7] = 1;
                        Fbitbuffer[6] = 0;
                        Fbitbuffer[5] = 0;
                        Fbitbuffer[4] = Carry_Helper[0];
                    }
                    if(hl[1] != 0x00)
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

                case 0x1E: // Flags Need Fixed
                    hlbuffer = hl[0] << 8 | hl[1];
                    Cbitbuffer = memory[hlbuffer];
                    Fbitbuffer = af[1];
                    Carry_Helper[0] = Cbitbuffer[0];
                    Carry_Helper2[0] = Fbitbuffer[4];
                    Cbitbuffer = Cbitbuffer >> 1;
                    Cbitbuffer[7] = Carry_Helper2[0];
                    memory[hlbuffer] = Cbitbuffer.to_ulong();
                    if(memory[hlbuffer] == 0x00)
                    {
                        Fbitbuffer[7] = 1;
                        Fbitbuffer[6] = 0;
                        Fbitbuffer[5] = 0;
                        Fbitbuffer[4] = Carry_Helper[0];
                    }
                    if(memory[hlbuffer] != 0x00)
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

                case 0x1F: // Flags Need Fixed
                    Cbitbuffer = af[0];
                    Fbitbuffer = af[1];
                    Carry_Helper[0] = Cbitbuffer[0];
                    Carry_Helper2[0] = Fbitbuffer[4];
                    Cbitbuffer = Cbitbuffer >> 1;
                    Cbitbuffer[7] = Carry_Helper2[0];
                    af[0] = Cbitbuffer.to_ulong();
                    if(af[0] == 0x00)
                    {
                        Fbitbuffer[7] = 1;
                        Fbitbuffer[6] = 0;
                        Fbitbuffer[5] = 0;
                        Fbitbuffer[4] = Carry_Helper[0];
                    }
                    if(af[0] != 0x00)
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

                case 0x20:
                    Abitbuffer = bc[0];
                    Fbitbuffer = af[1];
                    Carry_Helper[0] = Abitbuffer[7];
                    Abitbuffer = Abitbuffer << 1;
                    bc[0] = Abitbuffer.to_ulong();
                    if(bc[0] == 0x00)
                    {
                    Fbitbuffer[7] = 1;
                    Fbitbuffer[6] = 0;
                    Fbitbuffer[5] = 0;
                    Fbitbuffer[4] = Carry_Helper[0];
                    }
                    if(bc[0] != 0x00)
                    {
                    Fbitbuffer[7] = 0;
                    Fbitbuffer[6] = 0;
                    Fbitbuffer[5] = 0;
                    Fbitbuffer[4] = Carry_Helper[0];
                    }
                    af[1] = Fbitbuffer.to_ulong();
                    pc += 2;
                    cycles += 8;
                break;

                case 0x21:
                    Abitbuffer = bc[1];
                    Fbitbuffer = af[1];
                    Carry_Helper[0] = Abitbuffer[7];
                    Abitbuffer = Abitbuffer << 1;
                    bc[1] = Abitbuffer.to_ulong();
                    if(bc[1] == 0x00)
                    {
                    Fbitbuffer[7] = 1;
                    Fbitbuffer[6] = 0;
                    Fbitbuffer[5] = 0;
                    Fbitbuffer[4] = Carry_Helper[0];
                    }
                    if(bc[1] != 0x00)
                    {
                    Fbitbuffer[7] = 0;
                    Fbitbuffer[6] = 0;
                    Fbitbuffer[5] = 0;
                    Fbitbuffer[4] = Carry_Helper[0];
                    }
                    af[1] = Fbitbuffer.to_ulong();
                    pc += 2;
                    cycles += 8;
                break;

                case 0x22:
                    Abitbuffer = de[0];
                    Fbitbuffer = af[1];
                    Carry_Helper[0] = Abitbuffer[7];
                    Abitbuffer = Abitbuffer << 1;
                    de[0] = Abitbuffer.to_ulong();
                    if(de[0] == 0x00)
                    {
                    Fbitbuffer[7] = 1;
                    Fbitbuffer[6] = 0;
                    Fbitbuffer[5] = 0;
                    Fbitbuffer[4] = Carry_Helper[0];
                    }
                    if(de[0] != 0x00)
                    {
                    Fbitbuffer[7] = 0;
                    Fbitbuffer[6] = 0;
                    Fbitbuffer[5] = 0;
                    Fbitbuffer[4] = Carry_Helper[0];
                    }
                    af[1] = Fbitbuffer.to_ulong();
                    pc += 2;
                    cycles += 8;
                break;

                case 0x23:
                    Abitbuffer = de[1];
                    Fbitbuffer = af[1];
                    Carry_Helper[0] = Abitbuffer[7];
                    Abitbuffer = Abitbuffer << 1;
                    de[1] = Abitbuffer.to_ulong();
                    if(de[1] == 0x00)
                    {
                    Fbitbuffer[7] = 1;
                    Fbitbuffer[6] = 0;
                    Fbitbuffer[5] = 0;
                    Fbitbuffer[4] = Carry_Helper[0];
                    }
                    if(de[1] != 0x00)
                    {
                    Fbitbuffer[7] = 0;
                    Fbitbuffer[6] = 0;
                    Fbitbuffer[5] = 0;
                    Fbitbuffer[4] = Carry_Helper[0];
                    }
                    af[1] = Fbitbuffer.to_ulong();
                    pc += 2;
                    cycles += 8;
                break;

                case 0x24:
                    Abitbuffer = hl[0];
                    Fbitbuffer = af[1];
                    Carry_Helper[0] = Abitbuffer[7];
                    Abitbuffer = Abitbuffer << 1;
                    hl[0] = Abitbuffer.to_ulong();
                    if(hl[0] == 0x00)
                    {
                    Fbitbuffer[7] = 1;
                    Fbitbuffer[6] = 0;
                    Fbitbuffer[5] = 0;
                    Fbitbuffer[4] = Carry_Helper[0];
                    }
                    if(hl[0] != 0x00)
                    {
                    Fbitbuffer[7] = 0;
                    Fbitbuffer[6] = 0;
                    Fbitbuffer[5] = 0;
                    Fbitbuffer[4] = Carry_Helper[0];
                    }
                    af[1] = Fbitbuffer.to_ulong();
                    pc += 2;
                    cycles += 8;
                break;

                case 0x25:
                    Abitbuffer = hl[1];
                    Fbitbuffer = af[1];
                    Carry_Helper[0] = Abitbuffer[7];
                    Abitbuffer = Abitbuffer << 1;
                    hl[1] = Abitbuffer.to_ulong();
                    if(hl[1] == 0x00)
                    {
                    Fbitbuffer[7] = 1;
                    Fbitbuffer[6] = 0;
                    Fbitbuffer[5] = 0;
                    Fbitbuffer[4] = Carry_Helper[0];
                    }
                    if(hl[1] != 0x00)
                    {
                    Fbitbuffer[7] = 0;
                    Fbitbuffer[6] = 0;
                    Fbitbuffer[5] = 0;
                    Fbitbuffer[4] = Carry_Helper[0];
                    }
                    af[1] = Fbitbuffer.to_ulong();
                    pc += 2;
                    cycles += 8;
                break;

                case 0x26:
                    hlbuffer = hl[0] << 8 | hl[1];
                    Abitbuffer = memory[hlbuffer];
                    Fbitbuffer = af[1];
                    Carry_Helper[0] = Abitbuffer[7];
                    Abitbuffer = Abitbuffer << 1;
                    memory[hlbuffer] = Abitbuffer.to_ulong();
                    if(memory[hlbuffer] == 0x00)
                    {
                    Fbitbuffer[7] = 1;
                    Fbitbuffer[6] = 0;
                    Fbitbuffer[5] = 0;
                    Fbitbuffer[4] = Carry_Helper[0];
                    }
                    if(memory[hlbuffer] != 0x00)
                    {
                    Fbitbuffer[7] = 0;
                    Fbitbuffer[6] = 0;
                    Fbitbuffer[5] = 0;
                    Fbitbuffer[4] = Carry_Helper[0];
                    }
                    af[1] = Fbitbuffer.to_ulong();
                    pc += 2;
                    cycles += 8;
                break;

                case 0x27:
                    Abitbuffer = af[0];
                    Fbitbuffer = af[1];
                    Carry_Helper[0] = Abitbuffer[7];
                    Abitbuffer = Abitbuffer << 1;
                    af[0] = Abitbuffer.to_ulong();
                    if(af[0] == 0x00)
                    {
                    Fbitbuffer[7] = 1;
                    Fbitbuffer[6] = 0;
                    Fbitbuffer[5] = 0;
                    Fbitbuffer[4] = Carry_Helper[0];
                    }
                    if(af[0] != 0x00)
                    {
                    Fbitbuffer[7] = 0;
                    Fbitbuffer[6] = 0;
                    Fbitbuffer[5] = 0;
                    Fbitbuffer[4] = Carry_Helper[0];
                    }
                    af[1] = Fbitbuffer.to_ulong();
                    pc += 2;
                    cycles += 8;
                break;

                case 0x28: // Flags Need Fixed
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
                        Fbitbuffer[7] = 0;
                        Fbitbuffer[6] = 0;
                        Fbitbuffer[5] = 0;
                        Fbitbuffer[4] = Carry_Helper[0];
                    }
                    af[1] = Fbitbuffer.to_ulong();
                    pc += 2;
                    cycles += 8;
                break;

                case 0x29: // Flags Need Fixed
                    Bbitbuffer = bc[1];
                    Fbitbuffer = af[1];
                    MSB_Helper[0] = Bbitbuffer[7];
                    Carry_Helper[0] = Bbitbuffer[0];
                    Bbitbuffer = Bbitbuffer >> 1;
                    Bbitbuffer[7] = MSB_Helper[0];
                    bc[1] = Bbitbuffer.to_ulong();
                    if(bc[1] == 0x00)
                    {
                        Fbitbuffer[7] = 1;
                        Fbitbuffer[6] = 0;
                        Fbitbuffer[5] = 0;
                        Fbitbuffer[4] = Carry_Helper[0];
                    }
                    if(bc[1] != 0x00)
                    {
                        Fbitbuffer[7] = 0;
                        Fbitbuffer[6] = 0;
                        Fbitbuffer[5] = 0;
                        Fbitbuffer[4] = Carry_Helper[0];
                    }
                    af[1] = Fbitbuffer.to_ulong();
                    pc += 2;
                    cycles += 8;
                break;

                case 0x2A: // Flags Need Fixed
                    Bbitbuffer = de[0];
                    Fbitbuffer = af[1];
                    MSB_Helper[0] = Bbitbuffer[7];
                    Carry_Helper[0] = Bbitbuffer[0];
                    Bbitbuffer = Bbitbuffer >> 1;
                    Bbitbuffer[7] = MSB_Helper[0];
                    de[0] = Bbitbuffer.to_ulong();
                    if(de[0] == 0x00)
                    {
                        Fbitbuffer[7] = 1;
                        Fbitbuffer[6] = 0;
                        Fbitbuffer[5] = 0;
                        Fbitbuffer[4] = Carry_Helper[0];
                    }
                    if(de[0] != 0x00)
                    {
                        Fbitbuffer[7] = 0;
                        Fbitbuffer[6] = 0;
                        Fbitbuffer[5] = 0;
                        Fbitbuffer[4] = Carry_Helper[0];
                    }
                    af[1] = Fbitbuffer.to_ulong();
                    pc += 2;
                    cycles += 8;
                break;

                case 0x2B: // Flags Need Fixed
                    Bbitbuffer = de[1];
                    Fbitbuffer = af[1];
                    MSB_Helper[0] = Bbitbuffer[7];
                    Carry_Helper[0] = Bbitbuffer[0];
                    Bbitbuffer = Bbitbuffer >> 1;
                    Bbitbuffer[7] = MSB_Helper[0];
                    de[1] = Bbitbuffer.to_ulong();
                    if(de[1] == 0x00)
                    {
                        Fbitbuffer[7] = 1;
                        Fbitbuffer[6] = 0;
                        Fbitbuffer[5] = 0;
                        Fbitbuffer[4] = Carry_Helper[0];
                    }
                    if(de[1] != 0x00)
                    {
                        Fbitbuffer[7] = 0;
                        Fbitbuffer[6] = 0;
                        Fbitbuffer[5] = 0;
                        Fbitbuffer[4] = Carry_Helper[0];
                    }
                    af[1] = Fbitbuffer.to_ulong();
                    pc += 2;
                    cycles += 8;
                break;

                case 0x2C: // Flags Need Fixed
                    Bbitbuffer = hl[0];
                    Fbitbuffer = af[1];
                    MSB_Helper[0] = Bbitbuffer[7];
                    Carry_Helper[0] = Bbitbuffer[0];
                    Bbitbuffer = Bbitbuffer >> 1;
                    Bbitbuffer[7] = MSB_Helper[0];
                    hl[0] = Bbitbuffer.to_ulong();
                    if(hl[0] == 0x00)
                    {
                        Fbitbuffer[7] = 1;
                        Fbitbuffer[6] = 0;
                        Fbitbuffer[5] = 0;
                        Fbitbuffer[4] = Carry_Helper[0];
                    }
                    if(hl[0] != 0x00)
                    {
                        Fbitbuffer[7] = 0;
                        Fbitbuffer[6] = 0;
                        Fbitbuffer[5] = 0;
                        Fbitbuffer[4] = Carry_Helper[0];
                    }
                    af[1] = Fbitbuffer.to_ulong();
                    pc += 2;
                    cycles += 8;
                break;

                case 0x2D: // Flags Need Fixed
                    Bbitbuffer = hl[1];
                    Fbitbuffer = af[1];
                    MSB_Helper[0] = Bbitbuffer[7];
                    Carry_Helper[0] = Bbitbuffer[0];
                    Bbitbuffer = Bbitbuffer >> 1;
                    Bbitbuffer[7] = MSB_Helper[0];
                    hl[1] = Bbitbuffer.to_ulong();
                    if(hl[1] == 0x00)
                    {
                        Fbitbuffer[7] = 1;
                        Fbitbuffer[6] = 0;
                        Fbitbuffer[5] = 0;
                        Fbitbuffer[4] = Carry_Helper[0];
                    }
                    if(hl[1] != 0x00)
                    {
                        Fbitbuffer[7] = 0;
                        Fbitbuffer[6] = 0;
                        Fbitbuffer[5] = 0;
                        Fbitbuffer[4] = Carry_Helper[0];
                    }
                    af[1] = Fbitbuffer.to_ulong();
                    pc += 2;
                    cycles += 8;
                break;

                case 0x2E: // Flags Need Fixed
                    hlbuffer = hl[0] << 8 | hl[1];
                    Bbitbuffer = memory[hlbuffer];
                    Fbitbuffer = af[1];
                    MSB_Helper[0] = Bbitbuffer[7];
                    Carry_Helper[0] = Bbitbuffer[0];
                    Bbitbuffer = Bbitbuffer >> 1;
                    Bbitbuffer[7] = MSB_Helper[0];
                    memory[hlbuffer] = Bbitbuffer.to_ulong();
                    if(memory[hlbuffer] == 0x00)
                    {
                        Fbitbuffer[7] = 1;
                        Fbitbuffer[6] = 0;
                        Fbitbuffer[5] = 0;
                        Fbitbuffer[4] = Carry_Helper[0];
                    }
                    if(memory[hlbuffer] != 0x00)
                    {
                        Fbitbuffer[7] = 0;
                        Fbitbuffer[6] = 0;
                        Fbitbuffer[5] = 0;
                        Fbitbuffer[4] = Carry_Helper[0];
                    }
                    af[1] = Fbitbuffer.to_ulong();
                    pc += 2;
                    cycles += 8;
                break;

                case 0x2F: // Flags Need Fixed
                    Bbitbuffer = af[0];
                    Fbitbuffer = af[1];
                    MSB_Helper[0] = Bbitbuffer[7];
                    Carry_Helper[0] = Bbitbuffer[0];
                    Bbitbuffer = Bbitbuffer >> 1;
                    Bbitbuffer[7] = MSB_Helper[0];
                    af[0] = Bbitbuffer.to_ulong();
                    if(af[0] == 0x00)
                    {
                        Fbitbuffer[7] = 1;
                        Fbitbuffer[6] = 0;
                        Fbitbuffer[5] = 0;
                        Fbitbuffer[4] = Carry_Helper[0];
                    }
                    if(af[0] != 0x00)
                    {
                        Fbitbuffer[7] = 0;
                        Fbitbuffer[6] = 0;
                        Fbitbuffer[5] = 0;
                        Fbitbuffer[4] = Carry_Helper[0];
                    }
                    af[1] = Fbitbuffer.to_ulong();
                    pc += 2;
                    cycles += 8;
                break;

                case 0x30: // Flags Need Fixed
                    bc[0] = ( (bc[0] & 0x0F) << 4 | (bc[0] & 0xF0) >> 4 );
                    if (bc[0] == 0x00)
                    {
                        af[1] = 0x80;
                    }
                    if (bc[0] != 0x00)
                    {
                        af[1] = 0x00;
                    }
                    cycles += 8;
                    pc += 2;
                break;

                case 0x31: // Flags Need Fixed
                    bc[1] = ( (bc[1] & 0x0F) << 4 | (bc[1] & 0xF0) >> 4 );
                    if (bc[1] == 0x00)
                    {
                        af[1] = 0x80;
                    }
                    if (bc[1] != 0x00)
                    {
                        af[1] = 0x00;
                    }
                    cycles += 8;
                    pc += 2;
                break;

                case 0x32: // Flags Need Fixed
                    de[0] = ( (de[0] & 0x0F) << 4 | (de[0] & 0xF0) >> 4 );
                    if (de[0] == 0x00)
                    {
                        af[1] = 0x80;
                    }
                    if (de[0] != 0x00)
                    {
                        af[1] = 0x00;
                    }
                    cycles += 8;
                    pc += 2;
                break;

                case 0x33: // Flags Need Fixed
                    de[1] = ( (de[1] & 0x0F) << 4 | (de[1] & 0xF0) >> 4 );
                    if (de[1] == 0x00)
                    {
                        af[1] = 0x80;
                    }
                    if (de[1] != 0x00)
                    {
                        af[1] = 0x00;
                    }
                    cycles += 8;
                    pc += 2;
                break;

                case 0x34: // Flags Need Fixed
                    hl[0] = ( (hl[0] & 0x0F) << 4 | (hl[0] & 0xF0) >> 4 );
                    if (hl[0] == 0x00)
                    {
                        af[1] = 0x80;
                    }
                    if (hl[0] != 0x00)
                    {
                        af[1] = 0x00;
                    }
                    cycles += 8;
                    pc += 2;
                break;

                case 0x35: // Flags Need Fixed
                    hl[1] = ( (hl[1] & 0x0F) << 4 | (hl[1] & 0xF0) >> 4 );
                    if (hl[1] == 0x00)
                    {
                        af[1] = 0x80;
                    }
                    if (hl[1] != 0x00)
                    {
                        af[1] = 0x00;
                    }
                    cycles += 8;
                    pc += 2;
                break;

                case 0x36: // Flags Need Fixed
                    hlbuffer = hl[0] << 8 | hl[1];
                    memory[hlbuffer] = ( (memory[hlbuffer] & 0x0F) << 4 | (memory[hlbuffer] & 0xF0) >> 4 );
                    if (memory[hlbuffer] == 0x00)
                    {
                        af[1] = 0x80;
                    }
                    if (memory[hlbuffer] != 0x00)
                    {
                        af[1] = 0x00;
                    }
                    cycles += 8;
                    pc += 2;
                break;

                case 0x37: // Flags Need Fixed
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
                break; // Ends 0xCB37 case

                case 0x38: // Flags Need Fixed
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
                        Fbitbuffer[7] = 0;
                        Fbitbuffer[6] = 0;
                        Fbitbuffer[5] = 0;
                        Fbitbuffer[4] = Carry_Helper[0];
                    }
                    af[1] = Fbitbuffer.to_ulong();
                    pc += 2;
                    cycles += 8;
                break;

                case 0x39: // Flags Need Fixed
                    Bbitbuffer = bc[1];
                    Fbitbuffer = af[1];
                    MSB_Helper[0] = Bbitbuffer[7];
                    Carry_Helper[0] = Bbitbuffer[0];
                    Bbitbuffer = Bbitbuffer >> 1;
                    MSB_Helper[0] = 0;
                    Bbitbuffer[7] = MSB_Helper[0];
                    bc[1] = Bbitbuffer.to_ulong();
                    if(bc[1] == 0x00)
                    {
                        Fbitbuffer[7] = 1;
                        Fbitbuffer[6] = 0;
                        Fbitbuffer[5] = 0;
                        Fbitbuffer[4] = Carry_Helper[0];
                    }
                    if(bc[1] != 0x00)
                    {
                        Fbitbuffer[7] = 0;
                        Fbitbuffer[6] = 0;
                        Fbitbuffer[5] = 0;
                        Fbitbuffer[4] = Carry_Helper[0];
                    }
                    af[1] = Fbitbuffer.to_ulong();
                    pc += 2;
                    cycles += 8;
                break;

                case 0x3A: // Flags Need Fixed
                    Bbitbuffer = de[0];
                    Fbitbuffer = af[1];
                    MSB_Helper[0] = Bbitbuffer[7];
                    Carry_Helper[0] = Bbitbuffer[0];
                    Bbitbuffer = Bbitbuffer >> 1;
                    MSB_Helper[0] = 0;
                    Bbitbuffer[7] = MSB_Helper[0];
                    de[0] = Bbitbuffer.to_ulong();
                    if(de[0] == 0x00)
                    {
                        Fbitbuffer[7] = 1;
                        Fbitbuffer[6] = 0;
                        Fbitbuffer[5] = 0;
                        Fbitbuffer[4] = Carry_Helper[0];
                    }
                    if(de[0] != 0x00)
                    {
                        Fbitbuffer[7] = 0;
                        Fbitbuffer[6] = 0;
                        Fbitbuffer[5] = 0;
                        Fbitbuffer[4] = Carry_Helper[0];
                    }
                    af[1] = Fbitbuffer.to_ulong();
                    pc += 2;
                    cycles += 8;
                break;

                case 0x3B: // Flags Need Fixed
                    Bbitbuffer = de[1];
                    Fbitbuffer = af[1];
                    MSB_Helper[0] = Bbitbuffer[7];
                    Carry_Helper[0] = Bbitbuffer[0];
                    Bbitbuffer = Bbitbuffer >> 1;
                    MSB_Helper[0] = 0;
                    Bbitbuffer[7] = MSB_Helper[0];
                    de[1] = Bbitbuffer.to_ulong();
                    if(de[1] == 0x00)
                    {
                        Fbitbuffer[7] = 1;
                        Fbitbuffer[6] = 0;
                        Fbitbuffer[5] = 0;
                        Fbitbuffer[4] = Carry_Helper[0];
                    }
                    if(de[1] != 0x00)
                    {
                        Fbitbuffer[7] = 0;
                        Fbitbuffer[6] = 0;
                        Fbitbuffer[5] = 0;
                        Fbitbuffer[4] = Carry_Helper[0];
                    }
                    af[1] = Fbitbuffer.to_ulong();
                    pc += 2;
                    cycles += 8;
                break;

                case 0x3C: // Flags Need Fixed
                    Bbitbuffer = hl[0];
                    Fbitbuffer = af[1];
                    MSB_Helper[0] = Bbitbuffer[7];
                    Carry_Helper[0] = Bbitbuffer[0];
                    Bbitbuffer = Bbitbuffer >> 1;
                    MSB_Helper[0] = 0;
                    Bbitbuffer[7] = MSB_Helper[0];
                    hl[0] = Bbitbuffer.to_ulong();
                    if(hl[0] == 0x00)
                    {
                        Fbitbuffer[7] = 1;
                        Fbitbuffer[6] = 0;
                        Fbitbuffer[5] = 0;
                        Fbitbuffer[4] = Carry_Helper[0];
                    }
                    if(hl[0] != 0x00)
                    {
                        Fbitbuffer[7] = 0;
                        Fbitbuffer[6] = 0;
                        Fbitbuffer[5] = 0;
                        Fbitbuffer[4] = Carry_Helper[0];
                    }
                    af[1] = Fbitbuffer.to_ulong();
                    pc += 2;
                    cycles += 8;
                break;

                case 0x3D: // Flags Need Fixed
                    Bbitbuffer = hl[1];
                    Fbitbuffer = af[1];
                    MSB_Helper[0] = Bbitbuffer[7];
                    Carry_Helper[0] = Bbitbuffer[0];
                    Bbitbuffer = Bbitbuffer >> 1;
                    MSB_Helper[0] = 0;
                    Bbitbuffer[7] = MSB_Helper[0];
                    hl[1] = Bbitbuffer.to_ulong();
                    if(hl[1] == 0x00)
                    {
                        Fbitbuffer[7] = 1;
                        Fbitbuffer[6] = 0;
                        Fbitbuffer[5] = 0;
                        Fbitbuffer[4] = Carry_Helper[0];
                    }
                    if(hl[1] != 0x00)
                    {
                        Fbitbuffer[6] = 0;
                        Fbitbuffer[5] = 0;
                        Fbitbuffer[4] = Carry_Helper[0];
                    }
                    af[1] = Fbitbuffer.to_ulong();
                    pc += 2;
                    cycles += 8;
                break;

                case 0x3E: // Flags Need Fixed
                    hlbuffer = hl[0] << 8 | hl[1];
                    Bbitbuffer = memory[hlbuffer];
                    Fbitbuffer = af[1];
                    MSB_Helper[0] = Bbitbuffer[7];
                    Carry_Helper[0] = Bbitbuffer[0];
                    Bbitbuffer = Bbitbuffer >> 1;
                    MSB_Helper[0] = 0;
                    Bbitbuffer[7] = MSB_Helper[0];
                    memory[hlbuffer] = Bbitbuffer.to_ulong();
                    if(memory[hlbuffer] == 0x00)
                    {
                        Fbitbuffer[7] = 1;
                        Fbitbuffer[6] = 0;
                        Fbitbuffer[5] = 0;
                        Fbitbuffer[4] = Carry_Helper[0];
                    }
                    if(memory[hlbuffer] != 0x00)
                    {
                        Fbitbuffer[7] = 0;
                        Fbitbuffer[6] = 0;
                        Fbitbuffer[5] = 0;
                        Fbitbuffer[4] = Carry_Helper[0];
                    }
                    af[1] = Fbitbuffer.to_ulong();
                    pc += 2;
                    cycles += 8;
                break;

                case 0x3F: // Flags Need Fixed
                    Bbitbuffer = af[0];
                    Fbitbuffer = af[1];
                    MSB_Helper[0] = Bbitbuffer[7];
                    Carry_Helper[0] = Bbitbuffer[0];
                    Bbitbuffer = Bbitbuffer >> 1;
                    MSB_Helper[0] = 0;
                    Bbitbuffer[7] = MSB_Helper[0];
                    af[0] = Bbitbuffer.to_ulong();
                    if(af[0] == 0x00)
                    {
                        Fbitbuffer[7] = 1;
                        Fbitbuffer[6] = 0;
                        Fbitbuffer[5] = 0;
                        Fbitbuffer[4] = Carry_Helper[0];
                    }
                    if(af[0] != 0x00)
                    {
                        Fbitbuffer[6] = 0;
                        Fbitbuffer[5] = 0;
                        Fbitbuffer[4] = Carry_Helper[0];
                    }
                    af[1] = Fbitbuffer.to_ulong();
                    pc += 2;
                    cycles += 8;
                break;

                case 0x40: // Flags Need Fixed
                    Bbitbuffer = bc[0];
                    Fbitbuffer = af[1];
                    if(Bbitbuffer[0] == 0)
                    {
                        Fbitbuffer[7] = 1;
                        Fbitbuffer[6] = 0;
                        Fbitbuffer[5] = 1;
                    }
                    if(Bbitbuffer[0] == 1)
                    {
                        Fbitbuffer[7] = 0;
                        Fbitbuffer[6] = 0;
                        Fbitbuffer[5] = 1;
                    }
                    af[1] = Fbitbuffer.to_ulong();
                    pc += 2;
                    cycles += 8;
                break;

                case 0x41: // Flags Need Fixed
                    Cbitbuffer = bc[1];
                    Fbitbuffer = af[1];
                    if(Cbitbuffer[1] == 0)
                    {
                        Fbitbuffer[7] = 1;
                        Fbitbuffer[6] = 0;
                        Fbitbuffer[5] = 1;
                    }
                    if(Cbitbuffer[1] == 1)
                    {
                        Fbitbuffer[7] = 0;
                        Fbitbuffer[6] = 0;
                        Fbitbuffer[5] = 1;
                    }
                    af[1] = Fbitbuffer.to_ulong();
                    pc += 2;
                    cycles += 8;
                break;

                case 0x42: // Flags Need Fixed
                    Bbitbuffer = de[0];
                    Fbitbuffer = af[1];
                    if(Bbitbuffer[0] == 0)
                    {
                        Fbitbuffer[7] = 1;
                        Fbitbuffer[6] = 0;
                        Fbitbuffer[5] = 1;
                    }
                    if(Bbitbuffer[0] == 1)
                    {
                        Fbitbuffer[7] = 0;
                        Fbitbuffer[6] = 0;
                        Fbitbuffer[5] = 1;
                    }
                    af[1] = Fbitbuffer.to_ulong();
                    pc += 2;
                    cycles += 8;
                break;

                case 0x43: // Flags Need Fixed
                    Bbitbuffer = de[1];
                    Fbitbuffer = af[1];
                    if(Bbitbuffer[0] == 0)
                    {
                        Fbitbuffer[7] = 1;
                        Fbitbuffer[6] = 0;
                        Fbitbuffer[5] = 1;
                    }
                    if(Bbitbuffer[0] == 1)
                    {
                        Fbitbuffer[7] = 0;
                        Fbitbuffer[6] = 0;
                        Fbitbuffer[5] = 1;
                    }
                    af[1] = Fbitbuffer.to_ulong();
                    pc += 2;
                    cycles += 8;
                break;

                case 0x44: // Flags Need Fixed
                    Bbitbuffer = hl[0];
                    Fbitbuffer = af[1];
                    if(Bbitbuffer[0] == 0)
                    {
                        Fbitbuffer[7] = 1;
                        Fbitbuffer[6] = 0;
                        Fbitbuffer[5] = 1;
                    }
                    if(Bbitbuffer[0] == 1)
                    {
                        Fbitbuffer[7] = 0;
                        Fbitbuffer[6] = 0;
                        Fbitbuffer[5] = 1;
                    }
                    af[1] = Fbitbuffer.to_ulong();
                    pc += 2;
                    cycles += 8;
                break;

                case 0x45: // Flags Need Fixed
                    Bbitbuffer = hl[1];
                    Fbitbuffer = af[1];
                    if(Bbitbuffer[0] == 0)
                    {
                        Fbitbuffer[7] = 1;
                        Fbitbuffer[6] = 0;
                        Fbitbuffer[5] = 1;
                    }
                    if(Bbitbuffer[0] == 1)
                    {
                        Fbitbuffer[7] = 0;
                        Fbitbuffer[6] = 0;
                        Fbitbuffer[5] = 1;
                    }
                    af[1] = Fbitbuffer.to_ulong();
                    pc += 2;
                    cycles += 8;
                break;

                case 0x46: // Flags Need Fixed
                    hlbuffer = hl[0] << 8 | hl[1];
                    Bbitbuffer = memory[hlbuffer];
                    Fbitbuffer = af[1];
                    if(Bbitbuffer[0] == 0)
                    {
                        Fbitbuffer[7] = 1;
                        Fbitbuffer[6] = 0;
                        Fbitbuffer[5] = 1;
                    }
                    if(Bbitbuffer[0] == 1)
                    {
                        Fbitbuffer[7] = 0;
                        Fbitbuffer[6] = 0;
                        Fbitbuffer[5] = 1;
                    }
                    af[1] = Fbitbuffer.to_ulong();
                    pc += 2;
                    cycles += 16;
                break;

                case 0x47: // Flags Need Fixed
                    Abitbuffer = af[0];
                    Fbitbuffer = af[1];
                    if(Abitbuffer[0] == 0)
                    {
                        Fbitbuffer[7] = 1;
                        Fbitbuffer[6] = 0;
                        Fbitbuffer[5] = 1;
                    }
                    if(Abitbuffer[0] == 1)
                    {
                        Fbitbuffer[7] = 0;
                        Fbitbuffer[6] = 0;
                        Fbitbuffer[5] = 1;
                    }
                    af[1] = Fbitbuffer.to_ulong();
                    pc += 2;
                    cycles += 8;
                break;

                case 0x48: // Flags Need Fixed
                    Bbitbuffer = bc[0];
                    Fbitbuffer = af[1];
                    if(Bbitbuffer[1] == 0)
                    {
                        Fbitbuffer[7] = 1;
                        Fbitbuffer[6] = 0;
                        Fbitbuffer[5] = 1;
                    }
                    if(Bbitbuffer[1] == 1)
                    {
                        Fbitbuffer[7] = 0;
                        Fbitbuffer[6] = 0;
                        Fbitbuffer[5] = 1;
                    }
                    af[1] = Fbitbuffer.to_ulong();
                    pc += 2;
                    cycles += 8;
                break;

                case 0x49: // Flags Need Fixed
                    Bbitbuffer = bc[1];
                    Fbitbuffer = af[1];
                    if(Bbitbuffer[1] == 0)
                    {
                        Fbitbuffer[7] = 1;
                        Fbitbuffer[6] = 0;
                        Fbitbuffer[5] = 1;
                    }
                    if(Bbitbuffer[1] == 1)
                    {
                        Fbitbuffer[7] = 0;
                        Fbitbuffer[6] = 0;
                        Fbitbuffer[5] = 1;
                    }
                    af[1] = Fbitbuffer.to_ulong();
                    pc += 2;
                    cycles += 8;
                break;

                case 0x4A: // Flags Need Fixed
                    Bbitbuffer = de[0];
                    Fbitbuffer = af[1];
                    if(Bbitbuffer[1] == 0)
                    {
                        Fbitbuffer[7] = 1;
                        Fbitbuffer[6] = 0;
                        Fbitbuffer[5] = 1;
                    }
                    if(Bbitbuffer[1] == 1)
                    {
                        Fbitbuffer[7] = 0;
                        Fbitbuffer[6] = 0;
                        Fbitbuffer[5] = 1;
                    }
                    af[1] = Fbitbuffer.to_ulong();
                    pc += 2;
                    cycles += 8;
                break;

                case 0x4B: // Flags Need Fixed
                    Bbitbuffer = de[1];
                    Fbitbuffer = af[1];
                    if(Bbitbuffer[1] == 0)
                    {
                        Fbitbuffer[7] = 1;
                        Fbitbuffer[6] = 0;
                        Fbitbuffer[5] = 1;
                    }
                    if(Bbitbuffer[1] == 1)
                    {
                        Fbitbuffer[7] = 0;
                        Fbitbuffer[6] = 0;
                        Fbitbuffer[5] = 1;
                    }
                    af[1] = Fbitbuffer.to_ulong();
                    pc += 2;
                    cycles += 8;
                break;

                case 0x4C: // Flags Need Fixed
                    Bbitbuffer = hl[0];
                    Fbitbuffer = af[1];
                    if(Bbitbuffer[1] == 0)
                    {
                        Fbitbuffer[7] = 1;
                        Fbitbuffer[6] = 0;
                        Fbitbuffer[5] = 1;
                    }
                    if(Bbitbuffer[1] == 1)
                    {
                        Fbitbuffer[7] = 0;
                        Fbitbuffer[6] = 0;
                        Fbitbuffer[5] = 1;
                    }
                    af[1] = Fbitbuffer.to_ulong();
                    pc += 2;
                    cycles += 8;
                break;

                case 0x4D: // Flags Need Fixed
                    Bbitbuffer = hl[1];
                    Fbitbuffer = af[1];
                    if(Bbitbuffer[1] == 0)
                    {
                        Fbitbuffer[7] = 1;
                        Fbitbuffer[6] = 0;
                        Fbitbuffer[5] = 1;
                    }
                    if(Bbitbuffer[1] == 1)
                    {
                        Fbitbuffer[7] = 0;
                        Fbitbuffer[6] = 0;
                        Fbitbuffer[5] = 1;
                    }
                    af[1] = Fbitbuffer.to_ulong();
                    pc += 2;
                    cycles += 8;
                break;

                case 0x4E: // Flags Need Fixed
                    hlbuffer = hl[0] << 8 | hl[1];
                    Bbitbuffer = memory[hlbuffer];
                    Fbitbuffer = af[1];
                    if(Bbitbuffer[1] == 0)
                    {
                        Fbitbuffer[7] = 1;
                        Fbitbuffer[6] = 0;
                        Fbitbuffer[5] = 1;
                    }
                    if(Bbitbuffer[1] == 1)
                    {
                        Fbitbuffer[7] = 0;
                        Fbitbuffer[6] = 0;
                        Fbitbuffer[5] = 1;
                    }
                    af[1] = Fbitbuffer.to_ulong();
                    pc += 2;
                    cycles += 16;
                break;

                case 0x4F: // Flags Need Fixed
                    Bbitbuffer = af[0];
                    Fbitbuffer = af[1];
                    if(Bbitbuffer[1] == 0)
                    {
                        Fbitbuffer[7] = 1;
                        Fbitbuffer[6] = 0;
                        Fbitbuffer[5] = 1;
                    }
                    if(Bbitbuffer[1] == 1)
                    {
                        Fbitbuffer[7] = 0;
                        Fbitbuffer[6] = 0;
                        Fbitbuffer[5] = 1;
                    }
                    af[1] = Fbitbuffer.to_ulong();
                    pc += 2;
                    cycles += 8;
                break;

                case 0x50: // Flags Need Fixed
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

                case 0x51: // Flags Need Fixed
                    Bbitbuffer = bc[1];
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

                case 0x52: // Flags Need Fixed
                    Bbitbuffer = de[0];
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

                case 0x53: // Flags Need Fixed
                    Bbitbuffer = de[1];
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

                case 0x54: // Flags Need Fixed
                    Bbitbuffer = hl[0];
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

                case 0x55: // Flags Need Fixed
                    Bbitbuffer = hl[1];
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

                case 0x56: // Flags Need Fixed
                    hlbuffer = hl[0] << 8 | hl[1];
                    Bbitbuffer = memory[hlbuffer];
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

                case 0x57: // Flags Need Fixed
                    Abitbuffer = af[0];
                    Fbitbuffer = af[1];
                    if(Abitbuffer[2] == 0)
                    {
                        Fbitbuffer[7] = 1;
                        Fbitbuffer[6] = 0;
                        Fbitbuffer[5] = 1;
                    }
                    if(Abitbuffer[2] == 1)
                    {
                        Fbitbuffer[7] = 0;
                        Fbitbuffer[6] = 0;
                        Fbitbuffer[5] = 1;
                    }
                    af[1] = Fbitbuffer.to_ulong();
                    pc += 2;
                    cycles += 8;
                break;

                case 0x58: // Flags Need Fixed
                    Bbitbuffer = bc[0];
                    Fbitbuffer = af[1];
                    if(Bbitbuffer[3] == 0)
                    {
                        Fbitbuffer[7] = 1;
                        Fbitbuffer[6] = 0;
                        Fbitbuffer[5] = 1;
                    }
                    if(Bbitbuffer[3] == 1)
                    {
                        Fbitbuffer[7] = 0;
                        Fbitbuffer[6] = 0;
                        Fbitbuffer[5] = 1;
                    }
                    af[1] = Fbitbuffer.to_ulong();
                    pc += 2;
                    cycles += 8;
                break;

                case 0x59: // Flags Need Fixed
                    Bbitbuffer = bc[1];
                    Fbitbuffer = af[1];
                    if(Bbitbuffer[3] == 0)
                    {
                        Fbitbuffer[7] = 1;
                        Fbitbuffer[6] = 0;
                        Fbitbuffer[5] = 1;
                    }
                    if(Bbitbuffer[3] == 1)
                    {
                        Fbitbuffer[7] = 0;
                        Fbitbuffer[6] = 0;
                        Fbitbuffer[5] = 1;
                    }
                    af[1] = Fbitbuffer.to_ulong();
                    pc += 2;
                    cycles += 8;
                break;

                case 0x5A: // Flags Need Fixed
                    Bbitbuffer = de[0];
                    Fbitbuffer = af[1];
                    if(Bbitbuffer[3] == 0)
                    {
                        Fbitbuffer[7] = 1;
                        Fbitbuffer[6] = 0;
                        Fbitbuffer[5] = 1;
                    }
                    if(Bbitbuffer[3] == 1)
                    {
                        Fbitbuffer[7] = 0;
                        Fbitbuffer[6] = 0;
                        Fbitbuffer[5] = 1;
                    }
                    af[1] = Fbitbuffer.to_ulong();
                    pc += 2;
                    cycles += 8;
                break;

                case 0x5B: // Flags Need Fixed
                    Bbitbuffer = de[1];
                    Fbitbuffer = af[1];
                    if(Bbitbuffer[3] == 0)
                    {
                        Fbitbuffer[7] = 1;
                        Fbitbuffer[6] = 0;
                        Fbitbuffer[5] = 1;
                    }
                    if(Bbitbuffer[3] == 1)
                    {
                        Fbitbuffer[7] = 0;
                        Fbitbuffer[6] = 0;
                        Fbitbuffer[5] = 1;
                    }
                    af[1] = Fbitbuffer.to_ulong();
                    pc += 2;
                    cycles += 8;
                break;

                case 0x5C: // Flags Need Fixed
                    Bbitbuffer = hl[0];
                    Fbitbuffer = af[1];
                    if(Bbitbuffer[3] == 0)
                    {
                        Fbitbuffer[7] = 1;
                        Fbitbuffer[6] = 0;
                        Fbitbuffer[5] = 1;
                    }
                    if(Bbitbuffer[3] == 1)
                    {
                        Fbitbuffer[7] = 0;
                        Fbitbuffer[6] = 0;
                        Fbitbuffer[5] = 1;
                    }
                    af[1] = Fbitbuffer.to_ulong();
                    pc += 2;
                    cycles += 8;
                break;

                case 0x5D: // Flags Need Fixed
                    Bbitbuffer = hl[1];
                    Fbitbuffer = af[1];
                    if(Bbitbuffer[3] == 0)
                    {
                        Fbitbuffer[7] = 1;
                        Fbitbuffer[6] = 0;
                        Fbitbuffer[5] = 1;
                    }
                    if(Bbitbuffer[3] == 1)
                    {
                        Fbitbuffer[7] = 0;
                        Fbitbuffer[6] = 0;
                        Fbitbuffer[5] = 1;
                    }
                    af[1] = Fbitbuffer.to_ulong();
                    pc += 2;
                    cycles += 8;
                break;

                case 0x5E: // Flags Need Fixed
                    hlbuffer = hl[0] << 8 | hl[1];
                    Bbitbuffer = memory[hlbuffer];
                    Fbitbuffer = af[1];
                    if(Bbitbuffer[3] == 0)
                    {
                        Fbitbuffer[7] = 1;
                        Fbitbuffer[6] = 0;
                        Fbitbuffer[5] = 1;
                    }
                    if(Bbitbuffer[3] == 1)
                    {
                        Fbitbuffer[7] = 0;
                        Fbitbuffer[6] = 0;
                        Fbitbuffer[5] = 1;
                    }
                    af[1] = Fbitbuffer.to_ulong();
                    pc += 2;
                    cycles += 8;
                break;

                case 0x5F: // Flags Need Fixed
                    Abitbuffer = af[0];
                    Fbitbuffer = af[1];
                    if(Abitbuffer[3] == 0)
                    {
                        Fbitbuffer[7] = 1;
                        Fbitbuffer[6] = 0;
                        Fbitbuffer[5] = 1;
                    }
                    if(Abitbuffer[3] == 1)
                    {
                        Fbitbuffer[7] = 0;
                        Fbitbuffer[6] = 0;
                        Fbitbuffer[5] = 1;
                    }
                    af[1] = Fbitbuffer.to_ulong();
                    pc += 2;
                    cycles += 8;
                break;

                case 0x60: // Flags Need Fixed
                    Bbitbuffer = bc[0];
                    Fbitbuffer = af[1];
                    if(Bbitbuffer[4] == 0)
                    {
                        Fbitbuffer[7] = 1;
                        Fbitbuffer[6] = 0;
                        Fbitbuffer[5] = 1;
                    }
                    if(Bbitbuffer[4] == 1)
                    {
                        Fbitbuffer[7] = 0;
                        Fbitbuffer[6] = 0;
                        Fbitbuffer[5] = 1;
                    }
                    af[1] = Fbitbuffer.to_ulong();
                    pc += 2;
                    cycles += 8;
                break;

                case 0x61: // Flags Need Fixed
                    Cbitbuffer = bc[1];
                    Fbitbuffer = af[1];
                    if(Cbitbuffer[4] == 0)
                    {
                        Fbitbuffer[7] = 1;
                        Fbitbuffer[6] = 0;
                        Fbitbuffer[5] = 1;
                    }
                    if(Cbitbuffer[4] == 1)
                    {
                        Fbitbuffer[7] = 0;
                        Fbitbuffer[6] = 0;
                        Fbitbuffer[5] = 1;
                    }
                    af[1] = Fbitbuffer.to_ulong();
                    pc += 2;
                    cycles += 8;
                break;

                case 0x62: // Flags Need Fixed
                    Bbitbuffer = de[0];
                    Fbitbuffer = af[1];
                    if(Bbitbuffer[4] == 0)
                    {
                        Fbitbuffer[7] = 1;
                        Fbitbuffer[6] = 0;
                        Fbitbuffer[5] = 1;
                    }
                    if(Bbitbuffer[4] == 1)
                    {
                        Fbitbuffer[7] = 0;
                        Fbitbuffer[6] = 0;
                        Fbitbuffer[5] = 1;
                    }
                    af[1] = Fbitbuffer.to_ulong();
                    pc += 2;
                    cycles += 8;
                break;

                case 0x63: // Flags Need Fixed
                    Bbitbuffer = de[1];
                    Fbitbuffer = af[1];
                    if(Bbitbuffer[4] == 0)
                    {
                        Fbitbuffer[7] = 1;
                        Fbitbuffer[6] = 0;
                        Fbitbuffer[5] = 1;
                    }
                    if(Bbitbuffer[4] == 1)
                    {
                        Fbitbuffer[7] = 0;
                        Fbitbuffer[6] = 0;
                        Fbitbuffer[5] = 1;
                    }
                    af[1] = Fbitbuffer.to_ulong();
                    pc += 2;
                    cycles += 8;
                break;

                case 0x64: // Flags Need Fixed
                    Bbitbuffer = hl[0];
                    Fbitbuffer = af[1];
                    if(Bbitbuffer[4] == 0)
                    {
                        Fbitbuffer[7] = 1;
                        Fbitbuffer[6] = 0;
                        Fbitbuffer[5] = 1;
                    }
                    if(Bbitbuffer[4] == 1)
                    {
                        Fbitbuffer[7] = 0;
                        Fbitbuffer[6] = 0;
                        Fbitbuffer[5] = 1;
                    }
                    af[1] = Fbitbuffer.to_ulong();
                    pc += 2;
                    cycles += 8;
                break;

                case 0x65: // Flags Need Fixed
                    Bbitbuffer = hl[1];
                    Fbitbuffer = af[1];
                    if(Bbitbuffer[4] == 0)
                    {
                        Fbitbuffer[7] = 1;
                        Fbitbuffer[6] = 0;
                        Fbitbuffer[5] = 1;
                    }
                    if(Bbitbuffer[4] == 1)
                    {
                        Fbitbuffer[7] = 0;
                        Fbitbuffer[6] = 0;
                        Fbitbuffer[5] = 1;
                    }
                    af[1] = Fbitbuffer.to_ulong();
                    pc += 2;
                    cycles += 8;
                break;

                case 0x66: // Flags Need Fixed
                    hlbuffer = hl[0] << 8 | hl[1];
                    Bbitbuffer = memory[hlbuffer];
                    Fbitbuffer = af[1];
                    if(Bbitbuffer[4] == 0)
                    {
                        Fbitbuffer[7] = 1;
                        Fbitbuffer[6] = 0;
                        Fbitbuffer[5] = 1;
                    }
                    if(Bbitbuffer[4] == 1)
                    {
                        Fbitbuffer[7] = 0;
                        Fbitbuffer[6] = 0;
                        Fbitbuffer[5] = 1;
                    }
                    af[1] = Fbitbuffer.to_ulong();
                    pc += 2;
                    cycles += 8;
                break;

                case 0x67: // Flags Need Fixed
                    Bbitbuffer = af[0];
                    Fbitbuffer = af[1];
                    if(Bbitbuffer[4] == 0)
                    {
                        Fbitbuffer[7] = 1;
                        Fbitbuffer[6] = 0;
                        Fbitbuffer[5] = 1;
                    }
                    if(Bbitbuffer[4] == 1)
                    {
                        Fbitbuffer[7] = 0;
                        Fbitbuffer[6] = 0;
                        Fbitbuffer[5] = 1;
                    }
                    af[1] = Fbitbuffer.to_ulong();
                    pc += 2;
                    cycles += 8;
                break;

                case 0x68: // Flags Need Fixed
                    Bbitbuffer = bc[0];
                    Fbitbuffer = af[1];
                    if(Bbitbuffer[5] == 0)
                    {
                        Fbitbuffer[7] = 1;
                        Fbitbuffer[6] = 0;
                        Fbitbuffer[5] = 1;
                    }
                    if(Bbitbuffer[5] == 1)
                    {
                        Fbitbuffer[7] = 0;
                        Fbitbuffer[6] = 0;
                        Fbitbuffer[5] = 1;
                    }
                    af[1] = Fbitbuffer.to_ulong();
                    pc += 2;
                    cycles += 8;
                break;

                case 0x69: // Flags Need Fixed
                    Cbitbuffer = bc[1];
                    Fbitbuffer = af[1];
                    if(Cbitbuffer[5] == 0)
                    {
                        Fbitbuffer[7] = 1;
                        Fbitbuffer[6] = 0;
                        Fbitbuffer[5] = 1;
                    }
                    if(Cbitbuffer[5] == 1)
                    {
                        Fbitbuffer[7] = 0;
                        Fbitbuffer[6] = 0;
                        Fbitbuffer[5] = 1;
                    }
                    af[1] = Fbitbuffer.to_ulong();
                    pc += 2;
                    cycles += 8;
                break;

                case 0x6A: // Flags Need Fixed
                    Bbitbuffer = de[0];
                    Fbitbuffer = af[1];
                    if(Bbitbuffer[5] == 0)
                    {
                        Fbitbuffer[7] = 1;
                        Fbitbuffer[6] = 0;
                        Fbitbuffer[5] = 1;
                    }
                    if(Bbitbuffer[5] == 1)
                    {
                        Fbitbuffer[7] = 0;
                        Fbitbuffer[6] = 0;
                        Fbitbuffer[5] = 1;
                    }
                    af[1] = Fbitbuffer.to_ulong();
                    pc += 2;
                    cycles += 8;
                break;

                case 0x6B: // Flags Need Fixed
                    Bbitbuffer = de[1];
                    Fbitbuffer = af[1];
                    if(Bbitbuffer[5] == 0)
                    {
                        Fbitbuffer[7] = 1;
                        Fbitbuffer[6] = 0;
                        Fbitbuffer[5] = 1;
                    }
                    if(Bbitbuffer[5] == 1)
                    {
                        Fbitbuffer[7] = 0;
                        Fbitbuffer[6] = 0;
                        Fbitbuffer[5] = 1;
                    }
                    af[1] = Fbitbuffer.to_ulong();
                    pc += 2;
                    cycles += 8;
                break;

                case 0x6C: // Flags Need Fixed
                    Bbitbuffer = hl[0];
                    Fbitbuffer = af[1];
                    if(Bbitbuffer[5] == 0)
                    {
                        Fbitbuffer[7] = 1;
                        Fbitbuffer[6] = 0;
                        Fbitbuffer[5] = 1;
                    }
                    if(Bbitbuffer[5] == 1)
                    {
                        Fbitbuffer[7] = 0;
                        Fbitbuffer[6] = 0;
                        Fbitbuffer[5] = 1;
                    }
                    af[1] = Fbitbuffer.to_ulong();
                    pc += 2;
                    cycles += 8;
                break;

                case 0x6D: // Flags Need Fixed
                    Bbitbuffer = hl[1];
                    Fbitbuffer = af[1];
                    if(Bbitbuffer[5] == 0)
                    {
                        Fbitbuffer[7] = 1;
                        Fbitbuffer[6] = 0;
                        Fbitbuffer[5] = 1;
                    }
                    if(Bbitbuffer[5] == 1)
                    {
                        Fbitbuffer[7] = 0;
                        Fbitbuffer[6] = 0;
                        Fbitbuffer[5] = 1;
                    }
                    af[1] = Fbitbuffer.to_ulong();
                    pc += 2;
                    cycles += 8;
                break;

                case 0x6E: // Flags Need Fixed
                    hlbuffer = hl[0] << 8 | hl[1];
                    Bbitbuffer = memory[hlbuffer];
                    Fbitbuffer = af[1];
                    if(Bbitbuffer[5] == 0)
                    {
                        Fbitbuffer[7] = 1;
                        Fbitbuffer[6] = 0;
                        Fbitbuffer[5] = 1;
                    }
                    if(Bbitbuffer[5] == 1)
                    {
                        Fbitbuffer[7] = 0;
                        Fbitbuffer[6] = 0;
                        Fbitbuffer[5] = 1;
                    }
                    af[1] = Fbitbuffer.to_ulong();
                    pc += 2;
                    cycles += 8;
                break;

                case 0x6F: // Flags Need Fixed
                    Abitbuffer = af[0];
                    Fbitbuffer = af[1];
                    if(Abitbuffer[5] == 0)
                    {
                        Fbitbuffer[7] = 1;
                        Fbitbuffer[6] = 0;
                        Fbitbuffer[5] = 1;
                    }
                    if(Abitbuffer[5] == 1)
                    {
                        Fbitbuffer[7] = 0;
                        Fbitbuffer[6] = 0;
                        Fbitbuffer[5] = 1;
                    }
                    af[1] = Fbitbuffer.to_ulong();
                    pc += 2;
                    cycles += 8;
                break;

                case 0x70: // Flags Need Fixed
                    Bbitbuffer = bc[0];
                    Fbitbuffer = af[1];
                    if(Bbitbuffer[6] == 0)
                    {
                        Fbitbuffer[7] = 1;
                        Fbitbuffer[6] = 0;
                        Fbitbuffer[5] = 1;
                    }
                    if(Bbitbuffer[6] == 1)
                    {
                        Fbitbuffer[7] = 0;
                        Fbitbuffer[6] = 0;
                        Fbitbuffer[5] = 1;
                    }
                    af[1] = Fbitbuffer.to_ulong();
                    pc += 2;
                    cycles += 8;
                break;

                case 0x71: // Flags Need Fixed
                    Bbitbuffer = bc[1];
                    Fbitbuffer = af[1];
                    if(Bbitbuffer[6] == 0)
                    {
                        Fbitbuffer[7] = 1;
                        Fbitbuffer[6] = 0;
                        Fbitbuffer[5] = 1;
                    }
                    if(Bbitbuffer[6] == 1)
                    {
                        Fbitbuffer[7] = 0;
                        Fbitbuffer[6] = 0;
                        Fbitbuffer[5] = 1;
                    }
                    af[1] = Fbitbuffer.to_ulong();
                    pc += 2;
                    cycles += 8;
                break;

                case 0x72: // Flags Need Fixed
                    Bbitbuffer = de[0];
                    Fbitbuffer = af[1];
                    if(Bbitbuffer[6] == 0)
                    {
                        Fbitbuffer[7] = 1;
                        Fbitbuffer[6] = 0;
                        Fbitbuffer[5] = 1;
                    }
                    if(Bbitbuffer[6] == 1)
                    {
                        Fbitbuffer[7] = 0;
                        Fbitbuffer[6] = 0;
                        Fbitbuffer[5] = 1;
                    }
                    af[1] = Fbitbuffer.to_ulong();
                    pc += 2;
                    cycles += 8;
                break;

                case 0x73: // Flags Need Fixed
                    Bbitbuffer = de[1];
                    Fbitbuffer = af[1];
                    if(Bbitbuffer[6] == 0)
                    {
                        Fbitbuffer[7] = 1;
                        Fbitbuffer[6] = 0;
                        Fbitbuffer[5] = 1;
                    }
                    if(Bbitbuffer[6] == 1)
                    {
                        Fbitbuffer[7] = 0;
                        Fbitbuffer[6] = 0;
                        Fbitbuffer[5] = 1;
                    }
                    af[1] = Fbitbuffer.to_ulong();
                    pc += 2;
                    cycles += 8;
                break;

                case 0x74: // Flags Need Fixed
                    Bbitbuffer = hl[0];
                    Fbitbuffer = af[1];
                    if(Bbitbuffer[6] == 0)
                    {
                        Fbitbuffer[7] = 1;
                        Fbitbuffer[6] = 0;
                        Fbitbuffer[5] = 1;
                    }
                    if(Bbitbuffer[6] == 1)
                    {
                        Fbitbuffer[7] = 0;
                        Fbitbuffer[6] = 0;
                        Fbitbuffer[5] = 1;
                    }
                    af[1] = Fbitbuffer.to_ulong();
                    pc += 2;
                    cycles += 8;
                break;

                case 0x75: // Flags Need Fixed
                    Bbitbuffer = hl[1];
                    Fbitbuffer = af[1];
                    if(Bbitbuffer[6] == 0)
                    {
                        Fbitbuffer[7] = 1;
                        Fbitbuffer[6] = 0;
                        Fbitbuffer[5] = 1;
                    }
                    if(Bbitbuffer[6] == 1)
                    {
                        Fbitbuffer[7] = 0;
                        Fbitbuffer[6] = 0;
                        Fbitbuffer[5] = 1;
                    }
                    af[1] = Fbitbuffer.to_ulong();
                    pc += 2;
                    cycles += 8;
                break;

                case 0x76: // Flags Need Fixed
                    hlbuffer = hl[0] << 8 | hl[1];
                    Bbitbuffer = memory[hlbuffer];
                    Fbitbuffer = af[1];
                    if(Bbitbuffer[6] == 0)
                    {
                        Fbitbuffer[7] = 1;
                        Fbitbuffer[6] = 0;
                        Fbitbuffer[5] = 1;
                    }
                    if(Bbitbuffer[6] == 1)
                    {
                        Fbitbuffer[7] = 0;
                        Fbitbuffer[6] = 0;
                        Fbitbuffer[5] = 1;
                    }
                    af[1] = Fbitbuffer.to_ulong();
                    pc += 2;
                    cycles += 8;
                break;

                case 0x77: // Flags Need Fixed
                    Abitbuffer = af[0];
                    Fbitbuffer = af[1];
                    if(Abitbuffer[6] == 0)
                    {
                        Fbitbuffer[7] = 1;
                        Fbitbuffer[6] = 0;
                        Fbitbuffer[5] = 1;
                    }
                    if(Abitbuffer[6] == 1)
                    {
                        Fbitbuffer[7] = 0;
                        Fbitbuffer[6] = 0;
                        Fbitbuffer[5] = 1;
                    }
                    af[1] = Fbitbuffer.to_ulong();
                    pc += 2;
                    cycles += 8;
                break;

                case 0x78: // Flags Need Fixed
                    Bbitbuffer = bc[0];
                    Fbitbuffer = af[1];
                    if(Bbitbuffer[7] == 0)
                    {
                        Fbitbuffer[7] = 1;
                        Fbitbuffer[6] = 0;
                        Fbitbuffer[5] = 1;
                    }
                    if(Bbitbuffer[7] == 1)
                    {
                        Fbitbuffer[7] = 0;
                        Fbitbuffer[6] = 0;
                        Fbitbuffer[5] = 1;
                    }
                    af[1] = Fbitbuffer.to_ulong();
                    pc += 2;
                    cycles += 8;
                break;

                case 0x79: // Flags Need Fixed
                    Bbitbuffer = bc[1];
                    Fbitbuffer = af[1];
                    if(Bbitbuffer[7] == 0)
                    {
                        Fbitbuffer[7] = 1;
                        Fbitbuffer[6] = 0;
                        Fbitbuffer[5] = 1;
                    }
                    if(Bbitbuffer[7] == 1)
                    {
                        Fbitbuffer[7] = 0;
                        Fbitbuffer[6] = 0;
                        Fbitbuffer[5] = 1;
                    }
                    af[1] = Fbitbuffer.to_ulong();
                    pc += 2;
                    cycles += 8;
                break;

                case 0x7A: // Flags Need Fixed
                    Bbitbuffer = de[0];
                    Fbitbuffer = af[1];
                    if(Bbitbuffer[7] == 0)
                    {
                        Fbitbuffer[7] = 1;
                        Fbitbuffer[6] = 0;
                        Fbitbuffer[5] = 1;
                    }
                    if(Bbitbuffer[7] == 1)
                    {
                        Fbitbuffer[7] = 0;
                        Fbitbuffer[6] = 0;
                        Fbitbuffer[5] = 1;
                    }
                    af[1] = Fbitbuffer.to_ulong();
                    pc += 2;
                    cycles += 8;
                break;

                case 0x7B: // Flags Need Fixed
                    Bbitbuffer = de[1];
                    Fbitbuffer = af[1];
                    if(Bbitbuffer[7] == 0)
                    {
                        Fbitbuffer[7] = 1;
                        Fbitbuffer[6] = 0;
                        Fbitbuffer[5] = 1;
                    }
                    if(Bbitbuffer[7] == 1)
                    {
                        Fbitbuffer[7] = 0;
                        Fbitbuffer[6] = 0;
                        Fbitbuffer[5] = 1;
                    }
                    af[1] = Fbitbuffer.to_ulong();
                    pc += 2;
                    cycles += 8;
                break;

                case 0x7C: // Flags Need Fixed
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

                case 0x7D: // Flags Need Fixed
                    Bbitbuffer = hl[1];
                    Fbitbuffer = af[1];
                    if(Bbitbuffer[7] == 0)
                    {
                        Fbitbuffer[7] = 1;
                        Fbitbuffer[6] = 0;
                        Fbitbuffer[5] = 1;
                    }
                    if(Bbitbuffer[7] == 1)
                    {
                        Fbitbuffer[7] = 0;
                        Fbitbuffer[6] = 0;
                        Fbitbuffer[5] = 1;
                    }
                    af[1] = Fbitbuffer.to_ulong();
                    pc += 2;
                    cycles += 8;
                break;

                case 0x7E: // Flags Need Fixed
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

                case 0x7F: // Flags Need Fixed
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

                case 0x88:
                    Abitbuffer = bc[0];
                    Abitbuffer.reset(1);
                    bc[0] = Abitbuffer.to_ulong();
                    pc += 2;
                    cycles += 8;
                break;

                case 0x89:
                    Abitbuffer = bc[1];
                    Abitbuffer.reset(1);
                    bc[1] = Abitbuffer.to_ulong();
                    pc += 2;
                    cycles += 8;
                break;

                case 0x8A:
                    Abitbuffer = de[0];
                    Abitbuffer.reset(1);
                    de[0] = Abitbuffer.to_ulong();
                    pc += 2;
                    cycles += 8;
                break;

                case 0x8B:
                    Abitbuffer = de[1];
                    Abitbuffer.reset(1);
                    de[1] = Abitbuffer.to_ulong();
                    pc += 2;
                    cycles += 8;
                break;

                case 0x8C:
                    Abitbuffer = hl[0];
                    Abitbuffer.reset(1);
                    hl[0] = Abitbuffer.to_ulong();
                    pc += 2;
                    cycles += 8;
                break;

                case 0x8D:
                    Abitbuffer = hl[1];
                    Abitbuffer.reset(1);
                    hl[1] = Abitbuffer.to_ulong();
                    pc += 2;
                    cycles += 8;
                break;

                case 0x8E:
                    hlbuffer = hl[0] << 8 | hl[1];
                    MEMbitbuffer = memory[hlbuffer];
                    MEMbitbuffer.reset(1);
                    memory[hlbuffer] = MEMbitbuffer.to_ulong();
                    pc += 2;
                    cycles += 16;
                break;

                case 0x8F:
                    Abitbuffer = af[0];
                    Abitbuffer.reset(1);
                    af[0] = Abitbuffer.to_ulong();
                    pc += 2;
                    cycles += 8;
                break;

                case 0x90:
                    Abitbuffer = bc[0];
                    Abitbuffer.reset(2);
                    bc[0] = Abitbuffer.to_ulong();
                    pc += 2;
                    cycles += 8;
                break;

                case 0x91:
                    Abitbuffer = bc[1];
                    Abitbuffer.reset(2);
                    bc[1] = Abitbuffer.to_ulong();
                    pc += 2;
                    cycles += 8;
                break;

                case 0x92:
                    Abitbuffer = de[0];
                    Abitbuffer.reset(2);
                    de[0] = Abitbuffer.to_ulong();
                    pc += 2;
                    cycles += 8;
                break;

                case 0x93:
                    Abitbuffer = de[1];
                    Abitbuffer.reset(2);
                    de[1] = Abitbuffer.to_ulong();
                    pc += 2;
                    cycles += 8;
                break;

                case 0x94:
                    Abitbuffer = hl[0];
                    Abitbuffer.reset(2);
                    hl[0] = Abitbuffer.to_ulong();
                    pc += 2;
                    cycles += 8;
                break;

                case 0x95:
                    Abitbuffer = hl[1];
                    Abitbuffer.reset(2);
                    hl[1] = Abitbuffer.to_ulong();
                    pc += 2;
                    cycles += 8;
                break;

                case 0x96:
                    hlbuffer = hl[0] << 8 | hl[1];
                    Abitbuffer = memory[hlbuffer];
                    Abitbuffer.reset(2);
                    memory[hlbuffer] = Abitbuffer.to_ulong();
                    pc += 2;
                    cycles += 8;
                break;

                case 0x97:
                    Abitbuffer = af[0];
                    Abitbuffer.reset(2);
                    af[0] = Abitbuffer.to_ulong();
                    pc += 2;
                    cycles += 8;
                break;

                case 0x98:
                    Abitbuffer = bc[0];
                    Abitbuffer.reset(3);
                    bc[0] = Abitbuffer.to_ulong();
                    pc += 2;
                    cycles += 8;
                break;

                case 0x99:
                    Abitbuffer = bc[1];
                    Abitbuffer.reset(3);
                    bc[1] = Abitbuffer.to_ulong();
                    pc += 2;
                    cycles += 8;
                break;

                case 0x9A:
                    Abitbuffer = de[0];
                    Abitbuffer.reset(3);
                    de[0] = Abitbuffer.to_ulong();
                    pc += 2;
                    cycles += 8;
                break;

                case 0x9B:
                    Abitbuffer = de[1];
                    Abitbuffer.reset(3);
                    de[1] = Abitbuffer.to_ulong();
                    pc += 2;
                    cycles += 8;
                break;

                case 0x9C:
                    Abitbuffer = hl[0];
                    Abitbuffer.reset(3);
                    hl[0] = Abitbuffer.to_ulong();
                    pc += 2;
                    cycles += 8;
                break;

                case 0x9D:
                    Abitbuffer = hl[1];
                    Abitbuffer.reset(3);
                    hl[1] = Abitbuffer.to_ulong();
                    pc += 2;
                    cycles += 8;
                break;

                case 0x9E:
                    hlbuffer = hl[0] << 8 | hl[1];
                    Abitbuffer = memory[hlbuffer];
                    Abitbuffer.reset(3);
                    memory[hlbuffer] = Abitbuffer.to_ulong();
                    pc += 2;
                    cycles += 8;
                break;

                case 0x9F:
                    Abitbuffer = af[0];
                    Abitbuffer.reset(3);
                    af[0] = Abitbuffer.to_ulong();
                    pc += 2;
                    cycles += 8;
                break;

                case 0xA0:
                    Abitbuffer = bc[0];
                    Abitbuffer.reset(4);
                    bc[0] = Abitbuffer.to_ulong();
                    pc += 2;
                    cycles += 8;
                break;

                case 0xA1:
                    Abitbuffer = bc[1];
                    Abitbuffer.reset(4);
                    bc[1] = Abitbuffer.to_ulong();
                    pc += 2;
                    cycles += 8;
                break;

                case 0xA2:
                    Abitbuffer = de[0];
                    Abitbuffer.reset(4);
                    de[0] = Abitbuffer.to_ulong();
                    pc += 2;
                    cycles += 8;
                break;

                case 0xA3:
                    Abitbuffer = de[1];
                    Abitbuffer.reset(4);
                    de[1] = Abitbuffer.to_ulong();
                    pc += 2;
                    cycles += 8;
                break;

                case 0xA4:
                    Abitbuffer = hl[0];
                    Abitbuffer.reset(4);
                    hl[0] = Abitbuffer.to_ulong();
                    pc += 2;
                    cycles += 8;
                break;

                case 0xA5:
                    Abitbuffer = hl[1];
                    Abitbuffer.reset(4);
                    hl[1] = Abitbuffer.to_ulong();
                    pc += 2;
                    cycles += 8;
                break;

                case 0xA6:
                    hlbuffer = hl[0] << 8 | hl[1];
                    MEMbitbuffer = memory[hlbuffer];
                    MEMbitbuffer.reset(4);
                    memory[hlbuffer] = MEMbitbuffer.to_ulong();
                    pc += 2;
                    cycles += 16;
                break;

                case 0xA7:
                    Abitbuffer = af[0];
                    Abitbuffer.reset(4);
                    af[0] = Abitbuffer.to_ulong();
                    pc += 2;
                    cycles += 8;
                break;

                case 0xA8:
                    Abitbuffer = bc[0];
                    Abitbuffer.reset(5);
                    bc[0] = Abitbuffer.to_ulong();
                    pc += 2;
                    cycles += 8;
                break;

                case 0xA9:
                    Abitbuffer = bc[1];
                    Abitbuffer.reset(5);
                    bc[1] = Abitbuffer.to_ulong();
                    pc += 2;
                    cycles += 8;
                break;

                case 0xAA:
                    Abitbuffer = de[0];
                    Abitbuffer.reset(5);
                    de[0] = Abitbuffer.to_ulong();
                    pc += 2;
                    cycles += 8;
                break;

                case 0xAB:
                    Abitbuffer = de[1];
                    Abitbuffer.reset(5);
                    de[1] = Abitbuffer.to_ulong();
                    pc += 2;
                    cycles += 8;
                break;

                case 0xAC:
                    Abitbuffer = hl[0];
                    Abitbuffer.reset(5);
                    hl[0] = Abitbuffer.to_ulong();
                    pc += 2;
                    cycles += 8;
                break;

                case 0xAD:
                    Abitbuffer = hl[1];
                    Abitbuffer.reset(5);
                    hl[1] = Abitbuffer.to_ulong();
                    pc += 2;
                    cycles += 8;
                break;

                case 0xAE:
                    hlbuffer = hl[0] << 8 | hl[1];
                    Abitbuffer = memory[hlbuffer];
                    Abitbuffer.reset(5);
                    memory[hlbuffer] = Abitbuffer.to_ulong();
                    pc += 2;
                    cycles += 16;
                break;

                case 0xAF:
                    Abitbuffer = af[0];
                    Abitbuffer.reset(5);
                    af[0] = Abitbuffer.to_ulong();
                    pc += 2;
                    cycles += 8;
                break;

                case 0xB0:
                    Abitbuffer = bc[0];
                    Abitbuffer.reset(6);
                    bc[0] = Abitbuffer.to_ulong();
                    pc += 2;
                    cycles += 8;
                break;

                case 0xB1:
                    Abitbuffer = bc[1];
                    Abitbuffer.reset(6);
                    bc[1] = Abitbuffer.to_ulong();
                    pc += 2;
                    cycles += 8;
                break;

                case 0xB2:
                    Abitbuffer = de[0];
                    Abitbuffer.reset(6);
                    de[0] = Abitbuffer.to_ulong();
                    pc += 2;
                    cycles += 8;
                break;

                case 0xB3:
                    Abitbuffer = de[1];
                    Abitbuffer.reset(6);
                    de[1] = Abitbuffer.to_ulong();
                    pc += 2;
                    cycles += 8;
                break;

                case 0xB4:
                    Abitbuffer = hl[0];
                    Abitbuffer.reset(6);
                    hl[0] = Abitbuffer.to_ulong();
                    pc += 2;
                    cycles += 8;
                break;

                case 0xB5:
                    Abitbuffer = hl[1];
                    Abitbuffer.reset(6);
                    hl[1] = Abitbuffer.to_ulong();
                    pc += 2;
                    cycles += 8;
                break;

                case 0xB6:
                    hlbuffer = hl[0] << 8 | hl[1];
                    Abitbuffer = bc[0];
                    Abitbuffer.reset(6);
                    bc[0] = Abitbuffer.to_ulong();
                    pc += 2;
                    cycles += 8;
                break;

                case 0xB7:
                    Abitbuffer = af[0];
                    Abitbuffer.reset(6);
                    af[0] = Abitbuffer.to_ulong();
                    pc += 2;
                    cycles += 8;
                break;

                case 0xB8:
                    Abitbuffer = bc[0];
                    Abitbuffer.reset(7);
                    bc[0] = Abitbuffer.to_ulong();
                    pc += 2;
                    cycles += 8;
                break;

                case 0xB9:
                    Abitbuffer = bc[1];
                    Abitbuffer.reset(7);
                    bc[1] = Abitbuffer.to_ulong();
                    pc += 2;
                    cycles += 8;
                break;

                case 0xBA:
                    Abitbuffer = de[0];
                    Abitbuffer.reset(7);
                    de[0] = Abitbuffer.to_ulong();
                    pc += 2;
                    cycles += 8;
                break;

                case 0xBB:
                    Abitbuffer = de[1];
                    Abitbuffer.reset(7);
                    de[1] = Abitbuffer.to_ulong();
                    pc += 2;
                    cycles += 8;
                break;

                case 0xBC:
                    Abitbuffer = hl[0];
                    Abitbuffer.reset(7);
                    hl[0] = Abitbuffer.to_ulong();
                    pc += 2;
                    cycles += 8;
                break;

                case 0xBD:
                    Abitbuffer = hl[1];
                    Abitbuffer.reset(7);
                    hl[1] = Abitbuffer.to_ulong();
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

                case 0xC0:
                    Abitbuffer = bc[0];
                    Abitbuffer[0] = 1;
                    bc[0] = Abitbuffer.to_ulong();
                    pc += 2;
                    cycles += 8;
                break;

                case 0xC1:
                    Abitbuffer = bc[1];
                    Abitbuffer[0] = 1;
                    bc[1] = Abitbuffer.to_ulong();
                    pc += 2;
                    cycles += 8;
                break;

                case 0xC2:
                    Abitbuffer = de[0];
                    Abitbuffer[0] = 1;
                    de[0] = Abitbuffer.to_ulong();
                    pc += 2;
                    cycles += 8;
                break;

                case 0xC3:
                    Abitbuffer = de[1];
                    Abitbuffer[0] = 1;
                    de[1] = Abitbuffer.to_ulong();
                    pc += 2;
                    cycles += 8;
                break;

                case 0xC4:
                    Abitbuffer = hl[0];
                    Abitbuffer[0] = 1;
                    hl[0] = Abitbuffer.to_ulong();
                    pc += 2;
                    cycles += 8;
                break;

                case 0xC5:
                    Abitbuffer = hl[1];
                    Abitbuffer[0] = 1;
                    hl[1] = Abitbuffer.to_ulong();
                    pc += 2;
                    cycles += 8;
                break;

                case 0xC6:
                    hlbuffer = hl[0] << 8 | hl[1];
                    MEMbitbuffer = memory[hlbuffer];
                    MEMbitbuffer[0] = 1;
                    memory[hlbuffer] = MEMbitbuffer.to_ulong();
                    pc += 2;
                    cycles += 16;
                break;

                case 0xC7:
                    Abitbuffer = af[0];
                    Abitbuffer[0] = 1;
                    af[0] = Abitbuffer.to_ulong();
                    pc += 2;
                    cycles += 8;
                break;

                case 0xC8:
                    Abitbuffer = bc[0];
                    Abitbuffer[1] = 1;
                    bc[0] = Abitbuffer.to_ulong();
                    pc += 2;
                    cycles += 8;
                break;

                case 0xC9:
                    Abitbuffer = bc[1];
                    Abitbuffer[1] = 1;
                    bc[1] = Abitbuffer.to_ulong();
                    pc += 2;
                    cycles += 8;
                break;

                case 0xCA:
                    Abitbuffer = de[0];
                    Abitbuffer[1] = 1;
                    de[0] = Abitbuffer.to_ulong();
                    pc += 2;
                    cycles += 8;
                break;

                case 0xCB:
                    Abitbuffer = de[1];
                    Abitbuffer[1] = 1;
                    de[1] = Abitbuffer.to_ulong();
                    pc += 2;
                    cycles += 8;
                break;

                case 0xCC:
                    Abitbuffer = hl[0];
                    Abitbuffer[1] = 1;
                    hl[0] = Abitbuffer.to_ulong();
                    pc += 2;
                    cycles += 8;
                break;

                case 0xCD:
                    Abitbuffer = hl[1];
                    Abitbuffer[1] = 1;
                    hl[1] = Abitbuffer.to_ulong();
                    pc += 2;
                    cycles += 8;
                break;

                case 0xCE:
                    hlbuffer = hl[0] << 8 | hl[1];
                    Abitbuffer = memory[hlbuffer];
                    Abitbuffer[1] = 1;
                    memory[hlbuffer] = Abitbuffer.to_ulong();
                    pc += 2;
                    cycles += 16;
                break;

                case 0xCF:
                    Abitbuffer = af[0];
                    Abitbuffer[1] = 1;
                    af[0] = Abitbuffer.to_ulong();
                    pc += 2;
                    cycles += 8;
                break;

                case 0xD0:
                    Abitbuffer = bc[0];
                    Abitbuffer[2] = 1;
                    bc[0] = Abitbuffer.to_ulong();
                    pc += 2;
                    cycles += 8;
                break;

                case 0xD1:
                    Abitbuffer = bc[1];
                    Abitbuffer[2] = 1;
                    bc[1] = Abitbuffer.to_ulong();
                    pc += 2;
                    cycles += 8;
                break;

                case 0xD2:
                    Abitbuffer = de[0];
                    Abitbuffer[2] = 1;
                    de[0] = Abitbuffer.to_ulong();
                    pc += 2;
                    cycles += 8;
                break;

                case 0xD3:
                    Abitbuffer = de[1];
                    Abitbuffer[2] = 1;
                    de[1] = Abitbuffer.to_ulong();
                    pc += 2;
                    cycles += 8;
                break;

                case 0xD4:
                    Abitbuffer = hl[0];
                    Abitbuffer[2] = 1;
                    hl[0] = Abitbuffer.to_ulong();
                    pc += 2;
                    cycles += 8;
                break;

                case 0xD5:
                    Abitbuffer = hl[1];
                    Abitbuffer[2] = 1;
                    hl[1] = Abitbuffer.to_ulong();
                    pc += 2;
                    cycles += 8;
                break;

                case 0xD6:
                    hlbuffer = hl[0] << 8 | hl[1];
                    Abitbuffer = memory[hlbuffer];
                    Abitbuffer[2] = 1;
                    memory[hlbuffer] = Abitbuffer.to_ulong();
                    pc += 2;
                    cycles += 8;
                break;

                case 0xD7:
                    Abitbuffer = af[0];
                    Abitbuffer[2] = 1;
                    af[0] = Abitbuffer.to_ulong();
                    pc += 2;
                    cycles += 8;
                break;

                case 0xD8:
                    Abitbuffer = bc[0];
                    Abitbuffer[3] = 1;
                    bc[0] = Abitbuffer.to_ulong();
                    pc += 2;
                    cycles += 8;
                break;

                case 0xD9:
                    Abitbuffer = bc[1];
                    Abitbuffer[3] = 1;
                    bc[1] = Abitbuffer.to_ulong();
                    pc += 2;
                    cycles += 8;
                break;

                case 0xDA:
                    Abitbuffer = de[0];
                    Abitbuffer[3] = 1;
                    de[0] = Abitbuffer.to_ulong();
                    pc += 2;
                    cycles += 8;
                break;

                case 0xDB:
                    Abitbuffer = de[1];
                    Abitbuffer[3] = 1;
                    de[1] = Abitbuffer.to_ulong();
                    pc += 2;
                    cycles += 8;
                break;

                case 0xDC:
                    Abitbuffer = hl[0];
                    Abitbuffer[3] = 1;
                    hl[0] = Abitbuffer.to_ulong();
                    pc += 2;
                    cycles += 8;
                break;

                case 0xDD:
                    Abitbuffer = hl[1];
                    Abitbuffer[3] = 1;
                    hl[1] = Abitbuffer.to_ulong();
                    pc += 2;
                    cycles += 8;
                break;

                case 0xDE:
                    hlbuffer = hl[0] << 8 | hl[1];
                    MEMbitbuffer = memory[hlbuffer];
                    MEMbitbuffer[3] = 1;
                    memory[hlbuffer] = MEMbitbuffer.to_ulong();
                    pc += 2;
                    cycles += 16;
                break;

                case 0xDF:
                    Abitbuffer = af[0];
                    Abitbuffer[3] = 1;
                    af[0] = Abitbuffer.to_ulong();
                    pc += 2;
                    cycles += 8;
                break;

                case 0xE0:
                    Abitbuffer = bc[0];
                    Abitbuffer[4] = 1;
                    bc[0] = Abitbuffer.to_ulong();
                    pc += 2;
                    cycles += 8;
                break;

                case 0xE1:
                    Abitbuffer = bc[1];
                    Abitbuffer[4] = 1;
                    bc[1] = Abitbuffer.to_ulong();
                    pc += 2;
                    cycles += 8;
                break;

                case 0xE2:
                    Abitbuffer = de[0];
                    Abitbuffer[4] = 1;
                    de[0] = Abitbuffer.to_ulong();
                    pc += 2;
                    cycles += 8;
                break;

                case 0xE3:
                    Abitbuffer = de[1];
                    Abitbuffer[4] = 1;
                    de[1] = Abitbuffer.to_ulong();
                    pc += 2;
                    cycles += 8;
                break;

                case 0xE4:
                    Abitbuffer = hl[0];
                    Abitbuffer[4] = 1;
                    hl[0] = Abitbuffer.to_ulong();
                    pc += 2;
                    cycles += 8;
                break;

                case 0xE5:
                    Abitbuffer = hl[1];
                    Abitbuffer[4] = 1;
                    hl[1] = Abitbuffer.to_ulong();
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

                case 0xE7:
                    Abitbuffer = af[0];
                    Abitbuffer[4] = 1;
                    af[0] = Abitbuffer.to_ulong();
                    pc += 2;
                    cycles += 8;
                break;

                case 0xE8:
                    Abitbuffer = bc[0];
                    Abitbuffer[5] = 1;
                    bc[0] = Abitbuffer.to_ulong();
                    pc += 2;
                    cycles += 8;
                break;

                case 0xE9:
                    Abitbuffer = bc[1];
                    Abitbuffer[5] = 1;
                    bc[1] = Abitbuffer.to_ulong();
                    pc += 2;
                    cycles += 8;
                break;

                case 0xEA:
                    Abitbuffer = de[0];
                    Abitbuffer[5] = 1;
                    de[0] = Abitbuffer.to_ulong();
                    pc += 2;
                    cycles += 8;
                break;

                case 0xEB:
                    Abitbuffer = de[1];
                    Abitbuffer[5] = 1;
                    de[1] = Abitbuffer.to_ulong();
                    pc += 2;
                    cycles += 8;
                break;

                case 0xEC:
                    Abitbuffer = hl[0];
                    Abitbuffer[5] = 1;
                    hl[0] = Abitbuffer.to_ulong();
                    pc += 2;
                    cycles += 8;
                break;

                case 0xED:
                    Abitbuffer = hl[1];
                    Abitbuffer[5] = 1;
                    hl[1] = Abitbuffer.to_ulong();
                    pc += 2;
                    cycles += 8;
                break;

                case 0xEE:
                    hlbuffer = hl[0] << 8 | hl[1];
                    MEMbitbuffer = memory[hlbuffer];
                    MEMbitbuffer.set(5);
                    memory[hlbuffer] = MEMbitbuffer.to_ulong();
                    pc += 2;
                    cycles += 16;
                break;

                case 0xEF:
                    Abitbuffer = af[0];
                    Abitbuffer[5] = 1;
                    af[0] = Abitbuffer.to_ulong();
                    pc += 2;
                    cycles += 8;
                break;

                case 0xF0:
                    Abitbuffer = bc[0];
                    Abitbuffer[6] = 1;
                    bc[0] = Abitbuffer.to_ulong();
                    pc += 2;
                    cycles += 8;
                break;

                case 0xF1:
                    Abitbuffer = bc[1];
                    Abitbuffer[6] = 1;
                    bc[1] = Abitbuffer.to_ulong();
                    pc += 2;
                    cycles += 8;
                break;

                case 0xF2:
                    Abitbuffer = de[0];
                    Abitbuffer[6] = 1;
                    de[0] = Abitbuffer.to_ulong();
                    pc += 2;
                    cycles += 8;
                break;

                case 0xF3:
                    Abitbuffer = de[1];
                    Abitbuffer[6] = 1;
                    de[1] = Abitbuffer.to_ulong();
                    pc += 2;
                    cycles += 8;
                break;

                case 0xF4:
                    Abitbuffer = hl[0];
                    Abitbuffer[6] = 1;
                    hl[0] = Abitbuffer.to_ulong();
                    pc += 2;
                    cycles += 8;
                break;

                case 0xF5:
                    Abitbuffer = hl[1];
                    Abitbuffer[6] = 1;
                    hl[1] = Abitbuffer.to_ulong();
                    pc += 2;
                    cycles += 8;
                break;

                case 0xF6:
                    hlbuffer = hl[0] << 8 | hl[1];
                    MEMbitbuffer = memory[hlbuffer];
                    MEMbitbuffer.set(6);
                    memory[hlbuffer] = MEMbitbuffer.to_ulong();
                    pc += 2;
                    cycles += 16;
                break;

                case 0xF7:
                    Abitbuffer = af[0];
                    Abitbuffer[6] = 1;
                    af[0] = Abitbuffer.to_ulong();
                    pc += 2;
                    cycles += 8;
                break;

                case 0xF8:
                    Abitbuffer = bc[0];
                    Abitbuffer[7] = 1;
                    bc[0] = Abitbuffer.to_ulong();
                    pc += 2;
                    cycles += 8;
                break;

                case 0xF9:
                    Abitbuffer = bc[1];
                    Abitbuffer[7] = 1;
                    bc[1] = Abitbuffer.to_ulong();
                    pc += 2;
                    cycles += 8;
                break;

                case 0xFA:
                    Abitbuffer = de[0];
                    Abitbuffer[7] = 1;
                    de[0] = Abitbuffer.to_ulong();
                    pc += 2;
                    cycles += 8;
                break;

                case 0xFB:
                    Abitbuffer = de[1];
                    Abitbuffer[7] = 1;
                    de[1] = Abitbuffer.to_ulong();
                    pc += 2;
                    cycles += 8;
                break;

                case 0xFC:
                    Abitbuffer = hl[0];
                    Abitbuffer[7] = 1;
                    hl[0] = Abitbuffer.to_ulong();
                    pc += 2;
                    cycles += 8;
                break;

                case 0xFD:
                    Abitbuffer = hl[1];
                    Abitbuffer[7] = 1;
                    hl[1] = Abitbuffer.to_ulong();
                    pc += 2;
                    cycles += 8;
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
        break; // Ends entire 0xCB case


        case 0xCC: // Flag Checked
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
            }
            if(Abitbuffer[7] == 0)
            {
                pc += 3;
                cycles += 12;
            }
        break;

        case 0xCD: // Flag Checked
            help0xCD3 = (sp[0]);
            nn = (help0xCD3 - 0xFFFFFF00) << 8 | (sp[1] - 0xFFFFFF00);
            help0xCD = (pc + 0x3) >> 8;
            help0xCD2 = (pc + 0x3);
            memory[(nn - 0xFFFF0000) - 0x02] = (help0xCD2);
            memory[(nn - 0xFFFF0000) - 0x01] = (help0xCD);
            opnn[0] = memory[pc + 2];
            opnn[1] = memory[pc + 1];
            nn = (opnn[0]) << 8 | (opnn[1]);
            help0xCD4 = (nn);
            pc = (help0xCD4);
            sp[1] -= 0x02;
            if(sp[1] == 0xFF || sp[1] == 0xFE)
            {
                sp[0] -= 0x01;
            }
            cycles += 12;
        break;

        case 0xCE: // Flag Checked
            beforeHcheck = af[0];
            af[0] = af[0] + memory[pc + 1];
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
                Fbitbuffer[5] = halfcarrycheck(beforeHcheck,af[0]);
                Fbitbuffer[4] = overflowcheck(beforeHcheck,af[0]);
            }
            if (af[0] != 0x00)
            {
                Fbitbuffer[7] = 0;
                Fbitbuffer[6] = 0;
                Fbitbuffer[5] = halfcarrycheck(beforeHcheck,af[0]);
                Fbitbuffer[4] = overflowcheck(beforeHcheck,af[0]);
            }
            af[1] = Fbitbuffer.to_ulong();
            pc += 2;
            cycles += 8;
        break;

        case 0xCF: // Flag Checked
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

        case 0xD0: // Flag Checked
            Fbitbuffer = af[1];
            if(Fbitbuffer[4] == 0)
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
                goto done0xD0;
            }
            pc++;
            done0xD0:
            cycles += 8;
        break;

        case 0xD1: // Flag Checked
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

        case 0xD2: // Flag Checked
            Fbitbuffer = af[1];
            if (Fbitbuffer[4] == 0)
            {
                opnn[0] = memory[pc + 2];
                opnn[1] = memory[pc + 1];
                nn = opnn[0] << 8 | opnn[1];
                pc = nn;
                cycles += 12;
                goto done0xD2;
            }
            pc += 3;
            cycles += 12;
            done0xD2:
        break;

        case 0xD4: // Flag Checked
            Abitbuffer = af[1];
            if(Abitbuffer[4] == 0)
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
                goto done0xD4;
            }
            pc += 3;
            cycles += 12;
            done0xD4:
        break;

        case 0xD5: // Flag Checked
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

        case 0xD6: // Flag Checked
            tem = af[0];
            af[0] = af[0] - memory[pc + 1];
            Fbitbuffer = af[1];
            if(af[0] == 0x00)
            {
                Fbitbuffer[7] = 1;
                Fbitbuffer[6] = 1;
                Fbitbuffer[5] = halfcarrycheck(tem,af[0]);
                Fbitbuffer[4] = negativeoverflowcheck(tem,af[0]);
            }
            if(af[0] != 0x00)
            {
                Fbitbuffer[7] = 0;
                Fbitbuffer[6] = 1;
                Fbitbuffer[5] = halfcarrycheck(tem,af[0]);
                Fbitbuffer[4] = negativeoverflowcheck(tem,af[0]);
            }
            af[1] = Fbitbuffer.to_ulong();
            pc += 2;
            cycles += 8;
        break;

        case 0xD7: // Flag Checked
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
            pc = 0x0010;
            cycles += 32;
        break;

        case 0xD8: // Flag Checked
            Fbitbuffer = af[1];
            if(Fbitbuffer[4] == 1)
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
                goto done0xD8;
            }
            pc++;
            done0xD8:
            cycles += 8;
        break;

        case 0xD9: // Flag Checked
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

        case 0xDA: // Flag Checked
            Fbitbuffer = af[1];
            if (Fbitbuffer[4] == 1)
            {
                opnn[0] = memory[pc + 2];
                opnn[1] = memory[pc + 1];
                nn = opnn[0] << 8 | opnn[1];
                pc = nn;
                cycles += 12;
                goto done0xDA;
            }
            pc += 3;
            cycles += 12;
            done0xDA:
        break;

        case 0xDC: // Flag Checked
            Abitbuffer = af[1];
            if(Abitbuffer[4] == 1)
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
                goto done0xDC;
            }
            pc += 3;
            cycles += 12;
            done0xDC:
        break;

        case 0xDE: // Flag Checked
        beforeHcheck = af[0];
        Fbitbuffer = af[1];
        if(Fbitbuffer[4] == 1)
        {
            af[0] = af[0] - (memory[pc + 1] + 0x01);
        }
        if(Fbitbuffer[4] == 0)
        {
            af[0] = af[0] - (memory[pc + 1]);
        }
        if(af[0] == 0x00)
        {
            Fbitbuffer[7] = 1;
            Fbitbuffer[6] = 1;
            Fbitbuffer[5] = halfcarrycheck(beforeHcheck,af[0]);
            Fbitbuffer[4] = negativeoverflowcheck(beforeHcheck,af[0]);
        }
        if(af[0] != 0x00)
        {
            Fbitbuffer[7] = 0;
            Fbitbuffer[6] = 1;
            Fbitbuffer[5] = halfcarrycheck(beforeHcheck,af[0]);
            Fbitbuffer[4] = negativeoverflowcheck(beforeHcheck,af[0]);
        }
        af[1] = Fbitbuffer.to_ulong();
        pc += 2;
        cycles += 8;
        break;

        case 0xDF: // Flag Checked
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
            pc = 0x0018;
            cycles += 32;
        break;

        case 0xE0: // Flag Checked
            help0xE0[0] = 0xFF;
            help0xE0[1] = memory[pc + 1];
            help0xE0_2 = help0xE0[0] << 8 | help0xE0[1];
            memory[help0xE0_2] = af[0];
            pc += 2;
            cycles += 12;
        break;

        case 0xE1: // Flag Checked
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

        case 0xE2: // Flag Checked
            help0xE2[0] = 0xFF;
            help0xE2[1] = bc[1];
            help0xE2_2 = help0xE2[0] << 8 | help0xE2[1];
            memory[help0xE2_2] = af[0];
            pc++;
            cycles += 8;
        break;

        case 0xE5: // Flag Checked
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

        case 0xE6: // Flag Checked
            af[0] = af[0] & memory[pc + 0x01];
            Fbitbuffer = af[1];
            if(af[0] == 0x00)
            {
                Fbitbuffer[7] = 1;
                Fbitbuffer[6] = 0;
                Fbitbuffer[5] = 1;
                Fbitbuffer[4] = 0;
            }
            if(af[0] != 0x00)
            {
                Fbitbuffer[7] = 0;
                Fbitbuffer[6] = 0;
                Fbitbuffer[5] = 1;
                Fbitbuffer[4] = 0;
            }
            af[1] = Fbitbuffer.to_ulong();
            pc += 2;
            cycles += 8;
        break;

        case 0xE7: // Flag Checked
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
            pc = 0x0020;
            cycles += 32;
        break;

        case 0xE8: // Flags Need Fixed
            sp[1] = sp[1] + memory[pc + 1];
            Fbitbuffer = af[1];
            if(sp[1] <= help0xE8)
            {
            sp[0]++;
            Fbitbuffer[7] = 0;
            Fbitbuffer[6] = 0;
            Fbitbuffer[4] = 1;
            }
            if(sp[1] > help0xE8)
            {
            Fbitbuffer[7] = 0;
            Fbitbuffer[6] = 0;
            Fbitbuffer[4] = 0;
            }
            af[1] = Fbitbuffer.to_ulong();
            pc += 2;
            cycles += 16;
        break;

        case 0xE9: // Flag Checked
            hlbuffer = hl[0] << 8 | hl[1];
            pc = hlbuffer;
            cycles += 4;
        break;

        case 0xEA: // Flag Checked
            helpEA = memory[pc + 2] << 8 | memory[pc + 1];
            memory[(helpEA)] = af[0];
            cycles += 16;
            pc += 3;
        break;

        case 0xEE: // Flag Checked
            af[0] = memory[pc + 0x01] ^ af[0];
            Fbitbuffer = af[1];
            if(af[0] == 0x00)
            {
                Fbitbuffer[7] = 1;
                Fbitbuffer[6] = 0;
                Fbitbuffer[5] = 0;
                Fbitbuffer[4] = 0;
            }
            if(af[0] != 0x00)
            {
                Fbitbuffer[7] = 0;
                Fbitbuffer[6] = 0;
                Fbitbuffer[5] = 0;
                Fbitbuffer[4] = 0;
            }
            af[1] = Fbitbuffer.to_ulong();
            pc += 2;
            cycles += 8;
        break;

        case 0xEF: // Flag Checked
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

        case 0xF0: // Flag Checked
            help0xF0[0] = 0xFF;
            help0xF0[1] = memory[pc + 1];
            help0xF0_2 = help0xF0[0] << 8 | help0xF0[1];
            af[0] = memory[help0xF0_2];
            pc += 2;
            cycles += 12;
        break;

        case 0xF1: // Flag Checked
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

        case 0xF2: // Flag Checked
        af[0] = memory[0xFF00 + bc[1]];
        pc++;
        cycles += 8;
        break;

        case 0xF3: // DI (Disables Interupts)
            interruptEnable = false;
            MEMbitbuffer = memory[0xFFFF];
            MEMbitbuffer[0] = 0;
            MEMbitbuffer[1] = 0;
            MEMbitbuffer[2] = 0;
            MEMbitbuffer[3] = 0;
            MEMbitbuffer[4] = 0;
            memory[0xFFFF] = MEMbitbuffer.to_ulong();
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

        case 0xF6: // Flag Checked
            Abitbuffer = af[0];
            Bbitbuffer = memory[pc + 1];
            Fbitbuffer = af[1];
            bitcount = 7;
            while (helpOR == false)
            {
                if(Abitbuffer[bitcount] == 0 && Bbitbuffer[bitcount] == 1)
                {
                    Abitbuffer[bitcount] = 1;
                }
                bitcount--;
                if(bitcount == 0xFFFFFFFF)
                {
                    break;
                }
            }
            af[0] = Abitbuffer.to_ulong();
            if(af[0] == 0x00)
            {
                Fbitbuffer[7] = 1;
                Fbitbuffer[6] = 0;
                Fbitbuffer[5] = 0;
                Fbitbuffer[4] = 0;
            }
            if(af[0] != 0x00)
            {
                Fbitbuffer[7] = 0;
                Fbitbuffer[6] = 0;
                Fbitbuffer[5] = 0;
                Fbitbuffer[4] = 0;
            }
            af[1] = Fbitbuffer.to_ulong();
            pc += 2;
            cycles += 8;
        break;

        case 0xF7: // Flag Checked
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
            pc = 0x0030;
            cycles += 32;
        break;

        case 0xF8: // Flags Need Fixed
        hl[0] = sp[0];
        hl[1] = sp[1];
        help0xE8 = hl[1];
        hl[1] = hl[1] + memory[pc + 1];
        Fbitbuffer = af[1];
        if(hl[1] <= help0xE8)
        {
        hl[0]++;
        Fbitbuffer[7] = 0;
        Fbitbuffer[6] = 0;
        Fbitbuffer[4] = 1;
        }
        if(hl[1] > help0xE8)
        {
        Fbitbuffer[7] = 0;
        Fbitbuffer[6] = 0;
        Fbitbuffer[4] = 0;
        }
        pc += 2;
        cycles += 12;
        break;

        case 0xF9: // Flag Checked
            sp[0] = hl[0];
            sp[1] = hl[1];
            pc++;
            cycles += 8;
        break;

        case 0xFA: // Flag Checked
            nn = (memory[pc + 2] - 0xFFFFFF00) << 8 | (memory[pc + 1] - 0xFFFFFF00);
            af[0] = (memory[nn - 0xFFFF0000] - 0xFFFFFF00);
            pc += 3;
            cycles += 16;
        break;

        case 0xFB: // EI (Enables Interupts)
            MEMbitbuffer = memory[0xFFFF];
            MEMbitbuffer[0] = 1;
            MEMbitbuffer[1] = 1;
            MEMbitbuffer[2] = 1;
            MEMbitbuffer[3] = 1;
            MEMbitbuffer[4] = 1;
            memory[0xFFFF] = MEMbitbuffer.to_ulong();
            interruptEnable = true;
            cycles += 4;
            pc++;
        break;

        case 0xFE: // Flag Checked
            tem = af[0] - memory[pc + 1];
            Fbitbuffer = af[1];
            if(tem == 0x00)
            {
                Fbitbuffer[7] = 1;
                Fbitbuffer[6] = 1;
                Fbitbuffer[5] = halfcarrycheck(af[0],tem);
                Fbitbuffer[4] = negativeoverflowcheck(af[0],tem);
            }
            if(tem != 0x00)
            {
                Fbitbuffer[7] = 0;
                Fbitbuffer[6] = 1;
                Fbitbuffer[5] = halfcarrycheck(af[0],tem);
                Fbitbuffer[4] = negativeoverflowcheck(af[0],tem);
            }
            af[1] = Fbitbuffer.to_ulong();
            cycles += 8;
            pc += 2;
        break;

        case 0xFF: // Flag Checked
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
            if (opcode != 0x27)
            {
                printf("\nThe Emulated software has encountered an Invalid Opcode.\nOpcode: 0x%X\nThe Program will now Close.",opcode);
                goto invalid_opcode_jump2;
            }
            if (opcode == 0xCB)
            {
                printf("\nIf you are reading this message, I somehow messed up.  Let me know if you see it.");
            }
            printf("\nAn error has Occured\nUnknown Opcode: 0x%X", opcode);
            invalid_opcode_jump2:
            printf("\nProgram Counter: 0x%X\n", pc);
            printf("Stack Pointer: 0x%X%X\n", sp[0], sp[1]);
            printf("Cycles: %i\n", cycles);
            printf("Please see errorlog.txt for more details.\n");
            printf("Please see memdump for a full Gameboy RAM Dump.\n");
            if(sdl_wanted == true)
            {
                SDL_DestroyWindow(AGBE_window);
                SDL_Quit();
            }
            close_program = true;
            mem_dump = fopen ("log/memdump", "w+");
            fwrite (memory , sizeof(char), sizeof(memory), mem_dump);
            fclose (mem_dump);
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
    memory[0xFF01] = 0x00;
    memory[0xFF02] = 0x7E;
    memory[0xFF03] = 0xFF;
    memory[0xFF04] = 0xAB;
    memory[0xFF05] = 0x00;
    memory[0xFF06] = 0x00;
    memory[0xFF07] = 0xF8;
    memory[0xFF08] = 0xFF;
    memory[0xFF09] = 0xFF;
    memory[0xFF0A] = 0xFF;
    memory[0xFF0B] = 0xFF;
    memory[0xFF0C] = 0xFF;
    memory[0xFF0D] = 0xFF;
    memory[0xFF0E] = 0xFF;
    memory[0xFF0F] = 0xE1;
    memory[0xFF10] = 0x80;
    memory[0xFF11] = 0xBF;
    memory[0xFF12] = 0xF3;
    memory[0xFF13] = 0xFF;
    memory[0xFF14] = 0xBF;
    memory[0xFF15] = 0xFF;
    memory[0xFF16] = 0x3F;
    memory[0xFF17] = 0x00;
    memory[0xFF18] = 0xFF;
    memory[0xFF19] = 0xBF;
    memory[0xFF1A] = 0x7F;
    memory[0xFF1B] = 0xFF;
    memory[0xFF1C] = 0x9F;
    memory[0xFF1D] = 0xFF;
    memory[0xFF1E] = 0xBF;
    memory[0xFF1F] = 0xFF;
    memory[0xFF20] = 0xFF;
    memory[0xFF21] = 0x00;
    memory[0xFF22] = 0x00;
    memory[0xFF23] = 0xBF;
    memory[0xFF24] = 0x77;
    memory[0xFF25] = 0xF3;
    memory[0xFF26] = 0xF1;
    memory[0xFF27] = 0xFF;
    memory[0xFF28] = 0xFF;
    memory[0xFF29] = 0xFF;
    memory[0xFF2A] = 0xFF;
    memory[0xFF2B] = 0xFF;
    memory[0xFF2C] = 0xFF;
    memory[0xFF2D] = 0xFF;
    memory[0xFF2E] = 0xFF;
    memory[0xFF2F] = 0xFF;
    memory[0xFF30] = 0x30;
    memory[0xFF31] = 0xEF;
    memory[0xFF32] = 0x88;
    memory[0xFF33] = 0x27;
    memory[0xFF34] = 0x0F;
    memory[0xFF35] = 0x6D;
    memory[0xFF36] = 0x94;
    memory[0xFF37] = 0xA6;
    memory[0xFF38] = 0x41;
    memory[0xFF39] = 0xFE;
    memory[0xFF3A] = 0x03;
    memory[0xFF3B] = 0x1B;
    memory[0xFF3C] = 0xE2;
    memory[0xFF3D] = 0x77;
    memory[0xFF3E] = 0x49;
    memory[0xFF3F] = 0xFF;
    memory[0xFF40] = 0x91;
    memory[0xFF41] = 0x00;
    memory[0xFF42] = 0x00;
    memory[0xFF43] = 0x00;
    memory[0xFF44] = 0x91;
    memory[0xFF45] = 0x00;
    memory[0xFF07] = 0xFF;
    memory[0xFF47] = 0xFC;
    memory[0xFF48] = 0xFF;
    memory[0xFF49] = 0xFF;
    memory[0xFF4A] = 0x00;
    memory[0xFF4B] = 0x00;
    memory[0xFF4C] = 0xFF;
    memory[0xFF4D] = 0xFF;
    memory[0xFF4E] = 0xFF;
    memory[0xFF4F] = 0xFF;
    memory[0xFF50] = 0xFF;
    memory[0xFF51] = 0xFF;
    memory[0xFF52] = 0xFF;
    memory[0xFF53] = 0xFF;
    memory[0xFF54] = 0xFF;
    memory[0xFF55] = 0xFF;
    memory[0xFF56] = 0xFF;
    memory[0xFF57] = 0xFF;
    memory[0xFF58] = 0xFF;
    memory[0xFF59] = 0xFF;
    memory[0xFF5A] = 0xFF;
    memory[0xFF5B] = 0xFF;
    memory[0xFF5C] = 0xFF;
    memory[0xFF5D] = 0xFF;
    memory[0xFF5E] = 0xFF;
    memory[0xFF5F] = 0xFF;
    memory[0xFF60] = 0xFF;
    memory[0xFF61] = 0xFF;
    memory[0xFF62] = 0xFF;
    memory[0xFF63] = 0xFF;
    memory[0xFF64] = 0xFF;
    memory[0xFF65] = 0xFF;
    memory[0xFF66] = 0xFF;
    memory[0xFF67] = 0xFF;
    memory[0xFF68] = 0xFF;
    memory[0xFF69] = 0xFF;
    memory[0xFF6A] = 0xFF;
    memory[0xFF6B] = 0xFF;
    memory[0xFF6C] = 0xFF;
    memory[0xFF6D] = 0xFF;
    memory[0xFF6E] = 0xFF;
    memory[0xFF6F] = 0xFF;
    memory[0xFF70] = 0xFF;
    memory[0xFF71] = 0xFF;
    memory[0xFF72] = 0xFF;
    memory[0xFF73] = 0xFF;
    memory[0xFF74] = 0xFF;
    memory[0xFF75] = 0xFF;
    memory[0xFF76] = 0xFF;
    memory[0xFF77] = 0xFF;
    memory[0xFF78] = 0xFF;
    memory[0xFF79] = 0xFF;
    memory[0xFF7A] = 0xFF;
    memory[0xFF7B] = 0xFF;
    memory[0xFF7C] = 0xFF;
    memory[0xFF7D] = 0xFF;
    memory[0xFF7E] = 0xFF;
    memory[0xFF7F] = 0xFF;
    memory[0xFFCE] = 0x00;
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
        if(debugmeminit >= 0x10000)
        {
            memory[debugmeminit] = 0xFF;
        }
        if(debugmeminit < 0x10000)
        {
            memory[debugmeminit] = 0x00;
        }
        goto debug_mem_init_again;
    }
    if(debugmeminit == 0x10000)
    {

    }
}
