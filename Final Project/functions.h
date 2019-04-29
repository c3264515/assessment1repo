#include <string.h>
#include "config.h"
#include <stdio.h>
#include <stdbool.h>

void printLoadingBar(double percentage);
int getIndex(char * word, char letter);
bool matchToDictionary(FILE * file);
void shuffle(char * array);
void thoroughShuffle(char * array, int length);