#include "inputHandler.h"

Record inputHandler::binaryToRecord(char* recordBuffer, const int& size)
{
    std::vector<int> record;
    int number;
    std::string binaryString;
    for (int i = 0; i < size; i++)
    {
        binaryString = std::string(recordBuffer + i * 32, 32);
        number = stoi(binaryString, 0, 2);
        std::cout<<number<<std::endl;
        record.push_back(number);
    }
    return Record(record);
}
inputHandler::inputHandler() {}
Record inputHandler::readRecordFromFile(std::string fileName) 
{
    std::ifstream file;
    file.open(fileName, std::ios::in | std::ios::binary);
    if (!file.is_open())
    {
        std::cerr << "Error: Could not open file " << fileName << std::endl;
        exit(1);
    }
    //move to the curren index
    file.seekg(fileIndex);
    std::string bitSize(32, '0');
    file.read(&bitSize[0], 32);
    std::cout<<bitSize<<std::endl;
    int size = stoi(bitSize, 0, 2); 

    char *recordBuffer = new char[size * 32 + 1];
    recordBuffer[size * 32] = '\0';
    file.read(recordBuffer, size * 32);
    fileIndex += 32 + size * 32;
    std::cout<< size << std::endl;
    std::cout<< recordBuffer << std::endl;
    Record binRecord = binaryToRecord(recordBuffer, size);
    delete[] recordBuffer;
    file.close();
    return binRecord;

}
