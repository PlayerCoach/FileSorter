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
    std::string createFolder(const std::string& folderName);
    std::optional<Record> readRecordFromFile(const std::string& fileName);
    void writeRecordToFile(const std::string& fileName, const Record& content);
    void openFileForInput(const std::string& fileName);   
    void closeFileForInput(const std::string& fileName);
    void finalizeFileForInput(const std::string& fileName);
    void openFileForOutput(const std::string& fileName, const std::string& mode = "truncate");
    void closeFileForOutput(const std::string& fileName);
    void writeRecordToBuffer(const std::string& fileName, const Record& record);
    std::optional<Record> readRecordFromBuffer(const std::string& fileName);
    void flushWriteBuffer(const std::string& fileName);
    void displayFile(const std::string& fileName);
    bool allFilesRead(const std::string& fileName);
    const int getReadNumber(const std::string& fileName) const;
    const int getWriteNumber(const std::string& fileName) const;
    const int getNumberOfActiveFiles() const;
    const std::optional<int32_t> peekNextSize(const std::string& fileName);
    const std::optional<int32_t> peekNextSizeInBytes(const std::string& fileName);
    void saveCurrentOutputDirState(const std::string& outputDirStateFolderName);
    void renameFile(const std::string& oldName, const std::string& newName);
    void deleteFile(const std::string& fileName);
    void moveFile(const std::string& oldName, const std::string& newName); 
    void concatenateFilesInFolder(const std::string& folderPath, const std::string& outputFileName);
    void deleteFolder(const std::string& folderPath);
    void copyFile(const std::string& source, const std::string& destination);
    void convertTxtToInputBin(const std::string& txtFilePath);
    void deleteAllBinFilesExceptInput();
    void clearFile(const std::string& fileName);
    void displayNFirstRecords(const std::string& fileName, int n);

};