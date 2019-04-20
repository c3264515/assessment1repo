#include <string.h>
#include "constants.h"
#include <stdio.h>
#include <stdbool.h>



void processDictionary(void);
void processWord(char * word, int length);
void toString(int * pattern, int length, char * patternStr);
void readWordPattern(char * word, int length, int * wordPattern);
int getIndex(char * word, char letter);
bool matchToDictionary(FILE * file);
bool startsWith(const char * pre, const char * str);
void getFrequencies(FILE * file, int * frequencies);
int max(int * frequencies, int length);
void fillArrangements(char arrangements[26]);
void checkForPatterns(struct word words, char (*arrangements)[26]);






