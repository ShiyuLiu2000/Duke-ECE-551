#ifndef __RAND_STORY_H__
#define __RAND_STORY_H__

#include <stdio.h>

#include "provided.h"

/*
  Step 1: Parse the story template
*/

int findUnderscore(char * line, int start);
char * fillInBlank(char * line, int start, int end, const char * word);
char * extractName(char * line, int start, int end);
void errorMessage(char * line);
char * chooseWordUpdated(char * line,
                         catarray_t * cats,
                         char * name,
                         category_t * used,
                         int control,
                         int noRepeat);
char * processBlank(char * line,
                    int start,
                    catarray_t * cats,
                    category_t * used,
                    int control,
                    int noRepeat);
char * parseLine(char * line,
                 catarray_t * cats,
                 category_t * used,
                 int control,
                 int noRepeat);
void parseStory(FILE * stream, catarray_t * cats, int control, int noRepeat);

/*
  Step 2: Read categories and words, store them appropriately
*/

void getPair(char * line, char ** name, char ** value);
int categoryIndex(char * name, catarray_t * cats);
catarray_t * addCategory(catarray_t * cats, char * name, char * value);
int wordExist(catarray_t * cats, int position, char * value);
catarray_t * addWord(catarray_t * cats, int position, char * value);
void freeCats(catarray_t * cats);
catarray_t * generateCatsFromFile(FILE * stream);

/*
  Step 3: Create a random story program combining Step 1 and 2
*/

int backwardsCount(char * name);
void addUsedWord(const char * word, category_t * used);
void freeUsed(category_t * used);

/*
  Step 4: Add the option of not reusing words
*/
void removeWord(catarray_t * cats, char * name, const char * word);
int isNoRepeat(char * option);
void tellStory(char * wordsFileName, char * storyFileName, int noRepeat);
#endif
