#include "naturalMergeSort.h"
 
void NaturalMergeSort::sort() {
    initNaturalMergeSort();
    // merge();
    std::optional<std::string> sortedFile = std::nullopt;
    while(true)
    {
        merge();
        sortedFile = divide();
        if(sortedFile.has_value())
            break;
        // std::cout<< "TEMP OUTPUT 1" << std::endl;
        // this->IOhandler->displayFile(TEMP_OUTPUT1);
        // std::cout<< "TEMP OUTPUT 2" << std::endl;
        // this->IOhandler->displayFile(TEMP_OUTPUT2);
         //std::cout<< "MAIN OUTPUT" << std::endl;
         //this->IOhandler->displayFile(MAIN_OUTPUT);
    } 
    this->IOhandler->displayFile(sortedFile.value());
    //change name of sorted file
    // std::filesystem::remove(MAIN_OUTPUT);
    // std::filesystem::rename(sortedFile.value(), MAIN_OUTPUT);
    // //delte temp files
    // std::filesystem::remove(TEMP_OUTPUT1);
    // std::filesystem::remove(TEMP_OUTPUT2);

    std::cout << "Read number: " << this->readNumber << std::endl;
    std::cout << "Write number: " << this->writeNumber << std::endl;

    // std::cout << "Number of active files: " << this->IOhandler->getNumberOfActiveFiles() << std::endl;

}
void NaturalMergeSort::initNaturalMergeSort() {
    this->IOhandler->openFileForInput(inputFile);
    this->IOhandler->openFileForOutput(TEMP_OUTPUT1);
    this->IOhandler->openFileForOutput(TEMP_OUTPUT2);
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
            std::cout << "Unexpected end of file" << std::endl;
            std::cout << "Counter: " << counter << std::endl;
            exit(1);
        }

       if (currentRecord.value() > prevrecord.value()) {
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
    this->IOhandler->openFileForOutput(MAIN_OUTPUT);
    this->IOhandler->openFileForInput(TEMP_OUTPUT1);
    this->IOhandler->openFileForInput(TEMP_OUTPUT2);

    // Read initial records
    std::optional<Record> recordFromFirstFile = this->IOhandler->readRecordFromBuffer(TEMP_OUTPUT1);
    std::optional<Record> recordFromSecondFile = this->IOhandler->readRecordFromBuffer(TEMP_OUTPUT2);

    // Merge records from the two files
    while (recordFromFirstFile.has_value() || recordFromSecondFile.has_value()) {
        if (!recordFromFirstFile.has_value()) {
            // First file is empty, write from second file
            this->IOhandler->writeRecordToBuffer(MAIN_OUTPUT, recordFromSecondFile.value());
            recordFromSecondFile = this->IOhandler->readRecordFromBuffer(TEMP_OUTPUT2);
        } else if (!recordFromSecondFile.has_value()) {
            // Second file is empty, write from first file
            this->IOhandler->writeRecordToBuffer(MAIN_OUTPUT, recordFromFirstFile.value());
            recordFromFirstFile = this->IOhandler->readRecordFromBuffer(TEMP_OUTPUT1);
        } else if (recordFromFirstFile.value() > recordFromSecondFile.value()) {
            // Write smaller value to output
            this->IOhandler->writeRecordToBuffer(MAIN_OUTPUT, recordFromFirstFile.value());
            recordFromFirstFile = this->IOhandler->readRecordFromBuffer(TEMP_OUTPUT1);
        } else {
            // Write smaller value to output
            this->IOhandler->writeRecordToBuffer(MAIN_OUTPUT, recordFromSecondFile.value());
            recordFromSecondFile = this->IOhandler->readRecordFromBuffer(TEMP_OUTPUT2);
        }
    }

    // Flush and close files
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