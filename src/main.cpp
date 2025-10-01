#define SDL_MAIN_USE_CALLBACKS 1
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <string>
#include <print>
#include <ctime>

#include "game.h"
#include "renderer.h"

static SDL_Window *window = NULL;
static SDL_Renderer *renderer = NULL;

#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 480

SDL_AppResult SDL_AppInit(void **appstate, int argc, char *argv[]) {
  
  SDL_SetAppMetadata("HangMan Game", "0.0.1",
                     "github.com/MaxChip101/hangman_game");

  if (!SDL_Init(SDL_INIT_VIDEO)) {
    SDL_Log("Couldn't initialize SDL: %s", SDL_GetError());
    return SDL_APP_FAILURE;
  }

  if (!SDL_CreateWindowAndRenderer("HangMan Game", WINDOW_WIDTH, WINDOW_HEIGHT,
                                   0, &window, &renderer)) {
    SDL_Log("Couldn't create window/renderer: %s", SDL_GetError());
    return SDL_APP_FAILURE;
  }
  srand(time(NULL));

  InitGame("real");
  conveyer_on = true;
  conveyer_speed = 2;

  return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppEvent(void *appstate, SDL_Event *event) {
  switch (event->type) {
    case SDL_EVENT_QUIT:
      return SDL_APP_SUCCESS;
      break;
    case SDL_EVENT_KEY_DOWN:
      switch (event->key.scancode) {
        case SDL_SCANCODE_SPACE:
          SelectConveyerLetter();
          break;
        case SDL_SCANCODE_RETURN:
          SubmitBuffer();
          break;
        case SDL_SCANCODE_0:
          MinerInput(0);
          break;
        case SDL_SCANCODE_1:
          MinerInput(1);
          break;
        case SDL_SCANCODE_2:
          MinerInput(2);
          break;
        case SDL_SCANCODE_3:
          MinerInput(3);
          break;
        case SDL_SCANCODE_4:
          MinerInput(4);
          break;
        case SDL_SCANCODE_5:
          MinerInput(5);
          break;
        case SDL_SCANCODE_6:
          MinerInput(6);
          break;
        case SDL_SCANCODE_7:
          MinerInput(7);
          break;
        case SDL_SCANCODE_8:
          MinerInput(8);
          break;
        case SDL_SCANCODE_9:
          MinerInput(9);
          break;
        case SDL_SCANCODE_C:
          conveyer_on = !conveyer_on;
      }
      break;
    default:
      break;
  }

  return SDL_APP_CONTINUE;
}




SDL_AppResult SDL_AppIterate(void *appstate) {
  // logic
  const Uint64 now = SDL_GetTicks();
  ScrollConveyer(now);

  // rendering
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
  SDL_RenderClear(renderer);
  RenderBackground(renderer);
  RenderConveyer(renderer);
  RenderMiner(renderer);
  RenderBuffer(renderer);
  RenderAnswer(renderer);
  SDL_RenderPresent(renderer);

  return SDL_APP_CONTINUE;
}

void SDL_AppQuit(void *appstate, SDL_AppResult result) {
  EndGame();
}
