#pragma once
#include "fileHandler.h"

class SortingStrategy {
protected:
    fileHandler* IOhandler;
    std::string inputFile;
    int readNumber = 0;
    int writeNumber = 0;
    int phaseCounter = 1;
public:
    SortingStrategy(fileHandler* handler, std::string inputFile)
        : IOhandler(handler), inputFile(inputFile) {}
    virtual void sort() = 0;
    virtual ~SortingStrategy() = default;
    const int getReadNumber() const { return readNumber; }
    const int getWriteNumber() const { return writeNumber; }
    const int getPhaseCounter() const { return phaseCounter; }
    
};