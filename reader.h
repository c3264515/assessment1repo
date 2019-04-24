#include <string.h>
#include "constants.h"
#include <stdio.h>
#include <stdbool.h>



void processDictionary(void);
void processWord(char * word, int length);
void toString(int * pattern, int length, char * patternStr);
void readWordPattern(char * word, int * wordPattern);
int getIndex(char * word, char letter);
bool matchToDictionary(FILE * file);
bool startsWith(const char * pre, const char * str);
void getFrequencies(FILE * file, int * frequencies);
int maxArray(int * frequencies, int length);
void fillArrangements(char arrangements[26]);
void getRandomKey(char * array);
double score(char * key, FILE * file);
void swapKeyElements(char * key);
void initialise(char * array);
void shuffle(char * array);
void thoroughShuffle(char * array, int length);
//void checkForPatterns(struct word words, char (*arrangements)[26]);






