#pragma once
#include <string>
const int  MAX_RECORD_COUNT = 15;
const int MAX_NUMBER_VALUE = 20;
const int MIN_NUMBER_VALUE =  0;
const int APPROX_NUMBER_OF_RECORDS_IN_BLOCK = 4;
const int BLOCK_SIZE = 15 * sizeof(int32_t) * APPROX_NUMBER_OF_RECORDS_IN_BLOCK; // 15 numbers * 4 records * 4 bytes
const int BUFFER_SIZE = 15 * sizeof(int32_t) * APPROX_NUMBER_OF_RECORDS_IN_BLOCK; // 15 ints * 4 records
const std::string OUTPUT_FOLDER = "out";
