#include "mergeWithLargeBuffersSort.h"

void LargeBufferSort::sort() {
    createRuns();
    // mergeTapes();

    for(auto tape : this->tapes)
    {
        std::cout << "***************" << std::endl;
        this->IOhandler->displayFile(tape);
        std::cout << "***************" << std::endl;
    }
    
}

void LargeBufferSort::createRuns() {
    this->IOhandler->openFileForInput(this->inputFile);
    std::vector<Record> records;
    bool hasReadAll = false;
    int tapeIndex = 0;
    std::string currentTapeName = "";

    while (!hasReadAll) {
        if (tapeIndex < 100)  // for debugging
            this->tapes.push_back(TAPE_BASE + std::to_string(tapeIndex) + ".bin");

        
        hasReadAll = !readBuffers(records);
         if(records.size() == 0) {
            this->tapes.pop_back();
            break;
        }
        // Sort records in descending order
        std::sort(records.begin(), records.end(), std::greater<Record>());

       
        currentTapeName = this->tapes[tapeIndex];
        this->IOhandler->openFileForOutput(currentTapeName);
        for (Record record : records) {
            this->IOhandler->writeRecordToBuffer(currentTapeName, record);
        }
        this->IOhandler->flushWriteBuffer(currentTapeName);
        this->IOhandler->closeFileForOutput(currentTapeName);

        records.clear(); // Clear buffer for next tape
        tapeIndex++;
    }

    this->IOhandler->closeFileForInput(this->inputFile);
}

/* Version using bytes to determine buffer size, not ideal*/
// bool LargeBufferSort::readBuffers(std::vector<Record>& records)
// {
//     int initialReadBufferCount = this->IOhandler->getBufferReadCount(this->inputFile); 
//     int currentReadBufferCount = initialReadBufferCount;
//     while (currentReadBufferCount - initialReadBufferCount <= this->numberOfBuffersToRead) {
//         std::optional<Record> record = this->IOhandler->readRecordFromBuffer(this->inputFile);
//         if (!record.has_value()) {
//             return false;
//             break;
//         }

//         records.push_back(record.value());
//         currentReadBufferCount = this->IOhandler->getBufferReadCount(this->inputFile);
//     }
//     return true;
// } 

bool LargeBufferSort::readBuffers(std::vector<Record>& records)
{
    for(int i = 0; i < APPROX_NUMBER_OF_RECORDS_IN_BLOCK * this->numberOfBuffersToRead; i++) 
    {
        std::optional<Record> record = this->IOhandler->readRecordFromBuffer(this->inputFile);
        if (!record.has_value()) {
            return false;
            break;
        }

        records.push_back(record.value());
    }
    return true;
} 