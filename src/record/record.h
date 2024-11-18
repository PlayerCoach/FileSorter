#pragma once
#include <iostream>
#include "const.h"
#include <cstdlib>
#include <time.h>
#include <set>
#include <algorithm>
#include <iterator>
#include <vector>
#include <climits>
#include <random>
class Record
{
private:
    //attributes
    std::set<int> series;
    
    //methods 
    int getMaxUnique(const Record &other) const;

public:
    Record();
    Record(std::vector<int> series);
    const std::set<int>& getSeries() const;
    Record& operator = (const Record &record);
    bool operator<(const Record &record) const;
    bool operator>(const Record &record) const;
    bool operator==(const Record &record) const;
    bool operator!=(const Record &record) const;
    bool operator<=(const Record &record) const;
    bool operator>=(const Record &record) const;
    friend std::ostream &operator << (std::ostream &os, const Record &record);
    friend std::istream &operator >> (std::istream &is, Record &record);
    void insert(int value);
    void remove(int value);
    ~Record();
};
