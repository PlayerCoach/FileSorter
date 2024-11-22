#include "inputHandler.h"

inputHandler::inputHandler() {}
std::optional<Record> inputHandler::readRecordFromFile(std::string fileName) 
{
    
    if(!this->file.is_open())
    {
        std::cerr << "Error: File not open" << std::endl;
        return std::nullopt;
    }

    this->file.seekg(fileIndex);
 
    int32_t size;
    this->file.read(reinterpret_cast<char*>(&size), sizeof(size));

    if (this->file.eof() || this->file.fail())
    {
        std::cout<<"EOF or read failure"<<std::endl;
        return std::nullopt; // EOF or read failure
    }

    std::vector <int> mainBuffer;
    int32_t number;
    for(int i = 0; i < size; i++)
    {
        this->file.read(reinterpret_cast<char*>(&number), sizeof(number));
        mainBuffer.push_back(number);
    }
    fileIndex = file.tellg();
    if (fileIndex == -1) {
        std::cerr << "Error: Failed to get file position" << std::endl;
        fileIndex = 0;
        return std::nullopt;
    }

    return Record(mainBuffer);

}

char* inputHandler::readBlockFromFile(std::string fileName, bool& eof, int& size)
{
    if (!this->file.is_open())
    {
        std::cerr << "Error: File not open" << std::endl;
        return nullptr;
    }
    this->file.seekg(fileIndex);
    char* buffer = new char[BUFFER_SIZE];
    this->file.read(buffer, BUFFER_SIZE);
    this->readNumber++;
    std::streamsize bytesRead = this->file.gcount();
    
    fileIndex = file.tellg();
    if (fileIndex == -1) {
        fileIndex = 0;
        eof = true;
    }
     if (bytesRead == 0) // Nothing was read
    {
        delete[] buffer;
        eof = true;
        size = 0;
        return nullptr;
    }

    if (bytesRead < BUFFER_SIZE)
    {
        std::cout << "changing size" << std::endl;
        char* resizedBuffer = new char[bytesRead];
        std::memcpy(resizedBuffer, buffer, bytesRead);
        delete[] buffer;
        std::cout<< bytesRead << std::endl;
        size = static_cast<int>(bytesRead);
        return resizedBuffer;
    }
    return buffer;
}

void inputHandler::openFile(std::string fileName)
{
    this->file.open(fileName, std::ios::in | std::ios::binary);
    if (!file.is_open())
    {
        std::cerr << "Error: Could not open file " << fileName << std::endl;
        exit(1);
    }
    this->fileName = fileName;
    this->fileIndex = 0;

    char* readBuffer = nullptr;
    int readBufferSize = BUFFER_SIZE;
    int readBufferIndex  = BUFFER_SIZE; // symbolizes that the buffer is empty
    bool eof = false;
}

void inputHandler::closeFile()
{
    this->fileIndex = 0;
    this->file.close();
}

const int inputHandler::getReadNumber() const
{
    return this->readNumber;
}

std::optional<Record> inputHandler::readRecordFromBuffer()
{
    if(this->eof)
    {
        delete[] this->readBuffer;
        return std::nullopt;
    }
    if(this->readBufferIndex == this->readBufferSize)
    {
        delete[] this->readBuffer;
        this->readBuffer = readBlockFromFile(this->fileName, this->eof , this->readBufferSize);
        this->readBufferIndex = 0;
    }
    if(this->readBuffer == nullptr)
    {
        return std::nullopt;
    }
    int32_t size;

    reinterpret_cast<int32_t&>(size) = *reinterpret_cast<int32_t*>(this->readBuffer + this->readBufferIndex);
    this->readBufferIndex += sizeof(size);
    std::vector <int> mainBuffer;
    int32_t number;
    for(int i = 0; i < size; i++)
    {
        reinterpret_cast<int32_t&>(number) = *reinterpret_cast<int32_t*>(this->readBuffer + this->readBufferIndex);
        this->readBufferIndex += sizeof(number);
        mainBuffer.push_back(number);
        if(this->readBufferIndex == this->readBufferSize)
        {
            delete[] this->readBuffer;
            this->readBuffer = readBlockFromFile(this->fileName, this->eof , this->readBufferSize);
            this->readBufferIndex = 0;
        }
    }
    return Record(mainBuffer);

}