#include "cyoa.hpp"

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

// describePage() in NormalPage (Page), print the choices
void NormalPage::describePage() const {
  Page::describePage();
  std::cout << "What would you like to do?\n\n";
  // iterate choices and print them
  size_t cur = 1;
  std::vector<std::string>::const_iterator it = choices.begin();
  while (it != choices.end()) {
    std::cout << " " << cur << ". " << *it << "\n";
    cur++;
    ++it;  // more effective than it++
  }
}

// updateChoice() in NormalPage (Page), add choice to normal page
void NormalPage::updateChoice(size_t destPage, std::string choice) {
  choices.push_back(choice);
  nextPages.push_back(destPage);
}

// describePage() in WinPage (Page), print the win message
void WinPage::describePage() const {
  Page::describePage();
  std::cout << "Congratulations! You have won. Hooray!\n";
}

// describePage() in LosePage (Page), print the lose message
void LosePage::describePage() const {
  Page::describePage();
  std::cout << "Sorry, you have lost. Better luck next time!\n";
}

// updateVariables() in Page, update the variables for command [pagenum$var=value]
void Page::updateVariables(std::string variable, long value) {
  std::map<std::string, long>::iterator it = variables.find(variable);
  if (it == variables.end()) {
    variables[variable] = value;
  }
  else {
    (*it).second = value;
  }
}

// updateInfo() in NormalPage (Page), update information vector of parameterized choices
// for command [pagenum[var=value]:dest:text]
// vector entry is in form (index, (variable, value)), where index locates the parameterized choice's dest page num in nextPages
void NormalPage::updateInfo(size_t index, std::string variable, long value) {
  std::pair<std::string, long> newPair0(variable, value);
  std::pair<size_t, std::pair<std::string, long> > newPair1(index, newPair0);
  choicesWithVarInfo.push_back(newPair1);
}

// updateParameterizedChoices () in NormalPage (Page), update choices to align with current variables
void NormalPage::updateParameterizedChoices(
    std::map<std::string, long> & storyVariables) {
  std::vector<std::pair<size_t, std::pair<std::string, long> > >::iterator it =
      choicesWithVarInfo.begin();
  while (it != choicesWithVarInfo.end()) {
    std::map<std::string, long>::iterator cur = storyVariables.find((*it).second.first);
    if ((cur == storyVariables.end() && (*it).second.second != 0) ||
        (cur != storyVariables.end() && (*cur).second != (*it).second.second)) {
      size_t index = (*it).first;
      choices[index] = "<UNAVAILABLE>";
      //   A note about using std::numeric_limits<size_t>::max():
      //   I think this is a deficiency in my design: I should have tied
      // unavailable choices to some kind of bool to make them unavailable
      // when choosed. But I realized too late (it's the end of step 4).
      //   I would need to change a lot of things if I change my design at
      // this moment. So I'm supposing there won't be more than the maximum
      // number of pages a size_t could hold in the book, to avoid conflict.
      //   Sorry I know this is a bad design and might cause security issues
      // if I'm doing real-world projects. I'll plan things more in advance
      // in future when I do other projects.
      nextPages[index] = std::numeric_limits<size_t>::max();
    }
    ++it;
  }
}

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

// Specify the exception message for UnsupportedType
UnsupportedType::UnsupportedType(std::string type) : invalidType(type) {
  message += "Found unsupported page type: ";
  message += invalidType;
  message += " when parsing story.txt.\n";
  message += "Please only create page with type N, W, or L.";
}
// Specify the exception message for InvalidCommand
InvalidCommand::InvalidCommand(std::string c) : command(c) {
  message += "Found invalid command: ";
  message += command;
  message += " when parsing story.txt.\n";
  message += "Please only write commands under input format constraints,\n";
  message += "or only add choices to normal pages.";
}

// Specify the exception message for InvalidNumber
InvalidNumber::InvalidNumber(std::string num) : number(num) {
  message += "Cannot convert ";
  message += number;
  message += " into unsigned long as page numbers.";
}

// Specify the exception message for FileOpenFailure
FileOpenFailure::FileOpenFailure(std::string name) : fileName(name) {
  message += "Failed to open file: ";
  message += fileName;
}

// Specify the exception message for PageNotOrdered
PageNotOrdered::PageNotOrdered(std::string num) : pageNumber(num) {
  message += "Cannot declare or add choices to page No.";
  message + pageNumber;
  message += " without creating pages in order.";
}

// Specify the exception message for ReferenceNotexist
ReferenceNotExist::ReferenceNotExist(size_t page, size_t reference) :
    pageNum(page), referenceNum(reference) {
  message += "Page No.";
  message += referenceNum;
  message += " referenced by Page No.";
  message += pageNum;
  message += " does not exist.";
}

// Specify the exception message for ProblematicLinkage
ProblematicLinkage::ProblematicLinkage(size_t page) : pageNum(page) {
  message += "The page No.";
  message += pageNum;
  message += " is not referenced by any other page.\n";
  message += "Please check your linkage.";
}

/*
  =========================================================
  Step 1: Print the pages with choices or win/lose messages
  =========================================================
*/

// Read page from .txt file, store the contents into a single string
std::string readFile(std::ifstream & file) {
  std::stringstream s;
  std::string line;
  while (std::getline(file, line).good()) {
    s << line << "\n";
  }
  return s.str();
}

// Create a page (normal, win, or lose)
Page * createPage(std::string type, size_t pageNum, std::string text) {
  if (type == "N") {
    return new NormalPage(pageNum, text);
  }
  else if (type == "W") {
    return new WinPage(pageNum, text);
  }
  else if (type == "L") {
    return new LosePage(pageNum, text);
  }
  else {
    throw UnsupportedType(type);
  }
}

// Slice the command into 3 parts for further procession
void sliceCommandInto3(std::string command,
                       std::vector<std::string> & subparts,
                       size_t firstIndex,
                       size_t secondIndex) {
  subparts.push_back(command.substr(0, firstIndex));
  subparts.push_back(command.substr(firstIndex + 1, secondIndex - firstIndex - 1));
  subparts.push_back(command.substr(secondIndex + 1, command.size()));
}

// Parse the command for customized procession
std::vector<std::string> parseCommand(std::string command) {
  //std::cout << "Current command is: " << command << "\n";
  std::vector<std::string> subparts;
  // locate '@' in command
  size_t atIndex = command.find_first_of('@');
  // locate first ':' in command
  size_t colonIndex = command.find_first_of(':');
  // locate '$' in command
  size_t dollarIndex = command.find_first_of('$');
  // locate '[' in command
  size_t leftIndex = command.find_first_of('[');
  // parse two command types for step 1
  if (dollarIndex == std::string::npos && leftIndex == std::string::npos) {
    if (colonIndex == std::string::npos) {
      throw InvalidCommand(command);
    }
    // Type 1: command that declares a new page [number@type:filename]
    if (atIndex != std::string::npos) {
      if (colonIndex <= atIndex) {
        throw InvalidCommand(command);
      }
      sliceCommandInto3(command, subparts, atIndex, colonIndex);
      subparts.push_back("1");  // should translate subparts as type 1
    }
    // Type 2: command that adds choice to a normal page [pagenum:destpage:text]
    else {
      // make sure there is possibility for a second colon to exist
      if (colonIndex == command.size() - 1) {
        throw InvalidCommand(command);
      }
      size_t colonSecondIndex = command.find_first_of(':', colonIndex + 1);
      if (colonSecondIndex == std::string::npos) {
        throw InvalidCommand(command);
      }
      sliceCommandInto3(command, subparts, colonIndex, colonSecondIndex);
      subparts.push_back("2");  // should translate subparts as type 2
    }
  }
  // parse two command types for step 4
  else {
    // locate '=' in command
    size_t equalIndex = command.find_first_of('=');
    if (equalIndex == std::string::npos) {
      throw InvalidCommand(command);
    }
    // Type 3: command that sets value for a variable [pagenum$var=value]
    if (dollarIndex != std::string::npos) {
      if (equalIndex <= dollarIndex) {
        throw InvalidCommand(command);
      }
      sliceCommandInto3(command, subparts, dollarIndex, equalIndex);
      subparts.push_back("3");  // should translate subparts as type 3
    }
    // Type 4: command that ties a choice to a certain value of variable
    // [pagenum[var=value]:dest:text]
    else {
      if (leftIndex == std::string::npos) {
        throw InvalidCommand(command);
      }
      // locate ']' in command
      size_t rightIndex = command.find_first_of(']');
      // make sure there is possibility for a second colon to exist
      if (colonIndex == command.size() - 1) {
        throw InvalidCommand(command);
      }
      size_t colonSecondIndex = command.find_first_of(':', colonIndex + 1);
      if (colonSecondIndex == std::string::npos) {
        throw InvalidCommand(command);
      }
      if (colonIndex <= rightIndex || rightIndex <= equalIndex ||
          equalIndex <= leftIndex) {
        throw InvalidCommand(command);
      }
      sliceCommandInto5(command,
                        subparts,
                        leftIndex,
                        equalIndex,
                        rightIndex,
                        colonIndex,
                        colonSecondIndex);
      subparts.push_back("4");  // should translate subparts as type 4
    }
  }
  //printSubparts(subparts);
  return subparts;
}

// Turn string into unsigned long using strtoul while checking validity
// flag = 0 for parsing command, flag = 1 for dealing with user input gracefully
// We set different flags to throw different exceptions accordingly
size_t myStrtoul(std::string number, int flag) {
  char * endptr = NULL;
  size_t ans = strtoul(number.c_str(), &endptr, 10);
  if (ans == 0 && *endptr != '\0') {
    if (flag == 0) {
      throw InvalidNumber(number);
    }
    if (flag == 1) {
      throw InvalidUserInput("That is not a valid choice, please try again");
    }
  }
  return ans;
}

// Translate command into corresponding types, and execute correspondingly
void translateCommand(std::vector<Page *> & pages,
                      std::string command,
                      std::string dirName) {
  if (command.empty()) {
    return;
  }
  std::vector<std::string> parts = parseCommand(command);
  size_t pageNumber = myStrtoul(parts[0], 0);
  // Type 1: declare a new page [number@type:filename]
  if (parts.size() == 4 && parts[3] == "1") {
    if (pageNumber != pages.size()) {
      throw PageNotOrdered(parts[0]);
    }
    std::string type = parts[1];
    std::string fileName(dirName);
    fileName += parts[2];
    std::ifstream file(fileName.c_str());
    if (!file.is_open()) {
      throw FileOpenFailure(fileName);
    }
    // up to this point, all is good to create a new page
    std::string text = readFile(file);
    Page * newPage = createPage(type, pageNumber, text);
    pages.push_back(newPage);
    file.close();
    return;
  }
  if (pageNumber >= pages.size()) {
    throw PageNotOrdered(parts[0]);
  }
  std::string variable = parts[1];
  // Type 3: set a value to variable [pagenum$var=value]
  if (parts.size() == 4 && parts[3] == "3") {
    long value = myStrtol(parts[2]);
    pages[pageNumber]->updateVariables(variable, value);
    return;
  }
  if (pages[pageNumber]->getType() != "N") {
    throw InvalidCommand(command);
  }
  // we are safe for a downcasting to NormalPage now, to deal with choices
  NormalPage * normalPage = static_cast<NormalPage *>(pages[pageNumber]);
  // Type 2: specify a choice [pagenum:destpage:text]
  if (parts.size() == 4 && parts[3] == "2") {
    // up to this point, all is good to specify a choice for a normal page
    size_t destPage = myStrtoul(parts[1], 0);
    std::string choice = parts[2];
    normalPage->updateChoice(destPage, choice);
  }
  // Type 4: declare a variable value-specific choice
  if (parts.size() == 6 && parts[5] == "4") {
    long value = myStrtol(parts[2]);
    size_t destPage = myStrtoul(parts[3], 0);
    std::string choice = parts[4];
    normalPage->updateChoice(destPage, choice);
    normalPage->updateInfo(normalPage->getNextPages().size() - 1, variable, value);
  }
}

// Print the pages in given format
void printPages(const std::vector<Page *> & pages) {
  std::vector<Page *>::const_iterator it = pages.begin();
  while (it != pages.end()) {
    std::cout << "Page " << (*it)->getPageNum() << "\n";
    std::cout << "==========\n";
    (*it)->describePage();
    ++it;
  }
}

// Release all the memory taken by new-ed pages
void cleanMemory(std::vector<Page *> & pages) {
  std::vector<Page *>::iterator it = pages.begin();
  while (it != pages.end()) {
    delete *it;
    ++it;
  }
}

/*
  =========================================
  Step 2: Read from input and play the game
  =========================================
*/

// Make sure all referenced pages exist, and every page is referenced by at least one other page's choice
void checkValidReference(const std::vector<Page *> & pages) {
  // construct the status map: link every page to a false boolean
  // indicating it's not referenced by any other pages yet
  std::vector<std::pair<size_t, bool> > statusMap;
  for (size_t i = 1; i < pages.size(); i++) {
    std::pair<size_t, bool> pair(i, false);
    statusMap.push_back(pair);
  }
  // update the status map by traversing all the normal pages
  std::vector<Page *>::const_iterator cit = pages.begin();
  while (cit != pages.end()) {
    if ((*cit)->getType() == "N") {
      // we are safe for downcasting to NormalPage now
      NormalPage * normalPage = static_cast<NormalPage *>(*cit);
      std::vector<size_t>::const_iterator numIt = normalPage->getNextPages().begin();
      while (numIt != normalPage->getNextPages().end()) {
        if (*numIt >= pages.size()) {
          throw ReferenceNotExist((*cit)->getPageNum(), *numIt);
        }
        if (*numIt != (*cit)->getPageNum()) {
          statusMap[*numIt - 1].second = true;
        }
        ++numIt;
      }
    }
    ++cit;
  }
  // check if every page is referenced by other page
  std::vector<std::pair<size_t, bool> >::const_iterator it = statusMap.begin();
  while (it != statusMap.end()) {
    if ((*it).second == false) {
      throw ProblematicLinkage((*it).first);
    }
    ++it;
  }
}

// Make sure both win page and lose page exist
void checkEndingPages(const std::vector<Page *> & pages) {
  std::pair<bool, bool> winLose(false, false);
  std::vector<Page *>::const_iterator cit = pages.begin();
  while (cit != pages.end()) {
    if ((*cit)->getType() == "W") {
      winLose.first = true;
    }
    if ((*cit)->getType() == "L") {
      winLose.second = true;
    }
    ++cit;
  }
  if (winLose.first == false || winLose.second == false) {
    throw LackEndingPages();
  }
}

// Play the game with user inputs
// flag == 1 for play with step 4
void playGame(const std::vector<Page *> & pages, int flag) {
  Page * cur = pages[0];
  std::map<std::string, long> storyVariables;
  while (cur->getType() == "N") {
    NormalPage * normalPage = static_cast<NormalPage *>(cur);
    updateStoryVariables(storyVariables, cur);
    normalPage->updateParameterizedChoices(storyVariables);
    normalPage->describePage();
    if (flag != 1) {
      std::cout << "\n\n";
    }
    // ready to take user input
    std::string input;
    bool isValidInput = false;
    size_t num = 0;
    while (!isValidInput) {
      try {
        input.clear();
        std::getline(std::cin,
                     input);  // use getline to end the input by hitting enter!
        num = myStrtoul(input, 1);
        if (num < 1 || num > normalPage->getNextPages().size()) {
          throw InvalidUserInput("That is not a valid choice, please try again");
        }
        if (flag == 1 &&
            normalPage->getNextPages()[num - 1] == std::numeric_limits<size_t>::max()) {
          throw InvalidUserInput(
              "That choice is not available at this time, please try again");
        }
        isValidInput = true;
      }
      catch (const InvalidUserInput & e) {
        std::cout << e.what() << std::endl;
      }
    }
    cur = pages[normalPage->getNextPages()[num - 1]];
  }
  cur->describePage();
}

/*
  =======================================================
  Step 3: DFS to find all unique non-cycled winning paths
  =======================================================
*/

// Build the story graph in the form:
// {(currentpage0, (choicenumber0, nextpage0),
//                 (choicenumber1, nextpage1),
//                 ...),
//  (currentpage1, (choicenumber0, nextpage0),
//                 (choicenumber1, nextpage1),
//                 ...),
//  ...                                       }
void buildGraph(graph & storybook, const std::vector<Page *> & pages) {
  // find out all normal pages and use them to create page nodes
  std::vector<Page *>::const_iterator cit = pages.begin();
  while (cit != pages.end()) {
    if ((*cit)->getType() == "N") {
      NormalPage * normalPage = static_cast<NormalPage *>((*cit));
      const std::vector<size_t> nextPages = normalPage->getNextPages();
      std::vector<size_t>::const_iterator cit_inner = nextPages.begin();
      size_t choiceNumber = 1;
      choiceList newChoiceList;
      while (cit_inner != nextPages.end()) {
        choiceEntry newChoiceEntry(choiceNumber, *cit_inner);
        newChoiceList.push_back(newChoiceEntry);
        choiceNumber++;
        ++cit_inner;
      }
      graphEntry newGraphEntry((*cit)->getPageNum(), newChoiceList);
      storybook.push_back(newGraphEntry);
    }
    ++cit;
  }
}

// Tell if a page node is visited or not
bool isPageVisited(size_t pagenum, const std::set<size_t> & visited) {
  return visited.find(pagenum) != visited.end();
}

// Returns a pointer to page node for further processing
const graphEntry * findPageNode(size_t pagenum, const graph & storybook) {
  graph::const_iterator cit = storybook.begin();
  while (cit != storybook.end()) {
    if ((*cit).first == pagenum) {
      return &(*cit);
    }
    ++cit;
  }
  return NULL;
}

// Define path in the following form:
// {(curpage, (choicenum, destpage)),
//  (destpage, (choicenum, nextdestpage)),
//  (nextdestpage, ...), ...}
void printPath(const path & curPath) {
  if (curPath.size() == 0) {
    return;
  }
  path::const_iterator cit = curPath.begin();
  if (curPath.size() > 1) {
    while (cit != curPath.end() - 1) {
      std::cout << (*cit).first << "(";
      std::cout << (*cit).second.first << "),";
      ++cit;
    }
  }
  std::cout << (*cit).first << "(";
  std::cout << (*cit).second.first << "),";
  std::cout << (*cit).second.second << "(win)";
  std::cout << "\n";
}

// Update the "visited" set so that same nodes can be used in different paths
void updateVisited(std::set<size_t> & visited, const path & curPath) {
  visited.clear();
  path::const_iterator cit = curPath.begin();
  while (cit != curPath.end()) {
    visited.insert((*cit).first);
    ++cit;
  }
}

// Add new paths to the top of todo stack in DFS
void updateStack(std::stack<path> & todo,
                 const graphEntry * pageNode,
                 const path & curPath) {
  if (pageNode == NULL) {
    return;
  }
  choiceList::const_iterator choice = pageNode->second.begin();
  while (choice != pageNode->second.end()) {
    path curPathCopy(curPath);
    choiceEntry newChoiceEntry((*choice).first, (*choice).second);
    pathEntry newPathEntry(pageNode->first, newChoiceEntry);
    curPathCopy.push_back(newPathEntry);
    todo.push(curPathCopy);
    ++choice;
  }
}

// Use DFS to find all unique non-cycled winning paths
void hackStory(const std::vector<Page *> & pages) {
  if (pages.size() == 0) {
    return;
  }
  if (pages[0]->getType() == "W") {
    std::cout << "0(win)\n";
    return;
  }
  if (pages[0]->getType() == "L") {
    std::cout << "The story is unwinnable!\n";
    return;
  }
  graph storybook;
  buildGraph(storybook, pages);
  std::stack<path> todo;
  std::set<size_t> visited;
  bool foundWinningPath = false;
  path curPath;
  updateStack(todo, &storybook[0], curPath);
  while (!todo.empty()) {
    curPath = todo.top();
    todo.pop();
    updateVisited(visited, curPath);
    size_t lastIndex = curPath.size() - 1;
    size_t destPageNum = curPath[lastIndex].second.second;
    if (pages[destPageNum]->getType() == "W") {
      printPath(curPath);
      foundWinningPath = true;
      continue;
    }
    if (!isPageVisited(destPageNum, visited)) {
      updateStack(todo, findPageNode(destPageNum, storybook), curPath);
    }
  }
  if (!foundWinningPath) {
    std::cout << "This story is unwinnable!\n";
  }
}

/*
  ==========================================
  Step 4: Adapt to variable-specific choices
  ==========================================
*/

// Slice the command into 5 parts for further procession
void sliceCommandInto5(std::string command,
                       std::vector<std::string> & subparts,
                       size_t firstIndex,
                       size_t secondIndex,
                       size_t thirdIndex,
                       size_t fourthIndex,
                       size_t fifthIndex) {
  if (thirdIndex + 1 != fourthIndex) {
    throw InvalidCommand(command);
  }
  subparts.push_back(command.substr(0, firstIndex));
  subparts.push_back(command.substr(firstIndex + 1, secondIndex - firstIndex - 1));
  subparts.push_back(command.substr(secondIndex + 1, thirdIndex - secondIndex - 1));
  subparts.push_back(command.substr(fourthIndex + 1, fifthIndex - fourthIndex - 1));
  subparts.push_back(command.substr(fifthIndex + 1, command.size()));
}

// Turn string into long int using strtol while checking validity
// Note that we don't use template to combine it with myStrtoul because they are
// supposed to hold different parameters.
// myStrtol does not need to handle user input so we don't need flag here
long myStrtol(std::string number) {
  char * endptr = NULL;
  long ans = strtol(number.c_str(), &endptr, 10);
  if (ans == 0 && *endptr != '\0') {
    throw InvalidNumber(number);
  }
  return ans;
}

// Debugger function to help see if we parsed the command correctly
void printSubparts(const std::vector<std::string> & parts) {
  std::cout << "Current subparts are:\n";
  size_t index = 0;
  std::vector<std::string>::const_iterator cit = parts.begin();
  while (cit != parts.end()) {
    std::cout << "Part " << index << ": " << (*cit) << "\n";
    ++cit;
  }
}

// Update the variable vector for the whole story according to the current page
void updateStoryVariables(std::map<std::string, long> & storyVariables, Page * curPage) {
  std::map<std::string, long> pageVariables = curPage->getVariables();
  std::map<std::string, long>::const_iterator cit = pageVariables.begin();
  while (cit != pageVariables.end()) {
    std::map<std::string, long>::iterator cur = storyVariables.find((*cit).first);
    if (cur == storyVariables.end()) {
      storyVariables[(*cit).first] = (*cit).second;
    }
    else {
      storyVariables[(*cur).first] = (*cit).second;
    }
    ++cit;
  }
}
