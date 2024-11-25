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

std::string fileHandler::createFolder(const std::string& folderName) {
    if (!std::filesystem::exists(folderName))
    {
        std::string fullFolderPath = OUTPUT_FOLDER + "/" + folderName;
        std::filesystem::create_directory(fullFolderPath);
        return fullFolderPath;
    }
    return "";
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

void fileHandler::openFileForOutput(const std::string& fileName, const std::string& mode) {
    try
    {
        if(outputHandlers.find(fileName) == outputHandlers.end())
            outputHandlers[fileName] = std::make_unique<outputHandler>();
        
        outputHandlers[fileName]->openFile(fileName, mode);
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
    if (!std::filesystem::exists(fileName))
    {
        std::cerr << "Error: File does not exist" << std::endl;
        return;
    }
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
        return true;
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

void fileHandler::renameFile(const std::string& oldName, const std::string& newName) {
    std::filesystem::rename(oldName, newName);
}

void fileHandler::deleteFile(const std::string& fileName) {
    std::filesystem::remove(fileName);
}

void fileHandler::moveFile(const std::string& fileName, const std::string& folderName) {
    // Extract the file name from the full path
    std::filesystem::path sourcePath(fileName);
    std::string baseName = sourcePath.filename().string();
    
    // Construct the destination path
    std::filesystem::path destinationPath = std::filesystem::path(folderName) / baseName;

    // Perform the move operation
    std::filesystem::rename(fileName, destinationPath);
}

void fileHandler::concatenateFilesInFolder(const std::string& folderPath, const std::string& outputFileName) {
    // Ensure output file path is within OUTPUT_FOLDER
    std::filesystem::path fullOutputFilePath = std::filesystem::path(OUTPUT_FOLDER) / outputFileName;

    std::ofstream outputFile(fullOutputFilePath, std::ios::binary);
    for (const auto& entry : std::filesystem::directory_iterator(folderPath)) {
        if (entry.is_regular_file()) { // Check if it's a file
            std::ifstream inputFile(entry.path(), std::ios::binary);
            outputFile << inputFile.rdbuf();
            inputFile.close();
            std::filesystem::remove(entry.path());
        }
    }
    outputFile.close();
}

void fileHandler::deleteFolder(const std::string& folderPath) {
    std::filesystem::remove_all(folderPath);
}

void fileHandler::copyFile(const std::string& source, const std::string& destination) {
    
    std::filesystem::path fullOuputPath = std::filesystem::path(OUTPUT_FOLDER) / destination;
    std::filesystem::copy(source, fullOuputPath);
}

void fileHandler::convertTxtToInputBin(const std::string& txtFilePath)
{
    std::ifstream txtFile(txtFilePath);
    if (!txtFile.is_open())
    {
        std::cerr << "Error: Could not open text file " << txtFilePath << std::endl;
        return;
    }

   this->openFileForOutput(INPUT);

    std::string line;
    while (std::getline(txtFile, line))
    {
        std::istringstream numberStream(line);
        std::vector<int32_t> record;
        std::string numberString;
        int32_t number;

        // Parse the numbers in the current line
        while (std::getline(numberStream, numberString, ' '))
        {
            try
            {
                number = std::stoi(numberString);
                record.push_back(number);
            }
            catch (const std::exception& e)
            {
                std::cerr << "Invalid number in text file: " << numberString << ". Skipping line." << std::endl;
                record.clear();
                break;
            }
        }

        if (record.empty())
            continue;

        if (record.size() > MAX_RECORD_COUNT)
        {
            std::cerr << "Record too long, skipping line: " << line << std::endl;
            continue;
        }

        Record recordObj(record);
        this->writeRecordToFile(INPUT, recordObj);

    }

    txtFile.close();
    this->closeFileForOutput(INPUT);
}

void fileHandler::deleteAllBinFilesExceptInput() {
    std::filesystem::path targetPath = std::filesystem::absolute(INPUT);
    for (const auto& entry : std::filesystem::directory_iterator(OUTPUT_FOLDER)) {
        if (entry.is_regular_file() && std::filesystem::absolute(entry.path()) != targetPath) {
            std::filesystem::remove(entry.path());
        }
    }
}

void fileHandler::clearFile(const std::string& fileName) {
    std::ofstream file(fileName, std::ios::trunc);
    file.close();
}

void fileHandler::displayNFirstRecords(const std::string& fileName, int n) {
    openFileForInput(fileName);
    std::optional<Record> record;
    for (int i = 0; i < n; i++)
    {
        record = readRecordFromFile(fileName);
        if (record == std::nullopt)
            break;
        std::cout << record.value() << std::endl;
    }
    finalizeFileForInput(fileName);
}

