#include "rand_story.h"

int main(int argc, char ** argv) {
  if (argc == 3) {
    tellStory(argv[1], argv[2], 0);
  }
  else if (argc == 4) {
    int noRepeat = isNoRepeat(argv[1]);
    tellStory(argv[2], argv[3], noRepeat);
  }
  else {
    fprintf(stderr, "Usage: ./story-step4 (-n) myWords.txt myStory.txt\n");
    exit(EXIT_FAILURE);
  }
  return EXIT_SUCCESS;
}
