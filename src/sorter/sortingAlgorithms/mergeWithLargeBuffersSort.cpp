#include "mergeWithLargeBuffersSort.h"

void LargeBufferSort::sort() 
{
    createRuns();
    mergeAllTapes();

    std::cout << "Read number: " << this->readNumber << std::endl;
    std::cout << "Write number: " << this->writeNumber << std::endl;
    std::cout << "Total number of IOs: " << this->readNumber + this->writeNumber << std::endl;
    
}

void LargeBufferSort::createRuns() 
{
    this->IOhandler->openFileForInput(this->inputFile);
    std::vector<Record> records;
    bool hasReadAll = false;
    int tapeIndex = 0;

    while (!hasReadAll) 
    {
        std::string currentTapeName = createNextTape(tapeIndex);

        hasReadAll = !readBuffers(records);

         if(records.size() == 0)
        {
            this->tapes.pop_back(); // Remove empty tape
            break;
        }

        sortAndSaveRecords(records, currentTapeName);
        records.clear(); // Clear buffer for next tape
        tapeIndex++;
    }
    this->readNumber += this->IOhandler->getReadNumber(this->inputFile);
    this->IOhandler->finalizeFileForInput(this->inputFile);
}

std::string LargeBufferSort::createNextTape(int tempTapeIndex) 
{
    std::string tapeName = TAPE_BASE + std::to_string(tempTapeIndex) + ".bin";
    this->tapes.push_back(tapeName);
    return tapeName;
}

void LargeBufferSort::sortAndSaveRecords(std::vector<Record>& records, std::string outputTape) 
{
    // Sort records in descending order
    std::sort(records.begin(), records.end(), std::greater<Record>());

    this->IOhandler->openFileForOutput(outputTape);
    for (Record record : records) 
    {
        this->IOhandler->writeRecordToBuffer(outputTape, record);
    }
    this->IOhandler->flushWriteBuffer(outputTape);
    this->writeNumber += this->IOhandler->getWriteNumber(outputTape);
    this->IOhandler->closeFileForOutput(outputTape);
}

bool LargeBufferSort::readBuffers(std::vector<Record>& records)
{
    int32_t currentBufferSize = 0;
    int32_t maxSizeOfBuffer = this->numberOfBuffersToRead * BUFFER_SIZE;
    std::optional<int32_t> nextSize = 0;
    while(true)
    {
    
        nextSize = this->IOhandler->peekNextSizeInBytes(this->inputFile);
        if (!nextSize.has_value()) 
        {
            return false; // no more records to read
        }

        if (currentBufferSize + nextSize.value() > maxSizeOfBuffer) 
        {
            return true; // buffer is full but there are more records to read
        }
    
        std::optional<Record> record = this->IOhandler->readRecordFromBuffer(this->inputFile);
        if (!record.has_value()) 
        {
            return false; 
        }

        records.push_back(record.value());
        currentBufferSize += record.value().getSizeInBytes();
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
            this->mergeTempFiles(this->tapes);// Delete temp files this->mergeTempFiles(this->tapes, iterator);
            this->tapes.clear();
            this->tapes.insert(this->tapes.end(), newTapes.begin(), newTapes.end());
            newTapes.clear();
            changeBaseName = !changeBaseName;
            this->phaseCounter++;
            continue;
            
        }
        startTapeIndex += this->numberOfBuffersToRead;
        iterator++;
    }

    this->IOhandler->renameFile(this->tapes[0], MAIN_OUTPUT);
    this->tapes.clear();
}

auto LargeBufferSort::initializeHeap(int startTapeIndex, bool& hasReadAll) 
{
      auto compare = [](const std::pair<Record, int>& a, const std::pair<Record, int>& b) {
        return a.first < b.first;  // Max-heap based on the Record value
    };
    std::priority_queue<std::pair<Record, int>, std::vector<std::pair<Record, int>>, decltype(compare)> maxHeap(compare);

    for (int i = startTapeIndex; i < startTapeIndex + this->numberOfBuffersToRead; i++) {
        if (i >= this->tapes.size()) {
            hasReadAll = true;
            break;
        }

        std::string tapeName = this->tapes[i];
        this->IOhandler->openFileForInput(tapeName);
        std::optional<Record> record = this->IOhandler->readRecordFromBuffer(tapeName);
        this->IOhandler->closeFileForInput(tapeName);

        if (record.has_value()) {
            maxHeap.push({record.value(), i});
        }
    }

    return maxHeap;
}

std::string LargeBufferSort::determineOutputTapeName(int iterator, bool changeBaseName) {
    return changeBaseName
        ? TEMP_TAPE_BASE + std::to_string(iterator) + ".bin"
        : TAPE_BASE + std::to_string(iterator) + ".bin";
}

bool LargeBufferSort::mergeNTapes(int startTapeIndex, std::vector<std::string>& newTapes, int iterator, bool changeBaseName) {
    bool hasReadAll = false;

    auto maxHeap = initializeHeap(startTapeIndex, hasReadAll);

    // Determine output tape name
    std::string outputTape = determineOutputTapeName(iterator, changeBaseName);
    this->IOhandler->openFileForOutput(outputTape);

    // Merge logic
    while (!maxHeap.empty()) 
    {
        auto [record, tapeIndex] = maxHeap.top();
        maxHeap.pop();

        this->IOhandler->writeRecordToBuffer(outputTape, record);

        std::string tapeName = this->tapes[tapeIndex];
        this->IOhandler->openFileForInput(tapeName);
        std::optional<Record> nextRecord = this->IOhandler->readRecordFromBuffer(tapeName);
        this->IOhandler->closeFileForInput(tapeName);

        if (nextRecord.has_value()) 
        {
            maxHeap.push({nextRecord.value(), tapeIndex});
        } 
        else 
        {
            // Close the input tape if no more records are left
            this->readNumber += this->IOhandler->getReadNumber(tapeName);
            this->IOhandler->finalizeFileForInput(tapeName);
        }
    }

    this->IOhandler->flushWriteBuffer(outputTape);
    this->writeNumber += this->IOhandler->getWriteNumber(outputTape);
    this->IOhandler->closeFileForOutput(outputTape);

    newTapes.push_back(outputTape);
    return hasReadAll;
}

void LargeBufferSort::deleteTempFiles(std::vector<std::string> files)
{
    for(auto file : files)
    {
        this->IOhandler->deleteFile(file);
    }
}

void LargeBufferSort::mergeTempFiles(std::vector<std::string>& files)
{
    std::string outputFolderName = PHASE_DIR_BASE + std::to_string(this->phaseCounter);
    std::string outputFolderPath = this->IOhandler->createFolder(outputFolderName);

    for(auto file : files)
    {
        this->IOhandler->moveFile(file, outputFolderPath);
    }

    this->IOhandler->concatenateFilesInFolder(outputFolderPath, "stage" +  std::to_string(this->phaseCounter) + ".bin");
    this->IOhandler->deleteFolder(outputFolderPath);
}















