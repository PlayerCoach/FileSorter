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

std::optional<Record> fileHandler::readRecordFromFile(const std::string& fileName) {
    try
    {
       return this->inputHandlers.at(fileName)->readRecordFromFile();
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        exit(1);
    }
}

void fileHandler::writeRecordToFile(const std::string& fileName, const Record& record) {
    try
    {
        this->outputHandlers.at(fileName)->writeRecordToFile(record);
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        exit(1);
    }
    
    
}

void fileHandler::clearFile(const std::string& fileName) {
    std::ofstream file;
    file.open(fileName, std::ios::trunc);
    file.close();
}

void fileHandler::openFileForInput(const std::string& fileName) {
    try
    {
        if (inputHandlers.find(fileName) == inputHandlers.end()) 
            inputHandlers[fileName] = std::make_unique<inputHandler>();
        
        inputHandlers[fileName]->openFile(fileName);
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
}

void fileHandler::closeFileForInput(const std::string& fileName) {
    try
    {
        // add file is open later on
        this->inputHandlers.at(fileName)->closeFile();
        this->inputHandlers.erase(fileName);
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    
}

void fileHandler::openFileForOutput(const std::string& fileName) {
    try
    {
        if(outputHandlers.find(fileName) == outputHandlers.end())
            outputHandlers[fileName] = std::make_unique<outputHandler>();
        
        outputHandlers[fileName]->openFile(fileName);
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    
}

void fileHandler::closeFileForOutput(const std::string& fileName) {
    try
    {
        this->outputHandlers.at(fileName)->closeFile();
        this->outputHandlers.erase(fileName);
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    
}

void fileHandler::readReinterpretWrite(const std::string& inputFileName, const std::string& outputFileName) {
    openFileForInput(inputFileName);
    openFileForOutput(outputFileName);
    std::optional<Record> record;
   while ((record = readRecordFromFile(inputFileName)) != std::nullopt)
    {
        std::cout << record.value() << std::endl;
        writeRecordToFile(outputFileName, record.value());
    }
    std::cout<< "Write numbers: " <<  this->outputHandlers[outputFileName]->getWriteNumber() << std::endl;
    closeFileForInput(inputFileName);
    closeFileForOutput(outputFileName);
}

void fileHandler::readWriteBlock(const std::string& inputFileName, const std::string& outputFileName) {
    openFileForInput(inputFileName);
    openFileForOutput(outputFileName);

    std::optional<Record> record;
    while (!inputHandlers[inputFileName]->allFilesRead())
    {
        record = readRecordFromBuffer(inputFileName);
        writeRecordToBuffer(outputFileName, record.value());

       
    }
    flushWriteBuffer(outputFileName);
    std::cout<< "Read number" << inputHandlers[inputFileName]->getReadNumber() << std::endl;
    std::cout<< "Write number" << outputHandlers[outputFileName]->getWriteNumber() << std::endl;

    closeFileForInput(inputFileName);
    closeFileForOutput(outputFileName);
}

void fileHandler::writeRecordToBuffer(const std::string& fileName, const Record& record) {
    try
    {
        this->outputHandlers.at(fileName)->writeRecordToBuffer(record);
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        exit(1);
    }
}

std::optional<Record> fileHandler::readRecordFromBuffer(const std::string& fileName) {
    try
    {
        return this->inputHandlers.at(fileName)->readRecordFromBuffer();
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        exit(1);
    }
}

void fileHandler::flushWriteBuffer(const std::string& fileName) {
    try
    {
        this->outputHandlers.at(fileName)->flushBuffer();
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        exit(1);
    }
}

void fileHandler::displayFile(const std::string& fileName) {
    openFileForInput(fileName);
    std::optional<Record> record;
    while ((record = readRecordFromFile(fileName)) != std::nullopt)
    {
        std::cout << record.value() << std::endl;
    }
    closeFileForInput(fileName);
}

bool fileHandler::allFilesRead(const std::string& fileName) {
    try
    {
        return this->inputHandlers.at(fileName)->allFilesRead();
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    
}

int fileHandler::getReadNumber(const std::string& fileName) const {
    try
    {
        return this->inputHandlers.at(fileName)->getReadNumber();
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    
}

int fileHandler::getWriteNumber(const std::string& fileName) const {
    try
    {
        return this->outputHandlers.at(fileName)->getWriteNumber();
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    
}

int fileHandler::getNumberOfActiveFiles() const {
    return this->inputHandlers.size() + this->outputHandlers.size();
}

const int fileHandler::getBufferReadCount(const std::string& fileName) const {
    try
    {
        return this->inputHandlers.at(fileName)->getBufferReadCount();
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    
}