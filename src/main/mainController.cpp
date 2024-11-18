#include "mainController.h"

mainController::mainController() { 
    std::cout << "mainController created" << std::endl; 
    Record record;
    std::cout<<record.getSeries().size()<<std::endl;
    std::cout<<record<<std::endl;
    std::string filePath = OUTPUT_FOLDER + std::string("\\test.txt");
    fileHandler.writeRecordToFile(filePath, record);
    Record record2 = fileHandler.readRecordFromFile(filePath);
    std::cout<<record2<<std::endl;
    //fileHandler.clearFile(filePath);



}

void mainController::printMenu() {
    std::cout << "Menu" << std::endl;
    std::cout << "1. Read from file" << std::endl;
    std::cout << "2. Write to file" << std::endl;
    std::cout << "3. Exit" << std::endl;

}
