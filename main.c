#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdlib.h>
#include <math.h>
/*#include <cmath>*/

#define SDL_MAIN_HANDLED
#define UNUSED(x) (void)x

typedef enum { false, true } bool;
typedef enum { menu, game, end } scene;
float previousDt;
float dt = 0.f;

struct Player {
    SDL_Rect rect;
    float speed;
};

void player_update(struct Player *player, int move, float dt) {
    if (player->rect.y < 190) { 
        player->rect.y += floorf(9.81 * dt);
    }
    player->rect.x += move * floorf(player->speed * dt);
}

void player_render(struct Player *player, SDL_Renderer* renderer) {
    SDL_SetRenderDrawColor(renderer, 200, 200, 10, 255);
    SDL_RenderFillRect(renderer, &player->rect);
}


int main(int argc, char* args[]) {
    if(SDL_Init(SDL_INIT_EVERYTHING) > 0) {
        printf("SDL ERROR: %s\n", SDL_GetError());
        exit(-1);
    }

    if (!IMG_Init(IMG_INIT_PNG)) {
        printf("SDL ERROR: %s\n", SDL_GetError());
        exit(-1);
    }

    UNUSED(argc);
    UNUSED(args);

    SDL_Window* window = SDL_CreateWindow("dr4", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 700, 400, SDL_WINDOW_SHOWN);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    SDL_Surface* icon = IMG_Load("./assets/dr4.png");
    SDL_SetWindowIcon(window, icon);
    struct Player player;
    player.speed = 5.0f;
    player.rect.x = player.rect.y = 0;
    player.rect.w = 50;
    player.rect.h = 70;
    bool gameOver = false;
    SDL_Event event;
    int playerX = 0;

    while(!gameOver) {
        SDL_PollEvent(&event);
        dt = (SDL_GetTicks() - previousDt) / 10;
        previousDt = SDL_GetTicks();
        player_update(&player, playerX, dt);

        if(event.type == SDL_QUIT) {
            gameOver = true;
        } else if (event.type == SDL_KEYDOWN) { 
            if (event.key.keysym.sym == SDLK_a) {
                playerX = -1;
            } else if (event.key.keysym.sym == SDLK_d) {
                playerX = 1;
            }
        } else if (event.type == SDL_KEYUP) { 
            if (event.key.keysym.sym == SDLK_a) {
                playerX = 0;
            } else if (event.key.keysym.sym == SDLK_d) {
                playerX = 0;
            }
        }

        printf("Y: %d \n", player.rect.y);
        printf("dt: %f \n", dt);
        
        SDL_RenderClear(renderer);
        player_render(&player, renderer);
        SDL_SetRenderDrawColor(renderer, 50, 50, 50, 255);
        SDL_RenderPresent(renderer);
    }

    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
    return 0;
}
