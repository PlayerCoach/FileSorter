#include "record.h"

//private

int Record::getMaxUnique(const Record &other) const
{
    int maxUnique = 0;
    bool isSetMax = false;
    for (int num : this->series)
    {
        if (other.getSeries().find(num) == other.getSeries().end())
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


//public 

Record::Record()
{
  
    std::random_device rd;                     
    std::mt19937 gen(rd());           
    std::uniform_int_distribution<int> distOne(1, MAX_RECORD_COUNT); 
    int count = distOne(gen);         
    std::uniform_int_distribution<int> dist(MIN_NUMBER_VALUE, MAX_NUMBER_VALUE); 

    for(int i = 0; i < count; i++)
    {
        this->series.insert(dist(gen));
    }
    
}

Record::Record(std::vector<int> series)
{
    for (int element : series) {
        if (this->series.size() >= MAX_RECORD_COUNT) {
            break; 
        }
        this->series.insert(element);
    }
    
}

const std::set<int>& Record::getSeries() const
{
    return this->series;
}

Record& Record::operator=(const Record &record)
{
    this->series = record.series;
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
    return this->series == record.series;
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
    for (int num : record.series)
    {
        os << num << " ";
    }
    return os;
}

std::istream &operator>>(std::istream &is, Record &record)
{
    std::set<int> series;
    int num;
    while (is >> num)
    {
        series.insert(num);
    }
    return is;
}

Record::~Record(){}
