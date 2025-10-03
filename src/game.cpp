#include "game.h"

#include <string>
#include <vector>
#include <random>
#include <SDL3/SDL.h>
#include <cmath>
#include <print>
#include <algorithm>

GameState game_state = GameStatePlaying; 

std::string answer;
std::string letter_display;
std::vector<std::string> wrong_answers;
std::string letter_buffer;
int money = 0;

bool conveyer_on = false;
float conveyer_speed = 3;
char conveyer[5];
unsigned int conveyer_cost = 1;

NumberType miner[9];
int pay = 4;

std::string event_feed = "NOTHING HAPPENED";

float balance_velocity = 50;
float balance_position = 100;

Uint64 last_conveyer_scroll;
Uint64 last_event;
Uint64 last_balance_iterate;

void NewMinerSet() {
  if (game_state != GameStatePlaying) {
    return;
  }

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
  answer = word;

  for (int i = 0; i < answer.length(); i++) {
    answer[i] = toupper(answer[i]);
  }

  for (int i = 0; i < 5; i++) {
    conveyer[i] = 'A';
  }
  for (int i = 0; i < word.size(); i++) {
    letter_display += '-';
  }
  last_conveyer_scroll = SDL_GetTicks();
  last_event = SDL_GetTicks();
  last_balance_iterate = SDL_GetTicks();
  NewMinerSet();
}

void AddMoney(unsigned int amount) {
  if (game_state != GameStatePlaying) {
    return;
  }

  money += amount;
}

bool SubtractMoney(unsigned int amount) {
  if (game_state != GameStatePlaying) {
    return false;
  }

  if (money < amount) {
    return false;
  }
  money -= amount;
  return true;
}

int GetMoney() { return money; }

void ScrollConveyer(Uint64 time) {
  double interval = 1000.0 / std::fabs(static_cast<double>(conveyer_speed));
  conveyer_speed = std::round(conveyer_speed * 10) / 10;
  if (!conveyer_on || conveyer_speed == 0 || static_cast<double>(time - last_conveyer_scroll) < interval || game_state != GameStatePlaying) { return; }
  
  if (!SubtractMoney(conveyer_cost)) {
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
  if (game_state != GameStatePlaying || answer.size() - letter_buffer.size() <= 0) {
    return;
  }

  letter_buffer += conveyer[2];
}

void SubmitBuffer() {
  if (game_state != GameStatePlaying) {
    return;
  }

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
  if (game_state != GameStatePlaying) {
    return;
  }

  switch(miner[number - 1]) {
    case NumberSafe:
    AddMoney(pay);
    break;
    case NumberUnsafe:
    if (!SubtractMoney(pay * 1.5)) {
      money = 0;
    }
    break;
    case NumberTrick:
    if (!SubtractMoney(pay)) {
      money = 0;
    }
    break;
  }
  NewMinerSet();
}

void Event(EventType event) {
  if (game_state != GameStatePlaying) {
    return;
  }

  switch(event) {
    case EventNone:
      event_feed = "NOTHING HAPPENED";
      break;
    case EventRandomizeConveyerSpeed:
      event_feed = "RANDOMIZED CONVEYER SPEED";
      conveyer_speed = ((float)rand() / RAND_MAX) * 4 - 4;
      break;
    case EventWageEconomics:
      event_feed = "WAGE ECONOMICS CHANGED";
      pay = rand()%8 + 1;
      break;
    case EventVelocityShift:
      event_feed = "BALANCE VELOCITY SHIFTED";
      balance_velocity = ((float)rand() / RAND_MAX) * 60 - 30;
      break;
    case EventConveyerCost:
      event_feed = "CONVEUYER PRICE CHANGED";
      conveyer_cost = rand()%3;
      break;
  }
}

void RandomizeEvents(Uint64 time) {
  if (time - last_event < 10000.0 || game_state != GameStatePlaying) { return; }
  last_event = time;
  Event(static_cast<EventType>(rand()%6));
}

void BalanceIterate(Uint64 time) {
  conveyer_speed = std::round(conveyer_speed * 10) / 10;
  if (game_state != GameStatePlaying) { return; }
  double delta = static_cast<double>(time - last_balance_iterate) / 1000.0;
  balance_position += balance_velocity * delta;
  last_balance_iterate = time;
}

void CheckCondition() {
  if (balance_position - 5.0f <= 0 || balance_position + 5.0f >= 200) {
    game_state = GameStateLost;
  }

  if (wrong_answers.size() >= 6) {
    game_state = GameStateLost;
  } else if (answer == letter_display) {
    game_state = GameStateWon;
  }
}