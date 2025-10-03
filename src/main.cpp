#define SDL_MAIN_USE_CALLBACKS 1
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <string>
#include <print>
#include <ctime>
#include <fstream>

#include "game.h"
#include "renderer.h"

static SDL_Window *window = NULL;
static SDL_Renderer *renderer = NULL;

#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 480

SDL_AppResult SDL_AppInit(void **appstate, int argc, char *argv[]) {

  SDL_SetAppMetadata("HangMan Game", "0.0.1",
                     "github.com/MaxChip101/hangman_game");

  std::ifstream words_file("words.txt");

  if (!words_file.is_open()) {
    SDL_Log("HangMan Game needs a words.txt file with a list of words to run");
    return SDL_APP_FAILURE;
  }

  std::vector<std::string> words;

  std::string line;

  while (std::getline(words_file, line)) {
    words.push_back(line);
  }

  words_file.close();
  
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

  InitGame(words[rand()%words.size()]);

  return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppEvent(void *appstate, SDL_Event *event) {
  switch (event->type) {
    case SDL_EVENT_QUIT:
      return SDL_APP_SUCCESS;
      break;
    case SDL_EVENT_KEY_DOWN:
      if (game_state != GameStatePlaying) { return SDL_APP_CONTINUE; }
      switch (event->key.scancode) {
        case SDL_SCANCODE_SPACE:
          SelectConveyerLetter();
          break;
        case SDL_SCANCODE_RETURN:
          SubmitBuffer();
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
          break;
      }
      break;
    case SDL_EVENT_KEY_UP:
      if (game_state != GameStatePlaying) { return SDL_APP_CONTINUE; }
      switch (event->key.scancode) {
        case SDL_SCANCODE_UP:
          conveyer_speed += 0.1f;
          break;
        case SDL_SCANCODE_DOWN:
          conveyer_speed -= 0.1f;
          break;
        case SDL_SCANCODE_LEFT:
          balance_position -= 20.0f;
          break;
        case SDL_SCANCODE_RIGHT:
          balance_position += 20.0f;
          break;
      }

    default:
      break;
  }

  return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppIterate(void *appstate) {
  // logic
  const Uint64 now = SDL_GetTicks();
  ScrollConveyer(now);
  CheckCondition();
  RandomizeEvents(now);
  BalanceIterate(now);
  

  // rendering
  RenderBackground(renderer);
  RenderConveyer(renderer);
  RenderHangman(renderer);
  RenderMiner(renderer);
  RenderBuffer(renderer);
  RenderAnswer(renderer);
  RenderWrongWords(renderer);
  RenderStats(renderer);
  RenderHangman(renderer);
  RenderEvent(renderer);
  RenderBalance(renderer);

  RenderState(renderer);
  SDL_RenderPresent(renderer);

  return SDL_APP_CONTINUE;
}

void SDL_AppQuit(void *appstate, SDL_AppResult result) {}
