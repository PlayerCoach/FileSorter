#include <iostream>
#include "const.h"
#include <cstdlib>
#include <time.h>
#include <set>
#include <climits>
#include <random>
class Record
{
private:
    //attributes
    int series[RECORD_SERIES_LENGTH];
    
    //methods
    int getMaxUnique(const Record &other) const;
    const int* getSeries() const;

public:
    Record();
    Record(int series[RECORD_SERIES_LENGTH]);
    const int& operator[](int index) const;
    int& operator[](int index);
    Record& operator = (const Record &record);
    bool operator<(const Record &record) const;
    bool operator>(const Record &record) const;
    bool operator==(const Record &record) const;
    bool operator!=(const Record &record) const;
    bool operator<=(const Record &record) const;
    bool operator>=(const Record &record) const;
    friend std::ostream &operator << (std::ostream &os, const Record &record);
    friend std::istream &operator >> (std::istream &is, Record &record);
    ~Record();
};
