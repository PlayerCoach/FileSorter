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
        //std::cout << "changing size" << std::endl;
        char* resizedBuffer = new char[bytesRead];
        std::memcpy(resizedBuffer, buffer, bytesRead);
        delete[] buffer;
        //std::cout<< bytesRead << std::endl;
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

    
}

void inputHandler::closeFile()
{
    this->file.close();
}

const int inputHandler::getReadNumber() const
{
    return this->readNumber;
}

std::optional<Record> inputHandler::readRecordFromBuffer(bool& eofRef)
{
    if (this->readBufferIndex == this->readBufferSize) {
        delete[] this->readBuffer;
        this->readBufferSize = BUFFER_SIZE;
        this->readBuffer = readBlockFromFile(this->fileName, this->eof, this->readBufferSize);
        this->readBufferIndex = 0;
    }


    int32_t size;
    if (this->readBufferIndex + sizeof(int32_t) > this->readBufferSize) {
        std::cerr << "Error: Not enough data to read size" << std::endl;
        eofRef = true;
        return std::nullopt;
    }

    // Copy 4 bytes into the size variable
    std::memcpy(&size, this->readBuffer + this->readBufferIndex, sizeof(int32_t));
    this->readBufferIndex += sizeof(int32_t);

    //std::cout << "size: " << size << std::endl;

    std::vector<int32_t> mainBuffer;
    for (int i = 0; i < size; i++) {
        if (this->readBufferIndex + sizeof(int32_t) > this->readBufferSize) {
            delete[] this->readBuffer;
            this->readBufferSize = BUFFER_SIZE;
            this->readBuffer = readBlockFromFile(this->fileName, this->eof, this->readBufferSize);
            this->readBufferIndex = 0;
            eofRef = this->eof;

            if (this->readBuffer == nullptr) {
                std::cerr << "Error: Reached EOF while reading a record" << std::endl;
                return std::nullopt;
            }
        }

        int32_t number;
        std::memcpy(&number, this->readBuffer + this->readBufferIndex, sizeof(int32_t));
        this->readBufferIndex += sizeof(int32_t);
        mainBuffer.push_back(number);
    }
    std::cout << Record(mainBuffer) << std::endl;
    return Record(mainBuffer);
}
