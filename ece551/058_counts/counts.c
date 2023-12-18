#include "counts.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Allocate memory and initialize counts dictionary without counting anything
counts_t * createCounts(void) {
  counts_t * counts = malloc(sizeof(*counts));
  counts->array = NULL;
  counts->length = 0;
  counts->unknown = 0;
  return counts;
}

// Return position of name in counts if exist, else return -1
int nameInCounts(counts_t * counts, const char * name) {
  for (int i = 0; i < (int)counts->length; i++) {
    if (strcmp(name, counts->array[i]->name) == 0) {
      return i;
    }
  }
  return -1;
}

// Add name counts in appearance order
void addCount(counts_t * counts, const char * name) {
  if (name == NULL) {
    counts->unknown++;
    return;
  }
  int position = nameInCounts(counts, name);
  if (position == -1) {
    // initialize name struct
    counts->length++;
    counts->array = realloc(counts->array, counts->length * (sizeof(*counts->array)));
    counts->array[counts->length - 1] =
        malloc(sizeof(*counts->array[counts->length - 1]));
    counts->array[counts->length - 1]->name = malloc((strlen(name) + 1) * sizeof(char));
    strncpy(counts->array[counts->length - 1]->name, name, strlen(name));
    counts->array[counts->length - 1]->name[strlen(name)] = '\0';
    counts->array[counts->length - 1]->time = 1;
  }
  else {
    counts->array[position]->time++;
  }
}

void printCounts(counts_t * counts, FILE * outFile) {
  if (counts->unknown > 0) {
    counts->array = realloc(counts->array, (counts->length + 1) * sizeof(*counts->array));
    counts->array[counts->length] = malloc(sizeof(*counts->array[counts->length]));
    counts->array[counts->length]->name = malloc(11 * sizeof(char));
    strncpy(counts->array[counts->length]->name, "<unknown> ", 11);
    counts->array[counts->length]->time = counts->unknown;
    counts->length++;
  }
  for (size_t i = 0; i < counts->length; i++) {
    fprintf(outFile, "%s: %d\n", counts->array[i]->name, counts->array[i]->time);
  }
}

void freeCounts(counts_t * counts) {
  for (size_t i = 0; i < counts->length; i++) {
    free(counts->array[i]->name);
    free(counts->array[i]);
  }
  free(counts->array);
  free(counts);
}
