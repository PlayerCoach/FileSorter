#include <iostream> 
#include <fstream>
#include <string>
#include "const.h"
#include "record.h"
#include <bitset>
//class than handles the output of the program and writing blocks to the file // maby use inharitence later, for clarity
class outputHandler
{
private:
    std::ofstream file;
    int outputBuffer[BUFFER_SIZE];
    std::string recordToBinary(const Record& record);
public:
    outputHandler();
    void writeBlockToFile(std::string fileName, std::string content);
    void writeRecordToFile(std::string fileName, const Record& record);
    void openFile(std::string fileName);
    void closeFile();
};
