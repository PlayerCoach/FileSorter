#include "sortingStrategy.h"
#include "fileHandler.h"
#include "outputFileNames.h"

class NaturalMergeSort : public SortingStrategy {
public:
    void sort() override;
    void initNaturalMergeSort();
    
    void divide();
    void merge();
};
