#ifndef RENDERER_H
#define RENDERER_H

#include <SDL3/SDL.h>

#define CONVEYEROFFSETX 20
#define CONVEYEROFFSETY 300
#define HANGMANOFFSETX 5
#define HANGMANOFFSETY 20
#define MINEROFFSETX 500
#define MINEROFFSETY 300
#define BUFFEROFFSETX 5
#define BUFFEROFFSETY 410
#define ANSWEROFFSETX 5
#define ANSWEROFFSETY 200
#define WRONGWORDSOFFSETX 280
#define WRONGWORDSOFFSETY 15
#define STATSOFFSETX 180
#define STATSOFFSETY 300
#define STATEOFFSETX 200
#define STATEOFFSETY 150
#define EVENTOFFSETX 180
#define EVENTOFFSETY 260
#define BALANCEOFFSETX 200
#define BALANCEOFFSETY 440

void RenderBackground(SDL_Renderer *renderer);
void RenderConveyer(SDL_Renderer *renderer);
void RenderHangman(SDL_Renderer *renderer);
void RenderMiner(SDL_Renderer *renderer);
void RenderBuffer(SDL_Renderer *renderer);
void RenderAnswer(SDL_Renderer *renderer);
void RenderWrongWords(SDL_Renderer *renderer);
void RenderStats(SDL_Renderer *renderer);
void RenderState(SDL_Renderer *renderer);
void RenderEvent(SDL_Renderer *renderer);
void RenderBalance(SDL_Renderer *renderer);

#endif