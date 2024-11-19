#include "outputHandler.h"

outputHandler::outputHandler() {}
void outputHandler::writeBlockToFile(std::string fileName, std::string content) {}
void outputHandler::writeRecordToFile(std::string fileName, const Record& record)
{
    std::ofstream file;
    file.open(fileName, std::ios::app | std::ios::binary );

    if(!file.is_open())
    {
        std::cout << "Error opening file" << std::endl;
        return;
    }

    int32_t size = record.getSeries().size();
    file.write(reinterpret_cast<char*>(&size), sizeof(size));
    for(int number : record.getSeries())
    {
        file.write(reinterpret_cast<char*>(&number), sizeof(number));
    }
    file.close();
}