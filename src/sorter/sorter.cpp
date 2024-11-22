#include "sorter.h"


void Sorter::setStrategy(std::unique_ptr<SortingStrategy> newStrategy) {
    strategy = std::move(newStrategy);
}

void Sorter::sort() {
    if (strategy) {
        strategy->sort();  // Delegate to the strategy
    } else {
        throw std::runtime_error("No sorting strategy set!");
    }
}

