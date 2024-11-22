#include "sortingStrategy.h"
#include "fileHandler.h"
#include "outputFileNames.h"


class NaturalMergeSort : public SortingStrategy {
public:
    NaturalMergeSort(fileHandler* handler, std::string inputFile)
        : SortingStrategy(handler, inputFile) {}
        
    void sort() override;
    void initNaturalMergeSort();
    
    void divide();
    void merge();
};
