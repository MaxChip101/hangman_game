#include <SDL3/SDL.h>
#include <cmath>
#include "renderer.h"
#include "game.h"

void RenderBackground(SDL_Renderer *renderer) {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(renderer);
}

void RenderConveyer(SDL_Renderer *renderer) {
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
    SDL_RenderDebugText(renderer, CONVEYEROFFSETX, CONVEYEROFFSETY - 10, "CONVEYER:");

    SDL_SetRenderDrawColor(renderer, 50, 50, 50, SDL_ALPHA_OPAQUE);
    SDL_FRect background;
    background.x = CONVEYEROFFSETX + 23;
    background.w = 32;
    background.y = CONVEYEROFFSETY + 15;
    background.h = 76;
    SDL_RenderFillRect(renderer, &background);

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
    for (int i = 0; i < 5; i++) {
        SDL_RenderDebugTextFormat(renderer, CONVEYEROFFSETX + 35, CONVEYEROFFSETY + 20 + (i * 15), "%c", conveyer[i]);
    }
    SDL_SetRenderDrawColor(renderer, 200, 200, 200, SDL_ALPHA_OPAQUE);
    SDL_RenderRect(renderer, &background);

    SDL_SetRenderDrawColor(renderer, 100, 220, 255, SDL_ALPHA_OPAQUE);
    SDL_FRect conveyer_selector;
    conveyer_selector.x = CONVEYEROFFSETX + 23;
    conveyer_selector.w = 32;
    conveyer_selector.y = CONVEYEROFFSETY + 46;
    conveyer_selector.h = 15;
    SDL_RenderRect(renderer, &conveyer_selector);

    std::string indicator;

    if (conveyer_speed > 0.0f) {
        SDL_SetRenderDrawColor(renderer, 0, 200, 255, SDL_ALPHA_OPAQUE);
        indicator = "\\/";
    } else if (conveyer_speed < 0.0f) {
        SDL_SetRenderDrawColor(renderer, 160, 255, 200, SDL_ALPHA_OPAQUE);
        indicator = "/\\";
    } else {
        SDL_SetRenderDrawColor(renderer, 255, 100, 100, SDL_ALPHA_OPAQUE);
        indicator = "--";
        conveyer_speed = 0;
    }

    for (int i = 0; i < 8; i++) {
        SDL_RenderDebugText(renderer, CONVEYEROFFSETX, CONVEYEROFFSETY + 15 + (i * 10), indicator.c_str());
    }

    if (conveyer_on) {
        SDL_SetRenderDrawColor(renderer, 100, 255, 100, SDL_ALPHA_OPAQUE);
        SDL_RenderDebugText(renderer, CONVEYEROFFSETX + 23, CONVEYEROFFSETY + 3, "ON");
    } else {
        SDL_SetRenderDrawColor(renderer, 255, 100, 100, SDL_ALPHA_OPAQUE);
        SDL_RenderDebugText(renderer, CONVEYEROFFSETX + 23, CONVEYEROFFSETY + 3, "OFF");
    }
}

void RenderHangman(SDL_Renderer *renderer) {
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
    SDL_RenderDebugText(renderer, HANGMANOFFSETX, HANGMANOFFSETY - 10, "HANGMAN:");

    SDL_SetRenderDrawColor(renderer, 50, 50, 50, SDL_ALPHA_OPAQUE);
    SDL_FRect background;
    background.x = HANGMANOFFSETX;
    background.y = HANGMANOFFSETY;
    background.w = 150;
    background.h = 150;
    SDL_RenderFillRect(renderer, &background);

    SDL_SetRenderDrawColor(renderer, 200, 200, 200, SDL_ALPHA_OPAQUE);
    SDL_RenderRect(renderer, &background);

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
    
    // stand
    SDL_RenderLine(renderer, HANGMANOFFSETX + 85, HANGMANOFFSETY + 130, HANGMANOFFSETX + 135, HANGMANOFFSETY + 130);
    SDL_RenderLine(renderer, HANGMANOFFSETX + 110, HANGMANOFFSETY + 20, HANGMANOFFSETX + 110, HANGMANOFFSETY + 130);
    SDL_RenderLine(renderer, HANGMANOFFSETX + 60, HANGMANOFFSETY + 20, HANGMANOFFSETX + 110, HANGMANOFFSETY + 20);
    SDL_RenderLine(renderer, HANGMANOFFSETX + 60, HANGMANOFFSETY + 20, HANGMANOFFSETX + 60, HANGMANOFFSETY + 40);
    
    // head
    if (wrong_answers.size() >= 1) {
        SDL_FRect background;
        background.x = HANGMANOFFSETX + 50;
        background.y = HANGMANOFFSETY + 40;
        background.w = 20;
        background.h = 20;
        SDL_RenderRect(renderer, &background);
    }
    if (wrong_answers.size() >= 2) { // body
        SDL_RenderLine(renderer, HANGMANOFFSETX + 60, HANGMANOFFSETY + 60, HANGMANOFFSETX + 60, HANGMANOFFSETY + 100);
    }
    if (wrong_answers.size() >= 3) { // left arm
        SDL_RenderLine(renderer, HANGMANOFFSETX + 60, HANGMANOFFSETY + 60, HANGMANOFFSETX + 30, HANGMANOFFSETY + 90);
    }
    if (wrong_answers.size() >= 4) { // right arm
        SDL_RenderLine(renderer, HANGMANOFFSETX + 60, HANGMANOFFSETY + 60, HANGMANOFFSETX + 90, HANGMANOFFSETY + 90);
    }
    if (wrong_answers.size() >= 5) { // left leg
        SDL_RenderLine(renderer, HANGMANOFFSETX + 60, HANGMANOFFSETY + 100, HANGMANOFFSETX + 40, HANGMANOFFSETY + 130);
    }
    if (wrong_answers.size() >= 6) { // right leg
        SDL_RenderLine(renderer, HANGMANOFFSETX + 60, HANGMANOFFSETY + 100, HANGMANOFFSETX + 80, HANGMANOFFSETY + 130);
    }

    SDL_RenderDebugTextFormat(renderer, HANGMANOFFSETX, HANGMANOFFSETY + 155, "%i ATTEMPT(S) LEFT", 6 - wrong_answers.size());
}

void RenderMiner(SDL_Renderer *renderer) {
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
    SDL_RenderDebugText(renderer, MINEROFFSETX, MINEROFFSETY - 10, "MINER:");

    SDL_SetRenderDrawColor(renderer, 50, 50, 50, SDL_ALPHA_OPAQUE);
    SDL_FRect background;
    background.x = MINEROFFSETX;
    background.y = MINEROFFSETY;
    background.w = 58;
    background.h = 58;
    SDL_RenderFillRect(renderer, &background);

    SDL_SetRenderDrawColor(renderer, 200, 200, 200, SDL_ALPHA_OPAQUE);
    SDL_RenderRect(renderer, &background);

    

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
    SDL_RenderDebugTextFormat(renderer, BUFFEROFFSETX, BUFFEROFFSETY, "BUFFER: [ %s ]", letter_buffer.c_str());
}

void RenderAnswer(SDL_Renderer *renderer) {
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
    SDL_RenderDebugTextFormat(renderer, ANSWEROFFSETX, ANSWEROFFSETY, "SECRET: [ %s ]", letter_display.c_str());
}

void RenderWrongWords(SDL_Renderer *renderer) {
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
    SDL_RenderDebugText(renderer, WRONGWORDSOFFSETX, WRONGWORDSOFFSETY, "WRONG ANSWERS:");
    for (int i = 0; i < wrong_answers.size(); i++) {
        SDL_RenderDebugTextFormat(renderer, WRONGWORDSOFFSETX, WRONGWORDSOFFSETY + 15 + (i * 10), "- [ %s ]", wrong_answers[i].c_str());
    }
}

void RenderStats(SDL_Renderer *renderer) {
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
    SDL_RenderDebugText(renderer, STATSOFFSETX, STATSOFFSETY - 10, "STATS:");

    SDL_SetRenderDrawColor(renderer, 50, 50, 50, SDL_ALPHA_OPAQUE);
    SDL_FRect background;
    background.x = STATSOFFSETX;
    background.y = STATSOFFSETY;
    background.w = 240;
    background.h = 100;
    SDL_RenderFillRect(renderer, &background);

    SDL_SetRenderDrawColor(renderer, 200, 200, 200, SDL_ALPHA_OPAQUE);
    SDL_RenderRect(renderer, &background);

    SDL_SetRenderDrawColor(renderer, 0, 255, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderDebugTextFormat(renderer, STATSOFFSETX + 5, STATSOFFSETY + 5, "MONEY: ¢%i", money);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
    SDL_RenderDebugTextFormat(renderer, STATSOFFSETX + 5, STATSOFFSETY + 17, "PAY: %i ¢/MINE", pay);
    SDL_RenderDebugTextFormat(renderer, STATSOFFSETX + 5, STATSOFFSETY + 29, "COST: ¢%i/TURN", conveyer_cost);
    SDL_RenderDebugTextFormat(renderer, STATSOFFSETX + 5, STATSOFFSETY + 41, "SPEED: %.1f TURNS/SECOND", conveyer_speed);
}

void RenderState(SDL_Renderer *renderer) {
    if (game_state == GameStatePlaying) {
        return;
    }

    SDL_SetRenderDrawColor(renderer, 50, 50, 50, SDL_ALPHA_OPAQUE);
        SDL_FRect background;
        background.x = STATEOFFSETX;
        background.y = STATEOFFSETY;
        background.w = 200;
        background.h = 200;
        SDL_RenderFillRect(renderer, &background);

        SDL_SetRenderDrawColor(renderer, 200, 200, 200, SDL_ALPHA_OPAQUE);
        SDL_RenderRect(renderer, &background);

    switch (game_state) {
    case GameStateWon:
        SDL_SetRenderDrawColor(renderer, 100, 255, 100, SDL_ALPHA_OPAQUE);
        SDL_RenderDebugTextFormat(renderer, STATEOFFSETX + 74, STATEOFFSETY + 95, "YOU WON");
        break;
    case GameStateLost:
        SDL_SetRenderDrawColor(renderer, 255, 100, 100, SDL_ALPHA_OPAQUE);
        SDL_RenderDebugText(renderer, STATEOFFSETX + 5, STATEOFFSETY + 5, "YOU LOST");
        SDL_RenderDebugText(renderer, STATEOFFSETX + 5, STATEOFFSETY + 25, "THE WORD WAS:");
        SDL_RenderDebugTextFormat(renderer, STATEOFFSETX + 5, STATEOFFSETY + 40, "%s", answer.c_str());
        break;
    
    default:
        break;
    }
}

void RenderEvent(SDL_Renderer *renderer) {
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
    SDL_RenderDebugText(renderer, EVENTOFFSETX, EVENTOFFSETY - 10, "EVENT:");

    SDL_SetRenderDrawColor(renderer, 255, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderDebugTextFormat(renderer, EVENTOFFSETX, EVENTOFFSETY, "[ %s ]", event_feed.c_str());
}

void RenderBalance(SDL_Renderer *renderer) {
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
    SDL_RenderDebugText(renderer, BALANCEOFFSETX, BALANCEOFFSETY - 10, "BALANCE:");

    SDL_SetRenderDrawColor(renderer, 50, 50, 50, SDL_ALPHA_OPAQUE);
    SDL_FRect background;
    background.x = BALANCEOFFSETX;
    background.y = BALANCEOFFSETY;
    background.w = 200;
    background.h = 10;
    SDL_RenderFillRect(renderer, &background);

    SDL_SetRenderDrawColor(renderer, 120, 120, 120, SDL_ALPHA_OPAQUE);

    SDL_FRect center;
    center.x = BALANCEOFFSETX + 90;
    center.y = BALANCEOFFSETY;
    center.w = 20;
    center.h = 10;
    SDL_RenderFillRect(renderer, &center);

    SDL_SetRenderDrawColor(renderer, 255, 0, 0, SDL_ALPHA_OPAQUE);

    SDL_FRect left_death;
    left_death.x = BALANCEOFFSETX;
    left_death.y = BALANCEOFFSETY;
    left_death.w = 5;
    left_death.h = 10;
    SDL_RenderFillRect(renderer, &left_death);

    SDL_FRect right_death;
    right_death.x = BALANCEOFFSETX + 195;
    right_death.y = BALANCEOFFSETY;
    right_death.w = 5;
    right_death.h = 10;
    SDL_RenderFillRect(renderer, &right_death);

    SDL_SetRenderDrawColor(renderer, 200, 200, 200, SDL_ALPHA_OPAQUE);
    SDL_RenderRect(renderer, &background);

    SDL_SetRenderDrawColor(renderer, 0, 200, 255, SDL_ALPHA_OPAQUE);

    SDL_FRect balance;
    balance.x = BALANCEOFFSETX + balance_position - 5;
    balance.y = BALANCEOFFSETY;
    balance.w = 10;
    balance.h = 10;
    SDL_RenderFillRect(renderer, &balance);
}