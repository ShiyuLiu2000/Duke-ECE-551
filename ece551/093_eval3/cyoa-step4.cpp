#include "cyoa.hpp"

int main(int argc, char ** argv) {
  if (argc != 2) {
    std::cout << "Usage: cyoa-step4 (path to dir)\n";
    exit(EXIT_FAILURE);
  }
  std::string dirName(argv[1]);
  dirName += "/";
  std::string story(dirName);
  story += "story.txt";
  std::ifstream commands(story.c_str());
  if (!commands.is_open()) {
    std::cerr << "Failed to find or open story.txt in " << dirName << ".\n";
    exit(EXIT_FAILURE);
  }
  std::string command;
  std::vector<Page *> pages;
  try {
    while (std::getline(commands, command).good()) {
      translateCommand(pages, command, dirName);
    }
    //checkValidReference(pages);
    checkEndingPages(pages);
    playGame(pages, 1);
  }
  catch (const std::exception & e) {
    std::cerr << "Caught an exception:\n" << e.what() << std::endl;
    cleanMemory(pages);
    commands.close();
    exit(EXIT_FAILURE);
  }
  cleanMemory(pages);
  commands.close();
  return EXIT_SUCCESS;
}
