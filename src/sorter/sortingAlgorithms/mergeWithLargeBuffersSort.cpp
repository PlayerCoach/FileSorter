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

    //this->IOhandler->displayFile(MAIN_OUTPUT);
    std::cout << "Read number: " << this->readNumber << std::endl;
    std::cout << "Write number: " << this->writeNumber << std::endl;
    std::cout << "Total number of IOs: " << this->readNumber + this->writeNumber << std::endl;
    
}

void LargeBufferSort::createRuns() {
    this->IOhandler->openFileForInput(this->inputFile);
    std::vector<Record> records;
    bool hasReadAll = false;
    int tapeIndex = 0;
    std::string currentTapeName = "";

    while (!hasReadAll) {
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
        this->writeNumber += this->IOhandler->getWriteNumber(currentTapeName);
        this->IOhandler->closeFileForOutput(currentTapeName);

        records.clear(); // Clear buffer for next tape
        tapeIndex++;
    }
    this->readNumber += this->IOhandler->getReadNumber(this->inputFile);
    this->IOhandler->finalizeFileForInput(this->inputFile);
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
    int iterator = 0;
    std::vector<std::string> newTapes;
    bool changeBaseName = true;


    int startTapeIndex = 0;
    
    while(this->tapes.size() > 1)
    {
        bool hasReadAll = mergeNTapes(startTapeIndex, newTapes, iterator, changeBaseName);
        if(hasReadAll)
        {
            startTapeIndex = 0;
            iterator = 0;
            this->deleteFiles(this->tapes);
            this->tapes.clear();
            this->tapes.insert(this->tapes.end(), newTapes.begin(), newTapes.end());
            newTapes.clear();
            changeBaseName = !changeBaseName;
            continue;
            
        }
        startTapeIndex += this->numberOfBuffersToRead;
        iterator++;
    }

    std::filesystem::rename(this->tapes[0], MAIN_OUTPUT);
    this->tapes.clear();

 
}

bool LargeBufferSort::mergeNTapes(int startTapeIndex, std::vector<std::string>& newTapes, int iterator, bool changeBaseName) {
    bool hasReadAll = false;

    // A custom comparator for min-heap based on the Record value
    auto compare = [](const std::pair<Record, int>& a, const std::pair<Record, int>& b) {
        return a.first < b.first;  // Max-heap based on the Record value
    };

    // Priority queue (max heap) to merge records incrementally
    std::priority_queue<std::pair<Record, int>, std::vector<std::pair<Record, int>>, decltype(compare)> maxHeap(compare);

    for (int i = startTapeIndex; i < startTapeIndex + this->numberOfBuffersToRead; i++) 
    {
        if (i >= this->tapes.size()) {
            hasReadAll = true;
            break;
        }

        std::string tapeName = this->tapes[i];
        this->IOhandler->openFileForInput(tapeName);

        // Read the first record from the tape
        std::optional<Record> record = this->IOhandler->readRecordFromBuffer(tapeName);
        if (record.has_value()) 
        {
            maxHeap.push({record.value(), i});  // Store record and index of tape
        }
        this->IOhandler->closeFileForInput(tapeName);
    }

    // Determine output tape name
    std::string outputTape;
    if (changeBaseName)
    {
        outputTape = TEMP_TAPE_BASE + std::to_string(iterator) + ".bin";
    } else {
        outputTape = TAPE_BASE + std::to_string(iterator) + ".bin";
    }

    this->IOhandler->openFileForOutput(outputTape);

    // Merge logic
    while (!maxHeap.empty()) {
        // Get the smallest record from the heap
        auto [record, tapeIndex] = maxHeap.top();
        maxHeap.pop();

        // Write the record to the output buffer
        this->IOhandler->writeRecordToBuffer(outputTape, record);

        // Read the next record from the same tape and insert it into the heap
        std::string tapeName = this->tapes[tapeIndex];
        this->IOhandler->openFileForInput(tapeName);
        std::optional<Record> nextRecord = this->IOhandler->readRecordFromBuffer(tapeName);
        this->IOhandler->closeFileForInput(tapeName);
        if (nextRecord.has_value()) {
            maxHeap.push({nextRecord.value(), tapeIndex});
        } else {
            // Close the input tape if no more records are left
            this->readNumber += this->IOhandler->getReadNumber(tapeName);
            this->IOhandler->finalizeFileForInput(tapeName);
        }
    }

    // Flush the output buffer and close the output tape
    this->IOhandler->flushWriteBuffer(outputTape);
    this->writeNumber += this->IOhandler->getWriteNumber(outputTape);
    this->IOhandler->closeFileForOutput(outputTape);

    // Add the output tape to the list of new tapes
    newTapes.push_back(outputTape);
    return hasReadAll;
}


void LargeBufferSort::deleteFiles(std::vector<std::string> files)
{
    for(auto file : files)
    {
        std::filesystem::remove(file);
    }
}
















