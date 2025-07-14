#include <stddef.h>
#ifdef _WIN32
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ROCK 0
#define SCISSORS 1
#define PAPER 2

#define WIN 0
#define LOSE 1
#define DRAW 2

#define STATUS 3

typedef struct statistical{
  int percent_of_win, percent_of_lose, percent_of_draw;
} statistic;

statistic stats = {0, 0, 0};

const char *status[] = {"ROCK", "SCISSORS", "PAPER"};
const char *guess[] = {"WIN", "LOSE", "DRAW"};

float transition[STATUS][STATUS] = {
    {0.25, 0.35, 0.4},
    {0.5, 0.3, 0.2},
    {0.33, 0.33, 0.34}
};

const int track_table[STATUS][STATUS] = {
  {DRAW, WIN, LOSE},
  {LOSE, DRAW, WIN},
  {WIN, LOSE, DRAW}
};

int isShow_hint(){
  float limit = (float)rand() / RAND_MAX;
  return limit > 0.5;
}

int choice_change(int current_choice){
  float cumulative = 0;
  float limit = (float)rand() / (float)RAND_MAX;

  for(size_t i = 0; i < STATUS; i++){
    cumulative += transition[current_choice][i];
    if(cumulative > limit){
      return i;
    }
  }
  return rand() % STATUS;
}

int *create(int win, int lose, int draw){
  int *new = malloc(3 * sizeof(int));
  new[0] = win;
  new[1] = lose;
  new[2] = draw;
  return new;
}

int find_max(int *array){
  int index = 0;
  for(size_t i = 1; i < 3; i++){
    if(array[index] < array[i]){
      index = i;
    }
  }
  return index;
}

void debug(int times){
  printf("percent of win (bot): %0.4f%%\n", (stats.percent_of_win/(float)times) * 100.0);
  printf("percent of lose (bot): %0.4f%%\n", (stats.percent_of_lose/(float)times) * 100.0);
  printf("percent of draw (bot): %0.4f%%\n", (stats.percent_of_draw/(float)times) * 100.0);
  fflush(stdout);
}

int main(){

  srand(time(NULL));

  int player_current, times, player_guess, bot_current = ROCK;

  printf("0 for ROCK\n1 for SCISSORS\n2 for PAPER\n");
  fflush(stdout);
  scanf("%d", &player_current);

  printf("how many times you want to?\n");
  fflush(stdout);
  scanf("%d", &times);
  
  for(size_t i = 0; i < times; i++){
    bot_current = choice_change(bot_current);
    int result = track_table[bot_current][player_current];
    switch (result) {
    case WIN:
      stats.percent_of_lose++; // bot thng -> player thua
      break;
    case LOSE:
      stats.percent_of_win++;  // bot thua -> player thng
      break;
    case DRAW:
      stats.percent_of_draw++;
      break;
    }
  }

  int *create_array = create(stats.percent_of_win, stats.percent_of_lose, stats.percent_of_draw);
  if(!create_array){
    fprintf(stderr, "malloc\n");
    return EXIT_FAILURE;
  }

  int result = find_max(create_array);

  printf("===============\n");
  printf("you choose %s\n", status[player_current]);
  printf("bot will choose rock, scissors and paper randomly %d times\n", times);
  printf("what do you think the most likely outcome is?\n");
  printf("0 for win\n1 for lose\n2 for draw\n");
  fflush(stdout);

  printf("hint: ");

  for(size_t i = 0; i < 3; i++){
    int showing = isShow_hint();
    if(showing){
      printf("%d ", create_array[i]);
    } else {
      printf("? ");
    }
  }
  printf("\n");
  fflush(stdout);
  
  scanf("%d", &player_guess);

  if(player_current == result){
    printf("correct!\n");
    debug(times);
  } else {
    printf("sorry!\n");
    debug(times);
  }
  
  return EXIT_SUCCESS;
}
