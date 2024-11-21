#include "fileHandler.h"
#include "sortingStrategy.h"
#include <memory>
class Sorter {
private:
    std::unique_ptr<SortingStrategy> strategy;

public:
    void setStrategy(std::unique_ptr<SortingStrategy> newStrategy) ;
    void sort();
};