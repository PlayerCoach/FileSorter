#include "naturalMergeSort.h"
 
void NaturalMergeSort::sort() {
    IOhandler->openFileForInput(inputFile);
    IOhandler->openFileForOutput(TEMP_OUTPUT1);
    IOhandler->openFileForOutput(TEMP_OUTPUT2);
    initNaturalMergeSort();

}
void NaturalMergeSort::initNaturalMergeSort() 
{
    bool eof = false;
    std::string currentFile = TEMP_OUTPUT1;
    std::optional<Record> prevrecord = this->IOhandler->readRecordFromBuffer(inputFile, eof);
    if(!prevrecord.has_value())
    {
        std::cout << "Empty file" << std::endl;
        return;
    }
    this->IOhandler->writeRecordToBuffer(currentFile, prevrecord.value());
    std::optional<Record> currentRecord = std::nullopt;

    while(!eof)
    {
        currentRecord = this->IOhandler->readRecordFromBuffer(inputFile, eof);
        if(!currentRecord.has_value())
        {
            //std::cout << "error while reading value from file" << std::endl;
            eof = true;
            break;
        }
        if(currentRecord.value() < prevrecord.value())
        {
            currentFile = (currentFile == TEMP_OUTPUT1) ? TEMP_OUTPUT2 : TEMP_OUTPUT1;
        }
        this->IOhandler->writeRecordToBuffer(currentFile, currentRecord.value());
        prevrecord = currentRecord;


    }
    this->IOhandler->flushWriteBuffer(TEMP_OUTPUT1);
    this->IOhandler->flushWriteBuffer(TEMP_OUTPUT2);

    this->IOhandler->closeFileForInput(inputFile);
    this->IOhandler->closeFileForOutput(TEMP_OUTPUT1);
    this->IOhandler->closeFileForOutput(TEMP_OUTPUT2); 
   
}


void NaturalMergeSort::merge() 
{

   
}
