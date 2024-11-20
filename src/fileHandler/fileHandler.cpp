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

std::optional<Record> fileHandler::readRecordFromFile(std::string fileName) {
    return this->inputHandler.readRecordFromFile(fileName);
}

void fileHandler::writeRecordToFile(std::string fileName, const Record& record) {
    this->outputHandler.writeRecordToFile(fileName, record);
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
    std::optional<Record> record;
   while ((record = readRecordFromFile(inputFileName)) != std::nullopt)
    {
        std::cout << record.value() << std::endl;
        writeRecordToFile(outputFileName, record.value());
    }
    std::cout<< "Write numbers: " <<  this->outputHandler.getWriteNumber() << std::endl;
    closeFileForInput();
    closeFileForOutput();
}

void fileHandler::readWriteBlock(std::string inputFileName, std::string outputFileName) {
    openFileForInput(inputFileName);
    openFileForOutput(outputFileName);
    char* block;
    int size = BUFFER_SIZE;
    bool eof = false;
    while (!eof)
    {
        block = inputHandler.readBlockFromFile(inputFileName, eof, BUFFER_SIZE);
        outputHandler.writeBlockToFile(outputFileName, block);
        delete[] block;
       
    }
    closeFileForInput();
    closeFileForOutput();
}

