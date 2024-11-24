#include "mergeWithLargeBuffersSort.h"

void LargeBufferSort::sort() {
    createRuns();
    mergeAllTapes();

    // for(auto tape : this->tapes)
    // {
    //     std::cout << "***************" << std::endl;
    //     this->IOhandler->displayFile(tape);
    //     std::cout << "***************" << std::endl;
    // }

    this->IOhandler->displayFile("output.bin");
    
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
    int32_t currentBufferSize = 0;
    int32_t maxSizeOfBuffer = this->numberOfBuffersToRead * BUFFER_SIZE;
    std::optional<int32_t> nextSize = 0;
    bool firstRead = false;
    while(true)
    {
        if(firstRead)
        {
            nextSize = this->IOhandler->peekNextSizeInBytes(this->inputFile);
            if (!nextSize.has_value()) {
                return false;
            }
            if (currentBufferSize + nextSize.value() > maxSizeOfBuffer) {
                return true;
            }
        }
       
    
        std::optional<Record> record = this->IOhandler->readRecordFromBuffer(this->inputFile);
        if (!record.has_value()) {
            return false;
        }

        records.push_back(record.value());
        currentBufferSize += record.value().getSizeInBytes();
        firstRead = true;
    }
    return true;
} 

void LargeBufferSort::mergeAllTapes()
{
    int currentPhase = 0;
    std::vector<std::string> newTapes;
    bool changeBaseName = true;


    int startTapeIndex = 0;
    
    while(this->tapes.size() > 1)
    {
        bool hasReadAll = mergeNTapes(startTapeIndex, newTapes, currentPhase, changeBaseName);
        if(hasReadAll)
        {
            startTapeIndex = 0;
            currentPhase = 0;
            this->deleteFiles(this->tapes);
            this->tapes.clear();
            this->tapes.insert(this->tapes.end(), newTapes.begin(), newTapes.end());
            newTapes.clear();
            changeBaseName = !changeBaseName;
            continue;
            
        }
    }

    std::string finalOutput = "output.bin";
    std::filesystem::rename(this->tapes[0], finalOutput);
    this->tapes.clear();

 
}

bool LargeBufferSort::mergeNTapes(int startTapeIndex, std::vector<std::string>& newTapes, int iterator, bool changeBaseName)
{
    bool hasReadAll = false;
    std::priority_queue<Record> maxHeap;
    for(int i = startTapeIndex; i < startTapeIndex + this->numberOfBuffersToRead; i++)
    {
        if(i >= this->tapes.size())
        {
            hasReadAll = true;
            break;
        }
        std::string tapeName = this->tapes[i];
        this->IOhandler->openFileForInput(tapeName);
        std::optional<Record> record = this->IOhandler->readRecordFromBuffer(tapeName);
        if(record.has_value())
        {
            maxHeap.push(record.value());
        }
        this->IOhandler->closeFileForInput(tapeName);

    }
    std::string outputTape;
    if(changeBaseName)
    {
        outputTape = TEMP_TAPE_BASE + std::to_string(iterator) + ".bin";
    }
    else
    {
        outputTape = TAPE_BASE + std::to_string(iterator) + ".bin";
    }

    this->IOhandler->openFileForOutput(outputTape);
    while(!maxHeap.empty())
    {
        Record record = maxHeap.top();
        maxHeap.pop();
        this->IOhandler->writeRecordToBuffer(outputTape, record);
    }
    this->IOhandler->flushWriteBuffer(outputTape);
    this->IOhandler->closeFileForOutput(outputTape);

    // for(int i = startTapeIndex ; i < startTapeIndex + this->numberOfBuffersToRead; i++)
    // {
    //     std::filesystem::remove(this->tapes[i]);
    //     this->tapes.erase(this->tapes.begin() + i);
    // } -> cant remove them here cause it would change the indexes of the tapes
    newTapes.push_back(outputTape);
    return hasReadAll;

}

void deleteFiles(std::vector<std::string> files)
{
    for(auto file : files)
    {
        std::filesystem::remove(file);
    }
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