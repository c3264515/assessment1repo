#include "reader.h"
#include <ctype.h>
#include <stdlib.h>
#include <time.h>

/*
	Function to write a word from the dictionary and its pattern to the pattern file
*/

/*
	Converts int pattern array to a formatted string which we can process easily later
	ie. {0,1,2,1,1} -> "0,1,2,1,1"
*/
void toString(int * pattern, int length, char * patternStr)
{
	patternStr[0] = pattern[0];
	for(int i = 1; i < length; i++)
	{
		patternStr[2*i-1] = ',';
		patternStr[2*i] = (char)pattern[i];
	}
	patternStr[2*length-1] = '\0';
	
}



void getFrequencies(FILE * file, int * frequencies)
{
    char c = getc(file);
    while (!feof(file))
    {
		if (c >= 65 && c <= 90)
			frequencies[c-65] ++;
		else if (c >= 97 && c <= 122)
			frequencies[c-97] ++;
        c = getc(file);

    }
}









/*
	Takes in a word and its length and returns a pattern which the program can then process.
	Eg. bobby = 0,1,0,0,2
		puppy = 0,1,0,0,2
		brenton = 0,1,2,3,4,5,3
		parasitic = 0,1,2,1,3,4,5,4,6

*/
void readWordPattern(char * word, int * wordPattern)
{
	int number = 0;
	char usedLetters[26] = {0};
	int i = 0;
	while (word[i] != '\0')
	{
		int index = getIndex(usedLetters, word[i]);
		if (index == -1)
		{
			usedLetters[number] = word[i];
			wordPattern[i] = number;
			number++;
		}
		else //if (index != -1) 
		{
			wordPattern[i] = index;
		}
		i++;
	}
}

/*
	Takes in a string and character and returns the index position of the element
	If the character is not in the string, it returns -1
*/
int getIndex(char * word, char letter)
{
	char c = word[0];
	int i = 0;
	//printf("\nI: %c\n", c);
	if (c == '\0') return -1;
	while (c != '\0')
	{
		//printf("\nI: %c\n", word[i]);
		if (word[i] == letter)
			return i;
		i++;
	}	
	return -1;
}







bool inPatternFile(char * pattern)
{
	FILE * patternFile = fopen(PATTERN_FILE_PATH, "r");
	if (!patternFile)
	{
		fclose(patternFile);
		return false;
	}
	char line[MAX_WORD_LENGTH];
	while (fgets(line, 50, patternFile) != NULL)
	{
		if (strstr(line, pattern))
		{
			fclose(patternFile);
			return true;
		}
	}
	fclose(patternFile);
	return false;
}



void processWord(char * word, int length)
{
	FILE * patternFile;
	int pattern[MAX_WORD_LENGTH]; // the reason this is a constant and not using the length parameter is because the compiler was spitting errors.

	readWordPattern(word, pattern);

	patternFile = fopen(PATTERN_FILE_PATH, "a");
	if (!patternFile)
	{
		fclose(patternFile);
		patternFile = fopen(PATTERN_FILE_PATH, "w");
	}
	char patternStr[2*MAX_WORD_LENGTH]; // could be 2*length - 1 including the null character, but we add an extra just to be neater/safer
	toString(pattern, length, patternStr);
	fprintf(patternFile, "%s %s\n", patternStr, word);
	fclose(patternFile);

}
void processDictionary(void)
{
	/*
	FILE * dictionary;
	dictionary = fopen(DICT_FILE_PATH, "r");
	int lines = 1, max = 0;
	int maxCounter = 0;
	char chr;
	chr = getc(dictionary);
    while (chr != EOF)
    {
        //Count whenever new line is encountered
        if (chr == '\n')
            lines++;
        
        //take next character from file.
        chr = getc(dictionary);
    }

    fclose(dictionary);


*/

	char word[MAX_WORD_LENGTH];

    FILE * dictionary = fopen(DICT_FILE_PATH, "r");
    do
    {
        fscanf(dictionary, "%s", word);
    	processWord(word, strlen(word));
    } while (word && !feof(dictionary)); // word does not become null at EOF, so feof(..) is necessary

	
}






bool matchToDictionary(FILE * file)
{
    static int closest = 0;
    char newString[100][MAX_WORD_LENGTH] = {0}; 
    char c = getc(file);

    int chr = 0, wordCount = 0;
    while (!feof(file))
    {
        
        // if space or NULL found, assign NULL into newString[ctr]
        if(c == ' ' || c == '\n')
        {
            newString[wordCount][chr]='\0';
            wordCount++;  //for next word
            chr=0;    //for next word, init index to 0
        }
        else if((c >= 65 && c <= 90) || (c >= 97 && c <= 122))
        {
            //printf("%c", c);
            newString[wordCount][chr]=c;
            chr++;
        }
        c = getc(file);
    }

    //printf("here");
    //printf("\n= %d\n", wordCount);
    
    int i = 0;
    bool found = false;
    int correctCount = 0;
	FILE * dictionary = fopen(DICT_FILE_PATH, "r");
    for(int i = 0; i < wordCount; i++)
    {
        
        fseek(dictionary, 0L, SEEK_SET);
        //printf("%s", newString[i]);
        while (!feof(dictionary))
        {
            
            char tempString[50];
            fscanf(dictionary, "%s", tempString);
            //printf("Checking %s", tempString);
            if (strcmp(tempString, newString[i]) == 0)
            {
                correctCount++;
                break;
            }
            
        }
        
        //printf("== %d\n", correctCount);
        
    }
	fclose(dictionary);
    if (correctCount > closest) 
    {
        closest = correctCount;
        return true;
    }
    return false;
    
    
}




int maxArray(int * frequencies, int length)
{
    int max = 0;
    for (int i = 0; i < length; i++)
    {
        if (max < frequencies[i])
            max = frequencies[i];
    }
    return max;
}

void fillArrangements(char * arrangements)
{
    for (int i = 0; i < 26; i++)
        arrangements[i] = (char)i;
}










void hackSimpleSub(char * message)
{
	char intersectedMapping[26][26];
	for (int i = 0; i < 26; i++)
	{
		initialise(intersectedMapping[i]);
	}

	FILE * input = fopen(INPUT_FILE_PATH, "r");
	char c = getc(input);
	char newString[MAX_FILE_LENGTH][MAX_WORD_LENGTH];
	int wordCount = 0;
	int chr = 0;
	while (!feof(input))
    {
        
        // if space or NULL found, assign NULL into newString[ctr]
        if(c == ' ' || c == '\n')
        {
            newString[wordCount][chr]='\0';
            wordCount++;  //for next word
            chr=0;    //for next word, init index to 0
        }
        else if((c >= 65 && c <= 90) || (c >= 97 && c <= 122))
        {
            //printf("%c", c);
            newString[wordCount][chr]=c;
            chr++;
        }
        c = getc(input);
    }

	for (int i = 0; i < MAX_FILE_LENGTH; i++)
	{
		char candidateMap[26][26];
		for (int i = 0; i < 26; i++)
		{
			initialise(candidateMap[i]);
		}
		int pattern[strlen(newString[i])];
		readWordPattern(newString[i], pattern);
		char patternString[sizeof(pattern)*2];
		toString(pattern, sizeof(pattern), patternString);
		if (!inPatternFile(patternString))
			continue;


	}

}

void initialise(char * array)
{
	for (int i = 0; i < 26; i++)
	{
		array[i] = -1;
	}


}




void getRandomKey(char * array)
{
	for (int i = 0; i < 26; i++)
	{
		array[i] = i + 'A';
	}
	
	for (int i = 0; i < 26-1; i++)
	{
		int j = i + rand() / ((double)RAND_MAX / (26 - i) + 1);
		char t = array[j];
		array[j] = array[i];
		array[i] = t;
	}
	
}





// This is the important function to the whole decryption process
double score(char * key, FILE * file)
{
	fseek(file, 0L, SEEK_SET);
}

void swapKeyElements(char * key)
{

}




void shuffle(char * array)
{
	
	int a = rand() % 26;
	int b = rand() % 26;
	//printf("%d %d\n", a, b);
	char aValue = array[b];
	array[b] = array[a];
	array[a] = aValue;
}

void thoroughShuffle(char * array, int length)
{
	//srand(1500050);
	for (int i = 0; i < length; i++)
	{
		int a = rand() % length;
		int b = rand() % length;
		//printf("%d %d\n", a, b);
		char aValue = array[b];
		array[b] = array[a];
		array[a] = aValue;
		//printf("%d %d, %d %d\n", a, b, array[a], array[b]);
		//printf("%s\n", array);
	}
}