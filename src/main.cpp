#define SDL_MAIN_USE_CALLBACKS 1
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <print>

#include "game.h"

static SDL_Window *window = NULL;
static SDL_Renderer *renderer = NULL;

#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 480

std::string string = "real";
int number = 0;

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

  InitGame("real");

  return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppEvent(void *appstate, SDL_Event *event) {
  switch (event->type) {
    case SDL_EVENT_QUIT:
      return SDL_APP_SUCCESS;
      break;
    case SDL_EVENT_KEY_DOWN:
      if (event->key.scancode == SDL_SCANCODE_SPACE) {
        string = "beaugh";
        number += 1;
      } else if (event->key.scancode == SDL_SCANCODE_RETURN) {
        string = "real";
      }
      break;
    default:
      break;
  }

  return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppIterate(void *appstate) {
  const Uint64 now = SDL_GetTicks();
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
  SDL_RenderClear(renderer);
  SDL_SetRenderDrawColor(renderer, 255, 0, 255, SDL_ALPHA_OPAQUE);
  SDL_RenderDebugText(renderer, 200, 200, string.c_str());
  SDL_RenderDebugTextFormat(renderer, 10, 10, "hello %s %i", string.c_str(), number);
  SDL_RenderPresent(renderer);

  return SDL_APP_CONTINUE;
}

void SDL_AppQuit(void *appstate, SDL_AppResult result) {
  EndGame();
}
