// Class that handles input from the user, it takes the records stacks them to one block and writes it to the file
#include <iostream>
#include <fstream>
#include <string>
#include "const.h"

class inputHandler
{
private:
    int inputBuffer[BUFFER_SIZE];
    std::string binaryToRecord();
public:
    inputHandler();
    void readFromFile(std::string fileName);
};


