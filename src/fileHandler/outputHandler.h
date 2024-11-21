#pragma once
#include <iostream> 
#include <fstream>
#include <string>
#include "const.h"
#include "record.h"
#include <bitset>
class outputHandler
{
private:
    std::ofstream file;
    //char outputBuffer[BUFFER_SIZE];
    int outputBufferIndex = 0;
    std::string recordToBinary(const Record& record);
    int writeNumber = 0;
public:
    outputHandler();
    void writeRecordToFile(std::string fileName, const Record& record);
    void writeBlockToFile(std::string fileName, char* content, int size = BUFFER_SIZE);
    void openFile(std::string fileName);
    void closeFile();
    int getWriteNumber() const;
};
