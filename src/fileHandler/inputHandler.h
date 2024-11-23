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
    int bufferReadCount = 0;

    std::ifstream file;
    int readNumber = 0;
    std::streampos fileIndex = 0;

    char readBuffer[BUFFER_SIZE]; // buffer for reading from file
    int readBufferSize = BUFFER_SIZE;
    int readBufferIndex  = BUFFER_SIZE; // symbolizes that the buffer is empty
    bool eof = false;

    void readBlockFromFile();
    std::optional<int32_t> readNextInt();
    bool reloadBuffer();

public:
    inputHandler();
    void openFile(std::string fileName);
    std::optional<Record> readRecordFromFile();
    std::optional<Record> readRecordFromBuffer();
    bool allFilesRead() const;
    const int getReadNumber() const;
    const int getBufferReadCount() const;
    void closeFile();

};


