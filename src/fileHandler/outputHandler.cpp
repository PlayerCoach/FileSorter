#include "outputHandler.h"

outputHandler::outputHandler() {}

void outputHandler::openFile(const std::string& fileName, const std::string& mode)
{
    if(mode == "append")
        this->file.open(fileName, std::ios::binary | std::ios::app);
    else
    this->file.open(fileName, std::ios::binary); 

    if(!this->file.is_open())
    {
        std::cout << "Error opening file" << std::endl;
        return;
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

