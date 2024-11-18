#include "inputHandler.h"
#include "outputHandler.h"
#include "const.h"
#include "record.h"
#include <filesystem>

class fileHandler
{
private:
    inputHandler inputHandler;
    outputHandler outputHandler;
    int mainBuffer[BUFFER_SIZE];
public:
    fileHandler();
    void start(std::string inputFileName, std::string outputFileName);
    Record readRecordFromFile(std::string fileName);
    void writeRecordToFile(std::string fileName, const Record& content);
    void clearFile(std::string fileName);

};