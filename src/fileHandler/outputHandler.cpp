#include "outputHandler.h"

outputHandler::outputHandler() {}

void outputHandler::openFile(const std::string& fileName, const std::string& mode)
{
    if(mode == "append")
        this->file.open(fileName, std::ios::binary | std::ios::app);
    else
    this->file.open(fileName, std::ios::binary); 

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

void outputHandler::writeRecordToFile(const Record& record)
{
    
    int32_t size = static_cast<int32_t>(record.getSeries().size());
    this->file.write(reinterpret_cast<char*>(&size), sizeof(size));
    for(int number : record.getSeries())
    {
        this->file.write(reinterpret_cast<char*>(&number), sizeof(number));
    }
    
}

void outputHandler::writeBlockToFile() 
{

    this->file.write(this->writeBuffer, this->writeBufferIndex);
    this->file.flush(); 
    this->writeNumber++;
}

void outputHandler::writeIntToBuffer(int32_t value)
{
    if(this->writeBufferIndex + sizeof(value) > this->writeBufferSize)
    {
        this->writeBlockToFile();
        this->writeBufferIndex = 0;
    }
    memcpy(this->writeBuffer + this->writeBufferIndex, &value, sizeof(value));
    this->writeBufferIndex += sizeof(value);
}

void outputHandler::writeRecordToBuffer(const Record& record)
{
    
    writeIntToBuffer(static_cast<int32_t>(record.getSeries().size()));

    for(int number : record.getSeries())
    {
        writeIntToBuffer(static_cast<int32_t>(number));
    }
}

const int outputHandler::getWriteNumber() const
{
    return this->writeNumber;
}

void outputHandler::flushBuffer()
{
    if(this->writeBufferIndex <= 0)
        return;
    this->writeBlockToFile();  
    this->writeBufferIndex = 0;
}

void outputHandler::closeFile()
{
    this->file.close();
}

