#include "outputHandler.h"

outputHandler::outputHandler() {}
void outputHandler::writeBlockToFile(std::string fileName, std::string content) {}
void outputHandler::writeRecordToFile(std::string fileName, const Record& record)
{
    
    int32_t size = record.getSeries().size();
    this->file.write(reinterpret_cast<char*>(&size), sizeof(size));
    for(int number : record.getSeries())
    {
        this->file.write(reinterpret_cast<char*>(&number), sizeof(number));
    }
    this->file.close();
}

void outputHandler::openFile(std::string fileName)
{
    this->file.open(fileName, std::ios::app | std::ios::binary );

    if(!this->file.is_open())
    {
        std::cout << "Error opening file" << std::endl;
        return;
    }
}

void outputHandler::closeFile()
{
    this->file.close();
}