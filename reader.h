#include <string.h>
#include <constants.h>
#include <stdio.h>
#include <stdbool.h>








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


/*
	Function to write a word from the dictionary and its pattern to the pattern file
*/
void processWord(char * word, int length)
{
	FILE * patternFile;
	int pattern[MAX_WORD_LENGTH]; // the reason this is a constant and not using the length parameter is because the compiler was spitting errors.

	readWordPattern(word, length, pattern);

	patternFile = fopen(PATTERN_FILE_PATH, "a");
	if (!patternFile)
	{
		fclose(patternFile);
		patternFile = fopen(PATTERN_FILE_PATH, "w");
	}
	int patternStr[2*MAX_WORD_LENGTH]; // could be 2*length - 1 including the null character, but we add an extra just to be neater/safer
	toString(pattern, length, patternStr);
	fprintf("%s %s\n", patternStr, word);
	fclose(patternFile);

}

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









/*
	Takes in a word and its length and returns a pattern which the program can then process.
	Eg. bobby = 0,1,0,0,2
		puppy = 0,1,0,0,2
		brenton = 0,1,2,3,4,5,3
		parasitic = 0,1,2,1,3,4,5,4,6

*/
void readWordPattern(char * word, int length, int * wordPattern)
{
	int number = 0;
	char usedLetters[26] = {0};

	for (int i = 0; i < length; i++)
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
	}
}

/*
	Takes in a string and character and returns the index position of the element
	If the character is not in the string, it returns -1
*/
int getIndex(char * word, char letter)
{
	const char *ptr = strchr(word, letter);
	if (ptr)
	{
		return (ptr-word);
	}
	else
		return -1;
}





/*

bool inPatternFile(int * pattern)
{
	FILE * patternFile = fopen(PATTERN_FILE_PATH, "r");
	if (!patternFile)
	{
		fclose(patternFile);
		return false;
	}
	char line[50];
	char patternStr[100];
	while (fgets(line, 50, patternFile) != NULL)
	{
		toString(pattern, length, patternStr);
		if (strstr(line, patternStr))
		{
			fclose(patternFile);
			return true;
		}
	}
	fclose(patternFile);
	return false;
}

*/




