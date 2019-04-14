#include <string.h>
#include <constants.h>


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
	Takes in a word and its length and returns a pattern which the program can then process.
	Eg. bobby = [0,1,0,0,2]
		puppy = [0,1,0,0,2]
		brenton = [0,1,2,3,4,5,3]

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
		else if (index != -1) 
		{
			wordPattern[i] = index;
		}
	}



}



void readDictionary(void)
{
	FILE * dictionary;
	dictionary = fopen(DICT_FILE_PATH);

}



