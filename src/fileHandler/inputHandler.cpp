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
std::optional<Record> inputHandler::readRecordFromFile(std::string fileName) 
{
    
    if(!this->file.is_open())
    {
        std::cerr << "Error: File not open" << std::endl;
        return std::nullopt;
    }

    this->file.seekg(fileIndex);
 
    int32_t size;
    this->file.read(reinterpret_cast<char*>(&size), sizeof(size));

    if (this->file.eof() || this->file.fail())
    {
        std::cout<<"EOF or read failure"<<std::endl;
        return std::nullopt; // EOF or read failure
    }

    std::vector <int> mainBuffer;
    int32_t number;
    for(int i = 0; i < size; i++)
    {
        this->file.read(reinterpret_cast<char*>(&number), sizeof(number));
        mainBuffer.push_back(number);
    }
    fileIndex = file.tellg();
    if (fileIndex == -1) {
        std::cerr << "Error: Failed to get file position" << std::endl;
        fileIndex = 0;
        return std::nullopt;
    }

    return Record(mainBuffer);

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
    this->fileIndex = 0;
    this->file.close();
}