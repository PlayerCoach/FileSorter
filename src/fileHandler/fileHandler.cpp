#include "fileHandler.h"

fileHandler::fileHandler() { std::cout << "fileHandler created" << std::endl; }

void fileHandler::start(std::string inputFileName, std::string outputFileName) {}

void fileHandler::readFromFile(std::string fileName) {
    inputHandler.readFromFile(fileName);
}

void fileHandler::writeRecordToFile(std::string fileName, const Record& record) {
    outputHandler.writeRecordToFile(fileName, record);
}
