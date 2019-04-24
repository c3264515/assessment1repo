#include <stdio.h>
#include "reader.h"
#include "constants.h"
#include <math.h>
#include <time.h>
#include <ctype.h>
#include <stdlib.h>


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
    printf("Test");   
    // emulating a lookup dictionary where trigramIndex holds the key and trigramCount holds the values 
    char trigramIndex[NUM_TRIGRAMS][4];
    long trigramCount[NUM_TRIGRAMS];

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
    printf("%lu", sum);
    /*for (int i = 0; i < NUM_TRIGRAMS; i++)
    {
        trigramCount[i] = log10(trigramCount[i]/sum);
        if (strcmp("WIT", trigramIndex[i]) == 0)
            
        
    }
*/
    double floor = log10(0.01/sum);
    //printf("%lf", floor);

    FILE * input = fopen(INPUT_FILE_PATH, "r");
    //char fullText[MAX_WORD_LENGTH*MAX_FILE_LENGTH];
    char wordList[MAX_FILE_LENGTH][MAX_WORD_LENGTH];
    char cipher[27];
    int wordCount = 0, chr = 0, cipherCount = 0;
    char c = getc(input);
    int fullTextIndex = 0;
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
                printf("\nadded %c at index %d", c, cipherCount);
                cipher[cipherCount] = c;
                cipherCount++;
            }
            
        }
        //fullText[fullTextIndex] = c;
        //fullTextIndex++;
        c = getc(input);

    }
    //fullText[fullTextIndex] = '\0';

    char key[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    
    thoroughShuffle(cipher, cipherCount);
    cipher[cipherCount] = '\0';
    printf("\nCipher: %s\n", cipher);
    double points = -1000000.0;
    double maxPoints = points;
    printf("\nP: %lf\n", points);
    printf("\nMP: %lf\n", maxPoints);
    double temperature = 1.0;

    const float freezing = 0.9998;

    char bestKey[27];

    //printf("%s", cipher);
    printf("%s", key);
    while (temperature > 0.000001)
    {
        char newKey[27];
        strcpy(newKey, key);
        

        shuffle(newKey);
        
        
        
        
        
        double p = 0.0;


        {
            double tempScore1 = 0.0;
            for (int i = 0; i < wordCount; i++)
            {
                //printf("time");
                double tempScore2 = 0.0;
                char decryptedWord[MAX_WORD_LENGTH];
                //printf("%d\n", strlen(wordList[1]));
                int indexTracker = 0;
                for (int j = 0; j < (int)strlen(wordList[i]); j++)
                {
                    int index = getIndex(cipher, wordList[i][j]);
                    if (index != -1)
                    {
                        decryptedWord[indexTracker] = newKey[index];
                        indexTracker++;
                    }
                
                }
                decryptedWord[indexTracker] = '\0';
                //printf("%lf", p);
                
                //printf("Where");
                //printf("%d", (int)strlen(decryptedWord)-2);
                bool found = false;
                for (int j = 0; j < (int)strlen(decryptedWord)-2; j++)
                {
                    //printf("enter");
                    //printf("%d", (int)strlen(decryptedWord)-3<0);
                    if ((int)strlen(decryptedWord)-3 < 0)
                    {
                        //printf("1added floor\n");
                        p += floor;
                    }
                    
                    char trigram[4] = {
                        toupper(decryptedWord[j]),
                        toupper(decryptedWord[j+1]),
                        toupper(decryptedWord[j+2]),
                        '\0'
                    };
                    
                    for (int k = 0; k < NUM_TRIGRAMS; k++)
                    {
                        //printf("\n\nTHIS IS THE TRIGRAM: %s\n\n", trigram);
                        if (strcmp(trigram, trigramIndex[k]) == 0)
                        {
                            //printf("\nfound %s", trigram);
                            found = true;
                            //printf("\nbefore %f", tempScore2);
                            //printf("\nVALUE OF trigram[k], k : %ld, %d", trigramCount[k], k);
                            //printf("\nvalue to add: %f", log10((double)trigramCount[k]/sum));
                            tempScore2 += log10((double)trigramCount[k]/sum);
                            //printf("\nafter %f\n", tempScore2);
                            break;
                        }
                    }
                    //printf("two");
                    
                }
                if (!found)
                {
                    //printf("2 added floor");
                    //printf("\nbefore %f", tempScore2);
                    //printf("\nvalue to add: %f", floor);
                    tempScore2 += floor;
                    //printf("\nafter %f\n", tempScore2);
                }
                //printf("\nbefore %f", tempScore1);
                //printf("\nvalue of %f added to tempScore1", tempScore2);
                tempScore1 += tempScore2;
                //printf("\naftermath: %f\n", tempScore1);
            }
            //printf("\nbefore %f", p);
           // printf("\nvalue of %f added to p -----------", tempScore1);
            p += tempScore1;
            //printf("\naftermath: %f\n", p);
        }
        p = floorl(p * 1e8) * 1e-8;
        if (p > points)
        {
            //printf("Entered\n");
            //printf("\n\n%f\n\n", maxPoints);
            if (p > maxPoints)
            {
                strcpy(bestKey, newKey);
                maxPoints = p;
                printf("\nTemperature %lf\n", temperature);
                //printf("POINTS %lf\n", p);
                //printf("KEY %s\n", newKey);
                char decryptedWord[MAX_WORD_LENGTH];
                //printf("%d", wordCount);
                for (int i = 0; i < wordCount; i++)
                {
                    /*
                    if (isalpha(fullText[i])) {
                        int index = getIndex(cipher, fullText[i]);
                        //printf("index: %s\n", cipher);
                        if (index != -1)
                        {
                            fullText[i] = newKey[index];
                        }
                    }
                    printf("%c", fullText[i]);
                    */
                    //printf("%d", strlen(wordList[i]));
                    int indexTracker = 0;
                    for (int j = 0; j < (int)strlen(wordList[i]); j++)
                    {
                        int index = getIndex(cipher, wordList[i][j]);
                        //printf("index: %s\n", cipher);
                        if (index != -1)
                        {
                            decryptedWord[indexTracker] = newKey[index];
                            indexTracker++;
                        }
                    }
                    decryptedWord[(int)strlen(wordList[i])] = '\0';
                    printf("%s ", decryptedWord); 
                }
            }
            strcpy(key, newKey);
            points = p;
        }
        
        else
        {
            
            //printf("%d\n\n", (rand() / (float)RAND_MAX) < (float)temperature);
            if (rand() / (float)RAND_MAX < (float)temperature)
            {
                points = p;
                strcpy(key, newKey);
            }
        }
        //printf("\n\n1 %f\n\n", rand()/(float)RAND_MAX);
        temperature *= freezing;
        //printf("%f", temperature);

        //printf("%s\n", newKey);
    
    }



    FILE * output = fopen(OUTPUT_FILE_PATH, "w");
    fseek(input, 0L, SEEK_SET);
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
    fclose(input);
    fclose(output);




















    /*
    
    
    
    char key[26];
    getRandomKey(key);
    for (int i = 0; i < 1000; i++)
    {
        char testKey[26] = key;
        fseek(input, 0L, SEEK_SET);
        double fitness1 = score(key, input);
        swapKeyElements(testKey);
        double fitness2 = score(testKey, input);
        if (fitness2 > fitness1)
        {
            key = testKey;
        }


    }
    



    /*
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
        //checkForPatterns(words, possibleArrangements);
        
        //cleanse();

    } while (!solved);
    
    
    */

    



}