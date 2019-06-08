#include "cpu.h"

using namespace std;

int main(int argc, char** argv)
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
    char *filename;
    cout<<"Welcome to AGBE!"<<endl;
    if(argv[1] == NULL)
    {
    char filename2temp[20];
    cout<<"Enter Rom Name: ";
    cin>>filename2temp;
    filename = filename2temp;
    }
    if(argv[1] != NULL)
    {
    cout<<"Rom Automatically detected from Command Line Arguments."<<endl;
    cout<<"Rom: "<<argv[1]<<endl;
    filename = argv[1];
    }
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
    std::cerr<<filename<<" was successfully loaded."<<std::endl; // Does what it says.
    cout<<"Do you want Debugging printf statements? (y = yes, n = no): "; // Does what it says.
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
    cout<<"Do you want Advanced Debugging? (Slow) (y = yes, n = no): "; // Does what it says.
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
    cout<<"Would you like a Log of all Opcodes, Jumps, etc...?(CAN CREATE MASSIVE FILES! USE AT OWN RISK!) (y = yes, n = no)"<<endl; // Does what it says.
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
        test_for_sdl2: // A goto statement for a SDL2 Loop
        handleRegisters(); // Handles registers
        opcode = memory[pc]; // Sets the next opcode to be executed
        if(debugging_enabled == true) // If the User wants debugging, this code will execute.
        {
        printf("\nOpcode: 0x%X", opcode);  // Does what it says.
        }
        previous_opcode = opcode; // A variable to keep track of the previous opcode that was executed.
        next_opcode = memory[pc + 0x01];
        doOpcode(); // Runs 1 Opcode
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
        printf("\nContinue? (Y or N):"); // This option doesn't make a difference.  It's just here to make a sort of STEP Function.
        cin>>choice;
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
        if(close_program == true) // If close_program is true, close the program.
        {
        goto close_the_program; // Goes to the operation that closes the program
        }
        goto test_for_sdl2; // End of SDL2 Loop
        close_the_program: // Program Jumps here if close_program is set to true.
        SDL_DestroyWindow( AGBE_window ); // Destroys the SDL2 Window
        SDL_Quit(); // Quits SDL
        close_program = true; // IDK why this is here but i'm leaving it here for now.
        return 0; // return 0
}
