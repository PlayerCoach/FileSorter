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

void LargeBufferSort::mergeNTapes(int startTapeIndex)
{
    std::priority_queue<Record> maxHeap;
    for(int i = startTapeIndex; i < startTapeIndex + this->numberOfBuffersToRead; i++)
    {
        std::string tapeName = this->tapes[i];
        this->IOhandler->openFileForInput(tapeName);
        std::optional<Record> record = this->IOhandler->readRecordFromBuffer(tapeName);
        if(record.has_value())
        {
            maxHeap.push(record.value());
        }
        this->IOhandler->closeFileForInput(tapeName);

    }

    this->IOhandler->openFileForOutput(this->tapes[startTapeIndex]);
    while(!maxHeap.empty())
    {
        Record record = maxHeap.top();
        maxHeap.pop();
        this->IOhandler->writeRecordToBuffer(this->tapes[startTapeIndex], record);
    }
    this->IOhandler->flushWriteBuffer(this->tapes[startTapeIndex]);
    this->IOhandler->closeFileForOutput(this->tapes[startTapeIndex]);

    for(int i = startTapeIndex + 1; i < startTapeIndex + this->numberOfBuffersToRead; i++)
    {
        std::filesystem::remove(this->tapes[i]);
        this->tapes.erase(this->tapes.begin() + i);
    }



}

void LargeBufferSort::mergeAllTapes()
{
    int currentPhase = 0;
    int startTapeIndex = 0;
    while(this->tapes.size() > 1)
    {
        mergeNTapes(startTapeIndex);
        startTapeIndex += this->numberOfBuffersToRead;
        currentPhase++;
    } // i dont know how to manage file names here, like here would be a good place to delete the files that are no longer needed
 
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