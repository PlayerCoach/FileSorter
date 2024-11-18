#include <iostream> 
#include <fstream>
#include <string>
#include "const.h"
#include "record.h"
#include <bitset>
//class than handles the output of the program and writing blocks to the file
class outputHandler 
{
private:
    int inputBuffer[BUFFER_SIZE];
    std::string recordToBinary(const Record& record);
public:
    outputHandler();
    void writeBlockToFile(std::string fileName, std::string content);
    void writeRecordToFile(std::string fileName, const Record& record);
};
