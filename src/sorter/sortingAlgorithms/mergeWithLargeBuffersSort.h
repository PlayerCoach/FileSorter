#include "sortingStrategy.h"
#include "fileHandler.h"
#include "record.h"
#include <iostream>
#include <queue>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>
#include <optional>
#include <filesystem>
#include <memory>
#include <map>
#include "outputFileNames.h"

class LargeBufferSort : public SortingStrategy {
    private:
    const int numberOfBuffersToRead = 100;
    std::vector<std::string> tapes;

public:
    LargeBufferSort(fileHandler* handler, std::string inputFile)
        : SortingStrategy(handler, inputFile) {}
    void sort() override;
    void createRuns();
    bool mergeNTapes(int startTapeIndex, std::vector<std::string>& newTapes, int iterator, bool changeBaseName);
    void mergeAllTapes();
    bool readBuffers(std::vector<Record>& records);
    void deleteFiles(std::vector<std::string> files);
};
