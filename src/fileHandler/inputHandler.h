#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include "const.h"
#include "record.h"
#include <stdlib.h>
#include <optional>
class inputHandler
{
private:
    std::string fileName;

    std::ifstream file;
    int readNumber = 0;
    std::streampos fileIndex = 0;

    char readBuffer[BUFFER_SIZE]; // buffer for reading from file
    int readBufferSize = BUFFER_SIZE;
    int readBufferIndex  = BUFFER_SIZE; // symbolizes that the buffer is empty
    bool eof = false;

    void readBlockFromFile();
public:
    inputHandler();
    std::optional<Record> readRecordFromFile();
    void openFile(std::string fileName);
    void closeFile();
    const int getReadNumber() const;
    std::optional<Record> readRecordFromBuffer();
    bool allFilesRead() const;

};


