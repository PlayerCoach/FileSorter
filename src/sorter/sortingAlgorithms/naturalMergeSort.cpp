#include "naturalMergeSort.h"
 
void NaturalMergeSort::sort() {
    IOhandler->openFileForInput(inputFile);
    IOhandler->openFileForOutput(TEMP_OUTPUT1);
    IOhandler->openFileForOutput(TEMP_OUTPUT2);
    initNaturalMergeSort();

}
void NaturalMergeSort::initNaturalMergeSort() 
{
    bufferT block(BUFFER_SIZE);
    bufferT temp1Buffer(BUFFER_SIZE);
    bufferT temp2Buffer(BUFFER_SIZE);
    size_t currentRecordSize;
    std::vector<int> record;
    std::optional<Record> prevRecord = std::nullopt;


    int size = BUFFER_SIZE;
    bool eof = false;
    int startIndexOfCurrentRun = 0;
    int endIndexOfCurrentRun = 0;
    bool writeToTemp1 = true;
    while(!eof)
    {
        block.buffer = IOhandler->readBlockFromFile(inputFile, eof, size); // read new block
        
        currentRecordSize = reinterpret_cast<int32_t*>(block.buffer)[0]; // get the size of the record
        block.index += sizeof(int32_t);
        endIndexOfCurrentRun += currentRecordSize;

        for(int i = 0; i < currentRecordSize; i++)
        {
            record.push_back(reinterpret_cast<int32_t*>(block.buffer)[block.index]);
            block.index += sizeof(int32_t);
            endIndexOfCurrentRun+= sizeof(int32_t);

            if(block.isFull())
            {
                block.reset();
                block.buffer = IOhandler->readBlockFromFile(inputFile, eof, size);
            }
        }
        Record prevRecord(record);
    }
   
}


void NaturalMergeSort::merge() 
{

   
}