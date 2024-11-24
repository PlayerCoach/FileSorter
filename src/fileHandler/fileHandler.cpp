#include "fileHandler.h"

fileHandler::fileHandler() 
{
    
    if (!std::filesystem::exists(OUTPUT_FOLDER))
    {
        std::filesystem::create_directory(OUTPUT_FOLDER);
        std::cout << "Output folder created" << std::endl;
    }

    // if exists clear the folder
    else
    {
        std::filesystem::remove_all(OUTPUT_FOLDER);
        std::filesystem::create_directory(OUTPUT_FOLDER);
        std::cout << "Output folder cleared" << std::endl;
    }
    
}

void fileHandler::createFolder(const std::string& folderName) {
    if (!std::filesystem::exists(folderName))
    {
        std::string fullFolderPath = OUTPUT_FOLDER + "/" + folderName;
        std::filesystem::create_directory(fullFolderPath);
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
        this->inputHandlers.at(fileName)->closeFile();
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    
}

void fileHandler::finalizeFileForInput(const std::string& fileName) {
    try
    {
        if(this->inputHandlers.find(fileName) == this->inputHandlers.end())
            throw std::runtime_error("File not open");
        
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
        if(this->outputHandlers.find(fileName) == this->outputHandlers.end())
            throw std::runtime_error("File not open");
        this->outputHandlers.at(fileName)->closeFile();
        this->outputHandlers.erase(fileName);
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    
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
    finalizeFileForInput(fileName);
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

const int fileHandler::getReadNumber(const std::string& fileName) const {
    try
    {
        return this->inputHandlers.at(fileName)->getReadNumber();
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        return 0;
    }

    
}

const int fileHandler::getWriteNumber(const std::string& fileName) const {
    try
    {
        return this->outputHandlers.at(fileName)->getWriteNumber();
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        return 0;

    }
    
}

const int fileHandler::getNumberOfActiveFiles() const {
    return static_cast<int>(this->inputHandlers.size() + this->outputHandlers.size());
}

const std::optional<int32_t> fileHandler::peekNextSize(const std::string& fileName) {
    try
    {
        return this->inputHandlers.at(fileName)->peekNextSize();
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        return std::nullopt;
    }
    
}

const std::optional<int32_t> fileHandler::peekNextSizeInBytes(const std::string& fileName) {
    try
    {
        return this->inputHandlers.at(fileName)->peekNextSizeInBytes();
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        return std::nullopt;
    }
    
}

void fileHandler::saveCurrentOutputDirState(const std::string& outputDirStateFolderName) {
    this->createFolder(outputDirStateFolderName);

    for (const auto& entry : std::filesystem::directory_iterator(OUTPUT_FOLDER)) {
        if (entry.is_regular_file()) { // Check if it's a file
            std::filesystem::copy(
                entry.path(),
                std::filesystem::path(outputDirStateFolderName) / entry.path().filename()
            );
        }
    }
}