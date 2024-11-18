#include "mainController.h"

mainController::mainController() { 
    std::cout << "mainController created" << std::endl; 
    Record record;
    std::cout<<record.getSeries().size()<<std::endl;
    std::cout<<record<<std::endl;
    //if out\test.txt does not exist, it will be created
    fileHandler.writeRecordToFile("src\\out\\test.txt", record);


}

void mainController::printMenu() {
    std::cout << "Menu" << std::endl;
    std::cout << "1. Read from file" << std::endl;
    std::cout << "2. Write to file" << std::endl;
    std::cout << "3. Exit" << std::endl;

}
