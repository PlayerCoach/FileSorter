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
    std::ifstream file;
    int readNumber = 0;
    Record binaryToRecord(char* recordBuffer, const int& size);
    std::streampos fileIndex = 0;
public:
    inputHandler();
    std::optional<Record> readRecordFromFile(std::string fileName);
    char* readBlockFromFile(std::string fileName, bool& eof, int& size);
    void openFile(std::string fileName);
    void closeFile();
    const int getReadNumber() const;
};


