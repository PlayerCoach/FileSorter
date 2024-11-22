#include "outputHandler.h"

outputHandler::outputHandler() {}
void outputHandler::writeBlockToFile() {

    this->file.write(this->writeBuffer, this->writeBufferIndex);
    this->file.flush(); 
    this->writeNumber++;
}
void outputHandler::writeRecordToFile(const Record& record)
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
void outputHandler::openFile(const std::string& fileName)
{
    this->file.open(fileName, std::ios::binary); //  <- deleted app flag here

    if(!this->file.is_open())
    {
        std::cout << "Error opening file" << std::endl;
        return;
    }
    this->fileName = fileName;
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
        if(this->writeBufferIndex > this->writeBufferSize)
            this->writeBufferIndex = this->writeBufferIndex;
        this->writeBlockToFile();
        this->writeBufferIndex = 0;
    }

    int32_t number32;

    for(int number : record.getSeries())
    {
        number32 = static_cast<int32_t>(number);
        reinterpret_cast<char*>(&number32);
        memcpy(this->writeBuffer + this->writeBufferIndex, &number32, sizeof(number32));
        this->writeBufferIndex += sizeof(number32); // <- maby this is not 4?

        if(this->writeBufferIndex >= this->writeBufferSize)
        {
            this->writeBlockToFile();
            this->writeBufferIndex = 0;
            
        }
    }
}

void outputHandler::flushBuffer()
{
    if(this->writeBufferIndex > 0)
    {
        if(this->writeBufferIndex > this->writeBufferSize)
            this->writeBufferIndex = this->writeBufferIndex;
        this->writeBlockToFile();  
        this->writeBufferIndex = 0;
    }
}


