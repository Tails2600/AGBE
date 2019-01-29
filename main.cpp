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
    //window.setFramerateLimit(60);
    char filename[20];
    cout<<"Welcome to AGBE!"<<endl<<"Enter Rom Name: ";
    cin>>filename;

    cout<<"Loading "<<filename<<" please wait..."<<endl;

    FILE* rom = fopen(filename, "rb");
        if (rom == NULL){
            std::cerr<<"Failed to open ROM"<<std::endl;
            return false;
        }
    //std::cerr<<"Rom successfully opened."<<std::endl;

    fseek(rom, 0, SEEK_END);
    long rom_size = ftell(rom);
    rewind(rom);
    //std::cerr<<"End of Rom Successfully found."<<std::endl;

    char* rom_buffer = (char*) malloc(sizeof(char) * rom_size);
        if (rom_buffer == NULL){
            std::cerr<<"Failed to allocate memory for ROM"<<std::endl;
            return false;
        }
    //std::cerr<<"Memory for rom was successfully allocated."<<std::endl;

    size_t result = fread(rom_buffer, sizeof(char), (size_t)rom_size, rom);
        if(result != rom_size){
        std::cerr<<"Failed to Read Rom"<<std::endl;
        return false;
        }
    //std::cerr<<"Rom successfully read."<<std::endl;

    if ((32769) > rom_size){
            std::cerr<<"Loading Rom into memory"<<std::endl;
            for (int i = 0; i < rom_size; ++i) {
                memory[i + 0] = (uint8_t)rom_buffer[i];   // Load into memory starting
                                                        // at 0x0000 (=0)
                //printf("Rom byte %i successsfully loaded into memory\n", i);
            }
        }
    else {
        std::cerr << "ROM too large to fit in memory" << std::endl;
        return false;
    }

    fclose(rom);
    //std::cerr<<"Rom successfully closed."<<std::endl;
    free(rom_buffer);
    //std::cerr<<"Rom Buffer successfully freed"<<std::endl;
    std::cerr<<filename<<" was successfully loaded."<<std::endl;
    char optionslol;
    cout<<"Do you want Debugging printf statements? (y = yes, n = no): ";
    cin>>optionslol;
    if (optionslol == 'n')
    {
    debugging_enabled = false;
    goto donewithoptions;
    }
    if (optionslol == 'y')
    {
    debugging_enabled = true;
    }
    cout<<"Do you want Advanced Debugging? (Slow) (y = yes, n = no): ";
    cin>>optionslol;
    if (optionslol == 'n')
    {
    advanced_debugging_enabled = false;
    goto donewithoptions;
    }
    if (optionslol == 'y')
    {
    advanced_debugging_enabled = true;
    }
    //sf::RectangleShape rectangle(sf::Vector2f(900.f, 900.f));
    //rectangle.setFillColor(sf::Color(255, 255, 255));
    donewithoptions:
    gbPowerOn();

    //while (window.isOpen())
    //{
        test_for_sdl2:

        //while( SDL_PollEvent( &SDL_EVENT_HANDLING))
        //{

        handleRegisters();
        opcode = memory[pc];
        if(debugging_enabled == true)
        {
        printf("\nOpcode: 0x%X", opcode);
        }
        /*
        if(debugflagopcheck == true)
        {
        printf("\nDo This Opcode? :");
        cin>>choice;
        FILE * mem_dump;
        mem_dump = fopen ("memdump", "wb");
        fwrite (memory , sizeof(char), sizeof(memory), mem_dump);
        fclose (mem_dump);
        if(choice == 'n')
        {
        window.close();
        }
        }
        */
        doOpcode();
        // Note:  Remove these printf statments to speed up emulation
        if (advanced_debugging_enabled == true)
        {
        printf("\nA_flag: 0x%X", af[0]);
        printf("\nF_flag: 0x%X", af[1]);
        printf("\nB_flag: 0x%X", bc[0]);
        printf("\nC_flag: 0x%X", bc[1]);
        printf("\nD_flag: 0x%X", de[0]);
        printf("\nE_flag: 0x%X", de[1]);
        printf("\nH_flag: 0x%X", hl[0]);
        printf("\nL_flag: 0x%X", hl[1]);
        printf("\nPC_flag: 0x%X", pc);
        }
        //}
        while( SDL_PollEvent( &SDL_EVENT_HANDLING))
        {

        if (SDL_EVENT_HANDLING.type == SDL_QUIT)
        {
            goto iamdone;
        }
        else if (SDL_EVENT_HANDLING.type == SDL_KEYDOWN)
        {
            handle_controls();
        }


        }
        if(close_program == true)
        {
        goto iamdone;
        }


        goto test_for_sdl2;
        iamdone:
        SDL_DestroyWindow( AGBE_window );
        SDL_Quit();
        close_program = true;
        /*
        if(hl[0] == 0xCF && hl[1] == 0xFB)
        {
        window.close();
        }
        */
       // sf::Event event;
      //  while (window.pollEvent(event))
      //  {
      //      if (event.type == sf::Event::Closed)
        //        window.close();
      //  }

       // window.clear();
        //window.draw(rectangle);
        //window.display();


    return 0;
}
