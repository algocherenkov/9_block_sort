#include <iostream>
#include "sortings.h"
#include <string>
#include <ctime>
#include <chrono>
#include <random>
#include <iterator>
#include <chrono>
#include <fstream>

constexpr int N = 1e6;
constexpr int C = 1e3;
constexpr int PARTITION = 1e3;

#define BOOST_TEST_MODULE test_main

#include <boost/test/included/unit_test.hpp>

using namespace boost::unit_test;
BOOST_AUTO_TEST_SUITE(test_suite_main)

void generateBinaryFileWithData(std::string filename)
{
    std::ofstream out(filename, std::ios::binary|std::ios::app);
    srand(static_cast<unsigned int>(time(0)));

    unsigned short number = 0;
    for(int i = 0; i < N; i++)
    {
        number = static_cast<unsigned short>(rand());
        out.write((char*)&number, sizeof(number));
    }

    out.close();
}

BOOST_AUTO_TEST_CASE(bucket_sort)
{
    std::string filename("bucket.in");
    generateBinaryFileWithData(filename);

    std::vector<unsigned short> data;
    unsigned short temp = 0;
    std::ifstream in(filename, std::ios::binary);
    unsigned short buff[PARTITION];

    if(in)
    {
        in.read((char*)buff, sizeof(PARTITION));
    }

    for(int i = 0; i < PARTITION; i++)
    {
        in.read((char*)&temp, sizeof(temp));
        data.push_back(temp);
    }

    in.close();
    sortings::bucketSort(data, N/C);

    std::string filenameOut("bucket.out");
    std::ofstream out(filename, std::ios::binary|std::ios::app);
    srand(static_cast<unsigned int>(time(0)));

    unsigned short number = 0;
    for(int i = 0; i < N; i++)
    {
        number = static_cast<unsigned short>(rand());
        out.write((char*)&number, sizeof(number));
    }

    out.close();
    
    for(int i = 1; i < N; i++)
        BOOST_CHECK_MESSAGE(data[i] > data[i - 1], "data weren't sorted");
}

BOOST_AUTO_TEST_SUITE_END()
