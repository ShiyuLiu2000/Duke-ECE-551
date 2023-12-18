#include "rand_story.h"

int main(int argc, char ** argv) {
  // test scaffolding for step 2
  if (argc != 2) {
    fprintf(stderr, "Usage: ./story-step2 myWords.txt\n");
    exit(EXIT_FAILURE);
  }
  // open argv[1]
  FILE * stream = fopen(argv[1], "r");
  if (stream == NULL) {
    fprintf(stderr, "Failed to open file: %s\n", argv[1]);
    exit(EXIT_FAILURE);
  }
  // call generatecatsfromfile(), print, and free
  catarray_t * cats = generateCatsFromFile(stream);
  printWords(cats);
  freeCats(cats);

  // close file
  fclose(stream);

  return EXIT_SUCCESS;
}
