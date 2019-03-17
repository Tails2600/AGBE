#include "cpu.h"

using namespace std;

int main()
{

    init_memory();

    if( SDL_Init( SDL_INIT_VIDEO ) < 0)
    {
    cout<<"SDL2 WAS UNABLE TO INITIALIZE!"<<endl;
    return 1;
    }
    AGBE_window = SDL_CreateWindow("AGBE", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 160, 144, SDL_WINDOW_SHOWN);
    screenSurface = SDL_GetWindowSurface( AGBE_window );
    SDL_Renderer* renderer;
    SDL_Texture* const texture = ::SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888,SDL_TEXTUREACCESS_STREAMING, 160, 144);
    char filename[50];
    cout<<"Welcome to AGBE!"<<endl<<"Enter Rom Name: ";
    cin>>filename;
    cout<<"Loading "<<filename<<" please wait..."<<endl;
    FILE* rom = fopen(filename, "rb");
        if (rom == NULL){
            std::cerr<<"Failed to open ROM"<<std::endl;
            return false;
        }
    fseek(rom, 0, SEEK_END);
    long rom_size = ftell(rom);
    rewind(rom);
    char* rom_buffer = (char*) malloc(sizeof(char) * rom_size);
        if (rom_buffer == NULL){
            std::cerr<<"Failed to allocate memory for ROM"<<std::endl;
            return false;
        }
    size_t result = fread(rom_buffer, sizeof(char), (size_t)rom_size, rom);
        if(result != rom_size){
        std::cerr<<"Failed to Read Rom"<<std::endl;
        return false;
        }
    if ((32769) > rom_size){
            std::cerr<<"Loading Rom into memory"<<std::endl;
            for (int i = 0; i < rom_size; ++i) {
                memory[i + 0] = (uint8_t)rom_buffer[i];   // Load into memory starting at 0x0000
            }
        }
    else {
        std::cerr << "ROM too large to fit in memory" << std::endl;
        return false;
    }
    fclose(rom);
    free(rom_buffer);
    std::cerr<<filename<<" was successfully loaded."<<std::endl;
    cout<<"Do you want Debugging printf statements? (y = yes, n = no): ";
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
    cout<<"Do you want Advanced Debugging? (Slow) (y = yes, n = no): ";
    cin>>choice;
    if (choice == 'n')
    {
    advanced_debugging_enabled = false;
    goto donewithoptions1;
    }
    if (choice == 'y')
    {
    advanced_debugging_enabled = true;
    }
    donewithoptions1:
    cout<<"Would you like a Log of all Opcodes, Jumps, etc...?(CAN CREATE MASSIVE FILES! USE AT OWN RISK!) (y = yes, n = no)"<<endl;
    cin>>choice;
    if (choice == 'y')
    {
    log_file_made = true;
    gamelog = fopen ("log/log.txt", "w+");
    }
    if (choice == 'n')
    {
    log_file_made = false;
    }
    gbPowerOn(); // Powers on the Gameboy/runs Boot Sequence (Unfinished)
        test_for_sdl2: // A goto statement for a SDL2 Loop
        handleRegisters(); // Handles registers
        opcode = memory[pc]; // Sets the next opcode to be executed
        if(debugging_enabled == true) // If the User wants debugging, this code will execute.
        {
        printf("\nOpcode: 0x%X", opcode);
        }
        previous_opcode = opcode; // A variable to keep track of the previous opcode that was executed.
        doOpcode(); // Runs 1 Opcode
        handleInterupts();  // Handles Interupts

        if (advanced_debugging_enabled == true) // If the user wants Advanced Debugging, this code will execute.
        {
        printf("\nOpcode: 0x%X", opcode);
        printf("\nA_flag: 0x%X", af[0]);
        printf("\nF_flag: 0x%X", af[1]);
        printf("\nB_flag: 0x%X", bc[0]);
        printf("\nC_flag: 0x%X", bc[1]);
        printf("\nD_flag: 0x%X", de[0]);
        printf("\nE_flag: 0x%X", de[1]);
        printf("\nH_flag: 0x%X", hl[0]);
        printf("\nL_flag: 0x%X", hl[1]);
        printf("\nPC_flag: 0x%X", pc);
        printf("\nContinue? (Y or N):");
        cin>>choice;
        }
        if (log_file_made == true)  // If User wants a log file, then this will write stuff to it.
        {
        fprintf (gamelog, "OP %X\n", opcode);
        fprintf (gamelog, "PC %X\n", pc);
        fprintf (gamelog, "A %X\n", af[0]);
        fprintf (gamelog, "F %X\n", af[1]);
        fprintf (gamelog, "B %X\n", bc[0]);
        fprintf (gamelog, "C %X\n", bc[1]);
        fprintf (gamelog, "D %X\n", de[0]);
        fprintf (gamelog, "E %X\n", de[1]);
        fprintf (gamelog, "H %X\n", hl[0]);
        fprintf (gamelog, "L %X\n", hl[1]);
        fprintf (gamelog, "SP %X%X\n", sp[0], sp[1]);
        fprintf (gamelog, "CYC %d\n", cycles);
        }
        while( SDL_PollEvent( &SDL_EVENT_HANDLING))
        {

        if (SDL_EVENT_HANDLING.type == SDL_QUIT)
        {
            goto close_the_program;
        }
        else if (SDL_EVENT_HANDLING.type == SDL_KEYDOWN)
        {
            handle_controls();
        }
        }
        if(close_program == true)
        {
        goto close_the_program;
        }
        goto test_for_sdl2;
        close_the_program:
        SDL_DestroyWindow( AGBE_window );
        SDL_Quit();
        close_program = true;
        return 0;
}
