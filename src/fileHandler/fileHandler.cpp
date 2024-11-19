#include "fileHandler.h"

fileHandler::fileHandler() 
{
    //create folder
    if (!std::filesystem::exists(OUTPUT_FOLDER))
    {
        std::filesystem::create_directory(OUTPUT_FOLDER);
        std::cout << "Output folder created" << std::endl;
    }
    

}

void fileHandler::start(std::string inputFileName, std::string outputFileName) {}

Record* fileHandler::readRecordFromFile(std::string fileName) {
    return inputHandler.readRecordFromFile(fileName);
}

void fileHandler::writeRecordToFile(std::string fileName, const Record& record) {
    outputHandler.writeRecordToFile(fileName, record);
}

void fileHandler::clearFile(std::string fileName) {
    std::ofstream file;
    file.open(fileName, std::ios::trunc);
    file.close();
}

void fileHandler::openFileForInput(std::string fileName) {
    inputHandler.openFile(fileName);
}

void fileHandler::closeFileForInput() {
    inputHandler.closeFile();
}

void fileHandler::openFileForOutput(std::string fileName) {
    outputHandler.openFile(fileName);
}

void fileHandler::closeFileForOutput() {
    outputHandler.closeFile();
}

void fileHandler::readReinterpretWrite(std::string inputFileName, std::string outputFileName) {
    openFileForInput(inputFileName);
    openFileForOutput(outputFileName);
    Record* record;
    while ((record = readRecordFromFile(inputFileName)) != nullptr)
    {
        std::cout << "Current record" << *record << std::endl;
        writeRecordToFile(outputFileName, *record);
    }
    closeFileForInput();
    closeFileForOutput();
}

