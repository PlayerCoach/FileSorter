#include "mainController.h"

mainController::mainController() 
{ 
    this->filePath  = INPUT;
    printMenu();
    bool running = true;
    while(running)
    {
        running = getUserInput();

    }
    //experiment();// --> run expirement

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
        return true;
    }
    else if (tokens[0] == ADD_CMD)
    {
      
        tokens.erase(tokens.begin());
        addRecords(tokens);
        return true;
       
    }

    else if (tokens[0] == SORT_CMD)
    {
        tokens.erase(tokens.begin());
        parseSortCommand(tokens);
        return true;
    }
    else if(tokens[0] == QUIT_CMD)
    {
        tokens.erase(tokens.begin());
        if(!tokens.empty())
        {
            std::cout << "Invalid input" << std::endl;
            return true;
        }
        std::cout << "Exiting program" << std::endl;
        return false;
    }
    else if(tokens[0] == CLEAR_FILE_CMD)
    {
        clearInputFile();
        return true;
    }
    else if(tokens[0] == INPUT_FILE_CMD)
    {
        tokens.erase(tokens.begin());
        if(checkIfTokensAreEmpty(tokens))
        {
            std::cout << "Invalid input" << std::endl;
            return true;
        }
        this->fileHandler.convertTxtToInputBin(tokens[0]);
        return true;
    }
    else if(tokens[0] == HELP_CMD)
    {
        tokens.erase(tokens.begin());
        if(!tokens.empty())
        {
            std::cout << "Invalid input" << std::endl;
            return true;
        }
        printMenu();
        return true;
    }
    else if(tokens[0] == SHOW_CMD)
    {
        tokens.erase(tokens.begin());
        showFile(tokens);
        return true;
    }
    else
    {
        std::cout << "Invalid input" << std::endl;
        return true;
    }
    
}

void mainController::addRecords(std::vector<std::string>& tokens)
{
    
    if(checkIfTokensAreEmpty(tokens))
        return;

    int numberOfRecords;
   
    try
    {
        numberOfRecords = stoi(tokens[0]);
    }
    catch(const std::exception& e)
    {
        std::cout << "Invalid input" << std::endl;
        return;
    }
   
   tokens.erase(tokens.begin());

   if(checkIfTokensAreEmpty(tokens))
       return;

    if(tokens[0] == RANDOM_FLAG)
    {
        addRandomRecords(numberOfRecords);
        tokens.erase(tokens.begin());
    }
    else if(tokens[0] == SPECIFIED_FLAG)
    {
        addSpecifiedRecords(numberOfRecords);
        tokens.erase(tokens.begin());
    }
    else
    {
        std::cout << "Invalid input" << std::endl;
        return;
    }

    if(tokens.size() > 0 && tokens[0] == EXPLICIT_FLAG)
    {
        readInputFile();

    }
    else if(tokens.size() > 0)
    {
        std::cout << "Invalid input" << std::endl;
        return;
    }
   
}

bool mainController::checkIfTokensAreEmpty(std::vector<std::string>& tokens)
{
    if(tokens.empty())
    {
        std::cout << "Invalid input" << std::endl;
        return true;
    }
    return false;
}

void mainController::addRandomRecords(int numberOfRecords)
{
    this->fileHandler.openFileForOutput(filePath, "append");
    for (int i = 0; i < numberOfRecords; i++)
    {
        Record record;
        this->fileHandler.writeRecordToFile(filePath, record);
    }
    this->fileHandler.closeFileForOutput(filePath);
}

void mainController::addSpecifiedRecords(int numberOfRecords)
{
    this->fileHandler.openFileForOutput(filePath, "append");
    for (int i = 0; i < numberOfRecords; i++)
    {
        std::vector<int32_t> series;
        std::string userInput;
        std::getline(std::cin, userInput);

        std::string numberString;
        std::istringstream numberStream(userInput);
        int32_t number;

        while (std::getline(numberStream, numberString, ' '))
        {
            try
            {
                number = stoi(numberString);
                series.push_back(number);
            }
            catch(const std::exception& e)
            {
                std::cerr << e.what() << '\n';
                return;
            }
        }

        if(series.size() > MAX_RECORD_COUNT)
        {
            std::cout << "Invalid input, record too long" << std::endl;
            return;
        }

        Record record(series);
        this->fileHandler.writeRecordToFile(filePath, record);

    }
    this->fileHandler.closeFileForOutput(filePath);
}

void mainController::readInputFile()
{
    this->fileHandler.openFileForInput(filePath);
    std::optional<Record> record;
    while ((record = this->fileHandler.readRecordFromFile(filePath)) != std::nullopt)
    {
        std::cout << record.value() << std::endl;
    }
    this->fileHandler.finalizeFileForInput(filePath);
}

int mainController::sortFile()
{

    this->fileHandler.deleteAllBinFilesExceptInput(); 
    Sorter sorter;
    std::unique_ptr<SortingStrategy> largeBufferSort = std::make_unique<LargeBufferSort>(&fileHandler, filePath);
    sorter.setStrategy(std::move(largeBufferSort));
    sorter.sort();
    return sorter.getPhaseCounter();
}

void mainController::parseSortCommand(std::vector<std::string>& tokens)
{
    if(checkIfTokensAreEmpty(tokens))
        return;

    if(tokens[0] == HIDDEN_FLAG)
    {
        tokens.erase(tokens.begin());
        if(tokens.size() >= 1)
        {
            if(tokens[0] == FULL_FLAG)
            int phases = sortFile();
            return;
        }
        int phases = sortFile();
        this->fileHandler.displayFile(MAIN_OUTPUT);
        return;
    }
    else if(tokens[0] == EXPLICIT_FLAG)
    {
        int phases = sortFile();
        tokens.erase(tokens.begin());
        if(!tokens.empty())
        {
            try
            {
                int numberOfRecordsToRead = stoi(tokens[0]);
                tokens.erase(tokens.begin());
                if (!tokens.empty())
                {
                    std::cout << "Invalid input" << std::endl;
                    return;
                }
                
                
                for (int i = 1; i < phases; i++)
                {
                    std::cout << "***********PHASE NUMER "<< i << " *************" << std::endl;
                    this->fileHandler.displayNFirstRecords(PHASE_FILE_PATH + std::to_string(i) + ".bin", numberOfRecordsToRead);
                    
                }
                std::cout << "**********MAIN OUTPUT***************" << std::endl;
                this->fileHandler.displayNFirstRecords(MAIN_OUTPUT, numberOfRecordsToRead);

            }
            catch(const std::exception& e)
            {
                std::cerr << e.what() << '\n';
            }
            return;
        }
        for (int i = 1; i < phases; i++)
        {
            std::cout << "************PHASE NUMBER "<<i<<" ************" << std::endl;
            this->fileHandler.displayFile(PHASE_FILE_PATH + std::to_string(i) + ".bin");
        }
        std::cout << "*************MAIN OUTPUT**************" << std::endl;
        this->fileHandler.displayFile(MAIN_OUTPUT);
    }
    else
    {
        std::cout << "Invalid input" << std::endl;
        return;
    }
        
}

void mainController::showFile(std::vector<std::string>& tokens)
{
    if(checkIfTokensAreEmpty(tokens))
        return;

    if(tokens[0] == INPUT_FLAG)
    {
        this->fileHandler.displayFile(INPUT);
    }
    else if(tokens[0] == OUTPUT_FLAG)
    {
        this->fileHandler.displayFile(MAIN_OUTPUT);
    }
    else if(tokens[0] == PHASE_FLAG)
    {
        tokens.erase(tokens.begin());
        if(checkIfTokensAreEmpty(tokens))
            return;
        int phase;
        try
        {
            phase = stoi(tokens[0]);
        }
        catch(const std::exception& e)
        {
            std::cout << "Invalid input" << std::endl;
            return;
        }
        this->fileHandler.displayFile(PHASE_FILE_PATH + std::to_string(phase) + ".bin");
    }
    else
    {
        std::cout << "Invalid input" << std::endl;
        return;
    }
}

void mainController::clearInputFile()
{
    this->fileHandler.clearFile(INPUT);
}

void mainController::experiment()
{
   std::cout<<"Experiment"<<std::endl;

   for(int i = 10; i<=1000000000; i*=10)
   {
       std::cout<<"Number of records: "<<i<<std::endl;
       addRandomRecords(i);
       int phases = sortFile();
       clearInputFile();
       std::cout<<"***************************************"<<std::endl;
   }

}