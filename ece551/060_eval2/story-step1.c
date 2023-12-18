#include "rand_story.h"

int main(int argc, char ** argv) {
  // test scaffolding for step 1
  if (argc != 2) {
    fprintf(stderr, "Usage: ./story-step1 myStory.txt\n");
    exit(EXIT_FAILURE);
  }
  // open argv[1]
  FILE * stream = fopen(argv[1], "r");
  if (stream == NULL) {
    fprintf(stderr, "Failed to open file: %s\n", argv[1]);
    exit(EXIT_FAILURE);
  }
  // call parseStory(f)
  parseStory(stream, NULL, 0, 0);

  // close file
  fclose(stream);

  return EXIT_SUCCESS;
}
