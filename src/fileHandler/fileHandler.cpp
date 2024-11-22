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
       return this->inputHandlers.at(fileName).readRecordFromFile(fileName);
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
        this->outputHandlers.at(fileName).writeRecordToFile(fileName, record);
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
            inputHandlers[fileName] = inputHandler();
        
        inputHandlers[fileName].openFile(fileName);
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
        this->inputHandlers.at(fileName).closeFile();
        this->inputHandlers.erase(fileName);
        std::cout << "File closed" << std::endl;
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
            outputHandlers[fileName] = outputHandler();
        
        outputHandlers[fileName].openFile(fileName);
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    
}

void fileHandler::closeFileForOutput(const std::string& fileName) {
    try
    {
        this->outputHandlers.at(fileName).closeFile();
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
    std::cout<< "Write numbers: " <<  this->outputHandlers[outputFileName].getWriteNumber() << std::endl;
    closeFileForInput(inputFileName);
    closeFileForOutput(outputFileName);
}

char* fileHandler::readBlockFromFile(const std::string& fileName, bool& eof, int& size) {
    try
    {
        return this->inputHandlers.at(fileName).readBlockFromFile(fileName, eof, size);
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        exit(1);
    }
}

void fileHandler::writeBlockToFile(const std::string& fileName, char* content, int size) {
    try
    {
        this->outputHandlers.at(fileName).writeBlockToFile(fileName, content, size);
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        exit(1);
    }
}

void fileHandler::readWriteBlock(const std::string& inputFileName, const std::string& outputFileName) {
    openFileForInput(inputFileName);
    //openFileForOutput(outputFileName);
    char* block;
    int size = BUFFER_SIZE;
    bool eof = false;
    std::optional<Record> record;
    while (!eof)
    {
        record = readRecordFromBuffer(inputFileName, eof);
        //std::cout << record.value() << std::endl;
        //writeRecordToBuffer(outputFileName, record.value());

       
    }
    //flushWriteBuffer(outputFileName);
    std::cout<< "Read number" << inputHandlers[inputFileName].getReadNumber() << std::endl;
    //std::cout<< "Write number" << outputHandlers[outputFileName].getWriteNumber() << std::endl;

    closeFileForInput(inputFileName);
    //closeFileForOutput(outputFileName);
}

void fileHandler::writeRecordToBuffer(const std::string& fileName, const Record& record) {
    try
    {
        this->outputHandlers.at(fileName).writeRecordToBuffer(record);
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        exit(1);
    }
}

std::optional<Record> fileHandler::readRecordFromBuffer(const std::string& fileName, bool& eof) {
    try
    {
        return this->inputHandlers.at(fileName).readRecordFromBuffer(eof);
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
        this->outputHandlers.at(fileName).flushBuffer();
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        exit(1);
    }
}
