#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include "game.h"

// Para excutar: gcc -o naufrago .\SurvivalGame.c .\lists.c .\game.c

int main()
{
    srand(time(NULL));
    mainHistory();
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
        case 0:
          openInventory();
          break;
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