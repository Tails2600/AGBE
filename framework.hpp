#include "cpu.h"

using namespace std;

int doGameboy(char** argv2)
{
    interruptEnable = false;
    helperforHacks = false;
    AGBE_version = "Alpha v0.2";
    mode0x8800 = false;
    printf("Would you like to enable SDL2? (y = yes, n = no)\nOption: ");
    cin>>choice;
    if (choice == 'y')
    {
        sdl_wanted = true;
    }
    if (choice == 'n')
    {
        sdl_wanted = false;
    }
    printf("Would you like a seperate VRAM Debugger Window?\nOption: ");
    cin>>choice;
    if (choice == 'y')
    {
        VRAMdebugwanted = true;
    }
    if (choice == 'n')
    {
        VRAMdebugwanted = false;
    }
    /*
    FILE* palletef = fopen("pallete.pal", "rb");
    if(palletef != NULL)
    {
        fread(palletec,12,1,palletef);
    fclose(palletef);
    white[0] = palletec[0];
    white[1] = palletec[1];
    white[2] = palletec[2];
    lightgrey[0] = palletec[3];
    lightgrey[1] = palletec[4];
    lightgrey[2] = palletec[5];
    darkgrey[0] = palletec[6];
    darkgrey[1] = palletec[7];
    darkgrey[2] = palletec[8];
    black[0] = palletec[9];
    black[1] = palletec[10];
    black[2] = palletec[11];
    color_black = {black[0],black[1],black[2],black[3]}; // Black (3)
    color_darkgrey = {darkgrey[0], darkgrey[1], darkgrey[2], darkgrey[3]}; // Dark Gray (2)
    color_lightgrey = {lightgrey[0], lightgrey[1], lightgrey[2], lightgrey[3]}; // Light Grey (1)
    color_white = {white[0],white[1],white[2],white[3]}; // White (0)
    }
    */
    init_memory();
    if (sdl_wanted == true)
    {

        if( SDL_Init( SDL_INIT_VIDEO ) < 0)
        {
            printf("SDL2 was Unable to Initialize!");
            return 1;
        }
        AGBE_window = SDL_CreateWindow("AGBE v0.2", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 320, 288, SDL_WINDOW_RESIZABLE);
        SDL_Surface * titleSurface = SDL_LoadBMP("AGBE.bmp");
        renderer = SDL_CreateRenderer(AGBE_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
        SDL_Texture * texture = SDL_CreateTextureFromSurface(renderer, titleSurface);
        //SDL_SetRenderDrawColor(renderer,0,0,255,255);

        //if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 )
        //{
        //printf( "SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError() );
        //}
//        SDL_OpenAudioDevice(NULL,0,&want,&have,SDL_AUDIO_ALLOW_FORMAT_CHANGE);
        SDL_RenderCopy(renderer, texture, NULL, NULL);
        SDL_RenderPresent(renderer);
        if (VRAMdebugwanted == true)
        {
            AGBE_VRAM_DEBUG = SDL_CreateWindow("VRAM", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 256, 384, SDL_WINDOW_RESIZABLE);
            VRAM_renderer = SDL_CreateRenderer(AGBE_VRAM_DEBUG, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
            SDL_SetRenderDrawColor(VRAM_renderer,0,0,0,255);
            SDL_RenderClear(VRAM_renderer);
            SDL_RenderPresent(VRAM_renderer);
            //if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 4096 ) == -1 )
            //{
            //    return false;
            //}
            //testingSound();
        }
    }
    welcometoagbe:
    //std::thread framerate (framerateHandler);
    printf("Welcome to AGBE ");
    cout<<AGBE_version<<"!"<<endl;
    if(argv2[1] == NULL)
    {
        char filename2temp[20];
        printf("Enter Rom Name: ");
        scanf("%s",filename2temp);
        filename = filename2temp;
    }
    if(argv2[1] != NULL)
    {
        printf("Rom Automatically detected from Command Line Arguments.\n");
        filename = argv2[1];
    }
    // Beginning of rom loading code
    FILE* rom = fopen(filename, "rb");
    if (rom == NULL)
    {
        printf("Rom not detected.");
        return 1;
    }
    fseek(rom,0,SEEK_END);
    rom_size = ftell(rom);
    rewind(rom);
    if (rom_size <= 32768)
    {
        printf("Rom Size is %i Bytes.\n",rom_size);
        fread(memory,rom_size,1,rom);
        fclose(rom);
    }
    if (rom_size > 32768)
    {
        printf("Rom Size is larger than 32768 Bytes!\nRom Size is %i Bytes!\nRom only partially loaded into RAM!\nRom likely uses MBC.\n",rom_size);
        tempROMfile = fopen(filename,"rb");
        fread(tempROM2,rom_size,1,tempROMfile);
        fclose(tempROMfile);
        fread(memory,0x8000,1,rom);
        fclose(rom);
        printf("Generating Checksum for MBC Stuff\n");
        MBCcountHelp = 2000;
        mbcAgain:
        memChecksuminit += memory[MBCcountHelp];
        MBCcountHelp++;
        if(MBCcountHelp == 0x4000)
        {
            goto doneCheck;
        }
        goto mbcAgain;
        doneCheck:
        printf("Checksum Generated.\n");
        detectMBC();
    }
    // End of rom loading Code.
    printf("Rom was loaded.\n");
    printf("Do you want Console Debugging? (y = yes, n = no)\nOption: "); // Does what it says.
    cin>>choice;
    if (choice == 'n')
    {
        debugging_enabled = false;
        goto donewithoptions1;
    }
    if (choice == 'y')
    {
        debugging_enabled = true;
    }
    printf("Do you want Advanced Console Debugging? (Step by Step) (y = yes, n = no)\nOption: "); // Does what it says.
    cin>>choice; // Get Input from User
    if (choice == 'n') // If choice is No
    {
        advanced_debugging_enabled = false; // Disables Advanced Debugging
    }
    if (choice == 'y') // If Choice is Yes
    {
        advanced_debugging_enabled = true; // Enables advanced debugging.
    }
    donewithoptions1: // Done with the First set of options.
    printf("Would you like a Log File? (Creates Massive Files!) (y = yes, n = no)\nOption: "); // Does what it says.
    cin>>choice; // Get input from User.
    if (choice == 'y') // If choice is yes...
    {
        log_file_made = true; // Log File IS made.
        gamelog = fopen ("log/log.txt", "w+"); // Makes the Log File.
    }
    if (choice == 'n') // If choice is no...
    {
        log_file_made = false; // Log file is NOT made.
    }
    printf("Do you want to use the the BIOS? (BIOS should be located at BIOS/GB.BIOS)\nOption: ");
    cin>>choice;
    if (choice == 'y')
    {
        doBios = true;
    }
    if (choice == 'n')
    {
        doBios = false;
    }
    printf("Do you want to use Game Specific Hacks?\nOption: ");
    cin>>choice;
    if (choice == 'y')
    {
        gameHacks = true;
    }
    if (choice == 'n')
    {
        gameHacks = false;
    }
    printf("Emulation Started.\n");
    gbPowerOn(); // Powers on the Gameboy/runs Boot Sequence (Unfinished)
    test_for_sdl2: // A goto statement for a SDL2 Loop (is not disabled by sdl_wanted = false.)
    handleRegisters(); // Handles registers
    if(debugging_enabled == true && advanced_debugging_enabled == false) // If the User wants debugging, this code will execute.
    {
        Fbitbuffer = af[1];
        printf("\nProgram Counter: 0x%X", pc);
        printf("\nCurrent Opcode: 0x%X", opcode);  // Does what it says.
        printf("\nNext Opcode: 0x%X", next_opcode);
        printf("\nA Register: 0x%X\n",af[0]);
        cout<<"F Register: "<<Fbitbuffer; // Does what it says.
    }
    opcode = memory[pc]; // Sets the next opcode to be executed
    previous_opcode = opcode; // A variable to keep track of the previous opcode that was executed.
    next_opcode = memory[pc + 0x01];
    lyhelp1 = cycles;
    prev_pc = pc;
    //printf("opcode: 0x%X\n",memory[pc]);
    spbuffer = sp[0] << 8 | sp[1];
    helpEA = 0x00000000;
    if(handleEI == true)
    {
        handleEI = false;
        interruptEnable = true;
    }
    doOpcode();
    //printf("done\n");
    //doOpcode(); // Runs 1 Opcode
    //handleSound();
    //handleHalt();
    //playSound();
    //handleMBC();
    //checkInterrupts();  // DOESN'T WORK
    handleInterupts2();  // Handles Interupts
    //joypadInterrupt();
    if(doBios = true)
    {
        if(pc == 0x0100)
        {
            FILE* rom = fopen(filename, "rb");
            fread(memory,rom_size,1,rom);
            fclose(rom);
        }
    }

    //yhandleSound();
    //memory[0xFF00] = 0xCF;
    //memory[0xFF80] = 0x80;
    lyhelp2 = cycles;
    //antibreakpoint(0x20CB);
    //breakpoint(0x1E7E);

    //if (cycles == 411512 && ime == true) //This setup is hacky and will be replaced in the future.
    //{
    //VBlank_Interupt_Needs_Done = true;
    //}
    renderThreadFrame();
    if (cycles % 10000 == 0x00)
    {
        MEMbitbuffer = memory[0xFF40];
        if(MEMbitbuffer[7] == 1)
        {
            SDL_RenderPresent(renderer);
        }
    }


    //if(lyhelp1 <= 456 * lyhelp3 && lyhelp2 >= 456 * lyhelp3)
    if(memory[0xFF02] == 0xFFFFFF81 && beforeFF01 != memory[0xFF01])
    {
        printf("%c",memory[0xFF01]);
    }
    beforeFF01 = memory[0xFF01];
    if(cycles % 456 == 0x00)
    {
        memory[0xFF44]++;
        lyhelp3++;
        if((memory[0xFF44] - 0xFFFFFF00) == 0x99)
        {
            memory[0xFF44] = 0x00;
        }
        MEMbitbuffer = memory[0xFF40];
    }
    MEMbitbuffer = memory[0xFFFF]; // I forgot what this does.
    if(cycles % 240 <= 0x03 && cycles % 240 >= 0x00)
    {
        memory[0xFF04]++; // Counter
        MEMbitbuffer = memory[0xFF40];
    }

    //memory[0xFF85]++; // Hack to get tetris to the Title Screen.
    //memory[0xFF41]++;
    //breakpoint(0x028A);
    if(gameHacks == true)
    {
        processHacks();
    }
    handle_controls();
    otherThings(); // Holds other random code
    if (advanced_debugging_enabled == true) // If the user wants Advanced Debugging, this code will execute.
    {
        advanAgain:
        spbuffer = sp[0] << 8 | sp[1];
        Fbitbuffer = af[1];
        printf("\nOpcode: 0x%X", opcode); // Does what it says.
        printf("\nA Register: 0x%X", af[0]); // Does what it says.
        cout<<endl<<"F Register: "<<Fbitbuffer; // Does what it says.
        printf("\nB Register: 0x%X", bc[0]); // Does what it says.
        printf("\nC Register: 0x%X", bc[1]); // Does what it says.
        printf("\nD Register: 0x%X", de[0]); // Does what it says.
        printf("\nE Register: 0x%X", de[1]); // Does what it says.
        printf("\nH Register: 0x%X", hl[0]); // Does what it says.
        printf("\nL Register: 0x%X", hl[1]); // Does what it says.
        printf("\nProgram Counter: 0x%X", pc); // Does what it says.
        printf("\nStack Pointer: 0x%X",spbuffer); // Does what it says.
        printf("\nJoypad Value: 0x%X", memory[0xFF00]); // Does what it says.
        printf("\nCPU Cycles: %i\n",cycles);
        printf("FF85: 0x%X\n",memory[0xFF85]);
        printf("Continue? (Y or N):"); // This option doesn't make a difference.  It's just here to make a sort of STEP Function.
        cin>>choice;
        if(choice == 'f')
        {
            advanced_debugging_enabled = false;
        }
        if(choice == 'm')
        {
            ofstream myfile("log/memdump");
            myfile.write((char *)memory,sizeof(memory));
            myfile.close();
            goto advanAgain;
        }
        if(choice == 'n')
        {
            printf("\nProgram Counter: 0x%X\n", pc);
            printf("Stack Pointer: 0x%X%X\n", sp[0], sp[1]);
            printf("Cycles: %i\n", cycles);
            printf("Please see errorlog.txt for more details.\n");
            printf("Please see memdump for a full Gameboy RAM Dump.\n");
            if(sdl_wanted == true)
            {
                SDL_DestroyWindow(AGBE_window);
                SDL_DestroyWindow(AGBE_VRAM_DEBUG);
                SDL_Quit();
            }
            close_program = true;

            //FILE * mem_dump;
            //mem_dump = fopen ("log/memdump", "w+");
            //fwrite (memory , sizeof(char), sizeof(memory), mem_dump);
            //fclose (mem_dump);
            ofstream myfile("log/memdump");
            myfile.write((char *)memory,sizeof(memory));
            myfile.close();
        }
    }
    if (log_file_made == true)  // If User wants a log file, then this will write stuff to it.
    {
        fprintf (gamelog, "OP %X\n", opcode); // Does what it says.
        fprintf (gamelog, "PC %X\n", pc); // Does what it says.
        fprintf (gamelog, "A %X\n", af[0]); // Does what it says.
        fprintf (gamelog, "F %X\n", af[1]); // Does what it says.
        fprintf (gamelog, "B %X\n", bc[0]); // Does what it says.
        fprintf (gamelog, "C %X\n", bc[1]); // Does what it says.
        fprintf (gamelog, "D %X\n", de[0]); // Does what it says.
        fprintf (gamelog, "E %X\n", de[1]); // Does what it says.
        fprintf (gamelog, "H %X\n", hl[0]); // Does what it says.
        fprintf (gamelog, "L %X\n", hl[1]); // Does what it says.
        fprintf (gamelog, "SP %X%X\n", sp[0], sp[1]); // Does what it says.
        fprintf (gamelog, "CYC %d\n", cycles); // Does what it says.
    }
    if (sdl_wanted == true)
    {
            while( SDL_PollEvent( &SDL_EVENT_HANDLING)) // While Event to handle Random Stuff
            {
                handle_controls3();
                if (SDL_EVENT_HANDLING.type == SDL_QUIT) // If the SDL Window is Closed, close the program.
                {
                    goto close_the_program; // Closes the Program
                }
                if (SDL_EVENT_HANDLING.type == SDL_KEYDOWN) // If a key is being pressed, handle controls.
                {   // Handle Controls
                    //handle_controls();
                    if(restartAGBE == true)
                    {
                    restartAGBE = false;
                    goto welcometoagbe;
                    }
                }
            }
    }
    if(close_program == true) // If close_program is true, close the program.
    {
        goto close_the_program; // Goes to the operation that closes the program
    }
    goto test_for_sdl2; // End of SDL2 Loop
    close_the_program: // Program Jumps here if close_program is set to true.
        printf("\nOpcode: 0x%X", opcode); // Does what it says.
        printf("\nA Register: 0x%X", af[0]); // Does what it says.
        cout<<endl<<"F Register: "<<Fbitbuffer; // Does what it says.
        printf("\nB Register: 0x%X", bc[0]); // Does what it says.
        printf("\nC Register: 0x%X", bc[1]); // Does what it says.
        printf("\nD Register: 0x%X", de[0]); // Does what it says.
        printf("\nE Register: 0x%X", de[1]); // Does what it says.
        printf("\nH Register: 0x%X", hl[0]); // Does what it says.
        printf("\nL Register: 0x%X", hl[1]); // Does what it says.
        printf("\nProgram Counter: 0x%X", pc); // Does what it says.
        printf("\nStack Pointer: 0x%X",spbuffer); // Does what it says.
    //printf("Stack Pointer: 0x%X%X\n", sp[0], sp[1]);
    //printf("Cycles: %i\n", cycles);
    //printf("Please see errorlog.txt for more details.\n");
    //printf("Please see memdump for a full Gameboy RAM Dump.\n");
    FILE * mem_dump;
    mem_dump = fopen ("log/memdump", "w+");
    fwrite (memory , sizeof(char), sizeof(memory), mem_dump);
    fclose (mem_dump);
    if (sdl_wanted == true)
    {
        SDL_DestroyWindow( AGBE_window ); // Destroys the SDL2 Window
        SDL_Quit(); // Quits SDL
    }
    close_program = true; // This serves no purpose, but i'm leaving it here for now.
    return 0; // return 0
}
