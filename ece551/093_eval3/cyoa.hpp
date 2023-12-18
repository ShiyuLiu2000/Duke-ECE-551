#ifndef __CYOA_HPP__
#define __CYOA_HPP__

#include <cstdlib>    // EXIT_SUCCESS, EXIT_FAILURE
#include <exception>  // std::exception
#include <fstream>    // std::ifstream
#include <iostream>   // std::cout
#include <istream>    // std::istream
#include <limits>     // std::numeric_limits<size_t>::max()
#include <map>        // std::map
#include <set>        // std::set
#include <sstream>    // std::stringstream
#include <stack>      // std::stack
#include <stdexcept>  // built-in exception types
#include <string>     // std::string, std::strtoul, std::strtol, std::getline
#include <vector>     // std::vector

/* 
   ==================================
   Class Definition Used In All Steps
   ==================================
*/

// The uppermost base class of page hierarchy
class Page {
  size_t pageNum;
  std::string text;
  std::string type;  // for safe downcasting check
  std::map<std::string, long> variables;

 public:
  Page(size_t num, std::string content, std::string t) :
      pageNum(num), text(content), type(t) {}
  virtual void describePage() const { std::cout << text << "\n"; };
  size_t getPageNum() const { return pageNum; }
  const std::string getType() const { return type; }
  void updateVariables(std::string variable, long value);
  std::map<std::string, long> & getVariables() { return variables; }
  virtual ~Page() {}
};

// Page -> NormalPage; a normal page with choices
class NormalPage : public Page {
  std::vector<std::string> choices;
  std::vector<size_t> nextPages;
  std::vector<std::pair<size_t, std::pair<std::string, long> > > choicesWithVarInfo;

 public:
  NormalPage(size_t num, std::string content) : Page(num, content, "N") {}
  virtual void describePage() const;
  void updateChoice(size_t destPage, std::string choice);
  const std::vector<std::string> & getChoices() const { return choices; }
  const std::vector<size_t> & getNextPages() const { return nextPages; }
  void updateInfo(size_t index, std::string variable, long value);
  void updateParameterizedChoices(std::map<std::string, long> & storyVariables);
  virtual ~NormalPage() {}
};

// Page -> WinPage; a win page
class WinPage : public Page {
 public:
  WinPage(size_t num, std::string content) : Page(num, content, "W") {}
  virtual void describePage() const;
  virtual ~WinPage() {}
};

// Page -> LosePage; a lose page
class LosePage : public Page {
 public:
  LosePage(size_t num, std::string content) : Page(num, content, "L") {}
  virtual void describePage() const;
  virtual ~LosePage() {}
};

/*
  ==============================
  Self-defined Exception Classes
  ==============================
*/

//   I learned after I did this whole project that the meaning of
// exceptions is that they are supposed to be handled gracefully.
//   That is to say if I need to exit(EXIT_FAILURE) but not to prompt
// user again, then there is no need to define so many exception
// classes like what I've done here.
//   Also, I learned that we don't have to deal with memory issues if
// we exit(EXIT_FAILURE). This is very important, because to "exit in
// failure with all memory released" is exactly the reason why I
// define different exceptions, and make them propagate out to the
// main function(see cyoa-step%.cpp), so that I can clean all the
// used memory before I exit(EXIT_FAILURE).
//   Now that I learned we do not have memory issues in this case, I
// realized that I could have written this project code in a way more
// neat and tidy way. But I decide to keep it as it was, and wrote
// down this memo, as a mark of my learning.
//   I will bear this in mind, and do better in my future projects.
//   2023.12.6  (First semester of Duke ECE MEng)

// Throw an exception when declaring pages of unknown type
class UnsupportedType : public std::exception {
  std::string message;
  std::string invalidType;

 public:
  explicit UnsupportedType(std::string type);
  virtual const char * what() const throw() { return message.c_str(); }
  virtual ~UnsupportedType() throw() {}
};

// Throw an exception when found command of wrong input format, or trying to add choice to Win/Lose Page
class InvalidCommand : public std::exception {
  std::string message;
  std::string command;

 public:
  explicit InvalidCommand(std::string c);
  virtual const char * what() const throw() { return message.c_str(); }
  virtual ~InvalidCommand() throw() {}
};

// Throw an exception when numbers in command cannot be converted properly
class InvalidNumber : public std::exception {
  std::string message;
  std::string number;

 public:
  explicit InvalidNumber(std::string num);
  virtual const char * what() const throw() { return message.c_str(); }
  virtual ~InvalidNumber() throw() {}
};

// Throw an exception when failed to open file
class FileOpenFailure : public std::exception {
  std::string message;
  std::string fileName;

 public:
  explicit FileOpenFailure(std::string name);
  virtual const char * what() const throw() { return message.c_str(); }
  virtual ~FileOpenFailure() throw() {}
};

// Throw an exception when pages are not declared in order, or choices declared before corresponding pages
class PageNotOrdered : public std::exception {
  std::string message;
  std::string pageNumber;

 public:
  explicit PageNotOrdered(std::string num);
  virtual const char * what() const throw() { return message.c_str(); }
  virtual ~PageNotOrdered() throw() {}
};

// Throw an exception when a normal page is referencing to a non-existing page
class ReferenceNotExist : public std::exception {
  size_t pageNum;
  size_t referenceNum;
  std::string message;

 public:
  ReferenceNotExist(size_t page, size_t reference);
  virtual const char * what() const throw() { return message.c_str(); }
  virtual ~ReferenceNotExist() throw() {}
};

// Throw an exception when not every page is referenced by at least one other page
class ProblematicLinkage : public std::exception {
  size_t pageNum;
  std::string message;

 public:
  explicit ProblematicLinkage(size_t page);
  virtual const char * what() const throw() { return message.c_str(); }
  virtual ~ProblematicLinkage() throw() {}
};

// Throw an exception when lack win page or lose page
class LackEndingPages : public std::exception {
 public:
  virtual const char * what() const throw() {
    return "Please make sure the story has at least 1 win page and 1 lose page.";
  }
  virtual ~LackEndingPages() throw() {}
};

// Throw an exception when user input is not acceptable
class InvalidUserInput : public std::exception {
  std::string message;

 public:
  InvalidUserInput(std::string msg) : message(msg) {}
  virtual const char * what() const throw() { return message.c_str(); }
  virtual ~InvalidUserInput() throw() {}
};

/*
  =========================================================
  Step 1: Print the pages with choices or win/lose messages
  =========================================================
*/

std::string readFile(std::ifstream & file);
Page * createPage(std::string type, size_t pageNum, std::string text);
void sliceCommandInto3(std::string command,
                       std::vector<std::string> & subparts,
                       size_t firstIndex,
                       size_t secondIndex);
std::vector<std::string> parseCommand(std::string command);
void translateCommand(std::vector<Page *> & pages,
                      std::string command,
                      std::string dirName);
size_t myStrtoul(std::string number, int flag);
void printPages(const std::vector<Page *> & pages);
void cleanMemory(std::vector<Page *> & pages);

/*
  =========================================
  Step 2: Read from input and play the game
  =========================================
*/

void checkValidReference(const std::vector<Page *> & pages);
void checkEndingPages(const std::vector<Page *> & pages);
void checkValidNextPage(NormalPage * normalPage, size_t num);
void playGame(const std::vector<Page *> & pages, int flag);

/*
  =======================================================
  Step 3: DFS to find all unique non-cycled winning paths
  =======================================================
*/

typedef std::pair<size_t, size_t> choiceEntry;
typedef std::vector<choiceEntry> choiceList;
typedef std::pair<size_t, choiceList> graphEntry;
typedef std::vector<graphEntry> graph;
typedef std::pair<size_t, choiceEntry> pathEntry;
typedef std::vector<pathEntry> path;
void buildGraph(graph & storybook, const std::vector<Page *> & pages);
bool isPageVisited(size_t pagenum, const std::set<size_t> & visited);
const graphEntry * findPageNode(size_t pagenum, const graph & storybook);
void printPath(const path & curPath);
void updateVisited(std::set<size_t> & visited, const path & curPath);
void updateStack(std::stack<path> & todo,
                 const graphEntry * pageNode,
                 const path & curPath);
void hackStory(const std::vector<Page *> & pages);

/*
  ==========================================
  Step 4: Adapt to variable-specific choices
  ==========================================
*/

void sliceCommandInto5(std::string command,
                       std::vector<std::string> & subparts,
                       size_t firstIndex,
                       size_t secondIndex,
                       size_t thirdIndex,
                       size_t fourthIndex,
                       size_t fifthIndex);
long myStrtol(std::string number);
void printSubparts(const std::vector<std::string> & parts);
void updateStoryVariables(std::map<std::string, long> & storyVariables, Page * curPage);
#endif
