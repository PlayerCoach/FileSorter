#include "naturalMergeSort.h"
 
void NaturalMergeSort::sort() {
    initNaturalMergeSort();
    std::optional<std::string> sortedFile = std::nullopt;
    while(true)
    {
        sortedFile = divide();
        if(sortedFile.has_value())
            break;
        merge();
    } 
    //change name of sorted file
    std::filesystem::remove(MAIN_OUTPUT);
    std::filesystem::rename(sortedFile.value(), MAIN_OUTPUT);
    //delte temp files
    std::filesystem::remove(TEMP_OUTPUT1);
    std::filesystem::remove(TEMP_OUTPUT2);

    std::cout << "Read number: " << this->readNumber << std::endl;
    std::cout << "Write number: " << this->writeNumber << std::endl;

    std::cout << "Number of active files: " << this->IOhandler->getNumberOfActiveFiles() << std::endl;

}
void NaturalMergeSort::initNaturalMergeSort() {
    IOhandler->openFileForInput(inputFile);
    IOhandler->openFileForOutput(TEMP_OUTPUT1);
    IOhandler->openFileForOutput(TEMP_OUTPUT2);
    std::string currentOutputFile = TEMP_OUTPUT1;
    std::optional<Record> prevrecord = this->IOhandler->readRecordFromBuffer(inputFile);

    if(!prevrecord.has_value())
    {
        std::cout << "Empty file" << std::endl;
        return;
    }

    this->IOhandler->writeRecordToBuffer(currentOutputFile, prevrecord.value());
    std::optional<Record> currentRecord = std::nullopt;
    int counter = 0;

    while(!this->IOhandler->allFilesRead(inputFile))
    {
        currentRecord = this->IOhandler->readRecordFromBuffer(inputFile);
        if(!currentRecord.has_value())
        {
            /* MAIN ERROR IS SOMEWHERE HERE*/
            /*Error: Not enough data to read size*/
            std::cout << "Unexpected end of file" << std::endl;
            std::cout << "Counter: " << counter << std::endl;
            exit(1); 
        }

       if (currentRecord.value() < prevrecord.value()) {
            currentOutputFile = (currentOutputFile == TEMP_OUTPUT1) ? TEMP_OUTPUT2 : TEMP_OUTPUT1;
        }       
        this->IOhandler->writeRecordToBuffer(currentOutputFile, currentRecord.value());
        prevrecord = currentRecord;
        counter++;


    }
    this->IOhandler->flushWriteBuffer(TEMP_OUTPUT1);
    this->IOhandler->flushWriteBuffer(TEMP_OUTPUT2);
    this->readNumber += this->IOhandler->getReadNumber(inputFile);
    this->writeNumber += this->IOhandler->getWriteNumber(TEMP_OUTPUT1) + this->IOhandler->getWriteNumber(TEMP_OUTPUT2);

    this->IOhandler->closeFileForInput(inputFile);
    this->IOhandler->closeFileForOutput(TEMP_OUTPUT1);
    this->IOhandler->closeFileForOutput(TEMP_OUTPUT2); 
   
}


void NaturalMergeSort::merge() {
    IOhandler->openFileForOutput(MAIN_OUTPUT);
    IOhandler->openFileForInput(TEMP_OUTPUT1);
    IOhandler->openFileForInput(TEMP_OUTPUT2);

    std::optional<Record> recordFromFirstFile = this->IOhandler->readRecordFromBuffer(TEMP_OUTPUT1);
    std::optional<Record> recordFromSecondFile = this->IOhandler->readRecordFromBuffer(TEMP_OUTPUT2);

    while(!this->IOhandler->allFilesRead(TEMP_OUTPUT1) || !this->IOhandler->allFilesRead(TEMP_OUTPUT2))
    {
        if(!recordFromFirstFile.has_value() && !recordFromSecondFile.has_value())
        {
            std::cout << "Unexpected end of file" << std::endl;
            exit(1);
        }
        else if(!recordFromFirstFile.has_value())
        {
            this->IOhandler->writeRecordToBuffer(MAIN_OUTPUT, recordFromSecondFile.value());
            recordFromSecondFile = this->IOhandler->readRecordFromBuffer(TEMP_OUTPUT2);
        }
        else if(!recordFromSecondFile.has_value())
        {
            this->IOhandler->writeRecordToBuffer(MAIN_OUTPUT, recordFromFirstFile.value());
            recordFromFirstFile = this->IOhandler->readRecordFromBuffer(TEMP_OUTPUT1);
        }
        else if(recordFromFirstFile.value() > recordFromSecondFile.value())
        {
            this->IOhandler->writeRecordToBuffer(MAIN_OUTPUT, recordFromFirstFile.value());
            recordFromFirstFile = this->IOhandler->readRecordFromBuffer(TEMP_OUTPUT1);
        }
        else
        {
            this->IOhandler->writeRecordToBuffer(MAIN_OUTPUT, recordFromSecondFile.value());
            recordFromSecondFile = this->IOhandler->readRecordFromBuffer(TEMP_OUTPUT2);
        }
    }


    this->IOhandler->flushWriteBuffer(MAIN_OUTPUT);
    this->readNumber += this->IOhandler->getReadNumber(TEMP_OUTPUT1) + this->IOhandler->getReadNumber(TEMP_OUTPUT2);
    this->writeNumber += this->IOhandler->getWriteNumber(MAIN_OUTPUT);

    this->IOhandler->closeFileForInput(TEMP_OUTPUT1);
    this->IOhandler->closeFileForInput(TEMP_OUTPUT2);
    this->IOhandler->closeFileForOutput(MAIN_OUTPUT);
   
}

std::optional<std::string> NaturalMergeSort::divide() {
    bool isSorted = true;
    IOhandler->openFileForInput(MAIN_OUTPUT);
    IOhandler->openFileForOutput(TEMP_OUTPUT1);
    IOhandler->openFileForOutput(TEMP_OUTPUT2);

    std::string currentOutputFile = TEMP_OUTPUT1;
    std::optional<Record> prevrecord = this->IOhandler->readRecordFromBuffer(MAIN_OUTPUT);

    if(!prevrecord.has_value())
    {
        std::cout << "Empty file" << std::endl;
        return std::nullopt;
    }

    this->IOhandler->writeRecordToBuffer(currentOutputFile, prevrecord.value());
    std::optional<Record> currentRecord = std::nullopt;

    while(!this->IOhandler->allFilesRead(MAIN_OUTPUT))
    {
        currentRecord = this->IOhandler->readRecordFromBuffer(MAIN_OUTPUT);
        if(!currentRecord.has_value())
        {
            std::cout << "Unexpected end of file" << std::endl;
            exit(1);
        }

        if(currentRecord.value() > prevrecord.value())
        {
            isSorted = false;
            currentOutputFile = (currentOutputFile == TEMP_OUTPUT1) ? TEMP_OUTPUT2 : TEMP_OUTPUT1;
        }
        this->IOhandler->writeRecordToBuffer(currentOutputFile, currentRecord.value());
        prevrecord = currentRecord;
    }

    this->IOhandler->flushWriteBuffer(TEMP_OUTPUT1);
    this->IOhandler->flushWriteBuffer(TEMP_OUTPUT2);
    this->readNumber += this->IOhandler->getReadNumber(MAIN_OUTPUT);
    this->writeNumber += this->IOhandler->getWriteNumber(TEMP_OUTPUT1) + this->IOhandler->getWriteNumber(TEMP_OUTPUT2);

    this->IOhandler->closeFileForInput(MAIN_OUTPUT);
    this->IOhandler->closeFileForOutput(TEMP_OUTPUT1);
    this->IOhandler->closeFileForOutput(TEMP_OUTPUT2);

    if(isSorted)
    {
        return std::make_optional(currentOutputFile);
    }   
    else
    {
        return std::nullopt;
    }


}