#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "faro_shuffle.h"
#include "print_faro_val.h"

/*Creates a linked list of Cards
* Iterates over Card stream using pointers
* Creates structs with values from input before
* adding node to end of list
*/
struct Card* createList(char* strPtr){
  int i;
  int length = strlen(strPtr);

  struct Card* start = (struct Card*)malloc(sizeof(struct Card));//hold start of linked list
  struct Card* temp = (struct Card*)malloc(sizeof(struct Card));//node to traverse linked list

  for(i = 0; i < length; i+=3){
    if(i == 0 ){
      //case for head of linked list
      start->val = *(strPtr+i);
      start->suit = *(strPtr+i+1);
      start->next = NULL;
      temp = start;
    }else{
      //case for rest of list
      struct Card* current = (struct Card*)malloc(sizeof(struct Card));//node being created
      //create next card
      current->val = *(strPtr+i);
      current->suit = *(strPtr+i+1);
      current->next = NULL;
      //append to end of list
      temp->next = current;;
      //traverse list
      temp = temp->next;
    }
  }
  return start;
}

//Method with switch case for output to comply with spec.
void print_faro_val(const char *string, enum stringplace output_type){
  switch (output_type){
    case PREFIX_IN:
        printf("%s", "IN :");
      break;
    case PREFIX_OUT:
        printf("%s", "OUT:");
      break;
    case PREFIX_START:
        printf("%s", " ");
      break;
    case CARD_VAL:
        printf("%s ", string);
      break;
    case SUFFIX:
        printf("%s\n", "EoD");
      break;
  }

}

/*This method takes a shuffled list and shuffle type and prints
 *Prints the prefixes, prints each element in turn and then
 *prints the suffix.
*/
void printShuffle(struct Card* head, enum stringplace shuffle_type){
  //print type of shuffle
  if(shuffle_type == PREFIX_IN){
    print_faro_val("", PREFIX_IN);
  }else{
    print_faro_val("", PREFIX_OUT);
  }
  print_faro_val("",PREFIX_START);

  struct Card* navigator = head;//required to navigate list
  while(navigator != NULL){//print nodes of list
    char str[3];
    str[0] =  navigator->val;
    str[1] =  navigator->suit;
    print_faro_val(str, CARD_VAL);
    navigator = navigator->next;
  }
  print_faro_val("", SUFFIX);//print suffix
}

/*This method takes the binary representation, the linked list
 * and the number of cards to perform the required shuffles.
 * The results are printed after each call.
*/
void endPrinter(struct Card* start, int binaryRep[],int nCards){
  int first1 = false;//need to find start of binary number as it's in reverse
  for(int i = 5; i >= 0; i--){
    if(first1 == true || binaryRep[i] == 1){//makes sure we've found first 1
      first1 = true;//set to one to show we've hit the start of the binary number
      if(binaryRep[i] == 1){//call in shuffle methods
        //must re-assign start as new pointer at head
        start = inShuffle(start, nCards);
        printShuffle(start, PREFIX_IN);
      }else{//call out shuffle methods
        outShuffle(start, nCards);
        printShuffle(start, PREFIX_OUT);
      }
    }
  }

}
