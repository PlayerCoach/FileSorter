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
    bool isSetMaxA = false;
    bool isSetMaxB = false;
    int maxA = 0;
    int maxB = 0;
    std::set<int> uniqueInA(this->getSeries(), this->getSeries() + RECORD_SERIES_LENGTH);
    std::set<int> uniqueInB(record.getSeries(), record.getSeries() + RECORD_SERIES_LENGTH);

    for(int num: uniqueInA)
    {
        if(uniqueInB.find(num) == uniqueInB.end())
        {
            if(!isSetMaxA || maxA < num)
            {
                maxA = num;
                isSetMaxA = true;
            }
        }
    }

    for(int num:uniqueInB)
    {
        if(uniqueInA.find(num) == uniqueInA.end())
        {
            if(!isSetMaxB || maxB < num)
            {
                maxB = num;
                isSetMaxB = true;
            }
        }
    }
    if (!isSetMaxA || !isSetMaxB)
        return false;

    return maxA < maxB;


}

{
    std::cout << "Record::~Record()" << std::endl;
}
