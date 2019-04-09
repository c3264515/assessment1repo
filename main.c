#include <stdio.h>
#include <regex.h>

int main()
{
	char encryptionKey[] = "ZABCDEFGHIJKLMNOPQRSTUVWXY";
	int frequency[26] = {0};



}

void decryptRotation(char * file, char * encryptionKey)
{
	char word[20];
	int size = getNextWord(word);
	char newWord[size+1];
	memcpy( newWord, &word, size);
	newWord[size] = '\0';
	for (int i = 0; i < 26; i++)
	{

	}
}


int getNextWord(char * word)
{
	static int index = 0;
	int wordSize = 0;
	while (isalpha(dictionary[index])) {
		wordSize++;
		index++;
	}

	for (int i = 0; i < wordSize; i++)
		word[i] = dictionary[i];

	return wordSize;
}

int readFile(char * file, char * frequency, char * filePath)
{
	FILE * input;
	input = fopen(filePath, "r");
	int length = 0;
	while (!feof(input))
	{
		
		char letter;
		fscanf(input, "%c", &letter);
		file[length] = letter;
		if (letter >= 65 && letter <= 90)
			frequency[letter-65] ++;
		else if (letter >= 97 && letter <= 122)
			frequency[letter-97] ++;
		length++;
	}
	return length;
}
