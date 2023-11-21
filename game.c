#include "game.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define MAX_HEALTH 100
#define MAX_HUNGER 100
#define MAX_THIRST 100
#define STARTING_HOUR 1200
#define MAX_DAYS 7

// itens codes:
// med-kit = 1
// canned food = 2
// bottle of water = 3
// gun = 4

// global variables
struct list *inventory = NULL;
struct list *days = NULL;

int health = MAX_HEALTH;
int hunger = MAX_HUNGER;
int thirst = MAX_THIRST;
int time_of_the_day = STARTING_HOUR;
int day = 0;

// interface/initialization
void printStatus() {
  printf("\n=======================\n");
  printf("DAY %d\n", day);
  printf("Time: %.2d:%.2d\n", time_of_the_day / 100, time_of_the_day % 100);
  printf("Health: %d / %d\n", health, MAX_HEALTH);
  printf("Hunger: %d / %d\n", hunger, MAX_HUNGER);
  printf("Thirst: %d / %d\n", thirst, MAX_THIRST);
  printf("\n=======================\n");
}

void loading() {
  int tempo = 30000;
  fflush(stdout);
  usleep(tempo);
  printf(".");
  fflush(stdout);
  usleep(tempo);
  printf(".");
  fflush(stdout);
  usleep(tempo);
  printf(".");
  fflush(stdout);
  usleep(tempo);
  
}

void initializeDays(struct list **days) {

  for (int i = 0; i <= MAX_DAYS; i++) {

  Event *event = (Event *)malloc(sizeof(Event));

    if (i==0){
      event->health = 0;
      event->hunger = 0;
      event->thirst = 0;
      strcpy(event->event, "You awake in a deserted island in the middle of nowhere surrounded by wreckage of ships and planes, you need to survive until someone comes to rescue you!");
    }
    else if(i==1){
      event->health = 0;
      event->hunger = 0;
      event->thirst = -20;
      strcpy(event->event, "the day is very hot, you are starting to feel thirsty, you need to find some water!");
    }
    else if (i==2){
      event->health = -8;
      event->hunger = -20;
      event->thirst = 0;
      strcpy(event->event, "you ate something that you shouldn't, you have threw up your last meal, you need to find some food!");
    }
    else if(i==3){
      event->health = 0;
      event->hunger = 30;
      event->thirst = 30;
      strcpy(event->event, "you found a coconut tree, you ate some coconuts and drank some coconut water, you feel better now!");
    }
    else if(i==4){
      event->health = 29;
      event->hunger = 0;
      event->thirst = 0;
      strcpy(event->event, "you found a medkit, you used it to heal your wounds, you feel better now!");
    }
    else if(i==5){
      event->health = -1;
      event->hunger = 0;
      event->thirst = 0;
      strcpy(event->event, "Today the sun is covered by the clouds, the animals are so quiet, you can hear your self breathig, you feel is something bad is going to happen!");
    }
    else if(i==6){
      event->health = 0;
      event->hunger = 0;
      event->thirst = 0;
      strcpy(event->event, "");
    }
    else if(i==7){
      event->health = 0;
      event->hunger = 0;
      event->thirst = 0;
      strcpy(event->event, "Finally! Someone came to rescue you!");
    }
    
    insertLs(days, sizeLs(days), i, event);
    }
}

void mainHistory() {
  printf(
      "-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-="
      "-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n");
  printf("Voce eh o capitao de um navio com uma poderosa tripulacao, Valentes "
         "e sem nada a perder. Voces partem corajosamente em direcao ao\n");
  printf("Triangulo das Camisetas, uma regiao famosa por devorar navios, "
         "incluindo o grandioso Titanico.\n");
  printf("No entanto, mesmo com uma tripulacao tao destemida, voces nao "
         "conseguiram escapar das garras impiedosas do mar.\n\n");
  printf("O navio naufraga, e toda sua tripulacao sucumbe, deixando somente "
         "voce como sobrevivente\n");
  printf("em uma ilha deserta, com poucos recursos e uma unica chance de "
         "sobrevivencia.\n");
  printf("Seu desafio: aguentar sete dias a espera do resgate, enfrentando "
         "fome, sede e todas as adversidades dessa ilha amaldicoada.\n");
  printf("Mas tenha cuidado com os ursos! Se estiver armado, a vitoria e "
         "garantida! Caso contrario...\n");
  printf("-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=BEM-VINDO AO "
         "NAUFRAGO-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n");

  loading();
  loading();
  loading();
  loading();
  printf("\n");
}

void startEvent() {
  day = days->item;
  health += days->event->health;
  hunger += days->event->hunger;
  thirst += days->event->thirst;
  printf("%s\n", days->event->event);
}

void start() {
  srand(time(NULL));
  mainHistory();

  


  while (1){
    printf("Choose an option:\n");
    printf("-1.  Quit Game\n");
    printf("0.   View top scores\n");
    printf("1.   Start game\n");
    int option;
    scanf(" %d", &option);

    switch (option)
    {
    case -1:
      exit(0);
      break;
    case 0:
      readScore();
      break;

    case 1:
      inventory = NULL;
      days = NULL;

      initializeDays(&days);
      health = MAX_HEALTH;
      hunger = MAX_HUNGER;
      thirst = MAX_THIRST;
      time_of_the_day = STARTING_HOUR;
      day = 0;
      startEvent();
      actionMenu();
      break;

    default:
      break;
    }
    
  }
  
  
}

// actions
void actionMenu() {
  while (1){
    if(day == MAX_DAYS){
      break;
    }

    printStatus();
    printf("Choose an action:\n");
    printf("-1.  Quit to main menu\n");
    printf("0.   Inventory\n");
    printf("1.   Rest\n");
    printf("2.   Hunt\n");
    printf("3.   Scavenge\n");
    int choice;
    scanf("%d", &choice);
    printf("\n");
    system("cls");

    if (choice == -1){
      break;
    }
    else if (choice == 0){
      openInventory();
    }
    else if (choice == 1){
      rest();
    }
    else if (choice == 2){
      hunt();
    }
    else if (choice == 3){
      scavenge();
    }
    else{
      printf("Invalid choice.\n");
    }
    
  
    // usleep(100000); // wait for a short time (100 ms)
  }
}

void nextDay() {
  time_of_the_day = time_of_the_day % 2400;
  if(days->next != NULL){
    struct list* aux = days;
    days = days->next;
    free(aux);
  }
  else{
    free(days);
    days = NULL;
  }

  


  printf("\nAnother day has passed");
  loading();
  printf("\n\n");

  startEvent();


  if (day == MAX_DAYS-1){
    printf("Giant and angry wild bear has appeared!\n");
    printf("You need to kill it to survive!\n");
    if (countLs(&inventory, 4) != 0) {
      printf("luckly you had a gun with you!\n");
      printf("you broke your gun during the fight.\n");
      printf("the bear gave you plenty of nourishment.\n");
      printf("you feel revigorated with that meal.\n");

      deleteLs(&inventory, searchLs(&inventory, 4));

      hunger += 100;
      thirst += 100;
      health += 10;
    } else {
      printf(
          "unfortunatly, you did not had anything to defend yourself with.\n");
      health -= 100;
    }
  }
  if (day == MAX_DAYS) {
    printf("YOU WON!\n");
    printf("You have survived for %d days!\n", day);
    printf("Someone came to rescue you!\n\n");

    registerScore(day);

  }
  action(0, 0);
}

void action(double hours, double dificulty_modifier) {
  time_of_the_day += 100 * hours;
  hunger -= (int)((3 * dificulty_modifier) * hours);
  thirst -= (int)((5 * dificulty_modifier) * hours);

  if (health > MAX_HEALTH) {
    health = MAX_HEALTH;
  }

  if (hunger > MAX_HUNGER) {
    hunger = MAX_HUNGER;
  }

  if (thirst > MAX_THIRST) {
    thirst = MAX_THIRST;
  }

  if (hunger < 0) {
    health += 1 * hunger;
    hunger = 0;
  }

  if (thirst < 0) {
    health += 1 * thirst;
    thirst = 0;
  }

  if (health < 0) {
    printf("GAME OVER\n\n");

    printf("You died!\n");
    printf("Days survived: %d.\n", day);

    registerScore(day);
    readScore();

    // printf("cause of death:\n");

    // if (hunger <= 0){
    //   printf("starvation\n");
    // }

    // if (thirst <= 0){
    //   printf("dehydration\n");
    // }

    exit(0);
  }
  if (time_of_the_day >= 2400) {
    nextDay();
  }
}

void rest() {
  printf("You take a rest and recover some health.\n");
  health += 15;
  if (health > MAX_HEALTH) {
    health = MAX_HEALTH;
  }

  action(8, 1);
}

void hunt() {
  printf("You go hunting for food and water");
  loading();
  printf("\n\n");

  int chance = rand() % 100;

  if (chance < 40) {

    printf("You have found an wild rabbit.\n");
    printf("it barely fed you.\n");

    hunger += 30;
    thirst += 30;

  } else if (chance < 75) {
    printf("You have found an wild deer.\n");
    printf("it fed you a considerable amount.\n");

    hunger += 50;
    thirst += 50;
  } else if (chance < 85) {
    printf("You have found an wild Bear!\n");

    if (countLs(&inventory, 4) != 0) {
      printf("luckly you had a gun with you!\n");
      printf("you broke your gun during the fight.\n");
      printf("the bear gave you plenty of nourishment.\n");
      printf("you feel revigorated with that meal.\n");

      deleteLs(&inventory, searchLs(&inventory, 4));

      hunger += 100;
      thirst += 100;
      health += 10;
    } else {
      printf(
          "unfortunatly, you did not had anything to defend yourself with.\n");
      health -= 25;
    }
  } else {
    printf("You have lost the tracks of your prey.\n");
  }

  action(4, 1.5);
}

void scavenge() {
  printf("You went to scavenge for useful items");
  loading();
  printf("\n\n");

  int chance = rand() % 100;

  if (chance < 15) {
    printf("You found a medkit!\n");
    insertLs(&inventory, sizeLs(&inventory), 1, NULL);

  } else if (chance < 45) {
    printf("You found some canned food.\n");
    insertLs(&inventory, sizeLs(&inventory), 2, NULL);
  } else if (chance < 80) {
    printf("You found a bottle of water.\n");
    insertLs(&inventory, sizeLs(&inventory), 3, NULL);
  } else if (chance < 90) {
    printf("You found a gun.\n");

    if (countLs(&inventory, 4) == 0) {
      insertLs(&inventory, sizeLs(&inventory), 4, NULL);
    } else {
      printf("unfortunatly, you are already carrying a gun and can not carry "
             "another.\n");
    }
  } else {
    printf("You didn't find anything useful.\n");
  }
  action(2, 3);
}

void openInventory() {
  int option;

  while (1) {
    printf("\n======IVENTORY======\n");
    printf("Itens:\n");
    printf("Medkits: %d\n", countLs(&inventory, 1));
    printf("cans of food: %d\n", countLs(&inventory, 2));
    printf("bottles of water: %d\n", countLs(&inventory, 3));
    printf("gun: %d\n", countLs(&inventory, 4));

    printf("chose an action:\n");
    printf("0.  exit inventory\n");
    printf("1.  use medkit\n");
    printf("2.  use canned food\n");
    printf("3.  use bottle of water\n");

    scanf(" %d", &option);
    system("cls");

    if (option == 0) {
      break;
    } else if (option == 1) {
      if (countLs(&inventory, 1) != 0) {
        health += 35;

        deleteLs(&inventory, searchLs(&inventory, 1));

        printf("You have used a medkit!\n");
      } else {
        printf("You do not have a medkit to use!\n");
      }
    } else if (option == 2) {
      if (countLs(&inventory, 2) != 0) {
        hunger += 30;
        thirst += 10;
        deleteLs(&inventory, searchLs(&inventory, 2));

        printf("You have used a canned food!\n");
      } else {
        printf("You do not have a canned food to use!\n");
      }

    } else if (option == 3) {
      if (countLs(&inventory, 3) != 0) {
        thirst += 60;
        deleteLs(&inventory, searchLs(&inventory, 3));

        printf("You have used a bottle of water!\n");
      } else {
        printf("You do not have a bottle of water to use!\n");
      }

    } else {
      printf("Invalid choice.\n");
    }

    if (health > MAX_HEALTH) {
      health = MAX_HEALTH;
    }

    if (hunger > MAX_HUNGER) {
      hunger = MAX_HUNGER;
    }

    if (thirst > MAX_THIRST) {
      thirst = MAX_THIRST;
    }
  }
}


//score file
void registerScore(int days) {
  char nome[100];

  printf("Enter your first name to save your score\n");
  scanf("%s", nome);

  FILE *file;

  file = fopen("records.txt", "a");

  if (file == NULL) {
    printf("Something went wrong when saving your score");
    return;
  }

  fprintf(file, "Name: %s Days: %d\n", nome, days);

  fclose(file);
}

void sortScore(score arr[], int n) {
  int i, j;
  score chave;

  for (i = 1; i < n; i++) {
    chave = arr[i];
    j = i - 1;

    while (j >= 0 && arr[j].dias < chave.dias) {
      arr[j + 1] = arr[j];
      j = j - 1;
    }

    arr[j + 1] = chave;
  }
}

void readScore() {
  FILE *file;
  int numRow = 0;
  score scores[100];

  file = fopen("records.txt", "r");

  if (file == NULL) {
    file = fopen("records.txt", "w+");
    file = fopen("records.txt", "r");
    printf("Something went wrong when read scores\n");
    return;
  }

  char row[100];
  while (fgets(row, sizeof(row), file) != NULL) {
    if (sscanf(row, "Name: %99s Days: %d", scores[numRow].nome, &scores[numRow].dias) == 2) {
      numRow++;
    }
  }

  fclose(file);

  sortScore(scores, numRow);

  printf("\n-=-=-=-=-=-=-=-=-=-=-=-=TOP 5 SCORES-=-=-=-=-=-=-=-=-=-=-=-=\n");
  for (int i = 0; i < 5; i++) {
    printf("Name: %s \t| Days Survived: %d\n", scores[i].nome, scores[i].dias);
  }
}