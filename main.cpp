#include <chrono>
#include <ctime>
#include "SDL_utils.h"
#include "PlayGround.h"
#include "Target.h"

using namespace std;

void renderGameStart1(SDL_Renderer* renderer) {
    SDL_Texture* texture = NULL;
    SDL_Rect dstrect;

    texture = loadTexture("images/Background.png", renderer);
    SDL_RenderCopy(renderer, texture, NULL, NULL);
    SDL_DestroyTexture(texture);

    texture = loadTexture("images/Logo.png", renderer);
    dstrect.x = 170; dstrect.y = 20; dstrect.w = 561; dstrect.h = 411;
    SDL_RenderCopy(renderer, texture, NULL, &dstrect);
    SDL_DestroyTexture(texture);

    texture = loadTexture("images/Play1.png", renderer);
    dstrect.x = 300; dstrect.y = 400; dstrect.w = 300; dstrect.h = 300;
    SDL_RenderCopy(renderer, texture, NULL, &dstrect);
    SDL_DestroyTexture(texture);

    texture = loadTexture("images/button1.png", renderer);
    dstrect.x = 20; dstrect.y = 510; dstrect.w = 250; dstrect.h = 100;
    SDL_RenderCopy(renderer, texture, NULL, &dstrect);
    SDL_DestroyTexture(texture);

    texture = loadTexture("images/button2.png", renderer);
    dstrect.x = 660; dstrect.y = 510; dstrect.w = 150; dstrect.h = 100;
    SDL_RenderCopy(renderer, texture, NULL, &dstrect);
    SDL_DestroyTexture(texture);

    SDL_RenderPresent(renderer);
    SDL_Delay(100);
}

void renderGameStart2(SDL_Renderer* renderer) {
    SDL_Texture* texture = NULL;
    SDL_Rect dstrect;

    texture = loadTexture("images/Background.png", renderer);
    SDL_RenderCopy(renderer, texture, NULL, NULL);
    SDL_DestroyTexture(texture);

    texture = loadTexture("images/Logo.png", renderer);
    dstrect.x = 170; dstrect.y = 20; dstrect.w = 561; dstrect.h = 411;
    SDL_RenderCopy(renderer, texture, NULL, &dstrect);
    SDL_DestroyTexture(texture);

    texture = loadTexture("images/Play2.png", renderer);
    dstrect.x = 275; dstrect.y = 375; dstrect.w = 350; dstrect.h = 350;
    SDL_RenderCopy(renderer, texture, NULL, &dstrect);
    SDL_DestroyTexture(texture);

    texture = loadTexture("images/button1.png", renderer);
    dstrect.x = 20; dstrect.y = 510; dstrect.w = 250; dstrect.h = 100;
    SDL_RenderCopy(renderer, texture, NULL, &dstrect);
    SDL_DestroyTexture(texture);

    texture = loadTexture("images/button2.png", renderer);
    dstrect.x = 660; dstrect.y = 510; dstrect.w = 150; dstrect.h = 100;
    SDL_RenderCopy(renderer, texture, NULL, &dstrect);
    SDL_DestroyTexture(texture);

    SDL_RenderPresent(renderer);
    SDL_Delay(100);
}

void renderGameOver(SDL_Renderer* renderer, int &score) {
    TTF_Font * font = NULL; 
	SDL_Surface * surface = NULL;
    SDL_Texture* texture = NULL;
    SDL_Rect srcrect;
    SDL_Rect dstrect;

    texture = loadTexture("images/Background.png", renderer);
    SDL_RenderCopy(renderer, texture, NULL, NULL );
    SDL_DestroyTexture(texture);

    texture = loadTexture("images/Logo.png", renderer);
    dstrect.x = 170; dstrect.y = -40; dstrect.w = 561; dstrect.h = 411;
    SDL_RenderCopy(renderer, texture, NULL, &dstrect);
    SDL_DestroyTexture(texture);

    dstrect.x = 200; dstrect.y = 300; dstrect.w = 500; dstrect.h = 300;
    texture = loadTexture("images/score2.png", renderer);
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

void drawGems(SDL_Renderer* renderer, PlayGround &playGround, int i, int j) {
    SDL_Texture* texture = NULL;
    SDL_Rect dstrect;
    switch(playGround.getGem(i, j)) {
    case 1:
        if (playGround.getBomGem(i, j) < 0) {
            texture = loadTexture("images/1.png", renderer);
        } else {
            texture = loadTexture("images/01.webp", renderer);
        }
        break;
    case 2:
        if (playGround.getBomGem(i, j) < 0) {
            texture = loadTexture("images/2.png", renderer);
        } else {
            texture = loadTexture("images/02.webp", renderer);
        }
        break;
    case 3:
        if (playGround.getBomGem(i, j) < 0) {
            texture = loadTexture("images/3.png", renderer);
        } else {
            texture = loadTexture("images/03.webp", renderer);
        }
        break;
    case 4:
        if (playGround.getBomGem(i, j) < 0) {
            texture = loadTexture("images/4.png", renderer);
        } else {
            texture = loadTexture("images/04.webp", renderer);
        }
        break;
    case 5:
        if (playGround.getBomGem(i, j) < 0) {
            texture = loadTexture("images/5.png", renderer);
        } else {
            texture = loadTexture("images/05.webp", renderer);
        }
        break;
    case 6:
        if (playGround.getBomGem(i, j) < 0) {
            texture = loadTexture("images/6.png", renderer);
        } else {
            texture = loadTexture("images/06.webp", renderer);
        }
        break;
    case 7:
        if (playGround.getBomGem(i, j) < 0) {
            texture = loadTexture("images/7.png", renderer);
        } else {
            texture = loadTexture("images/07.webp", renderer);
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

void drawTime(SDL_Renderer* renderer, PlayGround &playGround) {
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

void drawTarget1(SDL_Renderer* renderer, Target &target) {
    SDL_Rect srcrect;
    SDL_Rect dstrect;
    SDL_Texture* texture = NULL;
    srcrect.x = 0; srcrect.y = 0; srcrect.w = 100; srcrect.h = 100;
    dstrect.x = 300 + (target.y)*50; dstrect.y = 100 + (target.x)*50; dstrect.w = 50; dstrect.h = 50;
    texture = loadTexture("images/target1.png", renderer);
    SDL_RenderCopy( renderer, texture, &srcrect, &dstrect );
    SDL_DestroyTexture(texture);
}

void drawTarget2(SDL_Renderer* renderer, Target &target) {
    SDL_Rect srcrect;
    SDL_Rect dstrect;
    SDL_Texture* texture = NULL;
    srcrect.x = 0; srcrect.y = 0; srcrect.w = 100; srcrect.h = 100;
    dstrect.x = 300 + (target.y)*50; dstrect.y = 100 + (target.x)*50; dstrect.w = 50; dstrect.h = 50;
    texture = loadTexture("images/target2.png", renderer);
    SDL_RenderCopy( renderer, texture, &srcrect, &dstrect );
    SDL_DestroyTexture(texture);
}

void drawScore(SDL_Renderer* renderer, int &score) {
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

void renderGamePlay(SDL_Renderer* renderer, PlayGround& playGround, Target &target, int &score) {
    SDL_Texture* texture = NULL;
    SDL_Rect dstrect;
    int gem;

    texture = loadTexture("images/Background.png", renderer);
    SDL_RenderCopy(renderer, texture, NULL, NULL );
    SDL_DestroyTexture(texture);

    dstrect.x = 290; dstrect.y = 90; dstrect.w = 520; dstrect.h = 520;
    texture = loadTexture("images/board.png", renderer);
    SDL_RenderCopy(renderer, texture, NULL, &dstrect ); 
    SDL_DestroyTexture(texture);

    dstrect.x = 40; dstrect.y = 200; dstrect.w = 205; dstrect.h = 303;
    texture = loadTexture("images/score1.png", renderer);
    SDL_RenderCopy( renderer, texture, NULL, &dstrect ); 
    SDL_DestroyTexture(texture);

    drawScore(renderer, score);
    for (int i = 0; i < 10; i++)
        for (int j = 0; j < 10; j++) {
            drawGems( renderer, playGround, i, j);
        }
    drawTime(renderer, playGround);
    drawTarget1( renderer, target);
    SDL_RenderPresent(renderer);
}

void moveTarget(SDL_Renderer* renderer, PlayGround& playGround, Target &target, SDL_Event &event2,int &score, bool &running) {
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
                    renderGamePlay(renderer, playGround, target, score);
                }
                break;
            case SDLK_RIGHT:
                if (target.y < 9) {
                    target.right();
                    Mix_PlayChannel(-1, chunk, 0);
                    renderGamePlay(renderer, playGround, target, score);
                }
                break;
            case SDLK_UP:
                if (target.x > 0) {
                    target.up();
                    Mix_PlayChannel(-1, chunk, 0);
                    renderGamePlay(renderer, playGround, target, score);
                }
                break;
            case SDLK_DOWN:
                if (target.x < 9) {
                    target.down();
                    Mix_PlayChannel(-1, chunk, 0);
                    renderGamePlay(renderer, playGround, target, score);
                }
                break;
            case SDLK_SPACE:
                Mix_PlayChannel(-1, chunk, 0);
                drawTarget2(renderer, target);
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
                            drawTarget1(renderer, target);
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

void fallingGems(SDL_Renderer* renderer, PlayGround& playGround, Target &target, int &score, int &loop) {
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
            renderGamePlay(renderer, playGround, target, score);
        }
    }
}

void update(int &score, int &loop, bool &correct, SDL_Event &event, SDL_Renderer* renderer, PlayGround& playGround, Target &target) {
    Mix_Chunk* chunk = NULL;
    playGround.resetBoardCheck();
    playGround.findGems(correct);
    if (correct) {
        chunk = Mix_LoadWAV("sounds/click3.wav");
        Mix_PlayChannel(-1, chunk, 0);
        playGround.deleteGems();
        renderGamePlay(renderer, playGround, target, score);
        SDL_Delay(300);
        fallingGems(renderer, playGround, target, score, loop);
    } else if (loop == 1) {
        chunk = Mix_LoadWAV("sounds/click2.wav");
        Mix_PlayChannel(-1, chunk, 0);
        returnTarget(playGround, target, event);
        renderGamePlay(renderer, playGround, target, score);
    }
}

int main(int argc, char** argv) {
    srand(time(0));
    SDL_Window *window;
    SDL_Renderer *renderer;
    Mix_Chunk* chunk = NULL;
    Mix_Music* music = NULL;
    initSDL(window, renderer);
    bool running = true;
    while(running) {
        PlayGround playGround;
        Target target(0,0);
        bool win = false;
        int score = 0, turn = 0;

        music = Mix_LoadMUS("sounds/background_music1.mp3");
        Mix_PlayMusic(music, -1);
        renderGameStart1(renderer);

        continueGame(running);
        if (!running) break;

        renderGameStart2(renderer);
        renderGameStart1(renderer);
        Mix_HaltMusic();
        music = Mix_LoadMUS("sounds/background_music2.mp3");
        Mix_PlayMusic(music, -1);

        renderGamePlay(renderer, playGround, target, score);
        while (!win) {
            SDL_Event event;
            moveTarget(renderer, playGround, target, event, score, running);
            if (!running) break;
            renderGamePlay(renderer, playGround, target, score);
            SDL_Delay(100);
            bool correct = true;
            int loop = 0;
            while (correct) {
                loop++;
                correct = false;
                update(score, loop, correct, event, renderer, playGround, target);
            }
            if (loop > 1) {
                turn++;
                win = (playGround.explode());
                playGround.addNewBomGem(turn);
                renderGamePlay(renderer, playGround, target, score);
            }
        }
        if (!running) break;
        renderGameOver(renderer, score);
        Mix_HaltMusic();
        music = Mix_LoadMUS("sounds/background_music3.mp3");
        Mix_PlayMusic(music, -1);
        continueGame(running);
        Mix_HaltMusic();
    }
    quitSDL(window, renderer);
    return 0;
}