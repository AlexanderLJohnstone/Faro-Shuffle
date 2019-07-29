#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "faro_shuffle.h"
#include "print_faro_val.h"

char const RANKSUIT[] = "RANKSUIT";
char const NUMERICAL[] = "NUMERICAL";
int const INT_MAX = 2147483647;
int const MAX_SIZE = 156; //SIZE OF 52 CARD CHAR ARRAY PLUS EOF

/*Main Method:
*Takes argument from command line for RANKSUIT or NUMERICAL
*Calls a series of subroutines to perfrom faro_shuffle
*Terminates when -1 is entered
*/
int main(int argc, char* const args[]){
  int rankOrNum = validateInput(args[1]);
  if(rankOrNum == 0){
    //do nothing
  }else{//RANKSUIT
    do{
      int nCards = getValue(); //number of cards input
      if(nCards == -1){
        terminateProcess();//exit program for poor input or exit case
      }
      int kPosition = getValue(); //desired position

      char* str = (char *)malloc((nCards*3+2) * sizeof(char)); //allocate space for cards
      char* strPtr = getCardStream(str);  //get card input

      struct Card* head = createList(strPtr);//get linked list
      binaryConversion(kPosition, head, nCards);//find binary and perform shuffles
      freeList(head);//release allocated space back to compiler
      free(str);
    }while(1 != 0);
  }
}

/*Takes input from command line
* Compares the string against RANKSUIT & NUMERICAL
* Returns value corresponding to validity (1 for Valid).
*/
int validateInput(char* input){//function validates input
  int k = strlen(input);
  int j;
  //find length of longest string
  if(k <= 8){
    j = strncmp(input, RANKSUIT, 8);

  }else{
    j = strncmp(input, RANKSUIT, k);
  }
  if(j == 0) return 1;
  return 0;
}

//Gets an integer from command line
int getValue(){
  int value;
  scanf("%d\n", &value);
  return value;
}

//Reads and returns card value stream
char* getCardStream(char* str){
  fgets(str, MAX_SIZE, stdin);
  return str;
}

/*This method gets the binary representation of k and calls the final print Method
 *The array created holds the numbers where in shuffles are required (in reverese)
 *Example K = 9, Binary = 1001, Array = {1,0,0,1,0}
 *
*/
void binaryConversion(int k, struct Card* head, int nCards){
  int binary[6] = {0};//6 is the maximum binary representation of 52 cards
  int position = 0; //keep position in array
  //create array
  if (k != 0){//if k is 0 do nothing
    do{
      double result = log10(k)/log10(2);
      binary[(int)result] = 1;
      int j = getPower(2, (int)result);
      k = k-(j);
      position++;
    }while(k != 0 && k != 1);
    //add this special clause to avoid dividing by 0 (logx(1) = 0)
    if(k == 1) {
      binary[0] = 1;
    }
    //call printer to output results
    endPrinter(head, binary, nCards);
  }

}
//this method returns a number 'x' raised to a power
int getPower(int x, int power){
  int result = x;
  for(int i = 1; i < power; i++){
    result = result*x;
  }
  return result;
}

//This method frees the memory allocated linked list one node at a time.
void freeList(struct Card* head){
  //temp required to keep rest of list from being 'lost'
    struct Card* temp;

    while(head != NULL){
      temp = head;
      head = head->next;
      free(temp);
    }
}
//exit program
void terminateProcess(){
  exit(0);
}
