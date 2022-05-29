#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <stdio.h>
#include <chrono>
#include <vector>
#include <string>
#include <cmath>
#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

#define SCREEN_WIDTH 900 
#define SCREEN_HEIGHT 700

typedef vector<vector<int>> Board;

class Painter {
    SDL_Window *window;
    SDL_Renderer *renderer;
public:
    Painter(SDL_Window *win, SDL_Renderer *ren) {
        window = win;
        renderer = ren;
    }
    SDL_Texture* loadTexture( string path ) {
        SDL_Texture* newTexture = NULL;
        SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
        if ( loadedSurface == NULL )
            cout << "Unable to load image " << path << " SDL_image Error: " << IMG_GetError() << endl;
        else {
            newTexture = SDL_CreateTextureFromSurface( renderer, loadedSurface );
            if( newTexture == NULL )
                cout << "Unable to create texture from " << path << " SDL Error: " << SDL_GetError() << endl;
            SDL_FreeSurface( loadedSurface );
        }
        return newTexture;
    }
};

struct Target {
    int x;
    int y;
public:
    Target(int _x = 0, int _y = 0) {
        x = _x;
        y = _y;
    }
    void up() { x--; }
    void down() { x++; }
    void left() { y--; }
    void right() { y++; }
};

class PlayGround {
    Board board;
    Board boardCheck;
    Board boardBom;
public:
    PlayGround()
        : board(10, vector<int>(10)), boardCheck(10, vector<int>(10)), boardBom(10, vector<int>(10))
    {
        newGame();
    }

    void addGem(int i, int j) {
        board[i][j] = (rand() % 7) + 1;
    }

    void addBomGem(int i, int j, int time) {
        boardBom[i][j] = time;
    }

    void addGems() {
        for (int i = 0; i < 10; i++)
        for (int j = 0; j < 10; j++) {
            addGem(i, j);
            addBomGem(i, j, -1);
        }
    }

    void addNewBomGem(int turn) {
        int j;
        if (turn < 20) {
        if (turn % 2 == 0) {
            do {
                j = (rand() % 8)+1;
            } while (boardBom[0][j] >= 0);
            addBomGem(0, j, 20 - turn/4);
        }
        } else {
            do {
                j = (rand() % 8)+1;
            } while (boardBom[0][j] >= 0);
            addBomGem(0, j, 15);
        }
    }
    
    void swapGem(int x1, int y1, int x2, int y2) {
        int temp = board[x1][y1];
        board[x1][y1] = board[x2][y2];
        board[x2][y2] = temp;
        temp = boardBom[x1][y1];
        boardBom[x1][y1] = boardBom[x2][y2];
        boardBom[x2][y2] = temp;
    }

    int getGem(int i, int j) {
        return board[i][j];
    }

    int getBomGem(int i, int j) {
        return boardBom[i][j];
    }

    void resetBoardCheck() {
    for (int i = 0; i < 10; i++)
        for (int j = 0; j < 10; j++) boardCheck[i][j] = 0;
    }

    bool explode() {
        for (int i = 0; i < 10; i++)
        for (int j = 0; j < 10; j++) {
            boardBom[i][j]--;
            if (boardBom[i][j] == 0) return true;
        }
        return false;
    }

    void findGems(bool &correct) {
        for (int i = 0; i < 10; i++)
        for (int j = 1; j < 9; j++)
            if (board[i][j] == board[i][j-1] && board[i][j] == board[i][j+1]) {
                boardCheck[i][j]++;
                boardCheck[i][j-1] += 2;
                boardCheck[i][j+1] += 2;
                correct = true;
            }
        for (int i = 1; i < 9; i++)
        for (int j = 0; j < 10; j++)
            if (board[i][j] == board[i-1][j] && board[i][j] == board[i+1][j]) {
                boardCheck[i][j]++;
                boardCheck[i-1][j] += 2;
                boardCheck[i+1][j] += 2;
                correct = true;
            }
    }

    void deleteGems() {
        for (int i = 0; i < 10; i++)
        for (int j = 0; j < 10; j++)
            switch (boardCheck[i][j]) {
            case 0:
                break;
            case 1: case 2:
                board[i][j] = 0;
                boardBom[i][j] = -1;
                break;
            case 3:
                for (int i0 = 0; i0 < 10; i0++) {
                    board[i0][j] = 0;
                    boardBom[i0][j] = -1;
                }
                for (int j0 = 0; j0 < 10; j0++) {
                    board[i][j0] = 0;
                    boardBom[i][j0] = -1;
                }
                break;
            case 4:
                for (int i0 = i-2; i0 <= i+2; i0++)
                for (int j0 = j-2; j0 <= j+2; j0++)
                    if ((i0 >= 0 && i0 < 10) && (j0 >=0 && j0 < 10)) {
                        board[i0][j0] = 0;
                        boardBom[i0][j0] = -1;
                }
                break;
            default:
                for (int i0 = i-2; i0 <= i+2; i0++)
                for (int j0 = 0; j0 < 10; j0++) 
                    if (i0 >= 0 && i0 < 10) {
                        board[i0][j0] = 0;
                        boardBom[i0][j0] = -1;
                    }
                for (int j0 = j-2; j0 <= j+2; j0++)
                for (int i0 = 0; i0 < 10; i0++) {
                    if (j0 >=0 && j0 < 10) {
                        board[i0][j0] = 0;
                        boardBom[i0][j0] = -1;
                    }
                }
                break;
            }
    }

    void newGame() {
        addGems();
        bool k = true;
        while (k) {
            k = false;
            resetBoardCheck();
            findGems(k);
            deleteGems();
            for (int i = 0; i < 10; i++)
            for (int j = 0; j < 10; j++)
                if (getGem(i, j) == 0) {
                    for (int i0 = i; i0 > 0; i0--) {
                        swapGem(i0, j, i0-1, j);
                    }
                    addGem(0, j);
                }
        }
        addNewBomGem(0);
    }

};

void initSDL(SDL_Window* &window, SDL_Renderer* &renderer) {
    if(SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("Error: SDL failed to initialize\nSDL Error: '%s'\n", SDL_GetError());
    }

    if(TTF_Init() < 0) {
		SDL_Log("%s", TTF_GetError());
	}

    if (Mix_OpenAudio (44100, MIX_DEFAULT_FORMAT, 2, 2048) == -1) {
	    printf ("% s", Mix_GetError ());
    }

    window = SDL_CreateWindow("Bejeweled Blitz", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
    if(!window) {
        printf("Error: Failed to open window\nSDL Error: '%s'\n", SDL_GetError());
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if(!renderer) {
        printf("Error: Failed to create renderer\nSDL Error: '%s'\n", SDL_GetError());
    }
}

void quitSDL(SDL_Window* win, SDL_Renderer* ren) {
    Mix_CloseAudio ();
    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);
    TTF_Quit ();
    SDL_Quit();
}

void renderGameStart1(SDL_Renderer* renderer, Painter &painter) {
    SDL_Texture* texture = NULL;
    SDL_Rect dstrect;

    texture = painter.loadTexture("images/Background.png");
    SDL_RenderCopy(renderer, texture, NULL, NULL);
    SDL_DestroyTexture(texture);

    texture = painter.loadTexture("images/Logo.png");
    dstrect.x = 170; dstrect.y = 20; dstrect.w = 561; dstrect.h = 411;
    SDL_RenderCopy(renderer, texture, NULL, &dstrect);
    SDL_DestroyTexture(texture);

    texture = painter.loadTexture("images/Play1.png");
    dstrect.x = 300; dstrect.y = 400; dstrect.w = 300; dstrect.h = 300;
    SDL_RenderCopy(renderer, texture, NULL, &dstrect);
    SDL_DestroyTexture(texture);

    texture = painter.loadTexture("images/button1.png");
    dstrect.x = 20; dstrect.y = 510; dstrect.w = 250; dstrect.h = 100;
    SDL_RenderCopy(renderer, texture, NULL, &dstrect);
    SDL_DestroyTexture(texture);

    texture = painter.loadTexture("images/button2.png");
    dstrect.x = 660; dstrect.y = 510; dstrect.w = 150; dstrect.h = 100;
    SDL_RenderCopy(renderer, texture, NULL, &dstrect);
    SDL_DestroyTexture(texture);

    SDL_RenderPresent(renderer);
    SDL_Delay(100);
}

void renderGameStart2(SDL_Renderer* renderer, Painter &painter) {
    SDL_Texture* texture = NULL;
    SDL_Rect dstrect;

    texture = painter.loadTexture("images/Background.png");
    SDL_RenderCopy(renderer, texture, NULL, NULL);
    SDL_DestroyTexture(texture);

    texture = painter.loadTexture("images/Logo.png");
    dstrect.x = 170; dstrect.y = 20; dstrect.w = 561; dstrect.h = 411;
    SDL_RenderCopy(renderer, texture, NULL, &dstrect);
    SDL_DestroyTexture(texture);

    texture = painter.loadTexture("images/Play2.png");
    dstrect.x = 275; dstrect.y = 375; dstrect.w = 350; dstrect.h = 350;
    SDL_RenderCopy(renderer, texture, NULL, &dstrect);
    SDL_DestroyTexture(texture);

    texture = painter.loadTexture("images/button1.png");
    dstrect.x = 20; dstrect.y = 510; dstrect.w = 250; dstrect.h = 100;
    SDL_RenderCopy(renderer, texture, NULL, &dstrect);
    SDL_DestroyTexture(texture);

    texture = painter.loadTexture("images/button2.png");
    dstrect.x = 660; dstrect.y = 510; dstrect.w = 150; dstrect.h = 100;
    SDL_RenderCopy(renderer, texture, NULL, &dstrect);
    SDL_DestroyTexture(texture);

    SDL_RenderPresent(renderer);
    SDL_Delay(100);
}

void renderGameOver(SDL_Renderer* renderer,Painter &painter, int &score) {
    TTF_Font * font = NULL; 
	SDL_Surface * surface = NULL;
    SDL_Texture* texture = NULL;
    SDL_Rect srcrect;
    SDL_Rect dstrect;

    texture = painter.loadTexture("images/Background.png");
    SDL_RenderCopy(renderer, texture, NULL, NULL );
    SDL_DestroyTexture(texture);

    texture = painter.loadTexture("images/Logo.png");
    dstrect.x = 170; dstrect.y = -40; dstrect.w = 561; dstrect.h = 411;
    SDL_RenderCopy(renderer, texture, NULL, &dstrect);
    SDL_DestroyTexture(texture);

    dstrect.x = 200; dstrect.y = 300; dstrect.w = 500; dstrect.h = 300;
    texture = painter.loadTexture("images/score2.png");
    SDL_RenderCopy( renderer, texture, NULL, &dstrect ); 
    SDL_DestroyTexture(texture);

    font = TTF_OpenFont("fonts/1.ttf", 70);
	SDL_Color fg = {255, 100, 0};
    string text = to_string(score);
	surface = TTF_RenderText_Solid(font, text.c_str(), fg);
	texture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);
    TTF_SizeText(font, text.c_str(), &srcrect.w, &srcrect.h);
    srcrect.x = 0; srcrect.y = 0;
    dstrect.x = 450 - srcrect.w/2; dstrect.y = 450; dstrect.w = srcrect.w; dstrect.h = srcrect.h;
    SDL_RenderCopy(renderer, texture, &srcrect, &dstrect);
    SDL_DestroyTexture(texture);

    SDL_RenderPresent(renderer);
}

void drawGems(SDL_Renderer* renderer, Painter &painter, PlayGround &playGround, int i, int j) {
    SDL_Texture* texture = NULL;
    SDL_Rect dstrect;
    switch(playGround.getGem(i, j)) {
    case 1:
        if (playGround.getBomGem(i, j) < 0) {
            texture = painter.loadTexture("images/1.png");
        } else {
            texture = painter.loadTexture("images/01.webp");
        }
        break;
    case 2:
        if (playGround.getBomGem(i, j) < 0) {
            texture = painter.loadTexture("images/2.png");
        } else {
            texture = painter.loadTexture("images/02.webp");
        }
        break;
    case 3:
        if (playGround.getBomGem(i, j) < 0) {
            texture = painter.loadTexture("images/3.png");
        } else {
            texture = painter.loadTexture("images/03.webp");
        }
        break;
    case 4:
        if (playGround.getBomGem(i, j) < 0) {
            texture = painter.loadTexture("images/4.png");
        } else {
            texture = painter.loadTexture("images/04.webp");
        }
        break;
    case 5:
        if (playGround.getBomGem(i, j) < 0) {
            texture = painter.loadTexture("images/5.png");
        } else {
            texture = painter.loadTexture("images/05.webp");
        }
        break;
    case 6:
        if (playGround.getBomGem(i, j) < 0) {
            texture = painter.loadTexture("images/6.png");
        } else {
            texture = painter.loadTexture("images/06.webp");
        }
        break;
    case 7:
        if (playGround.getBomGem(i, j) < 0) {
            texture = painter.loadTexture("images/7.png");
        } else {
            texture = painter.loadTexture("images/07.webp");
        }   
        break;   
    default:
        break;
    }
    if (playGround.getBomGem(i, j) < 0) {
        dstrect.x = 305 + j*50; dstrect.y = 105 + i*50; dstrect.w = 40; dstrect.h = 40;
    } else {
        dstrect.x = 298 + j*50; dstrect.y = 97 + i*50; dstrect.w = 55; dstrect.h = 55;
    }
    SDL_RenderCopy( renderer, texture, NULL, &dstrect );
    SDL_DestroyTexture(texture);
}

void drawTime(SDL_Renderer* renderer, Painter &painter, PlayGround &playGround) {
    TTF_Font * font = NULL; 
	SDL_Surface * surface = NULL; 
    SDL_Texture* texture = NULL;
    font = TTF_OpenFont("fonts/2.ttf", 26);
	SDL_Color fg = {0, 0, 0};
	SDL_Rect srcrect;
	SDL_Rect dstrect;
    for (int i = 0; i < 10; i++)
    for (int j = 0; j < 10; j++)
        if (playGround.getBomGem(i, j) >= 0) {
            string text = to_string(playGround.getBomGem(i, j));
	        surface = TTF_RenderText_Solid(font, text.c_str(), fg);
	        texture = SDL_CreateTextureFromSurface(renderer, surface);
	        SDL_FreeSurface(surface);
            TTF_SizeText(font, text.c_str(), &srcrect.w, &srcrect.h);
            srcrect.x = 0; srcrect.y = 0;
            dstrect.x = 325 + j*50 - srcrect.w/2; dstrect.y = 106 + i*50; dstrect.w = srcrect.w; dstrect.h = srcrect.h;
            SDL_RenderCopy(renderer, texture, &srcrect, &dstrect);
        }
    SDL_DestroyTexture(texture);
}

void drawTarget1(SDL_Renderer* renderer, Target &target, Painter &painter) {
    SDL_Rect srcrect;
    SDL_Rect dstrect;
    SDL_Texture* texture = NULL;
    srcrect.x = 0; srcrect.y = 0; srcrect.w = 100; srcrect.h = 100;
    dstrect.x = 300 + (target.y)*50; dstrect.y = 100 + (target.x)*50; dstrect.w = 50; dstrect.h = 50;
    texture = painter.loadTexture("images/target1.png");
    SDL_RenderCopy( renderer, texture, &srcrect, &dstrect );
    SDL_DestroyTexture(texture);
}

void drawTarget2(SDL_Renderer* renderer, Target &target, Painter &painter) {
    SDL_Rect srcrect;
    SDL_Rect dstrect;
    SDL_Texture* texture = NULL;
    srcrect.x = 0; srcrect.y = 0; srcrect.w = 100; srcrect.h = 100;
    dstrect.x = 300 + (target.y)*50; dstrect.y = 100 + (target.x)*50; dstrect.w = 50; dstrect.h = 50;
    texture = painter.loadTexture("images/target2.png");
    SDL_RenderCopy( renderer, texture, &srcrect, &dstrect );
    SDL_DestroyTexture(texture);
}

void drawScore(SDL_Renderer* renderer, Painter &painter, int &score) {
    TTF_Font * font = NULL; 
	SDL_Surface * surface = NULL; 
    SDL_Texture* texture = NULL;
    font = TTF_OpenFont("fonts/1.ttf", 55);
	SDL_Color fg = {255, 100, 0};
	string text = to_string(score);
	surface = TTF_RenderText_Solid(font, text.c_str(), fg);
	texture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);
	SDL_Rect srcrect;
	SDL_Rect dstrect;
    TTF_SizeText(font, text.c_str(), &srcrect.w, &srcrect.h);
    srcrect.x = 0; srcrect.y = 0;
    dstrect.x = 144 - srcrect.w/2; dstrect.y = 365; dstrect.w = srcrect.w; dstrect.h = srcrect.h;
    SDL_RenderCopy(renderer, texture, &srcrect, &dstrect);
    SDL_DestroyTexture(texture);
}

void renderGamePlay(SDL_Renderer* renderer, PlayGround& playGround, Target &target, Painter &painter, int &score) {
    SDL_Texture* texture = NULL;
    SDL_Rect dstrect;
    int gem;

    texture = painter.loadTexture("images/Background.png");
    SDL_RenderCopy(renderer, texture, NULL, NULL );
    SDL_DestroyTexture(texture);

    dstrect.x = 290; dstrect.y = 90; dstrect.w = 520; dstrect.h = 520;
    texture = painter.loadTexture("images/board.png");
    SDL_RenderCopy(renderer, texture, NULL, &dstrect ); 
    SDL_DestroyTexture(texture);

    dstrect.x = 40; dstrect.y = 200; dstrect.w = 205; dstrect.h = 303;
    texture = painter.loadTexture("images/score1.png");
    SDL_RenderCopy( renderer, texture, NULL, &dstrect ); 
    SDL_DestroyTexture(texture);

    drawScore(renderer, painter, score);
    for (int i = 0; i < 10; i++)
        for (int j = 0; j < 10; j++) {
            drawGems( renderer, painter, playGround, i, j);
        }
    drawTime(renderer, painter, playGround);
    drawTarget1( renderer, target, painter);
    SDL_RenderPresent(renderer);
}

void moveTarget(SDL_Renderer* renderer, PlayGround& playGround, Target &target, SDL_Event &event2, Painter &painter,int &score, bool &running) {
    SDL_Event event1;
    Mix_Chunk* chunk = NULL;
    chunk = Mix_LoadWAV("sounds/click1.wav"); 
    
    while (true) {
        if (SDL_WaitEvent(&event1)) switch(event1.type) {
        case SDL_QUIT:
            running = false;
            return;
        case SDL_KEYDOWN:
            switch(event1.key.keysym.sym) {
            case SDLK_LEFT:
                if (target.y > 0) {
                    target.left();
                    Mix_PlayChannel(-1, chunk, 0);
                    renderGamePlay(renderer, playGround, target, painter, score);
                }
                break;
            case SDLK_RIGHT:
                if (target.y < 9) {
                    target.right();
                    Mix_PlayChannel(-1, chunk, 0);
                    renderGamePlay(renderer, playGround, target, painter, score);
                }
                break;
            case SDLK_UP:
                if (target.x > 0) {
                    target.up();
                    Mix_PlayChannel(-1, chunk, 0);
                    renderGamePlay(renderer, playGround, target, painter, score);
                }
                break;
            case SDLK_DOWN:
                if (target.x < 9) {
                    target.down();
                    Mix_PlayChannel(-1, chunk, 0);
                    renderGamePlay(renderer, playGround, target, painter, score);
                }
                break;
            case SDLK_SPACE:
                Mix_PlayChannel(-1, chunk, 0);
                drawTarget2(renderer, target, painter);
                SDL_RenderPresent(renderer);
                Target target0 = target;
                bool k = true;
                while (k) {
                    if (SDL_WaitEvent(&event2)) switch(event2.type) {
                    case SDL_QUIT:
                        running = false;
                        return;
                    case SDL_KEYDOWN:
                        switch(event2.key.keysym.sym) {
                        case SDLK_LEFT:
                            if (target.y > 0) {
                                target.left();
                                playGround.swapGem(target.x, target.y, target0.x, target0.y);
                                return;
                            }
                            break;
                        case SDLK_RIGHT:
                            if (target.y < 9) {
                                target.right();
                                playGround.swapGem(target.x, target.y, target0.x, target0.y);
                                return;
                            }
                            break;
                        case SDLK_UP:
                            if (target.x > 0) {
                                target.up();
                                playGround.swapGem(target.x, target.y, target0.x, target0.y);
                                return;
                            }
                            break;
                        case SDLK_DOWN:
                            if (target.x < 9) {
                                target.down();
                                playGround.swapGem(target.x, target.y, target0.x, target0.y);
                                return;
                            }
                            break;
                        case SDLK_SPACE:
                            k = false;
                            Mix_PlayChannel(-1, chunk, 0);
                            drawTarget1(renderer, target, painter);
                            SDL_RenderPresent(renderer);
                            break;
                        }
                    }
                    SDL_Delay(10);
                }
                break;
            }
        }
        SDL_Delay(10);
    }
}

void continueGame(bool &running) {
    SDL_Event e;
    Mix_Chunk* chunk = NULL;
    chunk = Mix_LoadWAV("sounds/click3.wav"); 

    while (true) {
        if (SDL_WaitEvent(&e)) switch(e.type){
        case SDL_QUIT:
            running = false;
            return;
        case SDL_KEYDOWN:
            if(e.key.keysym.sym == SDLK_SPACE) {
                Mix_PlayChannel(-1, chunk, 0);
                return;
            }
            break;
        }
        SDL_Delay(10);
    }          
}

void returnTarget(PlayGround& playGround, Target &target, SDL_Event &event2) {
    Target target0 = target;
    switch(event2.key.keysym.sym){
    case SDLK_LEFT:
        target.right();
        break;
    case SDLK_RIGHT:
        target.left();
        break;
    case SDLK_UP:
        target.down();
        break;
    case SDLK_DOWN:
        target.up();
        break;
    default:
        break;
    }
    playGround.swapGem(target.x, target.y, target0.x, target0.y);
}

void fallingGems(SDL_Renderer* renderer, PlayGround& playGround, Target &target, Painter &painter, int &score, int &loop) {
    for (int i = 0; i < 10; i++){
        bool check = false;
        for (int j = 0; j < 10; j++)
            if (playGround.getGem(i, j) == 0) {
                check = true;
                score += loop;
                for (int i0 = i; i0 > 0; i0--) {
                    playGround.swapGem(i0, j, i0-1, j);
                }
                playGround.addGem(0, j);
            }
        if (check) {
            renderGamePlay(renderer, playGround, target, painter, score);
        }
    }
}

void update(int &score, int &loop, bool &correct, SDL_Event &event, SDL_Renderer* renderer, PlayGround& playGround, Target &target, Painter &painter) {
    Mix_Chunk* chunk = NULL;
    playGround.resetBoardCheck();
    playGround.findGems(correct);
    if (correct) {
        chunk = Mix_LoadWAV("sounds/click3.wav");
        Mix_PlayChannel(-1, chunk, 0);
        playGround.deleteGems();
        renderGamePlay(renderer, playGround, target, painter, score);
        SDL_Delay(300);
        fallingGems(renderer, playGround, target, painter, score, loop);
    } else if (loop == 1) {
        chunk = Mix_LoadWAV("sounds/click2.wav");
        Mix_PlayChannel(-1, chunk, 0);
        returnTarget(playGround, target, event);
        renderGamePlay(renderer, playGround, target, painter, score);
    }
}

int main(int argc, char** argv) {
    srand(time(0));
    SDL_Window *window;
    SDL_Renderer *renderer;
    Mix_Chunk* chunk = NULL;
    Mix_Music* music = NULL;
    initSDL(window, renderer);
    Painter painter(window, renderer);
    bool running = true;
    while(running) {
        PlayGround playGround;
        Target target(0,0);
        bool win = false;
        int score = 0, turn = 0;

        music = Mix_LoadMUS("sounds/background_music1.mp3");
        Mix_PlayMusic(music, -1);
        renderGameStart1(renderer, painter);

        continueGame(running);
        if (!running) break;

        renderGameStart2(renderer, painter);
        renderGameStart1(renderer, painter);
        Mix_HaltMusic();
        music = Mix_LoadMUS("sounds/background_music2.mp3");
        Mix_PlayMusic(music, -1);

        renderGamePlay(renderer, playGround, target, painter, score);
        while(!win) {
            SDL_Event event;
            moveTarget(renderer, playGround, target, event, painter, score, running);
            if (!running) break;
            renderGamePlay(renderer, playGround, target, painter, score);
            SDL_Delay(100);
            bool correct = true;
            int loop = 0;
            while (correct) {
                loop++;
                correct = false;
                update(score, loop, correct, event, renderer, playGround, target, painter);
            }
            if (loop > 1) {
                turn++;
                win = (playGround.explode());
                playGround.addNewBomGem(turn);
            }
        }
        if (!running) break;
        renderGameOver(renderer, painter, score);
        Mix_HaltMusic();
        music = Mix_LoadMUS("sounds/background_music3.mp3");
        Mix_PlayMusic(music, -1);
        continueGame(running);
        Mix_HaltMusic();
    }
    quitSDL(window, renderer);
    return 0;
}