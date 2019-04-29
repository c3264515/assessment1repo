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
#define DICT_FILE_PATH "lookup/dictionary.txt"

// Input file path
#define INPUT_FILE_PATH "input.txt"

// Output file path
#define OUTPUT_FILE_PATH "output.txt"

// Trigram file path
#define TRIGRAM_FILE_PATH "lookup/trigrams.txt"

// Rotation Cipher Key (number between 0 and 25)
#define ROTATION_KEY 1

// Substitution Cipher Key
#define SUBSTITUTION_KEY "QWERTYUIOPASDFGHJKLZXCVBNM"

// Theoretical Maximum word length
#define MAX_WORD_LENGTH 50

// Theoretical Maximum word count
#define MAX_FILE_LENGTH 100

// Number of Trigrams
#define NUM_TRIGRAMS 17556

// Uppercase A
#define A_UPPER 65

// Uppercase Z
#define Z_UPPER 90

// Lowercase A
#define A_LOWER 97

// Lowercase Z
#define Z_LOWER 122

// Size of alphabet
#define ALPHABET_SIZE 26

// Random Seed
#define RNG_SEED 1556419403


