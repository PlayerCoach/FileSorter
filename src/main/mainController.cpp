#include "mainController.h"

mainController::mainController() { std::cout << "mainController created" << std::endl; }

void mainController::printMenu() {
    std::cout << "Menu" << std::endl;
    std::cout << "1. Read from file" << std::endl;
    std::cout << "2. Write to file" << std::endl;
    std::cout << "3. Exit" << std::endl;
}
