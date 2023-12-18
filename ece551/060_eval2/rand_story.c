/*
  This program is to generate a story from template and a list of words to choose from.
  Step 1: Parse the story template
  Step 2: Read categories and words, store them appropriately
  Step 3: Create a random story program combining Step 1 and 2
  Step 4: Add the option of not reusing words
*/
#include "rand_story.h"

#include <string.h>

/* 
  Step 1: Parse the story template 
*/

// return index of '_' indicating start of blank in line[start:]; return -1 if no '_' found
int findUnderscore(char * line, int start) {
  char * dummy = line + start;
  char * position = strchr(dummy, (int)'_');
  if (position != NULL) {
    return (int)(position - line);
  }
  else {
    return -1;
  }
}

// replace _name_ with word in category name, and return the new line
char * fillInBlank(char * line, int start, int end, const char * word) {
  if (word == NULL) {
    fprintf(stderr, "Detected empty category\n");
    free(line);
    exit(EXIT_FAILURE);
  }
  int lenLine = strlen(line);
  int lenWord = strlen(word);
  char * newLine = malloc((start + lenWord + (lenLine - end)) * sizeof(*line));
  strncpy(newLine, line, start);
  strncpy(newLine + start, word, lenWord);
  if (end < lenLine - 1) {
    strcpy(newLine + start + lenWord, line + end + 1);
  }
  newLine[start + lenWord + (lenLine - end) - 1] = '\0';
  return newLine;
}

// extract name from a given blank in line
char * extractName(char * line, int start, int end) {
  char * name = malloc(sizeof(*name));
  name[0] = '\0';
  if (end - start == 1) {  // '__' is not considered an error!
    // fprintf(stderr, "Detected illegal '__' in line: %s", line);
    // free(line);
    // exit(EXIT_FAILURE);
  }
  else {
    name = realloc(name, (end - start) * sizeof(*name));
    strncpy(name, line + start + 1, end - start - 1);
    name[end - start - 1] = '\0';
  }
  return name;
}

// exit with unmatched underscores failure
void errorMessage(char * line) {
  fprintf(stderr, "Unmatched underscores found in line:\n%s", line);
  free(line);
  exit(EXIT_FAILURE);
}

// update the given chooseWord, choose words based on conditions
// accomodate step 3 and 4
char * chooseWordUpdated(char * line,
                         catarray_t * cats,
                         char * name,
                         category_t * used,
                         int control,
                         int noRepeat) {
  char * word;
  if (control == 0) {
    word = strdup(chooseWord(name, cats));
  }
  else {
    int backCount = backwardsCount(name);
    if (backCount == -1) {
      word = strdup(chooseWord(name, cats));
      addUsedWord(word, used);
      if (noRepeat == 1) {
        removeWord(cats, name, word);
      }
    }
    else {
      if (backCount > (int)used->n_words) {
        fprintf(stderr, "Cannot trace back %d words back in line:\n%s", backCount, line);
        free(name);
        free(line);
        exit(EXIT_FAILURE);
      }
      else {
        word = used->words[used->n_words - backCount];
        addUsedWord(word, used);
      }
    }
  }
  return word;
}

// process the blank, by choosing the right word and fill blank
// accomodating step 3: if control == 0 do step 1; if control == 1 do step 3
char * processBlank(char * line,
                    int start,
                    catarray_t * cats,
                    category_t * used,
                    int control,
                    int noRepeat) {
  // find the end index of blank
  int end = findUnderscore(line, start + 1);
  if (end == -1) {
    errorMessage(line);
  }
  // extract category name in the blank
  char * name = extractName(line, start, end);
  // choose an appropriate word
  char * word = chooseWordUpdated(line, cats, name, used, control, noRepeat);
  // fill in the blank with word
  char * newLine = fillInBlank(line, start, end, word);
  if (control == 0 || backwardsCount(name) == -1) {
    free(word);
  }
  free(name);
  return newLine;
}

// parse the line, filling the blanks from left to right recursively
char * parseLine(char * line,
                 catarray_t * cats,
                 category_t * used,
                 int control,
                 int noRepeat) {
  // find the start index of blank, do things while start index != -1
  int start = 0;
  start = findUnderscore(line, 0);
  int len = strlen(line);
  while (start != -1 && start < len - 1) {
    // fill in one blank
    char * newLine = processBlank(line, start, cats, used, control, noRepeat);
    free(line);
    line = newLine;
    // update start index, using substring starting from line[end+1]
    start = findUnderscore(line, 0);
    len = strlen(line);
  }
  if (start == len - 1) {
    errorMessage(line);
  }
  return line;
}

// parse the whole story by parsing lines recursively
// if control == 0 do step 1; if control == 1 do step 3
void parseStory(FILE * stream, catarray_t * cats, int control, int noRepeat) {
  // for each line of stream
  ssize_t len = 0;
  size_t sz = 0;
  char * line = NULL;
  category_t * used = NULL;
  if (control == 1) {
    used = malloc(sizeof(*used));
    used->name = NULL;
    used->words = NULL;
    used->n_words = 0;
  }
  while ((len = getline(&line, &sz, stream)) >= 0) {
    // parse the line, and print to stdout
    if (control == 0) {  // do step 1
      line = parseLine(line, NULL, NULL, 0, 0);
    }
    else {  // do step 3
      line = parseLine(line, cats, used, 1, noRepeat);
    }
    printf("%s", line);
    free(line);
    line = NULL;
  }
  // free malloced memory
  free(line);
  if (control == 1) {
    freeUsed(used);
  }
}

/*
  Step 2: Read categories and words, store them appropriately
*/

// analyze the line, get us the name and value pair initialized elsewhere
// upon call, *name and *value should both be NULL
void getPair(char * line, char ** name, char ** value) {
  size_t len = strlen(line) - 1;  // we don't want the newline character
  char * colon = strchr(line, (int)':');
  if (colon == NULL) {
    fprintf(stderr, "Invalid line: %sFormat for file should be name:value\n", line);
    free(line);
    exit(EXIT_FAILURE);
  }
  *name = malloc(sizeof(**name));
  *value = malloc(sizeof(**value));
  *name[0] = '\0';
  *value[0] = '\0';
  // case 1: ":"
  if (len == 1) {
    return;
  }
  // case 2: ":value"
  if (colon == line) {
    *value = realloc(*value, len * (sizeof(**value)));
    strncpy(*value, line + 1, len - 1);
    (*value)[len - 1] = '\0';
    return;
  }
  // case 3: "name:"
  if (colon == line + len - 1) {
    *name = realloc(*name, len * (sizeof(**name)));
    strncpy(*name, line, len - 1);
    (*name)[len - 1] = '\0';
    return;
  }
  // case 4: "name:value"
  *name = realloc(*name, (int)(colon - line + 1) * sizeof(**name));
  *value = realloc(*value, (int)(line + len - colon) * sizeof(**value));
  strncpy(*name, line, (int)(colon - line));
  (*name)[(int)(colon - line)] = '\0';
  strncpy(*value, colon + 1, (int)(line + len - colon - 1));
  (*value)[(int)(line + len - colon - 1)] = '\0';
}

// get category position in cats->arr. return -1 if category is new to cats
int categoryIndex(char * name, catarray_t * cats) {
  for (size_t i = 0; i < cats->n; i++) {
    if (strcmp(name, cats->arr[i].name) == 0) {
      // important: strcmp CANNOT take NULL!!!
      return (int)i;
    }
  }
  return -1;
}

// create a new category in cats with initializer name and value
catarray_t * addCategory(catarray_t * cats, char * name, char * value) {
  category_t newCat;
  newCat.name = name;
  newCat.words = NULL;
  newCat.n_words = 0;
  newCat.words = realloc(newCat.words, (newCat.n_words + 1) * sizeof(*newCat.words));
  newCat.words[newCat.n_words] = value;
  newCat.n_words++;
  cats->arr = realloc(cats->arr, (cats->n + 1) * sizeof(*cats->arr));
  cats->arr[cats->n] = newCat;
  cats->n++;
  return cats;
}

// check if a word already exists in cats->arr[position].words. Return 1 if exist, else 0
int wordExist(catarray_t * cats, int position, char * value) {
  for (size_t i = 0; i < cats->arr[position].n_words; i++) {
    if (strcmp(value, cats->arr[position].words[i]) == 0) {
      free(value);
      return 1;
    }
  }
  return 0;
}

// add value to an existing category in cats
catarray_t * addWord(catarray_t * cats, int position, char * value) {
  //  if (wordExist(cats, position, value) == 0) {
  cats->arr[position].words =
      realloc(cats->arr[position].words,
              (cats->arr[position].n_words + 1) * sizeof(*cats->arr[position].words));
  cats->arr[position].words[cats->arr[position].n_words] = value;
  cats->arr[position].n_words++;
  //}
  return cats;
}

// free all the memory used by cats (pay attention to NULL words!)
void freeCats(catarray_t * cats) {
  for (size_t i = 0; i < cats->n; i++) {
    free(cats->arr[i].name);
    if (cats->arr[i].n_words != 0) {
      for (size_t k = 0; k < cats->arr[i].n_words; k++) {
        free(cats->arr[i].words[k]);
      }
    }
    if (cats->arr[i].words != NULL) {
      free(cats->arr[i].words);
    }
  }
  free(cats->arr);
  free(cats);
}

// generate catarray_t * cats from given file
catarray_t * generateCatsFromFile(FILE * stream) {
  catarray_t * ans = malloc(sizeof(*ans));
  ans->arr = NULL;
  ans->n = 0;
  // for each line in stream, deal with the name and value pair
  ssize_t len = 0;
  size_t sz = 0;
  char * line = NULL;
  char * name = NULL;
  char * value = NULL;
  while ((len = getline(&line, &sz, stream)) >= 0) {
    // parse the line, update name and value
    getPair(line, &name, &value);
    // get the index of category in cats
    int position = categoryIndex(name, ans);
    // update cats with name and value accordingly (malloc!!)
    if (position == -1) {  // category does not exist
      ans = addCategory(ans, name, value);
    }
    else {  // add word to existing category
      ans = addWord(ans, position, value);
      free(name);  // important!!!!!!
    }
    // set name and value to NULL for next line input
    name = NULL;
    value = NULL;
  }
  // free line
  free(line);
  return ans;
}

/*
  Step 3: Create a random story program combining Step 1 and 2
*/

// for a given category, return its int value if it's in N*; otherwise return -1 for should not go backwards
int backwardsCount(char * name) {
  char * dummy = name;
  while (*dummy != '\0') {
    if ((int)(*dummy) < 48 || (int)(*dummy) > 57) {
      return -1;
    }
    dummy++;
  }
  if (atoi(name) == 0) {
    return -1;
  }
  else {
    return atoi(name);
  }
}

// helper function to keep record of used words
void addUsedWord(const char * word, category_t * used) {
  used->words = realloc(used->words, (used->n_words + 1) * sizeof(used->words));
  used->words[used->n_words] = strdup(word);
  used->n_words++;
}

// free the memory for storage of used words
void freeUsed(category_t * used) {
  for (size_t i = 0; i < used->n_words; i++) {
    free(used->words[i]);
  }
  if (used->words != NULL) {
    free(used->words);
  }
  free(used);
}

/*
  Step 4: Add the option of not reusing words
*/

// remove the used word from dictionary so that it cannot be chosen again
void removeWord(catarray_t * cats, char * name, const char * word) {
  // locate category and modify it
  for (size_t i = 0; i < cats->n; i++) {
    if (strcmp(name, cats->arr[i].name) == 0) {
      // locate word and delete it
      for (size_t k = 0; k < cats->arr[i].n_words; k++) {
        if (strcmp(word, cats->arr[i].words[k]) == 0) {
          free(cats->arr[i].words[k]);
          cats->arr[i].words[k] = NULL;
          for (size_t j = k; j < cats->arr[i].n_words - 1; j++) {
            cats->arr[i].words[j] = cats->arr[i].words[j + 1];
          }
          cats->arr[i].n_words--;
          return;
        }
      }
    }
  }
}

// decide whether we should process the story with repetition; 1 for yes
int isNoRepeat(char * option) {
  if (strcmp(option, "-n") != 0) {
    fprintf(stderr, "Invalid option: %s\n", option);
    exit(EXIT_FAILURE);
  }
  return 1;
}

// tell a story with given words, story template, and -n option
void tellStory(char * wordsFileName, char * storyFileName, int noRepeat) {
  // read words, generate dictionary for cats
  FILE * dictionary = fopen(wordsFileName, "r");
  if (dictionary == NULL) {
    fprintf(stderr, "Failed to open file: %s\n", wordsFileName);
    exit(EXIT_FAILURE);
  }
  catarray_t * cats = generateCatsFromFile(dictionary);
  fclose(dictionary);

  // read story template, parse story
  FILE * story = fopen(storyFileName, "r");
  if (story == NULL) {
    fprintf(stderr, "Failed to open file: %s\n", storyFileName);
    freeCats(cats);
    exit(EXIT_FAILURE);
  }
  parseStory(story, cats, 1, noRepeat);
  freeCats(cats);
  fclose(story);
}
