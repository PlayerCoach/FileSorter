#include <iostream>
#include "fileHandler.h"
#include "const.h"
#include "cmdConst.h"
#include <string>
#include <vector>
#include <sstream>
#include "sorter.h"
#include "MergeWithLargeBuffersSort.h"
#include "sortingStrategy.h"
#include "outputFileNames.h"

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
    void addRecords(std::vector<std::string>& tokens);
    bool checkIfTokensAreEmpty(std::vector<std::string>& tokens);
    void addRandomRecords(int numberOfRecords);
    void addSpecifiedRecords(int numberOfRecords);
    void readInputFile();
    void parseSortCommand(std::vector<std::string>& tokens);
    int sortFile();
    void showFile(std::vector<std::string>& tokens);
    void clearInputFile();
    void experiment();
};