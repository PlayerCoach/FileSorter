#include <iostream>
#include "fileHandler.h"
#include "const.h"
#include "cmdConst.h"
#include <string>
#include <vector>
#include <sstream>
#include "sorter.h"
#include "naturalMergeSort.h"
#include "sortingStrategy.h"

class mainController
{
private:
    fileHandler fileHandler;
    std::string filePath;
public:
    mainController();
    void printMenu();
    bool getUserInput();
    bool parseInput(std::string userInput);
    bool interpretUserInput(std::vector<std::string> tokens);
};