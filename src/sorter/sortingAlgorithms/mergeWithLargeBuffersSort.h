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
#include "const.h"

class LargeBufferSort : public SortingStrategy {
    private:
    const int numberOfBuffersToRead = AVAILABLE_BUFFERS;
    std::vector<std::string> tapes;

    std::string createNextTape(int tempTapeIndex);
    void sortAndSaveRecords(std::vector<Record>& records, std::string outputTape);
    void mergeTempFiles(std::vector<std::string>& files);
    auto initializeHeap(int startTapeIndex, bool& hasReadAll);
    std::string determineOutputTapeName(int iterator, bool changeBaseName);


public:
    LargeBufferSort(fileHandler* handler, std::string inputFile)
        : SortingStrategy(handler, inputFile) {}
    void sort() override;
    void createRuns();
    bool mergeNTapes(int startTapeIndex, std::vector<std::string>& newTapes, int iterator, bool changeBaseName);
    void mergeAllTapes();
    bool readBuffers(std::vector<Record>& records);
    void deleteTempFiles(std::vector<std::string> files);
};
