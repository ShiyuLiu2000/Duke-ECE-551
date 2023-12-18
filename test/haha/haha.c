#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct _haha_t {
  char ** hahaha;
  size_t length;
};

typedef struct _haha_t haha_t;

int checkAlreadyRead(char ** read, size_t n, char * line) {
  for (size_t i = 0; i < n; i++) {
    if (strcmp(read[i], line) == 0) {
      return 1;
    }
  }
  return 0;
}

haha_t * noRepeatLines(FILE * stream) {
  haha_t * answer = malloc(sizeof(*answer));
  ssize_t len = 0;
  size_t sz = 0;
  char * line = NULL;

  answer->hahaha = NULL;
  size_t i = 0;

  while ((len = getline(&line, &sz, stream)) >= 0) {
    if (checkAlreadyRead(answer->hahaha, i, line) == 1) {
      continue;
    }
    answer->hahaha = realloc(answer->hahaha, (i + 1) * sizeof(*answer->hahaha));
    answer->hahaha[i] = line;
    line = NULL;
    i++;
  }
  answer->length = i;
  return answer;
}

void printData(char ** hahaha, size_t n) {
  for (size_t i = 0; i < n; i++) {
    printf("%s", hahaha[i]);
  }
}

void freeData(haha_t * thing) {
  for (size_t i = 0; i < thing->length; i++) {
    free(thing->hahaha[i]);
  }
  free(thing->hahaha);
  free(thing);
}

int main(int argc, char ** argv) {
  if (argc <= 1) {
    fprintf(stderr, "Usage: ./haha input.txt");
    exit(EXIT_FAILURE);
  }
  haha_t * lol = NULL;

  for (int i = 1; i < argc; i++) {
    FILE * f = fopen(argv[i], "r");
    if (f == NULL) {
      fprintf(stderr, "Cannot open file %s", argv[i]);
      exit(EXIT_FAILURE);
    }

    lol = noRepeatLines(f);
    printData(lol->hahaha, lol->length);
    freeData(lol);
    lol = NULL;

    fclose(f);
  }
  return EXIT_SUCCESS;
}
