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
    std::string fileName;

    std::ofstream file;
    int writeNumber = 0;
    
    char writeBuffer[BUFFER_SIZE];
    const int writeBufferSize = BUFFER_SIZE;
    int writeBufferIndex= 0;

    void writeBlockToFile();
public:
    outputHandler();
    void writeRecordToFile(const Record& record);
    void openFile(const std::string& fileName);
    void closeFile();
    int getWriteNumber() const;
    void writeRecordToBuffer(const Record& record);
    void flushBuffer();

};
