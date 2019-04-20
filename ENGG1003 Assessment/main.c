#include <stdio.h>
#include "reader.h"
#include "constants.h"

void encryptRotation(int key);
void decryptRotation(int key);
void decryptRotationNoKey(void);

void encryptSubsitution();
void decryptSubstitution(void);
void decryptSubstitutionNoKey(void);

struct word
{
    int pattern[MAX_WORD_LENGTH];
    char text[MAX_WORD_LENGTH];
};


int main()
{
    switch(MODE)
    {
        case 0:
            encryptRotation(ROTATION_KEY);
            break;
        case 1:
            decryptRotation(ROTATION_KEY);
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
            printf("Wtf are you doing. Not a valid mode");
    }

    

    return 0;
}



void encryptRotation(int key)
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
        if (c >= 65 && c <= 90)
        {
			c -= 65;
            c += key;
            c %= 26;
            c += 65;
        }
        else if (c >= 97 && c <= 122)
		{
            c -= 97;
            c += key;
            c %= 26;
            c += 97;
        }
        
        fprintf(output, "%c", c);
        c = getc(input);
    }
    fclose(input);
    fclose(output);
}

void decryptRotation(int key)
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
        if (c >= 65 && c <= 90)
        {
			c -= 65;
            c += 26 - key;
            c %= 26;
            c += 65;
        }
        else if (c >= 97 && c <= 122)
		{
            c -= 97;
            c += 26 - key;
            c %= 26;
            c += 97;
        }
        
        fprintf(output, "%c", c);
        c = getc(input);
    }
    fclose(input);
    fclose(output);
}

void decryptRotationNoKey(void)
{
    int closestKey = 0;
    for (int testKey = 0; testKey < 26; testKey++)
    {
        printf("Testing key: %d....\n", testKey);
        printf("Current closest key: %d\n", closestKey);
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
            if (c >= 65 && c <= 90)
            {
                c -= 65;
                c += 26 - testKey;
                c %= 26;
                c += 97;
            }
            else if (c >= 97 && c <= 122)
            {
                c -= 97;
                c += 26 - testKey;
                c %= 26;
                c += 97;
            }
            
            fprintf(output, "%c", c);
            c = getc(input);
        }
        fclose(input);
        fclose(output);
        output = fopen(OUTPUT_FILE_PATH, "r");
        
        if (matchToDictionary(output)) closestKey = testKey;
    }
    decryptRotation(closestKey);
}
void encryptSubsitution(void)
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
        if (c >= 65 && c <= 90)
        {
			fprintf(output, "%c", SUBSTITUTION_KEY[c-65]);
        }
        else if (c >= 97 && c <= 122)
		{
            fprintf(output, "%c", SUBSTITUTION_KEY[c-97]);
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

void decryptSubstitution(void)
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
        if (c >= 65 && c <= 90)
        {
			fprintf(output, "%c", getIndex(SUBSTITUTION_KEY, c) + 65);
        }
        else if (c >= 97 && c <= 122)
		{
            fprintf(output, "%c", getIndex(SUBSTITUTION_KEY, c) + 97);
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

void decryptSubstitutionNoKey(void)
{
    FILE * input = fopen(INPUT_FILE_PATH, "r");
    int frequencies[26] = {0};
    processDictionary();
    getFrequencies(input, frequencies);
    fclose(input);

    
    char possibleArrangements[26][26];
    for (int i = 0; i < 26; i++)
    {
        fillArrangements(possibleArrangements[i]);
    }



    input = fopen(INPUT_FILE_PATH, "r");

    char wordList[100][MAX_WORD_LENGTH];
    int wordCount = 0, chr = 0;
    char c = getc(input);
    while (!feof(input))
    {
        
        // if space or NULL found, assign NULL into newString[ctr]
        if(c == ' ' || c == '\n')
        {
            wordList[wordCount][chr]='\0';
            
            wordCount++;  //for next word
            chr=0;    //for next word, init index to 0
        }
        else if((c >= 65 && c <= 90) || (c >= 97 && c <= 122))
        {
            //printf("%c", c);
            wordList[wordCount][chr]=c;
            chr++;
        }
        c = getc(input);

    }
    struct word words[wordCount];
    for (int i = 0; i < wordCount; i++)
    {
        strcpy(words[i].text, wordList[i]);
        readWordPattern(words[i].text, strlen(words[i].text), words[i].pattern);

    }

    bool solved = false;
    do
    {
        checkForPatterns(words, possibleArrangements);
        
        cleanse();

    } while (!solved)
    
    



}