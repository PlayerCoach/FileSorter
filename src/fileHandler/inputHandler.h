#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include "const.h"
#include "record.h"
#include <stdlib.h>
#include <optional>
#include <cstring>
#include <cerrno>
#include <sstream>
#include "outputFileNames.h"

class inputHandler
{
private:
    std::string fileName;
    int bufferReadCount = 0;

    std::ifstream file;
    int readNumber = 0;
    std::streampos fileIndex = 0;

    char readBuffer[BUFFER_SIZE]; // buffer for reading from file maby change it for disk or smth
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
    const std::optional<int32_t> peekNextSize();
    const std::optional<int32_t> peekNextSizeInBytes();
    void closeFile();

};


