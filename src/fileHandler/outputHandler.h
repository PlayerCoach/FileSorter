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
    int writeBufferSize = BUFFER_SIZE;
    int writeBufferIndex= 0;
    bool eof = false;
public:
    outputHandler();
    void writeRecordToFile(std::string fileName, const Record& record);
    void writeBlockToFile(std::string fileName, char* content, int size = BUFFER_SIZE);
    void openFile(std::string fileName);
    void closeFile();
    int getWriteNumber() const;
    void writeRecordToBuffer(const Record& record);
    void flushBuffer();

};
