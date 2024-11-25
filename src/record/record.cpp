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

void Record::sortDescending()
{
    std::vector<int> sortedSeries(this->series.begin(), this->series.end());
    std::sort(sortedSeries.begin(), sortedSeries.end(), std::less<int>());
    this->series.clear();
    for (int num : sortedSeries)
    {
        this->series.insert(num);
    }
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

       // If both are invalid (INT_MIN), they are considered equal
    if (maxA == INT_MIN && maxB == INT_MIN)
        return false;

    // INT_MIN is considered smaller than any valid value
    if (maxA == INT_MIN)
        return true;
    if (maxB == INT_MIN)
        return false;

    return maxA < maxB;


}

bool Record::operator>(const Record &record) const
{
    int maxA = this->getMaxUnique(record);
    int maxB = record.getMaxUnique(*this);

        if (maxA == INT_MIN && maxB == INT_MIN)
        return false;

    // INT_MIN is considered smaller than any valid value
    if (maxB == INT_MIN)
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
    for (auto it = record.series.rbegin(); it != record.series.rend(); it++)
    {
        os << *it << " ";
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
    record.series.clear();
    record.series = series;
    return is;
}

void Record::insert(int value)
{
    this->series.insert(value);
}

void Record::remove(int value)
{
    this->series.erase(value);
}

const int32_t Record::getSize() const
{
    return static_cast<int32_t>(this->series.size());
}

const int32_t Record::getSizeInBytes() const
{
    return static_cast<int32_t>(this->series.size() * sizeof(int32_t) + sizeof(int32_t));
}

Record::~Record(){}
