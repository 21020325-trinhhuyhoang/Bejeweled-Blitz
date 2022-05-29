all:
	g++ -Isrc/include/SDL2 -Lsrc/lib main.cpp SDL_utils.cpp PlayGround.cpp -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer -o main