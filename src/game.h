#ifndef GAME_H
#define GAME_H

#include <string>
#include <vector>
#include <SDL3/SDL.h>

enum NumberType {
  NumberSafe,
  NumberUnsafe,
  NumberTrick
};

enum EventType {
  EventNone,
  EventRandomizeConveyerSpeed,
  EventRecession,
  EventMinimizeWindow,
  EventColorBackground,
  EventMoneyGallore
};

extern std::string answer;          // the correct word answer
extern std::string letter_display;  // the characters that were guessed right &
                              // the missing letters
extern std::vector<std::string> wrong_answers;  //  list of answers that are incorrect
extern std::string letter_buffer;   // fill characters left to right
extern bool minigame_mode;    // false: conveyer, true: crypto mining
extern int money;    // game currency

extern bool conveyer_on;
extern float conveyer_speed;
extern char conveyer[5];
extern unsigned int conveyer_cost; // money/cycle

extern NumberType miner[9];

extern std::string event_feed;  // scrolls across the screen
extern EventType current_event;

void InitGame(std::string word);
void AddMoney(unsigned int amount);
bool SubtractMoney(unsigned int amount);  // false if not possible, true if done
int GetMoney();
void SwitchMinigame();  // toggle
void ScrollConveyer(Uint64 time);
void SelectConveyerLetter();
void SubmitBuffer();
void MinerInput(int number);
void EndGame();

#endif