// Class that handles input from the user, it takes the records stacks them to one block and writes it to the file
#include <iostream>
#include <fstream>
#include <string>
#include "const.h"
#include "record.h"
#include <bit>
#include <bitset>
#include <stdlib.h>
#include <optional>
class inputHandler
{
private:
    std::ifstream file;
    int inputBuffer[BUFFER_SIZE];
    Record binaryToRecord(char* recordBuffer, const int& size);
    std::streampos fileIndex = 0;
public:
    inputHandler();
    std::optional<Record> readRecordFromFile(std::string fileName);
    void openFile(std::string fileName);
    void closeFile();
};


