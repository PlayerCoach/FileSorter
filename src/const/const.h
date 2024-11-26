#pragma once
#include <string>
const int  MAX_RECORD_COUNT = 15;
const int MAX_NUMBER_VALUE = 20;
const int MIN_NUMBER_VALUE =  -20;
const int AVAILABLE_BUFFERS = 10;
const int APPROX_NUMBER_OF_RECORDS_IN_PAGE = 10;
const int PAGE_SIZE = 9 * sizeof(int32_t) * APPROX_NUMBER_OF_RECORDS_IN_PAGE; // ~8.5 numbers * 10 records * 4 bytes

