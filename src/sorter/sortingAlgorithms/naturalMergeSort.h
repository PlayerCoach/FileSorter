#include "sortingStrategy.h"
#include "fileHandler.h"
#include "outputFileNames.h"
#include "bufferrType.h"


class NaturalMergeSort : public SortingStrategy {
public:
    void sort() override;
    void initNaturalMergeSort();
    
    void divide();
    void merge();
    void interpretBlock(bufferT block, bufferT temp1Buffer, bufferT temp2Buffer);
};
