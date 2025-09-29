#ifndef GAME_H
#define GAME_H

#include <string>
#include <vector>

typedef struct {
} Number;

enum EventType {
  None,
  RandomizeConveyerSpeed,
  Recession,
  MinimizeWindow,
  ColorBackground,
  MoneyGallore
};

extern std::string answer;          // the correct word answer
extern std::string letter_display;  // the characters that were guessed right &
                              // the missing letters
extern std::vector<std::string> wrong_answers;  //  list of answers that are incorrect
extern std::string letter_buffer;   // fill characters left to right
extern bool minigame_mode;    // false: conveyer, true: crypto mining
extern unsigned int money;    // game currency

extern bool conveyer_on;
extern int conveyer_speed;
extern char conveyer[3];

extern std::string event_feed;  // scrolls across the screen
extern EventType current_event;

void InitGame(std::string word);
void AddMoney(int amount);
bool SubtractMoney(int amount);  // false if not possible, true if done
int GetMoney();
void SwitchMinigame();  // toggle
void EndGame();

#endif