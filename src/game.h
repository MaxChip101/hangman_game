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
  EventWageEconomics,
  EventVelocityShift,
  EventConveyerCost
};

enum GameState {
  GameStatePlaying,
  GameStateWon,
  GameStateLost
};

extern GameState game_state; 

extern std::string answer;          // the correct word answer
extern std::string letter_display;  // the characters that were guessed right &
                              // the missing letters
extern std::vector<std::string> wrong_answers;  //  list of answers that are incorrect
extern std::string letter_buffer;   // fill characters left to right
extern int money;    // cents

extern bool conveyer_on;
extern float conveyer_speed;
extern char conveyer[5];
extern unsigned int conveyer_cost; // money/cycle

extern NumberType miner[9];
extern int pay;

extern std::string event_feed;

extern float balance_velocity;
extern float balance_position;

void InitGame(std::string word);
void AddMoney(unsigned int amount);
bool SubtractMoney(unsigned int amount);  // false if not possible, true if done
int GetMoney();
void ScrollConveyer(Uint64 time);
void SelectConveyerLetter();
void SubmitBuffer();
void MinerInput(int number);
void RandomizeEvents(Uint64 time);
void BalanceIterate(Uint64 time);
void CheckCondition();

#endif