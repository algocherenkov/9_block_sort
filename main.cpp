#include <iostream>
#include "sortings.h"
#include <string>
#include <ctime>
#include <chrono>
#include <random>
#include <iterator>
#include <chrono>
#include <fstream>

constexpr int N_million = 1e6;
constexpr int N_10_million = 1e7;
constexpr int N_100_million = 1e8;
constexpr int N_billion = 1e9;

constexpr int k_thousand = 1e3;
constexpr int k_10_thousands = 1e4;
constexpr int k_100_thousands = 1e5;
constexpr int k_million = 1e6;

#define BOOST_TEST_MODULE test_main

#include <boost/test/included/unit_test.hpp>

using namespace boost::unit_test;
BOOST_AUTO_TEST_SUITE(test_suite_main)

int generateBinaryFileWithData(std::string filename, int N)
{
    std::ofstream out(filename, std::ios::binary);
    srand(static_cast<unsigned int>(time(0)));

    unsigned short number = 0;
    int max = 0;
    for(int i = 0; i < N; i++)
    {
        number = rand() % UINT16_MAX;
        if (number > max)
            max = number;
        out.write((char*)&number, sizeof(unsigned short));
    }
   
    out.close();
    return max;
}

//BOOST_AUTO_TEST_CASE(bucket_sort_million_test)
//{
//    std::string filename("bucket_1million_");
//    auto maxElement = generateBinaryFileWithData(filename, N_million);
//
//    sortings::bucketSort(filename, 100, maxElement);
//    
//    BOOST_TEST_MESSAGE("bucket_sort_million_test has been ended. Look for quality of sorting manually");
//}

//BOOST_AUTO_TEST_CASE(bucket_sort_10million_test)
//{
//    std::string filename("bucket_10million_");
//    auto maxElement = generateBinaryFileWithData(filename, N_10_million);
//
//    sortings::bucketSort(filename, 100, maxElement);
//
//    BOOST_TEST_MESSAGE("bucket_sort_10million_test has been ended. Look for quality of sorting manually");
//}

//BOOST_AUTO_TEST_CASE(bucket_sort_100million_test)
//{
//    std::string filename("bucket_100million_");
//    auto maxElement = generateBinaryFileWithData(filename, N_100_million);
//
//    sortings::bucketSort(filename, 100, maxElement);
//
//    BOOST_TEST_MESSAGE("bucket_sort_100million_test has been ended. Look for quality of sorting manually");
//}

//takes a very long time. Uncomment, run and makesure that you have free hour
//BOOST_AUTO_TEST_CASE(bucket_sort_billion_test)
//{
//    std::string filename("bucket_billion_");
//    auto maxElement = generateBinaryFileWithData(filename, N_billion);
//
//    sortings::bucketSort(filename, 100, maxElement);
//
//    BOOST_TEST_MESSAGE("bucket_sort_billion_test has been ended. Look for quality of sorting manually");
//}

//BOOST_AUTO_TEST_CASE(count_sort_million_test)
//{
//    std::string filename("count_million_");
//    auto maxElement = generateBinaryFileWithData(filename, N_million);
//
//    sortings::countSort(filename);
//
//    BOOST_TEST_MESSAGE("count_sort_million_test has been ended. Look for quality of sorting manually");
//}

//BOOST_AUTO_TEST_CASE(count_sort_10_million_test)
//{
//    std::string filename("count_10_million_");
//    auto maxElement = generateBinaryFileWithData(filename, N_10_million);
//
//    sortings::countSort(filename);
//
//    BOOST_TEST_MESSAGE("count_sort_10_million_test has been ended. Look for quality of sorting manually");
//}

//BOOST_AUTO_TEST_CASE(count_sort_100_million_test)
//{
//    std::string filename("count_100_million_");
//    auto maxElement = generateBinaryFileWithData(filename, N_100_million);
//
//    sortings::countSort(filename);
//
//    BOOST_TEST_MESSAGE("count_sort_100_million_test has been ended. Look for quality of sorting manually");
//}

//BOOST_AUTO_TEST_CASE(count_sort_billion_test)
//{
//    std::string filename("count_billion_");
//    auto maxElement = generateBinaryFileWithData(filename, N_billion);
//
//    sortings::countSort(filename);
//
//    BOOST_TEST_MESSAGE("count_sort_billion_test has been ended. Look for quality of sorting manually");
//}

//this one works for appropriate time. Rest tests - only if you have free half of day
BOOST_AUTO_TEST_CASE(radix_sort_10_thousands_test)
{
    std::string filename("radix_million_");
    auto maxElement = generateBinaryFileWithData(filename, N_million);

    sortings::radixSort(filename, maxElement);

    BOOST_TEST_MESSAGE("radix_sort_million_test has been ended. Look for quality of sorting manually");
}


//BOOST_AUTO_TEST_CASE(radix_sort_million_test)
//{
//    std::string filename("radix_million_");
//    auto maxElement = generateBinaryFileWithData(filename, N_million);
//
//    sortings::radixSort(filename, maxElement);
//
//    BOOST_TEST_MESSAGE("radix_sort_million_test has been ended. Look for quality of sorting manually");
//}

//BOOST_AUTO_TEST_CASE(radix_sort_10_million_test)
//{
//    std::string filename("radix_10_million_");
//    auto maxElement = generateBinaryFileWithData(filename, N_10_million);
//
//    sortings::radixSort(filename, maxElement);
//
//    BOOST_TEST_MESSAGE("radix_sort_10_million_test has been ended. Look for quality of sorting manually");
//}
//
//BOOST_AUTO_TEST_CASE(radix_sort_100_million_test)
//{
//    std::string filename("radix_100_million_");
//    auto maxElement = generateBinaryFileWithData(filename, N_100_million);
//
//    sortings::radixSort(filename, maxElement);
//
//    BOOST_TEST_MESSAGE("radix_sort_100_million_test has been ended. Look for quality of sorting manually");
//}
//
//BOOST_AUTO_TEST_CASE(radix_sort_billion_test)
//{
//    std::string filename("radix_billion_");
//    auto maxElement = generateBinaryFileWithData(filename, N_billion);
//
//    sortings::radixSort(filename, maxElement);
//
//    BOOST_TEST_MESSAGE("radix_sort_billion_test has been ended. Look for quality of sorting manually");
//}
BOOST_AUTO_TEST_SUITE_END()
