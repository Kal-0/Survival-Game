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

//list
struct list{
int item;
struct list* next;
struct list* last;

};


int sizeLs(struct list** listH){
  struct list* temp = *listH;
  int size = 0;


  while(temp != NULL){
    size++;
    temp = temp->next;
  }

  return size;
}


int insertLs(struct list** listH, int index, int value){
  struct list* temp = *listH;
  int size = sizeLs(listH);
  int target = index;

  //set target
  if(index<0){
    target = size + index;
  }

  if((size-target) < 0){
    //index out of range
    return -1;
  }

  //new module
  struct list* newModule;
  newModule = (struct list*)malloc(sizeof(struct list));
  newModule->item = value;
  newModule->next = NULL;
  newModule->last = NULL;



  //go to target
  for(int i=0; i<target; i++){
    if(temp->next != NULL){
      temp = temp->next;
    }
  }


  //insertion cases

  if(*listH == NULL){
    //insert into empty-list
    *listH = newModule;
    return 0;
  }

  //debug//
  //printLs(listH);
  //printf("size: %d\ntarget: %d\ntarget value: %d\n",size, target, temp->item);
  //printf("-VV(%d)->>%d\n", value, temp->item);

  if(target == size){
  //   //insert at end

    newModule->last = temp;
    temp->next = newModule;
  //   //change tail here
  }
  else if(temp->last == NULL){
  //   //insert at beginning

    newModule->next = temp;
    temp->last = newModule;
    *listH = newModule;
  }
  else{
    //insert in the middle
    newModule->next = temp;
    newModule->last = temp->last;
    temp->last->next = newModule;
    temp->last = newModule;

  }

  return 0;

}


int deleteLs(struct list** listH, int index){
  struct list* temp = *listH;
  int size = sizeLs(listH);
  int target = index;



  //set target
  if(index<0){
    target = size + index;
  }

  if((size-target) < 0){
    //index out of range
    return -1;
  }

  //empty-list check
  if(*listH == NULL){
    return -1;
  }


  //go to target
  for(int i=0; i<target; i++){
    if(temp->next != NULL){
      temp = temp->next;
    }
  }


  //deletion cases

  //debug//
  //printf("target: %d\ntarget value: %d\n", target, temp->item);


  if(temp->last == NULL){
    //delete at beginning
    //printf("==================\n");
    if(temp->next != NULL){
      temp->next->last = NULL;
      *listH = temp->next;
    }
    else{
      *listH = NULL;
    }

  }
  else if(temp->next == NULL){
    //delete at end

    temp->last->next = NULL;
    //change tail here

  }
  else{
    //delete in the middle

    temp->last->next = temp->next;
    temp->next->last = temp->last;


  }

  free(temp);
  return 0;
}


int searchLs(struct list** listH, int value){
  struct list* temp = *listH;
  int size = sizeLs(listH);
  int index = 0;

  while(temp != NULL){
    if(temp->item == value){
      return index;
    }
    temp = temp->next;
    index++;
  }

  return -1;

}



struct list* inventory = NULL;

int health, hunger, thirst, time_of_the_day, day;


//interface
void printStatus(){
  printf("\n=======================\n");
  printf("DAY %d\n", day);
  printf("Time: %.2d:%.2d\n", time_of_the_day/100, time_of_the_day%100);
  printf("Health: %d / %d\n", health, MAX_HEALTH);
  printf("Hunger: %d / %d\n", hunger, MAX_HUNGER);
  printf("Thirst: %d / %d\n", thirst, MAX_THIRST);
  printf("\n=======================\n");

}

void loading(){
  fflush(stdout);
  usleep(500000);
  printf(".");
  fflush(stdout);
  usleep(500000);
  printf(".");
  fflush(stdout);
  usleep(500000);
  printf(".");
  fflush(stdout);
  usleep(500000);
  
}

//actions
void nextDay(){
  time_of_the_day = time_of_the_day%2400;
  day++;
  printf("\nAnother day has passed");
  loading();
  printf("\n\n");

  if (day == MAX_DAYS){
    printf("YOU WON!\n");
    printf("You have survived for %d days!\n", day);
    printf("Someone came to rescue you!\n\n");

    exit(0);
  }
}

void action(double hours, double dificulty_modifier){
  time_of_the_day += 100*hours;
  hunger -= (int)((3*dificulty_modifier)*hours);
  thirst -= (int)((5*dificulty_modifier)*hours);
  
  if(hunger > MAX_HUNGER){
    hunger = MAX_HUNGER;
  }

  if(thirst > MAX_THIRST){
    thirst = MAX_THIRST;
  }
  
  if (hunger < 0){
    health += 1*hunger;
    hunger = 0;
  }

  if (thirst < 0){
    health += 1*thirst;
    thirst = 0;
  }

  if (health < 0){
    printf("GAME OVER\n\n");
    
    printf("You died!\n");
    printf("Days survived: %d.\n", day);
    // printf("cause of death:\n");

    // if (hunger <= 0){
    //   printf("starvation\n");
    // }

    // if (thirst <= 0){
    //   printf("dehydration\n");
    // }

    exit(0);
  }
  if (time_of_the_day >= 2400){
    nextDay();
  }
}

void rest(){
  printf("You take a rest and recover some health.\n");
  health += 20;
  if (health > MAX_HEALTH){
    health = MAX_HEALTH;
  }

  action(8, 1);
  
}

void hunt(){
  printf("You go hunting for food and water");
  loading();
  printf("\n\n");

  int chance = rand() % 100;

  if (chance < 40){

    printf("You have found an wild rabbit.\n");
  
    hunger += 30;
    thirst += 30;
    
  }
  else if (chance < 75){
    printf("You have found an wild deer.\n");
    hunger += 50;
    thirst += 50;
  }
  else if (chance < 85){
    printf("You have found an wild Bear!.\n");
    health -= 25;
  }
  else{
    printf("You have lost the tracks of your prey.\n");
  }

  action(4, 1.5);
}

void scavenge(){
  printf("You scavenge for useful items.\n");
  int chance = rand() % 100;
  
  if (chance < 15){
    printf("You found a first-aid kit!\n");
    insertLs(&inventory, -1, 1);
    
  }
  else if (chance < 45){
    printf("You found some canned food.\n");
    insertLs(&inventory, -1, 2);
  }
  else if (chance < 80){
    printf("You found a bottle of water.\n");
    insertLs(&inventory, -1, 3);
  }
  else if (chance < 90){
    printf("You found a gun.\n");
    insertLs(&inventory, -1, 4);
  }
  else{
    printf("You didn't find anything useful.\n");
  }
  action(2, 3);
}

void openInventory(){
  
}




int main()
{
    srand(time(NULL));
    health = MAX_HEALTH;
    hunger = MAX_HUNGER;
    thirst = MAX_THIRST;
    time_of_the_day = STARTING_HOUR;
    day = 0;
    while (1)
    {
      printStatus();
      printf("Choose an action:\n");
      printf("-1.  Quit Game\n");
      printf("0.   Inventory\n");
      printf("1.   Rest\n");
      printf("2.   Hunt\n");
      printf("3.   Scavenge\n");
      int choice;
      scanf("%d", &choice);
      printf("\n");

      switch (choice){
        case 1:
          rest();
          break;
        case 2:
          hunt();
          break;
        case 3:
          scavenge();
          break;
        default:
          printf("Invalid choice.\n");
          continue;
      }
    
      // usleep(100000); // wait for a short time (100 ms)
    }
    return 0;
}