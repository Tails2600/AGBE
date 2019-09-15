#include "include.hpp"





int handleMBC()
{
    if(memory[0x0147] == 0x00) // If the rom doesn't use an MBC, we just skip this entire function to save lag.
    {
        return true;
    }
    // If the rom DOES use an MBC, run this code.
    mbcExist = true;
    tempROMfile = fopen(filename,"rb");
    fread(tempROM,0x4000,1,tempROMfile);
    fclose(tempROMfile);
    MBCcountHelp = 0;
    mbcAgain:
    if(memory[MBCcountHelp] == tempROM[MBCcountHelp])
    {
        MBCcountHelp++;
            if(MBCcountHelp == 0x4000) // If no change has been detected, end the function
            {
                return true;
            }
        goto mbcAgain;
    }
    if(memory[MBCcountHelp] != tempROM[MBCcountHelp] && MBCcountHelp > 0x1FFF && MBCcountHelp < 0x4000) // A Rom Bank Switch Occured
    {
        bankSwitch = memory[MBCcountHelp];
        printf("\nbankSwitch: 0x%X\n",bankSwitch);
            mem_dump = fopen ("log/memdump", "w+");
            fwrite (memory , sizeof(char), sizeof(memory), mem_dump);
            fclose (mem_dump);
            mem_dump = fopen ("log/memdumptemp", "w+");
            fwrite (tempROM , sizeof(char), sizeof(tempROM), mem_dump);
            fclose (mem_dump);
        memory[MBCcountHelp] = tempROM[MBCcountHelp];
        romLocate = bankSwitch * 0x4000;
        MBCcount2 = 0x4000;
        mbcAgain2:
        if(MBCcount2 == 0x8000) // End function because ROM BANK has been successfully been copied to RAM.
        {
            return true;
        }
        if(MBCcount2 != 0x8000) // Copy new Rom bank into RAM
        {
            tempROMfile = fopen(filename,"rb");
            fseek(tempROMfile,romLocate,SEEK_SET);
            fread(memory + 0x4000,0x4000,1,tempROMfile);
            fclose(tempROMfile);
            printf("madeithere\n");
            //memory[MBCcount2] = tempROM2[romLocate];
           // MBCcount2++;
           // romLocate++;
            return true;
            //goto mbcAgain2;
        }
    }
}
