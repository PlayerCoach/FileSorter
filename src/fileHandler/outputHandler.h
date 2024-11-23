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
    void writeIntToBuffer(int32_t value);
public:
    outputHandler();
    void openFile(const std::string& fileName, const std::string& mode = "truncate");
    void writeRecordToFile(const Record& record);
    void writeRecordToBuffer(const Record& record);
    const int getWriteNumber() const;
    void flushBuffer();
    void closeFile();

};
