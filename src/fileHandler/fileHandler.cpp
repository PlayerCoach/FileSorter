#include "fileHandler.h"

fileHandler::fileHandler() { std::cout << "fileHandler created" << std::endl; }

void fileHandler::start(std::string inputFileName, std::string outputFileName) {
    readFromFile(inputFileName);
    writeToFile(outputFileName, "content");
}

void fileHandler::readFromFile(std::string fileName) {
    inputHandler.readFromFile(fileName);
}

void fileHandler::writeToFile(std::string fileName, std::string content) {
    outputHandler.writeToFile(fileName, content);
}
