#include <SDL3/SDL.h>
#include "renderer.h"
#include "game.h"

void RenderBackground(SDL_Renderer *renderer) {
}

void RenderConveyer(SDL_Renderer *renderer) {
    SDL_SetRenderDrawColor(renderer, 120, 120, 120, SDL_ALPHA_OPAQUE);
    SDL_FRect conveyer_background;
    conveyer_background.x = CONVEYEROFFSETX + 23;
    conveyer_background.w = 32;
    conveyer_background.y = CONVEYEROFFSETY + 15;
    conveyer_background.h = 76;
    SDL_RenderFillRect(renderer, &conveyer_background);

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
    for (int i = 0; i < 5; i++) {
        SDL_RenderDebugTextFormat(renderer, CONVEYEROFFSETX + 35, CONVEYEROFFSETY + 20 + (i * 15), "%c", conveyer[i]);
    }
    SDL_SetRenderDrawColor(renderer, 180, 180, 180, SDL_ALPHA_OPAQUE);
    SDL_RenderRect(renderer, &conveyer_background);

    SDL_SetRenderDrawColor(renderer, 100, 220, 255, SDL_ALPHA_OPAQUE);
    SDL_FRect conveyer_selector;
    conveyer_selector.x = CONVEYEROFFSETX + 23;
    conveyer_selector.w = 32;
    conveyer_selector.y = CONVEYEROFFSETY + 46;
    conveyer_selector.h = 15;
    SDL_RenderRect(renderer, &conveyer_selector);

    std::string indicator;
    if (conveyer_speed > 0) {
        SDL_SetRenderDrawColor(renderer, 0, 200, 255, SDL_ALPHA_OPAQUE);
        indicator = "\\/";
    } else if (conveyer_speed < 0) {
        SDL_SetRenderDrawColor(renderer, 160, 255, 200, SDL_ALPHA_OPAQUE);
        indicator = "/\\";
    } else {
        SDL_SetRenderDrawColor(renderer, 255, 100, 100, SDL_ALPHA_OPAQUE);
        indicator = "--";
    }

    for (int i = 0; i < 8; i++) {
        SDL_RenderDebugText(renderer, CONVEYEROFFSETX, CONVEYEROFFSETY + 15 + (i * 10), indicator.c_str());
    }

    if (conveyer_on) {
        SDL_SetRenderDrawColor(renderer, 100, 255, 100, SDL_ALPHA_OPAQUE);
        SDL_RenderDebugText(renderer, CONVEYEROFFSETX + 23, CONVEYEROFFSETY, "ON");
    } else {
        SDL_SetRenderDrawColor(renderer, 255, 100, 100, SDL_ALPHA_OPAQUE);
        SDL_RenderDebugText(renderer, CONVEYEROFFSETX + 23, CONVEYEROFFSETY, "OFF");
    }
}

void RenderHangman(SDL_Renderer *renderer) {
    
}
// 48 - 57

void RenderMiner(SDL_Renderer *renderer) {
    SDL_SetRenderDrawColor(renderer, 50, 50, 50, SDL_ALPHA_OPAQUE);

    SDL_FRect background;
    background.x = MINEROFFSETX;
    background.y = MINEROFFSETY;
    background.w = 58;
    background.h = 58;
    SDL_RenderFillRect(renderer, &background);

    for (int x = 0; x < 3; x++) {
        for (int y = 0; y < 3; y++) {
            NumberType type = miner[(y * 3) + x];
            switch (type)
            {
            case NumberSafe:
                SDL_SetRenderDrawColor(renderer, 0, 255, 0, SDL_ALPHA_OPAQUE);
                break;
            case NumberTrick:
                SDL_SetRenderDrawColor(renderer, 255, 255, 0, SDL_ALPHA_OPAQUE);
                break;
            case NumberUnsafe:
                SDL_SetRenderDrawColor(renderer, 255, 0, 0, SDL_ALPHA_OPAQUE);
            default:
                break;
            }

            SDL_RenderDebugTextFormat(renderer, MINEROFFSETX + 5 + (x * 20), MINEROFFSETY + 5 + ((2 - y) * 20), "%i", (y * 3) + x + 1);
        }
    }
}

void RenderBuffer(SDL_Renderer *renderer) {
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
    SDL_RenderDebugTextFormat(renderer, BUFFEROFFSETX, BUFFEROFFSETY, "--[%s]--", letter_buffer.c_str());
}

void RenderAnswer(SDL_Renderer *renderer) {
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
    SDL_RenderDebugTextFormat(renderer, ANSWEROFFSETX, ANSWEROFFSETY, "[%s]", letter_display.c_str());
}

void RenderWrongWords(SDL_Renderer *renderer) {
    
}

void RenderStats(SDL_Renderer *renderer) {
    
}