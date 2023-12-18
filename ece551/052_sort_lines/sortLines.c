#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//This function is used to figure out the ordering of the strings
//in qsort. You do not need to modify it.
int stringOrder(const void * vp1, const void * vp2) {
  const char * const * p1 = vp1;
  const char * const * p2 = vp2;
  return strcmp(*p1, *p2);
}
//This function will sort data (whose length is count).
void sortData(char ** data, size_t count) {
  qsort(data, count, sizeof(char *), stringOrder);
}

// Convert s size_t number to string
char * size_tToString(size_t i) {
  char * res = malloc(21 * sizeof(char));
  sprintf(res, "%lu", i);
  return res;
}

// Read lines of input from stream, return an array of stirngs for these lines
char ** readFile(FILE * stream) {
  size_t sz = 0;        // reserved for use in getline()
  ssize_t len = 0;      // return value of getline()
  char ** data = NULL;  // result array of strings
  char * line = NULL;   // current buffer we are storing input line into
  size_t i = 0;         // store number of lines of input

  // let data[0] store the length of data in form of string
  data = malloc(sizeof(*data));
  data[0] = size_tToString(i);

  while ((len = getline(&line, &sz, stream)) >= 0) {
    data = realloc(
        data,
        (i + 2) *
            sizeof(
                *data));  // i+2 because data[0] is always taken up by the length of data
    data[i + 1] = line;
    line = NULL;
    i++;
  }

  free(line);
  free(data[0]);
  data[0] = size_tToString(i);

  return data;
}

// Free all the malloced memory for data, part (1/2)
void freeArray(char ** data, size_t length) {
  for (size_t i = 0; i < length + 1; i++) {
    free(data[i]);
  }
}

// Free all the malloced memory for data, part (2/2)
void freeData(char ** data) {
  size_t length = atoi(data[0]);
  freeArray(data, length);
  free(data);
}

// Perform data sort and print the sorted array
void printSortedData(char ** data) {
  size_t length = atoi(data[0]);
  char ** dummy = data;
  dummy++;
  sortData(dummy, length);
  for (size_t i = 1; i < length + 1; i++) {
    printf("%s", data[i]);
  }
}

int main(int argc, char ** argv) {
  //WRITE YOUR CODE HERE!
  char ** data = NULL;

  if (argc == 1) {
    data = readFile(stdin);
    printSortedData(data);
    freeData(data);
    data = NULL;
    return EXIT_SUCCESS;
  }

  for (int k = 1; k < argc; k++) {
    FILE * f = fopen(argv[k], "r");
    if (f == NULL) {
      fprintf(stderr, "Failed to open file %s\n", argv[k]);
      exit(EXIT_FAILURE);
    }
    data = readFile(f);
    printSortedData(data);
    freeData(data);
    data = NULL;
    fclose(f);  // remember to close the file!!
  }

  return EXIT_SUCCESS;
}
