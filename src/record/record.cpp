#include "record.h"

Record::Record()
{
    for (int i = 0; i < RECORD_SERIES_LENGTH; i++)
    {
        std::srand(time(NULL));
        for(int i = 0; i < RECORD_SERIES_LENGTH; i++)
        {
            this->series[i] = MIN_NUMBER_VALUE + std::rand() % (MAX_NUMBER_VALUE - MIN_NUMBER_VALUE + 1);
        }
    }
}

Record::~Record(int series[RECORD_SERIES_LENGTH])
{
    for (int i = 0; i < RECORD_SERIES_LENGTH; i++)
    {
        this->series[i] = series[i];
    }
}

const Record &Record::operator[](int index) const
{
    return this->series[index];
}

Record &Record::operator[](int index)
{
    return this->series[index];
}

Record &Record::operator=(const Record &record)
{
    for (int i = 0; i < RECORD_SERIES_LENGTH; i++)
    {
        this->series[i] = record.series[i];
    }
    return *this;
}

const int* getRecord()
{
    return this->series;
}

Record::operator<(const Record &record) const
{
    int maxA = 0;
    int maxB = 0;
    bool initialMaxSet = false;
    std::vector<int> bCopy(std::begin(record.getSeries()), std::end(record.getSeries()));
    for(int i=0; i<RECORD_SERIES_LENGTH; i++)
    {
        for(int j=0; j<RECORD_SERIES_LENGTH; j++)
        {
            if(this[i] == record[j])
            {
                bCopy.erase(std::remove(bCopy.begin(), bCopy.end(), num), bCopy.end());
                break;
            }
            if(this[i] > maxA || initialMaxSet == false)
            {
                initialMaxSet = true;
                maxA = this[i];
            }
        }
    }
    maxB = std::max_element(bCopy.begin(), bCopy.end());
    if(maxA < maxB)
        return true;
    return false;
}

{
    std::cout << "Record::~Record()" << std::endl;
}
