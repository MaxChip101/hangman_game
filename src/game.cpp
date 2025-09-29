#include "game.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <string>
#include <vector>

std::string answer;
std::string letter_display;
std::vector<std::string> wrong_answers;
std::string letter_buffer;
bool minigame_mode = false;
unsigned int money = 0;

bool conveyer_on = false;
int conveyer_speed = 1;
char conveyer[3];

std::string event_feed;
EventType current_event;

void InitGame(std::string word) {
  answer = word;
  for (int i = 0; i < 2; i++) {
    conveyer[i] = ' ';
  }
  for (int i = 0; i < word.size(); i++) {
    letter_display += word[i];
    letter_buffer += word[i];
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

void EndGame() {
}