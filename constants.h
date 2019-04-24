/*

	Program Mode

	Modes:
	0 - Encrypt Rotation
	1 - Decrypt Rotation with key
	2 - Decrypt Rotation without key

	3 - Encrypt Subsitution
	4 - Decrpyt Substitution with key
	5 - Decrpyt Substitution without key
*/ 
#define MODE 5





// File path to dictionary
#define DICT_FILE_PATH "dictionary.txt"

// Pattern file
#define PATTERN_FILE_PATH "patterns.txt"

// Input file path
#define INPUT_FILE_PATH "input.txt"

// Output file path
#define OUTPUT_FILE_PATH "output.txt"

// Trigram file path
#define TRIGRAM_FILE_PATH "trigrams.txt"

// Rotation Cipher Key (number between 0 and 25)
#define ROTATION_KEY 1

// Substitution Cipher Key
#define SUBSTITUTION_KEY "QWERTYUIOPASDFGHJKLZXCVBNM"

// Theoretical Maximum word length
#define MAX_WORD_LENGTH 50

// Theoretical Maximum word count
#define MAX_FILE_LENGTH 50

// Number of Trigrams
#define NUM_TRIGRAMS 17556

