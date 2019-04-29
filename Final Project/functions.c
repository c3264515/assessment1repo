#include "functions.h"
#include <ctype.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>





/*
	Takes in a string and character and returns the index position of the element
	If the character is not in the string, it returns -1
*/



// Correctly formats the percentage into a form where we can use it for the loading bar
void printLoadingBar(double percentage)
{
    char loadingBar[11][27] = {
        "Deciphering - |          |",
        "Deciphering - |#         |",
        "Deciphering - |##        |",
        "Deciphering - |###       |",
        "Deciphering - |####      |",
        "Deciphering - |#####     |",
        "Deciphering - |######    |",
        "Deciphering - |#######   |",
        "Deciphering - |########  |",
        "Deciphering - |######### |",
        "Deciphering - |##########|"
    };
    
    int bar = (percentage/100) * 11;
    printf("\r%s [%.1f%%]", loadingBar[bar], percentage);
}

int getIndex(char * word, char letter)
{
	char c = word[0];
	int i = 0;
	if (c == '\0') return -1;
	while (c != '\0')
	{
		if (word[i] == letter)
			return i;
		i++;
		c = word[i];
	}	
	return -1;

	
}



void getAllIndexes(char * word, char letter, int * indexes)
{
	char c = word[0];
	int i = 0, j = 0;
	while (c != '\0')
	{
		if (word[i] == letter)
			indexes[j] = i;
			j++;
		i++;
		c = word[i];
	}
	indexes[j] = -1;
}


bool matchToDictionary(FILE * file)
{
	fseek(file, 0L, SEEK_SET);
    static int closest = 0;
    char newString[100][MAX_WORD_LENGTH] = {0}; 
    char c = getc(file);

    int chr = 0, wordCount = 0;
	
    while (!feof(file))
    {
        
        if(c == ' ' || c == '\n')
        {
            newString[wordCount][chr]='\0';
            wordCount++;  
            chr=0;
        }
        else if((c >= 65 && c <= 90) || (c >= 97 && c <= 122))
        {

            newString[wordCount][chr]=c;
            chr++;
        }
        c = getc(file);
	
    }

    
    int i = 0;
    bool found = false;
    int correctCount = 0;
	FILE * dictionary = fopen(DICT_FILE_PATH, "r");
    for(int i = 0; i < wordCount; i++)
    {
        
        fseek(dictionary, 0L, SEEK_SET);
        while (!feof(dictionary))
        {
            
            char tempString[50];
            fscanf(dictionary, "%s", tempString);
            if (strcmp(tempString, newString[i]) == 0)
            {
                correctCount++;
                break;
            }
            
        }
    }
	fclose(dictionary);
    if (correctCount > closest) 
    {
        closest = correctCount;
        return true;
    }
    return false;
    
    
}

void shuffle(char * array)
{
	
	int a = rand() % 26;
	int b = rand() % 26;
	char aValue = array[b];
	array[b] = array[a];
	array[a] = aValue;
}

void thoroughShuffle(char * array, int length)
{
    // we use a predefinied seed since it seems to work the most effectively with a wide variety of inputs
	srand(RNG_SEED);
	for (int i = 0; i < length; i++)
	{
		int a = rand() % length;
		int b = rand() % length;
		char aValue = array[b];
		array[b] = array[a];
		array[a] = aValue;
	}
}





