#pragma once
#include "inputHandler.h"
#include "outputHandler.h"
#include "const.h"
#include "record.h"
#include <filesystem>
#include <iostream>
#include <fstream>
#include <string>
#include <optional>
#include <unordered_map>
#include <memory>

class fileHandler
{
private:
    std::unordered_map<std::string, std::unique_ptr<inputHandler>> inputHandlers;
    std::unordered_map<std::string, std::unique_ptr<outputHandler>> outputHandlers;
public:
    fileHandler();
    std::optional<Record> readRecordFromFile(const std::string& fileName);
    void writeRecordToFile(const std::string& fileName, const Record& content);
    void clearFile(const std::string& fileName);
    void openFileForInput(const std::string& fileName);   
    void closeFileForInput(const std::string& fileName);
    void openFileForOutput(const std::string& fileName);
    void closeFileForOutput(const std::string& fileName);
    void readReinterpretWrite(const std::string& inputFileName, const std::string& outputFileName);
    void readWriteBlock(const std::string& inputFileName, const std::string& outputFileName);
    void writeRecordToBuffer(const std::string& fileName, const Record& record);
    std::optional<Record> readRecordFromBuffer(const std::string& fileName);
    void flushWriteBuffer(const std::string& fileName);
    void displayFile(const std::string& fileName);
    bool allFilesRead(const std::string& fileName);
    int getReadNumber(const std::string& fileName) const;
    int getWriteNumber(const std::string& fileName) const;
    int getNumberOfActiveFiles() const;


};