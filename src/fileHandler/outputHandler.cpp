#include "outputHandler.h"

outputHandler::outputHandler() {}
void outputHandler::writeBlockToFile(std::string fileName, char* content, int size) {
    // dont need to check for content size, if will be handled by the fileHandler class

    this->file.write(content, size);
    this->writeNumber++;
}
void outputHandler::writeRecordToFile(std::string fileName, const Record& record)
{
    
    int32_t size = static_cast<int32_t>(record.getSeries().size());
    this->file.write(reinterpret_cast<char*>(&size), sizeof(size));
    //this->writeNumber++;
    for(int number : record.getSeries())
    {
        this->file.write(reinterpret_cast<char*>(&number), sizeof(number));
        //this->writeNumber++;
        
    }
    
}
void outputHandler::openFile(std::string fileName)
{
    this->file.open(fileName, std::ios::binary); //  <- deleted app flag here

    if(!this->file.is_open())
    {
        std::cout << "Error opening file" << std::endl;
        return;
    }
    this->fileName = fileName;
    this->writeNumber = 0;

    this->writeBufferIndex = BUFFER_SIZE;
    this->eof = false;

}
void outputHandler::closeFile()
{
    this->file.close();
}
int outputHandler::getWriteNumber() const
{
    return this->writeNumber;
}

void outputHandler::writeRecordToBuffer(const Record& record)
{
    int32_t size = static_cast<int32_t>(record.getSeries().size());
    reinterpret_cast<char*>(&size);
    memcpy(this->writeBuffer + this->writeBufferIndex, &size, sizeof(size));
    this->writeBufferIndex += sizeof(size);
    
    if(this->writeBufferIndex >= this->writeBufferSize)
    {
        this->writeBlockToFile(this->fileName, this->writeBuffer, this->writeBufferSize);
        this->writeBufferIndex = 0;
    }
    for(int number : record.getSeries())
    {
        reinterpret_cast<char*>(&number);
        memcpy(this->writeBuffer + this->writeBufferIndex, &number, sizeof(number));
        this->writeBufferIndex += sizeof(number);
        if(this->writeBufferIndex >= this->writeBufferSize)
        {
            this->writeBlockToFile(this->fileName, this->writeBuffer, this->writeBufferSize);
            this->writeBufferIndex = 0;
            
        }
    }
}

void outputHandler::flushBuffer()
{
    this->writeBlockToFile(this->fileName, this->writeBuffer, this->writeBufferIndex);
    this->writeBufferIndex = 0;
}


