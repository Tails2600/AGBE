#include "cpu.h"

using namespace std;

int main(int argc, char** argv)
{
    AGBE_version = 0.1;
    printf("Before we begin, do you want to enable SDL2? (y = yes, n = no)\nSDL2 is for Graphics and Input, which aren't implemented yet.\nOption: ");
    cin>>choice;
    if (choice == 'y')
    {
    sdl_wanted = true;
    goto beginbeforeinitmemory;
    }
    if (choice == 'n')
    {
    sdl_wanted = false;
    }
    beginbeforeinitmemory:
    init_memory();
    if (sdl_wanted == true)
    {
        if( SDL_Init( SDL_INIT_VIDEO ) < 0)
        {
        printf("SDL2 was Unable to Initialize!");
        return 1;
        }
        AGBE_window = SDL_CreateWindow("AGBE", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 160, 144, SDL_WINDOW_SHOWN);
        screenSurface = SDL_GetWindowSurface( AGBE_window );
        renderer = SDL_CreateRenderer(AGBE_window, -1, SDL_RENDERER_ACCELERATED);
        texture = SDL_CreateTexture(renderer,SDL_PIXELFORMAT_RGBA8888,SDL_TEXTUREACCESS_TARGET,160,144);
    }
    char *filename;
    printf("Welcome to AGBE!\n");
    if(argv[1] == NULL)
    {
    char filename2temp[20];
    printf("Enter Rom Name: ");
    scanf("%s",filename2temp);
    filename = filename2temp;
    }
    if(argv[1] != NULL)
    {
    printf("Rom Automatically detected from Command Line Arguments.\n");
    filename = argv[1];
    }
    // Beginning of rom loading code
    printf("Loading... Please Wait.\n");
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
    printf("Rom Size is %i Bytes.\nIt will be compatible with AGBE.\n",rom_size);
    }
    if (rom_size > 32768)
    {
    printf("Rom Size is larger than 32768 Bytes!\nRom Size is %i Bytes!\nRom is not compatible with AGBE.\nClosing Program.",rom_size);
    return 1;
    }
    fread(memory,rom_size,1,rom);
    fclose(rom);
    // End of rom loading Code.
    printf("Rom was Successfully loaded.\n");
    printf("Do you want Debugging printf statements? (y = yes, n = no)\nOption: "); // Does what it says.
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
    printf("Do you want Advanced Debugging? (Slow) (y = yes, n = no)\nOption: "); // Does what it says.
    cin>>choice; // Get Input from User
    if (choice == 'n') // If choice is No
    {
    advanced_debugging_enabled = false; // Disables Advanced Debugging
    goto donewithoptions1; // Does what it says.
    }
    if (choice == 'y') // If Choice is Yes
    {
    advanced_debugging_enabled = true; // Enables advanced debugging.
    }
    donewithoptions1: // Done with the First set of options.
    printf("Would you like a Log File?(Creates Massive Files!) (y = yes, n = no)\nOption: "); // Does what it says.
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
    gbPowerOn(); // Powers on the Gameboy/runs Boot Sequence (Unfinished)
        test_for_sdl2: // A goto statement for a SDL2 Loop (is not disabled by sdl_wanted = false.)
        handleRegisters(); // Handles registers
        opcode = memory[pc]; // Sets the next opcode to be executed
        if(debugging_enabled == true) // If the User wants debugging, this code will execute.
        {
        printf("\nPC: 0x%X", pc);
        printf("\nOpcode: 0x%X", opcode);  // Does what it says.
        printf("\nA: 0x%X",af[0]);
        }
        previous_opcode = opcode; // A variable to keep track of the previous opcode that was executed.
        next_opcode = memory[pc + 0x01];
        doOpcode(); // Runs 1 Opcode
        /*
        if (help0xC92 == 0x49)
        {
        advanced_debugging_enabled = true;
        }
        */
        if (cycles % 344 == 0) //This setup is hacky and will be replaced in the distant future.
        {
        memory[0xFF44]++;
        }
        if (cycles == 411512) //This setup is hacky and will be replaced in the distant future.
        {
        VBlank_Interupt_Needs_Done = true;
        }
        if(sdl_wanted == true) // Handles Rendering
        {
        if(pc == 0x036E)
        {
        RenderFrame(); // Renders a frame
        printf("main");
        }
        }
        handleInterupts();  // Handles Interupts
        if (advanced_debugging_enabled == true) // If the user wants Advanced Debugging, this code will execute.
        {
        printf("\nOpcode: 0x%X", opcode); // Does what it says.
        printf("\nA_flag: 0x%X", af[0]); // Does what it says.
        printf("\nF_flag: 0x%X", af[1]); // Does what it says.
        printf("\nB_flag: 0x%X", bc[0]); // Does what it says.
        printf("\nC_flag: 0x%X", bc[1]); // Does what it says.
        printf("\nD_flag: 0x%X", de[0]); // Does what it says.
        printf("\nE_flag: 0x%X", de[1]); // Does what it says.
        printf("\nH_flag: 0x%X", hl[0]); // Does what it says.
        printf("\nL_flag: 0x%X", hl[1]); // Does what it says.
        printf("\nPC_flag: 0x%X", pc); // Does what it says.
        printf("\nSP_flag: 0x%X%X", sp[0], sp[1]); // Does what it says.
        printf("\nMem_Joypad: 0x%X", memory[0xFF00]); // Does what it says.
        printf("\nCycles: %i\n",cycles);
        printf("\nContinue? (Y or N):"); // This option doesn't make a difference.  It's just here to make a sort of STEP Function.
        cin>>choice;
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
        SDL_Quit();
        }
        close_program = true;
        FILE * mem_dump;
        mem_dump = fopen ("log/memdump", "w+");
        fwrite (memory , sizeof(char), sizeof(memory), mem_dump);
        fclose (mem_dump);
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
            if (SDL_EVENT_HANDLING.type == SDL_QUIT) // If the SDL Window is Closed, close the program.
            {
                goto close_the_program; // Closes the Program
            }
            else if (SDL_EVENT_HANDLING.type == SDL_KEYDOWN) // If a key is being pressed, handle controls.
            {
                handle_controls(); // Handle Controls
            }
            }
        }
        if(close_program == true) // If close_program is true, close the program.
        {
        goto close_the_program; // Goes to the operation that closes the program
        }
        goto test_for_sdl2; // End of SDL2 Loop
        close_the_program: // Program Jumps here if close_program is set to true.
printf("\nProgram Counter: 0x%X\n", pc);
printf("Stack Pointer: 0x%X%X\n", sp[0], sp[1]);
printf("Cycles: %i\n", cycles);
printf("Please see errorlog.txt for more details.\n");
printf("Please see memdump for a full Gameboy RAM Dump.\n");
        if (sdl_wanted == true)
        {
        SDL_DestroyWindow( AGBE_window ); // Destroys the SDL2 Window
        SDL_Quit(); // Quits SDL
        }
        close_program = true; // This serves no purpose, but i'm leaving it here for now.
        return 0; // return 0
}
