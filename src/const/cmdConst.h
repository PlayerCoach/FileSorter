#include <string>

const std::string ADD_CMD = "add";
    const std::string RANDOM_FLAG = "-r";
    const std::string SPECIFIED_FLAG = "-s";
const std::string CLEAR_FILE_CMD = "cf";
const std::string PRINT_FILE_CMD = "pf";
const std::string SORT_CMD = "sort";
    const std::string HIDDEN_FLAG = "-h";
    const std::string EXPLICIT_FLAG = "-e";
const std::string QUIT_CMD = "q";
const std::string HELP_CMD = "help";

  const::std::string menu = "* " + ADD_CMD +" [n] [" + RANDOM_FLAG + "/" + SPECIFIED_FLAG + "] [" + EXPLICIT_FLAG + "] | Add n random/specified records to file, -e shows them *\n" 
    "* " + CLEAR_FILE_CMD + " | Clears input file *\n" 
    "* " + PRINT_FILE_CMD + " | Prints content of input file * \n" 
    "* " + SORT_CMD + " [ " + EXPLICIT_FLAG + "/" + HIDDEN_FLAG + "] | Sorts file [" + HIDDEN_FLAG + "] prints only final result [" + EXPLICIT_FLAG+ "] shows file after every phase * \n" 
    "* " + QUIT_CMD + " | Quits the program * \n"
    "* " + HELP_CMD + " | Prints this menu * \n";