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

    char* readBuffer = nullptr;
    int readBufferSize = BUFFER_SIZE;
    int readBufferIndex  = BUFFER_SIZE; // symbolizes that the buffer is empty
    bool eof = false;
public:
    inputHandler();
    std::optional<Record> readRecordFromFile(std::string fileName);
    char* readBlockFromFile(std::string fileName, bool& eof, int& size);
    void openFile(std::string fileName);
    void closeFile();
    const int getReadNumber() const;
    std::optional<Record> readRecordFromBuffer(bool& eofRef);
};


