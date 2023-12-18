#include "rand_story.h"

int main(int argc, char ** argv) {
  if (argc != 3) {
    fprintf(stderr, "Usage: ./story-step3 myWords.txt myStory.txt\n");
    exit(EXIT_FAILURE);
  }
  // read words, generate dictionary for cats
  FILE * dictionary = fopen(argv[1], "r");
  if (dictionary == NULL) {
    fprintf(stderr, "Failed to open file: %s\n", argv[1]);
    exit(EXIT_FAILURE);
  }
  catarray_t * cats = generateCatsFromFile(dictionary);
  fclose(dictionary);

  // read story template, parse story
  FILE * story = fopen(argv[2], "r");
  parseStory(story, cats, 1, 0);
  freeCats(cats);
  fclose(story);

  return EXIT_SUCCESS;
}
