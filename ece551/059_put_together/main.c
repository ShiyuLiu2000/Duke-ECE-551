#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "counts.h"
#include "kv.h"
#include "outname.h"

// Return the position index of key/value pair in dictionary; if not exist then return -1
int positionOfKV(kvarray_t * kv, const char * key) {
  for (size_t i = 0; i < kv->length; i++) {
    char * tmp = malloc(strlen(kv->array[i]->key) + 2);
    snprintf(tmp, strlen(kv->array[i]->key) + 2, "%s\n", kv->array[i]->key);
    if (strcmp(key, tmp) == 0) {
      free(tmp);
      return i;
    }
    free(tmp);
  }
  return -1;
}

// Compute the counts of values that appear in a particular input file
counts_t * countFile(const char * filename, kvarray_t * kvPairs) {
  counts_t * c = createCounts();
  FILE * f = fopen(filename, "r");
  if (f == NULL) {
    fprintf(stderr, "Cannot open file %s", filename);
    exit(EXIT_FAILURE);
  }
  size_t sz = 0;
  ssize_t len = 0;
  char * line = NULL;
  while ((len = getline(&line, &sz, f)) >= 0) {
    int position = positionOfKV(kvPairs, line);
    if (position == -1) {
      addCount(c, NULL);
    }
    else {
      addCount(c, kvPairs->array[position]->value);
    }
  }
  free(line);
  fclose(f);
  return c;
}

int main(int argc, char ** argv) {
  //WRITE ME (plus add appropriate error checking!)
  if (argc <= 2) {
    fprintf(stderr, "Usage: ./count_values kvs value0 value1 value2...");
    exit(EXIT_FAILURE);
  }
  //read the key/value pairs from the file named by argv[1] (call the result kv)
  kvarray_t * kv = readKVs(argv[1]);
  //count from 2 to argc (call the number you count i)
  for (int i = 2; i < argc; i++) {
    //count the values that appear in the file named by argv[i], using kv as the key/value pair
    //   (call this result c)
    counts_t * c = countFile(argv[i], kv);
    //compute the output file name from argv[i] (call this outName)
    char * outName = computeOutputFileName(argv[i]);
    //open the file named by outName (call that f)
    FILE * f = fopen(outName, "w+");
    //print the counts from c into the FILE f
    printCounts(c, f);
    //close f
    fclose(f);
    //free the memory for outName and c
    free(outName);
    freeCounts(c);
  }
  //free the memory for kv
  freeKVs(kv);
  return EXIT_SUCCESS;
}
