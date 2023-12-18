#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

// count letter frequency, store in a pre-defined array "frequency"
void countFrequency(int * frequency, FILE * stream) {
  int c;
  while ((c = fgetc(stream)) != EOF) {
    if (isalpha(c)) {
      int pos = c - 'a';
      frequency[pos] += 1;
    }
  }
}

// return index of the maximum value in the array of size n
size_t findMaximum(int * array, size_t n) {
  size_t res = 0;
  for (size_t i = 0; i < n; i++) {
    if (array[i] > array[res]) {
      res = i;
    }
  }
  return res;
}

// decode the text file, return the decoder number key
int encrypt(FILE * stream) {
  int frequency[26] = {0};
  countFrequency(frequency, stream);

  // e is the letter with highest ferquency
  size_t e_pos = findMaximum(frequency, 26);

  if (e_pos < 4) {
    return 26 - (4 - e_pos);
  }
  else {
    return e_pos - 4;
  }
}

int main(int argc, char ** argv) {
  if (argc != 2) {
    fprintf(stderr, "Usage: encrypt inputFileName\n");
    exit(EXIT_FAILURE);
  }

  FILE * f = fopen(argv[1], "r");
  // ALWAYS check if fopen succeeds or not
  if (f == NULL) {
    fprintf(stderr, "Could not open file");
    exit(EXIT_FAILURE);
  }

  fprintf(stdout, "%d\n", encrypt(f));
  if (fclose(f) != 0) {
    fprintf(stderr, "Failed to close the input file!");
    exit(EXIT_FAILURE);
  }

  return EXIT_SUCCESS;
}
