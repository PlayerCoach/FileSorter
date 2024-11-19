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
    
    if(!this->file.is_open())
    {
        std::cerr << "Error: File not open" << std::endl;
        return nullptr;
    }

    this->file.seekg(fileIndex);
    //check for end of file
    if (this->file.eof())
    {
        std::cerr << "Error: End of file reached" << std::endl;
        return nullptr;
    }
    
    int32_t size;
    this->file.read(reinterpret_cast<char*>(&size), sizeof(size));

    std::vector <int> mainBuffer;
    int32_t number;
    for(int i = 0; i < size; i++)
    {
        this->file.read(reinterpret_cast<char*>(&number), sizeof(number));
        mainBuffer.push_back(number);
    }

    return &Record(mainBuffer);

}

void inputHandler::openFile(std::string fileName)
{
    this->file.open(fileName, std::ios::in | std::ios::binary);
    if (!file.is_open())
    {
        std::cerr << "Error: Could not open file " << fileName << std::endl;
        exit(1);
    }
}

void inputHandler::closeFile()
{
    this->file.close();
}