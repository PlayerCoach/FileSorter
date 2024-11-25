#include "inputHandler.h"

inputHandler::inputHandler() {}

void inputHandler::openFile(std::string fileName)
{
    this->file.open(fileName, std::ios::in | std::ios::binary);
    if (!file.is_open())
    {
        std::cerr << "Error: Could not open file " << fileName << std::endl;
        char buffer[256];
        strerror_s(buffer, sizeof(buffer), errno);
        std::cerr << "Reason: " << buffer << std::endl;
        // Additional debugging info
        std::ifstream test(fileName);
        if (!test.is_open()) {
            std::cerr << "File does not exist or is inaccessible." << std::endl;
        } else {
            std::cerr << "File exists, but there may be permission issues or it's locked." << std::endl;
        }
        test.close();

        exit(1);
    }
    this->fileName = fileName;
}

std::optional<Record> inputHandler::readRecordFromFile() 
{
    if(!this->file.is_open())
    {
        std::cerr << "Error: File not open" << std::endl;
        return std::nullopt;
    }

    this->file.seekg(this->fileIndex);
 
    int32_t size;
    this->file.read(reinterpret_cast<char*>(&size), sizeof(size));

    if (this->file.eof())
    {
        std::cout<<"**********EOF**********"<<std::endl;
        return std::nullopt; // EOF or read failure
    }

    if(this->file.fail())
    {
        std::cerr << "Error: Failed to read size" << std::endl;
        return std::nullopt;
    }

    std::vector <int32_t> mainBuffer;
    int32_t number;

    for(int i = 0; i < size; i++)
    {
        this->file.read(reinterpret_cast<char*>(&number), sizeof(number));
        mainBuffer.push_back(number);
    }
    this->fileIndex = file.tellg();
    if (fileIndex == -1) 
    {
        std::cerr << "Error: Failed to get file position" << std::endl;
        this->fileIndex = 0;
        return std::nullopt;
    }

    return Record(mainBuffer);
}

void inputHandler::readBlockFromFile()
{
    if (!this->file.is_open())
    {
        std::cerr << "Error: File not open" << std::endl;
        this->readBufferSize = 0;
        this->eof = true;
        return;
    }

    this->file.seekg(this->fileIndex);
    this->file.read(this->readBuffer, BUFFER_SIZE);
    std::streamsize bytesRead = this->file.gcount();
    this->fileIndex = file.tellg();
  
    this->readNumber++;

    this->eof = (bytesRead < BUFFER_SIZE) || (this->file.peek() == EOF) || (this->fileIndex == -1);

    this->readBufferSize = static_cast<int>(bytesRead);
    this->readBufferIndex = 0;
}

std::optional<int32_t> inputHandler::readNextInt()
{
     if (this->readBufferIndex + sizeof(int32_t) > this->readBufferSize) {
        if (!this->reloadBuffer()) {
            return std::nullopt;
        }
    }

    int32_t value;
    std::memcpy(&value, this->readBuffer + this->readBufferIndex, sizeof(int32_t));
    this->readBufferIndex += sizeof(int32_t);
    return value;
}

bool inputHandler::reloadBuffer()
{
   if (this->allFilesRead()) 
   {
        return false;
    }

    this->readBlockFromFile();
    this->bufferReadCount++;

    return this->readBufferSize > 0;
}

std::optional<Record> inputHandler::readRecordFromBuffer()
{

    if(this->allFilesRead())
    {
        return std::nullopt;
    }
    auto sizeOpt = this->readNextInt();
    if (!sizeOpt.has_value()) {
        return std::nullopt;
    }

    int32_t size = sizeOpt.value();
  
    std::vector<int32_t> mainBuffer;
    mainBuffer.reserve(size);

    for (int i = 0; i < size; i++) {
        auto numberOpt = this->readNextInt();
        if (!numberOpt.has_value()) {
            return std::nullopt;
        }
        mainBuffer.push_back(numberOpt.value());
    }
    return Record(mainBuffer);
}

bool inputHandler::allFilesRead() const
{
    return this->eof && (this->readBufferIndex >= this->readBufferSize);
}

const int inputHandler::getReadNumber() const
{
    return this->readNumber;
}

// Returns the size of the next record in the buffer without moving the read index but with reloading buffer if necessary
const std::optional<int32_t> inputHandler::peekNextSize() 
{
    if(allFilesRead())
    {
        return std::nullopt;
    }
    
    if (this->readBufferIndex + sizeof(int32_t) > this->readBufferSize) {
         if (!this->reloadBuffer()) 
        {
            return std::nullopt;
        }
    }

    int32_t value;
    std::memcpy(&value, this->readBuffer + this->readBufferIndex, sizeof(int32_t));
    return value;
}

const std::optional<int32_t> inputHandler::peekNextSizeInBytes() 
{
    auto sizeOpt = this->peekNextSize();
    if (!sizeOpt.has_value()) {
        return std::nullopt;
    }
    return static_cast<int32_t>(sizeOpt.value() * sizeof(int32_t) + sizeof(int32_t));
}

void inputHandler::closeFile()
{
    this->file.close();
}
