#include "record.h"

//private

int Record::getMaxUnique(const Record &other) const
{
    std::set<int> uniqueInThis(this->getSeries(), this->getSeries() + RECORD_SERIES_LENGTH);
    std::set<int> uniqueInOther(other.getSeries(), other.getSeries() + RECORD_SERIES_LENGTH);

    int maxUnique = 0;
    bool isSetMax = false;

    for (int num : uniqueInThis)
    {
        if (uniqueInOther.find(num) == uniqueInOther.end())
        {
            if (!isSetMax || num > maxUnique)
            {
                maxUnique = num;
                isSetMax = true;
            }
        }
    }

    return isSetMax ? maxUnique : INT_MIN; 
}

const int* Record::getSeries() const
{
    return this->series;
}

//public 

Record::Record()
{
  
    std::random_device rd;                     
    std::mt19937 gen(rd());                     
    std::uniform_int_distribution<int> dist(MIN_NUMBER_VALUE, MAX_NUMBER_VALUE); 

    for(int i = 0; i < RECORD_SERIES_LENGTH; i++)
    {
        this->series[i] = dist(gen);
    }
    
}

Record::Record(int series[RECORD_SERIES_LENGTH])
{
    for (int i = 0; i < RECORD_SERIES_LENGTH; i++)
    {
        this->series[i] = series[i];
    }
}



const int& Record::operator[](int index) const
{
    return this->series[index];
}

int& Record::operator[](int index)
{
    return this->series[index];
}

Record& Record::operator=(const Record &record)
{
    for (int i = 0; i < RECORD_SERIES_LENGTH; i++)
    {
        this->series[i] = record.series[i];
    }
    return *this;
}

bool Record::operator<(const Record &record) const
{
    int maxA = this->getMaxUnique(record);
    int maxB = record.getMaxUnique(*this);

    if (maxA == INT_MIN && maxB != INT_MIN)
        return true;
    if (maxB == INT_MIN)
        return false;

    return maxA < maxB;


}

bool Record::operator>(const Record &record) const
{
    int maxA = this->getMaxUnique(record);
    int maxB = record.getMaxUnique(*this);

    if (maxB == INT_MIN && maxA != INT_MIN)
        return true;
    if (maxA == INT_MIN)
        return false;

    return maxA > maxB;
}

bool Record::operator==(const Record &record) const
{
    for (int i = 0; i < RECORD_SERIES_LENGTH; i++)
    {
        if (this->series[i] != record.series[i])
            return false;
    }
    return true;
}

bool Record::operator!=(const Record &record) const
{
    return !(*this == record);
}

bool Record::operator<=(const Record &record) const
{
    return *this < record || *this == record;
}

bool Record::operator>=(const Record &record) const
{
    return *this > record || *this == record;
}

std::ostream &operator<<(std::ostream &os, const Record &record)
{
    for (int i = 0; i < RECORD_SERIES_LENGTH; i++)
    {
        os << record.series[i] << " ";
    }
    return os;
}

std::istream &operator>>(std::istream &is, Record &record)
{
    for (int i = 0; i < RECORD_SERIES_LENGTH; i++)
    {
        is >> record.series[i];
    }
    return is;
}

Record::~Record(){}
