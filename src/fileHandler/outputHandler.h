#include <iostream> 
#include <fstream>
#include <string>
#include "const.h"
//class than handles the output of the program and writing blocks to the file
class outputHandler 
{
private:
    int inputBuffer[BUFFER_SIZE];
    std::string recordToBinary();
public:
    outputHandler();
    void writeToFile(std::string fileName, std::string content);
};
