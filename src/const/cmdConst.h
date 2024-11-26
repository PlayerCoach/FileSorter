#include <string>

const std::string ADD_CMD = "add";
    const std::string RANDOM_FLAG = "-r";
    const std::string SPECIFIED_FLAG = "-s";
const std::string CLEAR_FILE_CMD = "clear";
const std::string SORT_CMD = "sort";
    const std::string HIDDEN_FLAG = "-h";
        const std::string FULL_FLAG = "-f";
    const std::string EXPLICIT_FLAG = "-e";
const std::string QUIT_CMD = "q";
const std::string HELP_CMD = "help";
const std::string SHOW_CMD = "show";
    const std::string PHASE_FLAG = "phase";
    const std::string OUTPUT_FLAG = "output";
    const std::string INPUT_FLAG = "input";
const std::string INPUT_FILE_CMD = "input";


  const::std::string menu = "* " + ADD_CMD +" [n] [" + RANDOM_FLAG + "/" + SPECIFIED_FLAG + "] [" + EXPLICIT_FLAG + "] | Add n random/specified records to file, -e shows them *\n" 
    "* " + CLEAR_FILE_CMD + " | Clears input file *\n" 
    "* " + SORT_CMD + " [ " + EXPLICIT_FLAG + "/" + HIDDEN_FLAG + "] | Sorts file [" + HIDDEN_FLAG + "{"+ FULL_FLAG + "} optional, hides everything ] prints only final result [" + EXPLICIT_FLAG+ "] + {N}(optional - show N first records from every phase) shows file after every phase * \n" 
    "* " + QUIT_CMD + " | Quits the program * \n"
    "* " + HELP_CMD + " | Prints this menu * \n"
    "* " + SHOW_CMD + " [input] - Shows the input file | + [phase{n}] - shows phase n if it existed and is not output | [output] shows output  * \n"
    "* " + INPUT_FILE_CMD + " [filename] | Sets the input file * \n";