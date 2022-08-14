# `sdl2-config --cflags --libs`
# The below command is the output of the above command MINUS the -mwindows option
# This is so that I can see the console output;
all:
	g++ -o SDLMain -Wall main.cpp chip8.cpp -IC:\msys64\mingw64\include -Dmain=SDL_main -LC:\msys64\mingw64\lib -lSDL2main -lmingw32 -lSDL2main -lSDL2 
