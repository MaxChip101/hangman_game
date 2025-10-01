#ifndef RENDERER_H
#define RENDERER_H

#include <SDL3/SDL.h>

#define CONVEYEROFFSETX 5
#define CONVEYEROFFSETY 280
#define HANGMANOFFSETX 5
#define HANGMANOFFSETY 280
#define MINEROFFSETX 300
#define MINEROFFSETY 300
#define BUFFEROFFSETX 5
#define BUFFEROFFSETY 380
#define ANSWEROFFSETX 5
#define ANSWEROFFSETY 5
#define WRONGWORDSOFFSETX 5
#define WRONGWORDSOFFSETY 280
#define STATSOFFSETX 5
#define STATSOFFSETY 280

void RenderBackground(SDL_Renderer *renderer);
void RenderConveyer(SDL_Renderer *renderer);
void RenderHangman(SDL_Renderer *renderer);
void RenderMiner(SDL_Renderer *renderer);
void RenderBuffer(SDL_Renderer *renderer);
void RenderAnswer(SDL_Renderer *renderer);
void RenderWrongWords(SDL_Renderer *renderer);
void RenderStats(SDL_Renderer *renderer);

#endif