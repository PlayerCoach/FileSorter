#include "outputHandler.h"


std::string outputHandler::recordToBinary(const Record& record) 
{   
    std::bitset<32> binary(record.getSeries().size());
    std::string binaryString = binary.to_string();

    // for (int number : record.getSeries())
    // {
    //     std::bitset<32> binary(number);
    //     binaryString += binary.to_string();
    // }
    return binaryString;
}
outputHandler::outputHandler() {}
void outputHandler::writeBlockToFile(std::string fileName, std::string content) {}
void outputHandler::writeRecordToFile(std::string fileName, const Record& record)
{
    std::ofstream file;
    file.open(fileName, std::ios::app);

    if(!file.is_open())
    {
        std::cout << "Error opening file" << std::endl;
        return;
    }

    file << recordToBinary(record);
    file.close();
}