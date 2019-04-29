#include <stdio.h>
#include "functions.h"
#include "config.h"
#include <math.h>
#include <time.h>
#include <ctype.h>
#include <stdlib.h>

// Function prototypes for Rotation Cipher
void encryptRotation();
void decryptRotation();
void decryptRotationNoKey();

// Function prototypes for Substitution Cipher
void encryptSubsitution();
void decryptSubstitution();
void decryptSubstitutionNoKey();




// Main Function
int main()
{

    // Uses MODE from the constants header file
    switch(MODE)
    {
        case 0:
            encryptRotation();
            break;
        case 1:
            decryptRotation();
            break;
        case 2:
            decryptRotationNoKey();
            break;
        case 3:
            encryptSubsitution();
            break;
        case 4:
            decryptSubstitution();
            break;
        case 5:
            decryptSubstitutionNoKey();
            break;
        default:
            // if someone inputs an invalid method
            printf("Wtf are you doing. Not a valid mode");
    }

    

    return 0;
}



void encryptRotation()
{
    // open the files
    FILE * input = fopen(INPUT_FILE_PATH, "r");
    FILE * output = fopen(OUTPUT_FILE_PATH, "w");

    // check if the files exist
    if (!input || !output)
    {
        printf("Something went wrong");
        return;
    }

    // we use c to hold each character that we read from the file
    char c;
    c = getc(input);
    while (c != EOF)
    {
        // if character is an uppercase letter
        if (c >= A_UPPER && c <= Z_LOWER)
        {
            // convert an a-z char to a number between 0 and 25 inclusive
			c -= A_UPPER;
            
            // add the rotation
            c += ROTATION_KEY;

            // use modular arithmetic to convert all rotated numbers to a value between 0-25
            c %= ALPHABET_SIZE;

            // remap to a-z
            c += A_UPPER;
        }
        // if character is a lowercase letter
        else if (c >= A_LOWER && c <= Z_LOWER)
		{
            // convert an a-z char to a number between 0 and 25 inclusive
            c -= A_LOWER;

            // add the rotation
            c += ROTATION_KEY;

            // use modular arithmetic to convert all rotated numbers to a value between 0-25
            c %= ALPHABET_SIZE;

            // remap to a-z
            c += A_LOWER;
        }
        
        // if character is not a letter, just write to the file as it is
        fprintf(output, "%c", c);

        // get the next character
        c = getc(input);
    }

    // close the files
    fclose(input);
    fclose(output);
}

void decryptRotation()
{
    // open the files
    FILE * input = fopen(INPUT_FILE_PATH, "r");
    FILE * output = fopen(OUTPUT_FILE_PATH, "w");

    // check if the files exist
    if (!input || !output)
    {
        printf("Something went wrong");
        return;
    }

    // we use c to hold each character that we read from the file
    char c;
    c = getc(input);
    while (c != EOF)
    {
        if (c >= A_UPPER && c <= Z_UPPER)
        {
            // convert an a-z char to a number between 0 and 25 inclusive
			c -= A_UPPER;
            
            // subtract the rotation so there aren't any negative numbers
            c += ALPHABET_SIZE - ROTATION_KEY;

            // use modular arithmetic to convert all rotated numbers to a value between 0-25
            c %= ALPHABET_SIZE;

            // remap to a-z
            c += A_UPPER;
        }
        else if (c >= A_LOWER && c <= Z_LOWER)
		{
            // convert an a-z char to a number between 0 and 25 inclusive
            c -= A_LOWER;

            // subtract the rotation so there aren't any negative numbers
            c += ALPHABET_SIZE - ROTATION_KEY;
            
            // use modular arithmetic to convert all rotated numbers to a value between 0-25
            c %= ALPHABET_SIZE;

            // remap to a-z
            c += A_LOWER;
        }
        
        // if character is not a letter, just write to the file as it is
        fprintf(output, "%c", c);

        // get the next character
        c = getc(input);
    }

    // close the files
    fclose(input);
    fclose(output);
}

void decryptRotationNoKey()
{
    // track the closest found key
    int closestKey = 0;

    // test all possible keys
    for (int testKey = 0; testKey < 26; testKey++)
    {
        // print the loading bar
        printLoadingBar(testKey*100.0/26.0);
        
        // open the files
        FILE * input = fopen(INPUT_FILE_PATH, "r");
        FILE * output = fopen(OUTPUT_FILE_PATH, "w");

        // check if the files exist
        if (!input || !output)
        {
            printf("Something went wrong");
            return;
        }

        // we use c to hold each character that we read from the file
        char c;
        c = getc(input);
        while (c != EOF)
        {
            if (c >= A_UPPER && c <= Z_UPPER)
            {
                // convert an a-z char to a number between 0 and 25 inclusive
                c -= A_UPPER;
                
                // subtract the rotation so there aren't any negative numbers
                c += ALPHABET_SIZE - testKey;

                // use modular arithmetic to convert all rotated numbers to a value between 0-25
                c %= ALPHABET_SIZE;

                // remap to a-z
                c += A_LOWER;
            }
            else if (c >= A_LOWER && c <= Z_LOWER)
            {
                // convert an a-z char to a number between 0 and 25 inclusive
                c -= A_LOWER;
                
                // subtract the rotation so there aren't any negative numbers
                c += ALPHABET_SIZE - testKey;

                // use modular arithmetic to convert all rotated numbers to a value between 0-25
                c %= ALPHABET_SIZE;

                // remap to a-z
                c += A_LOWER;
            }
            
            // if character is not a letter, just write to the file as it is
            fprintf(output, "%c", c);

            // get the next character
            c = getc(input);
        }

        // check output against dictionary
        fclose(output);
        output = fopen(OUTPUT_FILE_PATH, "r");
        if (matchToDictionary(output)) closestKey = testKey;

        // close the files
        fclose(output);
        fclose(input);

    }
    
    // rewrite the output file using the best key
    FILE * input = fopen(INPUT_FILE_PATH, "r");
    FILE * output = fopen(OUTPUT_FILE_PATH, "w");
    char c = getc(input);
    while (c != EOF)
    {
        if (c >= A_UPPER && c <= Z_UPPER)
        {
            // convert an a-z char to a number between 0 and 25 inclusive
			c -= A_UPPER;
            
            // subtract the rotation so there aren't any negative numbers
            c += ALPHABET_SIZE - closestKey;

            // use modular arithmetic to convert all rotated numbers to a value between 0-25
            c %= ALPHABET_SIZE;

            // remap to a-z
            c += A_UPPER;
        }
        else if (c >= A_LOWER && c <= Z_LOWER)
		{
            // convert an a-z char to a number between 0 and 25 inclusive
            c -= A_LOWER;

            // subtract the rotation so there aren't any negative numbers
            c += ALPHABET_SIZE - closestKey;
            
            // use modular arithmetic to convert all rotated numbers to a value between 0-25
            c %= ALPHABET_SIZE;

            // remap to a-z
            c += A_LOWER;
        }
        
        //write the character to the file
        fprintf(output, "%c", c);
        c = getc(input);
    }

    // close the files
    fclose(input);
    fclose(output);
}

void encryptSubsitution()
{
    // open the files
    FILE * input = fopen(INPUT_FILE_PATH, "r");
    FILE * output = fopen(OUTPUT_FILE_PATH, "w");

    // check if the files exist
    if (!input || !output)
    {
        printf("Something went wrong");
        return;
    }


    char c;
    c = getc(input);
    while (c != EOF)
    {
        if (c >= A_UPPER && c <= Z_UPPER)
        {
            // use the key to get the correct value
			fprintf(output, "%c", SUBSTITUTION_KEY[c-A_UPPER]);
        }
        else if (c >= A_LOWER && c <= Z_LOWER)
		{
            // use the key to get the correct value
            fprintf(output, "%c", SUBSTITUTION_KEY[c-A_LOWER]);
        }
        else
        {
            // if the character is not a letter, just write it as it appears
            fprintf(output, "%c", c);
        }
        
        // get the next character
        c = getc(input);
    }
    
    // close the files
    fclose(input);
    fclose(output);
}

void decryptSubstitution()
{
    FILE * input = fopen(INPUT_FILE_PATH, "r");
    FILE * output = fopen(OUTPUT_FILE_PATH, "w");
    if (!input || !output)
    {
        printf("Something went wrong");
        return;
    }

    char c;
    c = getc(input);
    while (c != EOF)
    {
        if (c >= A_UPPER && c <= Z_UPPER)
        {
			fprintf(output, "%c", getIndex(SUBSTITUTION_KEY, c) + A_UPPER);
        }
        else if (c >= A_LOWER && c <= Z_LOWER)
		{
            fprintf(output, "%c", getIndex(SUBSTITUTION_KEY, c) + A_LOWER);
        }
        else
        {
            fprintf(output, "%c", c);
        }
        
        
        c = getc(input);
    }
    fclose(input);
    fclose(output);
}

void decryptSubstitutionNoKey()
{
    // emulating a lookup dictionary where trigramIndex holds the key and trigramCount holds the values 
    char trigramIndex[NUM_TRIGRAMS][4];
    long trigramCount[NUM_TRIGRAMS];

    // open and read the trigram file
    FILE * file = fopen(TRIGRAM_FILE_PATH, "r");
    int count = 0;
    unsigned long sum = 0;
    while(!feof(file))
    {
        long temp;
        fscanf(file, "%s %d", trigramIndex[count], &temp);
        trigramIndex[count][3] = '\0';
        trigramCount[count] = temp;
        sum += temp;

        count++;
    }
    
    // floor represents the case where a trigram does not exist
    double floor = log10(0.01/sum);

    // open and read the input file
    FILE * input = fopen(INPUT_FILE_PATH, "r");
    char wordList[MAX_FILE_LENGTH][MAX_WORD_LENGTH];
    char cipher[27];
    int wordCount = 0, chr = 0, cipherCount = 0;

    char c = getc(input);
    while (!feof(input))
    {
        
        // if space or NULL found, assign NULL into wordList[ctr]
        if(c == ' ' || c == '\n')
        {
            wordList[wordCount][chr]='\0';
            
            wordCount++;  //for next word
            chr=0;    //for next word, init index to 0
        }
        else if((c >= 65 && c <= 90) || (c >= 97 && c <= 122))
        {
            // if character is alphanumeric, write to the file
            wordList[wordCount][chr]=c;
            chr++;

            // track whether the character exists in the cipher
            bool found = false;
            for (int i = 0; i < cipherCount; i++)
            {
                if (cipherCount == 0)
                    break;
                if (cipher[i] == c)
                {
                    found = true;
                    break;
                }
            }
            if (!found)
            {
                // if character was not found in cipher
                cipher[cipherCount] = c;
                cipherCount++;
            }
            
        }
        // get next character
        c = getc(input);

    }

    // starting key
    char key[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    
    // shuffle the cipher
    thoroughShuffle(cipher, cipherCount);
    cipher[cipherCount] = '\0';

    // set a very low points value
    double points = -1000000.0;

    // initialise the optimal points value
    double maxPoints = points;
   
    // create our temperature
    double temperature = 1.0;

    // create our freezing variable which is multiplied with temperature to reduce it asymptotically
    const float freezing = 0.9998;

    // holds the best key that's been found
    char bestKey[27];

    // main loop, if temperature is > frozen
    while (temperature > 0.000001)
    {

        // creates a nice console loading bar
        printLoadingBar(sqrt(-10000*log10(temperature)/6.0));



        // stores temporary key
        char newKey[27];
        strcpy(newKey, key);
        
        // switches 2 values of the new key
        shuffle(newKey);
        
        
        // stores a temporary point value
        double p = 0.0;


        {

            // the double value of p varies drastically for some unknown reason if we do not use these intermediate double values of tempScore1 and 2
            double tempScore1 = 0.0;
            for (int i = 0; i < wordCount; i++)
            {
                // explained above 
                double tempScore2 = 0.0;

                // stores the word that has been decrypted using the cipher and key that we have made
                char decryptedWord[MAX_WORD_LENGTH];

                // holds the value of the index that the scan is up to
                int indexTracker = 0;
                for (int j = 0; j < (int)strlen(wordList[i]); j++)
                {
                    int index = getIndex(cipher, wordList[i][j]);
                    // getIndex returns -1 if the value of wordList[i][j] is not in cipher
                    if (index != -1)
                    {
                        decryptedWord[indexTracker] = newKey[index];
                        indexTracker++;
                    }
                
                }
                // add the string null character
                decryptedWord[indexTracker] = '\0';
                
                bool found = false;
                for (int j = 0; j < (int)strlen(decryptedWord)-2; j++)
                {
                    // if the word has a length less than 3 break
                    if ((int)strlen(decryptedWord)-3 < 0)
                    {
                        p += floor;
                        break;
                    }
                    
                    // create the trigram which is a substring of length 3 starting from the j-th position
                    char trigram[4] = {
                        toupper(decryptedWord[j]),
                        toupper(decryptedWord[j+1]),
                        toupper(decryptedWord[j+2]),
                        '\0'
                    };
                    
                    // iterate through and see if the trigram exists in the english language
                    for (int k = 0; k < NUM_TRIGRAMS; k++)
                    {
                        if (strcmp(trigram, trigramIndex[k]) == 0)
                        {
                            // we have found a match
                            found = true;
                            
                            // add its value to the score
                            tempScore2 += log10((double)trigramCount[k]/sum);
                            break;
                        }
                    }
                    
                }
                if (!found)
                {
                    // if we dont find the trigram, then add the floor value
                    tempScore2 += floor;
                }
                
                // add the value to the outer temporary score
                tempScore1 += tempScore2;
            }
            // add the outer temporary score to the overall points for this iteration
            p += tempScore1;
        }
        // truncate the value of p to 8 d.p.
        p = floorl(p * 1e8) * 1e-8;
    
        // analyse p against points and maxPoints
        if (p > points)
        {
            // check if it beats the maximum score so far
            if (p > maxPoints)
            {
                // save this key
                strcpy(bestKey, newKey);

                // set the maxPoints to this round
                maxPoints = p;
                
            }
            strcpy(key, newKey);
            points = p;
        }
        
        else
        {
            // randomly allocate a new key to avoid getting stuck, based on temperature
            if (rand() / (float)RAND_MAX < (float)temperature)
            {
                points = p;
                strcpy(key, newKey);
            }
        }
        
        // reduce temperature asymptotically
        temperature *= freezing;
    
    }


    // write to the output file based on the optimal key
    FILE * output = fopen(OUTPUT_FILE_PATH, "w");

    // reset position indicator
    fseek(input, 0L, SEEK_SET);

    // get character from input file
    c = getc(input);
    while (c != EOF)
    {
        if (c >= 65 && c <= 90)
        {
			fprintf(output, "%c", bestKey[getIndex(cipher, c)]);
        }
        else if (c >= 97 && c <= 122)
		{
            fprintf(output, "%c", bestKey[getIndex(cipher, c-32)]);
        }
        else
        {
            fprintf(output, "%c", c);
        }
        
        
        c = getc(input);
    }

    // close the files
    fclose(input);
    fclose(output);
}