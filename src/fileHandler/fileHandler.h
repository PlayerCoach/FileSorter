#include "inputHandler.h"
#include "outputHandler.h"

class fileHandler
{
private:
    inputHandler inputHandler;
    outputHandler outputHandler;
    int mainBuffer[BUFFER_SIZE];
public:
    fileHandler();
    void start(std::string inputFileName, std::string outputFileName);
    void readFromFile(std::string fileName);
    void writeToFile(std::string fileName, std::string content);
};