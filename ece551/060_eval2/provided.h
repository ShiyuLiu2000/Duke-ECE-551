#ifndef __PROVIDED_H__
#define __PROVIDED_H__

#include <stdlib.h>

struct category_tag {
  char * name;     // category name string
  char ** words;   // word strings under name
  size_t n_words;  // number of words of name
};
typedef struct category_tag category_t;

struct catarray_tag {
  category_t * arr;  // categories and the corresponding words
  size_t n;          // number of categories in array
};
typedef struct catarray_tag catarray_t;

const char * chooseWord(char * category, catarray_t * cats);
void printWords(catarray_t * cats);

#endif
