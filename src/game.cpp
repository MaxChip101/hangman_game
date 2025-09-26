#include "game.h"

#include <string>

std::string answer;
std::string letter_display;
std::vector<std::string> wrong_answers;
std::string letter_buffer;
bool minigame_mode;
unsigned int money;

bool conveyer_on;
int conveyer_speed;
char conveyer[3];

char* event_feed;
EventType current_event;

void InitGame(std::string word) {
  minigame_mode = false;
  money = 0;
  answer = word;
  for (int i = 0; i < 2; i++) {
    conveyer[i] = ' ';
  }
}

void AddMoney(int amount) { money += amount; }

bool SubtractMoney(int amount) {
  if (money - amount < 0) {
    return false;
  }
  money -= amount;
  return true;
}

int GetMoney() { return money; }

void SwitchMinigame() { minigame_mode = !minigame_mode; }
