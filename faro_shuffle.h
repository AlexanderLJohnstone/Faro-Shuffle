int main(int argc, char* const args[]);
int validateInput(char* input);
int getValue();
char* getCardStream(char* str);
void terminateProcess();
//define node in list to represent card
struct Card{
  char val;
  char suit;
  struct Card *next;
};

struct Card* createList(char* strPtr);
struct Card* outShuffle(struct Card* list, int nCards);
struct Card* inShuffle(struct Card* list, int nCards);
void binaryConversion(int k, struct Card* head, int nCards);
int getPower(int x, int power);
void freeList(struct Card* head);
