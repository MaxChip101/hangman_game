#include "game.h"

#include <string>
#include <vector>
#include <random>
#include <SDL3/SDL.h>
#include <cmath>
#include <print>
#include <algorithm>

std::string answer;
std::string letter_display;
std::vector<std::string> wrong_answers;
std::string letter_buffer;
bool minigame_mode = false;
 int money = 0;

bool conveyer_on = false;
float conveyer_speed = 1;
char conveyer[5];
unsigned int conveyer_cost;

NumberType miner[9];

std::string event_feed;
EventType current_event;

Uint64 last_conveyer_scroll;

void NewMinerSet() {
  for (int i = 0; i < 9; i++) {
    int type = rand()%2;

    switch (type)
    {
    case 0:
       miner[i] = NumberUnsafe;
      break;
      case 1:
       miner[i] = NumberTrick;
      break;
    }
  }
  miner[rand()%9] = NumberSafe;
}

void InitGame(std::string word) {
  money = 5;
  answer = word;

  for (int i = 0; i < answer.length(); i++) {
    answer[i] = toupper(answer[i]);
  }

  for (int i = 0; i < 5; i++) {
    conveyer[i] = 'A';
  }
  for (int i = 0; i < word.size(); i++) {
    letter_display += '_';
  }
  last_conveyer_scroll = SDL_GetTicks();
  NewMinerSet();
}

void AddMoney(unsigned int amount) { money += amount; }

bool SubtractMoney(unsigned int amount) {
  if (money < amount) {
    return false;
  }
  money -= amount;
  return true;
}

int GetMoney() { return money; }

void SwitchMinigame() { minigame_mode = !minigame_mode; }

void ScrollConveyer(Uint64 time) {
  if (!conveyer_on || conveyer_speed == 0 || time - last_conveyer_scroll < 1000.0/std::fabs(conveyer_speed)) { return; }
  
  if (!SubtractMoney(1)) {
    conveyer_on = false;
    return;
  }

  last_conveyer_scroll = time;
  char letter = 65 + rand()%26;

  if (conveyer_speed > 0) { // scroll down
    conveyer[4] = conveyer[3];
    conveyer[3] = conveyer[2];
    conveyer[2] = conveyer[1];
    conveyer[1] = conveyer[0];
    conveyer[0] = letter;
  } else if (conveyer_speed < 0) { // scroll up
    conveyer[0] = conveyer[1];
    conveyer[1] = conveyer[2];
    conveyer[2] = conveyer[3];
    conveyer[3] = conveyer[4];
    conveyer[4] = letter;
  }
}

void SelectConveyerLetter() {
  letter_buffer += conveyer[2];
}

void SubmitBuffer() {
  // search for if the string is valid & replace the blanks with the letter
  bool found_all = false;
  std::vector<int> positions;
  size_t start = 0;
  while (!found_all) {
    int pos = answer.find(letter_buffer, start);
    if (pos == std::string::npos) {
      found_all = true;
      break;
    }

    positions.push_back(pos);
    start = pos + 1;
  }

  if (positions.size() <= 0) {
    wrong_answers.push_back(letter_buffer);
  }

  for (int i = 0; i < positions.size(); i++) {
    letter_display.replace(positions[i], letter_buffer.size(), letter_buffer);
  }

  letter_buffer.clear();
}

void MinerInput(int number) {
  if (number == 0) {
    NewMinerSet();
    return;
  }

  printf("number: %i\n", number);

  switch(miner[number - 1]) {
    case NumberSafe:
    AddMoney(2);
    printf("right\n");
    break;
    case NumberUnsafe:
    if (!SubtractMoney(4)) {
      money = 0;
    }
    printf("wrong\n");
    break;
    case NumberTrick:
    if (!SubtractMoney(3)) {
      money = 0;
    }
    printf("trick\n");
    break;
  }
  NewMinerSet();
}

void EndGame() {
}