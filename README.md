# AGBE (Another Game Boy Emulator)
This is a Gameboy Emulator that I'm working on as a side project.
This means that there may occasionally be gaps of no progress between commits.
## Running (Windows)
In the bin/Debug folder, there is a file called AGBE.exe  
Download that file and put it into a seperate folder. (This is also where you put your roms.)  
In order for it to run, you need 4 dll files.  
- libgcc_s_dw2-1.dll
- libgcc_s_sjlj-1.dll
- libstdc++-6.dll
- SDL2.dll  

Once you have these dll files, put them where you put AGBE.exe  
Next, go to the top of Windows Explorer where the directory is, and click in an empty space.  
Next, type cmd and press enter.  
This should bring up a Command Prompt located in the directory AGBE is in, if not then navigate there using the cd command.  
From there, type AGBE or AGBE.exe and this should run AGBE.  
Optionally, you can also put the name of the rom after AGBE.exe in the command prompt.  
This will load the rom for you.  
Also you can optionally create a folder named log where you put AGBE.  
This will give you log files.  
## Running (Linux)
In the bin/Debug folder, there is a file called AGBE. (NOT AGBE.exe)  
Download that and put it in a seperate folder.  
Put your roms there as well.  
From there, open a terminal and navigate to the place that you put AGBE and the roms.  
Type ./AGBE and press enter.  
Optionally, you can also put the name of the rom after ./AGBE in the command prompt.  
This will load the rom for you.  
Also you can optionally create a folder named log where you put AGBE.  
This will give you log files.  
## Notes
Note that the Windows build could possibly be more buggy than the Linux build.  
Not everything is implemented yet so don't expect everything to work correctly.  
If there is a problem, bug, or suggetion, put it into Issues.  
