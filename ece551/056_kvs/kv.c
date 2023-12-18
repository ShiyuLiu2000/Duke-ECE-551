#include "kv.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Read .txt input, split the lines into key/value pairs
kvarray_t * readKVs(const char * fname) {
  // declare return value
  kvarray_t * ans = malloc(sizeof(*ans));
  ans->array = NULL;
  ans->length = 0;
  // open file
  FILE * f = fopen(fname, "r");
  if (f == NULL) {
    fprintf(stderr, "Cannot open file %s", fname);
    exit(EXIT_FAILURE);
  }
  // scan the lines of .txt file
  ssize_t len = 0;
  size_t sz = 0;
  char * line = NULL;
  size_t i = 0;
  while ((len = getline(&line, &sz, f)) >= 0) {
    // locate the first occurence of '='
    char * equal = strchr(line, (int)'=');
    if (equal == NULL) {
      fprintf(stderr, "File %s contains invalid line without '='", fname);
      exit(EXIT_FAILURE);
    }
    // resize ans->array
    ans->array = realloc(ans->array, (i + 1) * sizeof(*(ans->array)));
    ans->array[i] = malloc(sizeof(*(ans->array[i])));
    // fill in the key/value pair with given line
    ans->array[i]->key = malloc((equal - line + 1) * sizeof(*(ans->array[i]->key)));
    strncpy(ans->array[i]->key, line, (size_t)(equal - line));
    ans->array[i]->key[(int)(equal - line)] = '\0';
    ans->array[i]->value =
        malloc((strlen(line) - (equal - line + 1)) * sizeof(*(ans->array[i]->value)));
    strncpy(ans->array[i]->value,
            equal + 1,
            strlen(line) - 1 -
                (equal - line + 1));  // -1 because we don't want the newlinw character
    ans->array[i]->value[(int)(strlen(line) - 1 - (equal - line + 1))] = '\0';
    ans->length++;
    i++;
  }
  free(line);
  fclose(f);
  return ans;
}

// Free all the memory taken up by key/value dictionary
void freeKVs(kvarray_t * pairs) {
  for (size_t i = 0; i < pairs->length; i++) {
    free(pairs->array[i]->key);
    free(pairs->array[i]->value);
  }
  for (size_t i = 0; i < pairs->length; i++) {
    free(pairs->array[i]);
  }
  free(pairs->array);
  free(pairs);
}

// Print out key/value dictionary
void printKVs(kvarray_t * pairs) {
  for (size_t i = 0; i < pairs->length; i++) {
    printf("key = '%s' value = '%s'\n", pairs->array[i]->key, pairs->array[i]->value);
  }
}

// Return the first value matched with given key
char * lookupValue(kvarray_t * pairs, const char * key) {
  for (size_t i = 0; i < pairs->length; i++) {
    if (strcmp(key, pairs->array[i]->key) == 0) {
      return pairs->array[i]->value;
    }
  }
  return NULL;
}
