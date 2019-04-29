#include "functions.h"
#include <ctype.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>









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




/*
	Takes in a string and character and returns the first index position of the element
	If the character is not in the string, it returns -1
*/
int getIndex(char * word, char letter)
{
	char c = word[0];
	int i = 0;
	if (c == '\0') return -1;
	while (c != '\0')
	{
        // check if the character is found
		if (word[i] == letter)
			return i;
		i++;
		c = word[i];
	}
    // returns -1 if the character is not found	
	return -1;

	
}



/*
    saves the maximum number of words found in the dictionary
    if the new maximum is greater than the old maximum, returns true, otherwise returns false
*/
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
        // reset the position indicator
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


/*
    switches 2 random elements of the array
*/
void shuffle(char * array)
{
	
	int a = rand() % 26;
	int b = rand() % 26;
	char aValue = array[b];
	array[b] = array[a];
	array[a] = aValue;
}

/*
    switches 2 random elements of the array, n times
*/
void thoroughShuffle(char * array, int n)
{
    // we use this predefinied seed since it seems to work the most effectively with a wide variety of inputs
	srand(RNG_SEED);
	for (int i = 0; i < n; i++)
	{
		int a = rand() % n;
		int b = rand() % n;
		char aValue = array[b];
		array[b] = array[a];
		array[a] = aValue;
	}
}
