#include <iostream>
#include "const.h"
#include <cstdlib>
#include <time.h>
#include <vector>
class Record
{
private:
    int series[RECORD_SERIES_LENGTH];
public:
    Record();
    Record(int series[RECORD_SERIES_LENGTH]);
    const Record& operator [] (int index) const;
    Record& operator [] (int index);
    const int* getSeries() const;
    Record& operator = (const Record &record);
    bool operator < (const Record &record) const;
    bool operator > (const Record &record) const;
    bool operator == (const Record &record) const;
    bool operator != (const Record &record) const;
    bool operator <= (const Record &record) const;
    bool operator >= (const Record &record) const;
    friend std::ostream &operator << (std::ostream &os, const Record &record);
    friend std::istream &operator >> (std::istream &is, Record &record);
    ~Record();
};
