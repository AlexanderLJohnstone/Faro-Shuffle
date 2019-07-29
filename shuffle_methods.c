#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "faro_shuffle.h"

//method performs out shuffle
struct Card* outShuffle(struct Card* list, int nCards){
  if(nCards == 1){
    //do nothing
  }else{
    struct Card* temp = list;//node to hold half the list
    int split = nCards/2; //holds the value of half the cards given

    //loop till temp holds last card of what will be the first pile
    for(int j = 0; j < split-1; j++){
      temp = temp->next;
    }

    struct Card* temp2 = temp;//this value enables split
    temp = temp->next;
    temp2->next = NULL;

    //re-route pointers to get new order
    for(int j = 0; j < split; j++){
      temp2 = list->next;
      list->next = temp;
      temp = temp->next;
      list = list->next;
      list->next = temp2;
      list = list->next;
    }
  }
  return list;
}

//this method performs in shuffle
struct Card* inShuffle(struct Card* list, int nCards){
  struct Card* temp = list;//node to hold half the list
  struct Card* newHead = list;//node to hold half the list
  if(nCards == 1){
    //do nothing
  }else{
    int split = nCards/2; //holds the value of half the cards given

    //loop till temp holds last card of what will be the first pile
    for(int j = 0; j < split-1; j++){
      temp = temp->next;
    }
    struct Card* temp2 = temp;//this value enables split
    temp = temp->next;
    temp2->next = NULL;
    newHead = temp;

    //re-route pointers to get new order
    for(int j = 0; j < split; j++){
      temp2 = temp->next;
      temp->next = list;
      list = list->next;
      temp = temp->next;
      temp->next = temp2;
      temp = temp->next;
    }
  }
  return newHead;
}
