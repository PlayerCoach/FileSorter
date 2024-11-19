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
        record.push_back(number);
    }
    return Record(record);
}
inputHandler::inputHandler() {}
Record* inputHandler::readRecordFromFile(std::string fileName) 
{
    std::ifstream file;
    file.open(fileName, std::ios::in | std::ios::binary);
    if (!file.is_open())
    {
        std::cerr << "Error: Could not open file " << fileName << std::endl;
        exit(1);
    }

    file.seekg(fileIndex);
    //check for end of file
    if (file.eof())
    {
        std::cerr << "Error: End of file reached" << std::endl;
        exit(1);
    }
    
    int32_t size;
    file.read(reinterpret_cast<char*>(&size), sizeof(size));

    std::vector <int> mainBuffer;
    int32_t number;
    for(int i = 0; i < size; i++)
    {
        file.read(reinterpret_cast<char*>(&number), sizeof(number));
        mainBuffer.push_back(number);
    }

    return Record(mainBuffer);

}
