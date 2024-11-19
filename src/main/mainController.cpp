#include "mainController.h"

mainController::mainController() 
{ 
    this->filePath  = OUTPUT_FOLDER + "\\output.bin";
    fileHandler.clearFile(filePath);
    printMenu();
    bool running = true;
    while(running)
    {
        running = getUserInput();

    }
    
    

}

void mainController::printMenu() {
    const std::string verticalFrame(100, '*');
    const std::string horizontalFrame = "*";
  
    std::cout << verticalFrame << std::endl;
    std::cout << horizontalFrame << std::setw(48) << "Menu" << std::setw(48) << horizontalFrame << std::endl;
    std::cout << verticalFrame << std::endl;
    std::cout << menu;
    std::cout << verticalFrame << std::endl;
    


}

bool mainController::getUserInput()
{
    std::string userInput;
    std::cout << "Enter your choice: ";
    
    std::getline(std::cin, userInput);
    return parseInput(userInput);
}

bool mainController::parseInput(std::string userInput)
{
    //Split the user input into a vector of strings
    std::vector<std::string> tokens;
    std::string token;
    std::istringstream tokenStream(userInput);
    while (std::getline(tokenStream, token, ' '))
    {
        tokens.push_back(token);
    }

    return interpretUserInput(tokens);

}

bool mainController::interpretUserInput(std::vector<std::string> tokens)
{
    if (tokens.size() == 0)
    {
        std::cout << "Invalid input" << std::endl;
    }
    else if (tokens[0] == ADD_CMD)
    {
       try
       {
        int numberOfRecords = stoi(tokens[1]);
        std::cout<< "Adding " << numberOfRecords << " records to the file" << std::endl;
        this->fileHandler.openFileForInput(filePath);
        for (int i = 0; i < numberOfRecords; i++)
        {
            Record record;
            fileHandler.writeRecordToFile(filePath, record);
        }
        this->fileHandler.closeFileForInput();

        this->fileHandler.readReinterpretWrite(filePath, "out\\test.bin");
       }
       catch(const std::exception& e)
       {
        std::cerr << e.what() << '\n';
       }

       return true;
       
    }
    else if(tokens[0] == QUIT_CMD)
    {
        std::cout << "Exiting program" << std::endl;
        return false;
    }
    else
    {
        std::cout << "Invalid input" << std::endl;
        return true;
    }
    
}
