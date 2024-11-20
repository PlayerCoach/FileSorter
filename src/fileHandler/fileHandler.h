#include "inputHandler.h"
#include "outputHandler.h"
#include "const.h"
#include "record.h"
#include <filesystem>
#include <iostream>
#include <fstream>
#include <string>
#include <optional>

class fileHandler
{
private:
    inputHandler inputHandler;
    outputHandler outputHandler;
    int mainBuffer[BUFFER_SIZE];
public:
    fileHandler();
    void start(std::string inputFileName, std::string outputFileName);
    std::optional<Record> readRecordFromFile(std::string fileName);
    void writeRecordToFile(std::string fileName, const Record& content);
    void clearFile(std::string fileName);
    void openFileForInput(std::string fileName);   
    void closeFileForInput();
    void openFileForOutput(std::string fileName);
    void closeFileForOutput();
    void readReinterpretWrite(std::string inputFileName, std::string outputFileName);
    void readWriteBlock(std::string inputFileName, std::string outputFileName);

};