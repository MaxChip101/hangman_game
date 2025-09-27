#include "game.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* answer;
char* letter_display;
char** wrong_answers;
char* letter_buffer;
bool minigame_mode = false;
unsigned int money = 0;

bool conveyer_on = false;
int conveyer_speed = 1;
char conveyer[3];

char* event_feed;
EventType current_event;

void InitGame(char* word) {
  answer = (char*)calloc(strlen(word), sizeof(char*));
  letter_display = (char*)calloc(strlen(word), sizeof(char*));
  letter_buffer = (char*)calloc(strlen(word), sizeof(char*));
  sprintf(answer, word);
  for (int i = 0; i < 2; i++) {
    conveyer[i] = ' ';
  }
  for (int i = 0; i < strlen(word); i++) {
    letter_display[i] = '_';
    letter_buffer[i] = ' ';
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
  free(answer);
  free(letter_display);
  free(letter_buffer);
}