#include "record.h"

//private

std::optional<int32_t> Record::getMaxUnique(const Record &other) const
{
    std::optional<int32_t> maxUnique;
    for (int num : this->series)
    {
        if (other.getSeries().find(num) == other.getSeries().end())
        {
            if (!maxUnique.has_value() ||  num > maxUnique.value())
            {
                maxUnique = num;
            }
        }
    }

    return maxUnique;
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
    std::optional<int> maxA = this->getMaxUnique(record);
    std::optional<int> maxB = record.getMaxUnique(*this);

    if (!maxA.has_value() && maxB.has_value())
        return true; // No unique max is less than a valid max

    if (maxA.has_value() && !maxB.has_value())
        return false; // Valid max is greater than no unique max

    if (!maxA.has_value() && !maxB.has_value())
        return false; // Both have no unique max, considered equal

    return maxA.value() < maxB.value(); // Compare actual values
}

bool Record::operator>(const Record &record) const
{
    std::optional<int> maxA = this->getMaxUnique(record);
    std::optional<int> maxB = record.getMaxUnique(*this);

    if (!maxA.has_value() && maxB.has_value())
        return false; // No unique max is less than a valid max

    if (maxA.has_value() && !maxB.has_value())
        return true; // Valid max is greater than no unique max

    if (!maxA.has_value() && !maxB.has_value())
        return false; // Both have no unique max, considered equal

    return maxA.value() > maxB.value(); // Compare actual values
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
