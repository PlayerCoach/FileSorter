#include "inputHandler.h"

inputHandler::inputHandler() {}
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
        std::cout<<"EOF "<<std::endl;
        return std::nullopt; // EOF or read failure
    }

    if(this->file.fail())
    {
        std::cerr << "Error: Failed to read size" << std::endl;
        return std::nullopt;
    }

    std::vector <int> mainBuffer;
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
    }
    this->file.seekg(this->fileIndex);
    this->file.read(this->readBuffer, BUFFER_SIZE);
    this->readNumber++;
    std::streamsize bytesRead = this->file.gcount();
    
    this->fileIndex = file.tellg();
    if (this->fileIndex == -1) 
    {
        this->fileIndex = 0;
        this->eof = true;
    }

     if (bytesRead == 0) // Nothing was read
    {
        this->eof = true;
        this->readBufferSize = 0;
    }

    if (bytesRead < BUFFER_SIZE)
    {
        this->readBufferSize = static_cast<int>(bytesRead);
    }
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

    
}

void inputHandler::closeFile()
{
    this->file.close();
}

const int inputHandler::getReadNumber() const
{
    return this->readNumber;
}

std::optional<Record> inputHandler::readRecordFromBuffer()
{

    if(this->allFilesRead())
    {
        return std::nullopt;
    }

    if (this->readBufferIndex == this->readBufferSize) {
        this->readBufferSize = BUFFER_SIZE;
        this->readBlockFromFile();
        this->readBufferIndex = 0;
    }


    int32_t size;
    if (this->readBufferIndex + sizeof(int32_t) > this->readBufferSize) {
        std::cerr << "Error: Not enough data to read size" << std::endl;
        return std::nullopt;
    }

    std::memcpy(&size, this->readBuffer + this->readBufferIndex, sizeof(int32_t));
    this->readBufferIndex += sizeof(int32_t);

    std::vector<int32_t> mainBuffer;

    for (int i = 0; i < size; i++) {
        if (this->readBufferIndex + sizeof(int32_t) > this->readBufferSize) 
        {
            this->readBufferSize = BUFFER_SIZE;
            this->readBufferIndex = 0;
            this->readBlockFromFile();

            if(this->readBufferSize == 0)
            {
                std::cerr << "Error: Not enough data to read number" << std::endl;
                return std::nullopt;
            }
        }

        int32_t number;
        std::memcpy(&number, this->readBuffer + this->readBufferIndex, sizeof(int32_t));
        this->readBufferIndex += sizeof(int32_t);
        mainBuffer.push_back(number);
    }
    //std::cout << Record(mainBuffer) << std::endl;
    return Record(mainBuffer);
}
bool inputHandler::allFilesRead() const
{
    return this->eof && (this->readBufferIndex >= this->readBufferSize);
}