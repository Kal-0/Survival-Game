#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lists.h"

int sizeLs(struct list** listH){
  struct list* temp = *listH;
  int size = 0;


  while(temp != NULL){
    size++;
    temp = temp->next;
  }

  return size;
}


int insertLs(struct list** listH, int index, int value, Event* event){

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
  newModule->event = event;
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


int countLs(struct list** listH, int value){
  struct list* temp = *listH;
  int size = sizeLs(listH);
  int amount = 0;

  while(temp != NULL){
    if(temp->item == value){
      amount++;
    }

    temp = temp->next;
  }

  return amount;
}

void freeLs(struct list** listH){
  struct list* temp = *listH;
  struct list* aux;

  if(*listH == NULL){
    return;
  }
  
  while(temp != NULL){
    aux = temp;
    temp = temp->next;
    
    if(aux->event != NULL){
      free(aux->event);
    }
    free(aux);
  }

  *listH = NULL;
}