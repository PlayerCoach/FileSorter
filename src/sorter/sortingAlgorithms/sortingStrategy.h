#pragma once
#include "fileHandler.h"

class SortingStrategy {
protected:
    fileHandler* IOhandler;
    std::string inputFile;
public:
    SortingStrategy(fileHandler* handler, std::string inputFile)
        : IOhandler(handler), inputFile(inputFile) {}
    virtual void sort() = 0;
    virtual ~SortingStrategy() = default;
};