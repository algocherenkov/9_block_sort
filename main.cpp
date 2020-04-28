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

constexpr int k_hundred = 100;
constexpr int k_thousand = 1e3;
constexpr int k_10_thousands = 1e4;
constexpr int k_100_thousands = 1e5;
constexpr int k_million = 1e6;

constexpr const char* SUMMARY= "results";

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
//    auto start = std::chrono::high_resolution_clock::now();
//
//    // unsync the I/O of C and C++.
//    std::ios_base::sync_with_stdio(false);
//
//    sortings::bucketSort(filename, k_hundred, maxElement);
//
//    auto end = std::chrono::high_resolution_clock::now();
//
//    // Calculating total time taken by the BM algorithm.
//    double time_taken =
//        std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
//
//    time_taken *= 1e-9;
//    std::ios_base::sync_with_stdio(true);
//
//    std::fstream resultFile(SUMMARY, std::ios::out | std::ios::app);
//    resultFile << "bucket_sort_million_test" << "--------------------------" << std::fixed << time_taken << std::setprecision(9) << " sec" << std::endl;
//    resultFile.close();
//
//    BOOST_TEST_MESSAGE("bucket_sort_million_test has been ended. Look for quality of sorting manually");
//}
//
//BOOST_AUTO_TEST_CASE(bucket_sort_10million_test)
//{
//    std::string filename("bucket_10million_");
//    auto maxElement = generateBinaryFileWithData(filename, N_10_million);
//
//    auto start = std::chrono::high_resolution_clock::now();
//
//    // unsync the I/O of C and C++.
//    std::ios_base::sync_with_stdio(false);
//
//    sortings::bucketSort(filename, k_hundred, maxElement);
//
//    auto end = std::chrono::high_resolution_clock::now();
//
//    // Calculating total time taken by the BM algorithm.
//    double time_taken =
//        std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
//
//    time_taken *= 1e-9;
//    std::ios_base::sync_with_stdio(true);
//
//    std::fstream resultFile(SUMMARY, std::ios::out | std::ios::app);
//    resultFile << "bucket_sort_10million_test" << "--------------------------" << std::fixed << time_taken << std::setprecision(9) << " sec" << std::endl;
//    resultFile.close();
//
//    BOOST_TEST_MESSAGE("bucket_sort_10million_test has been ended. Look for quality of sorting manually");
//}
//
//BOOST_AUTO_TEST_CASE(bucket_sort_100million_test)
//{
//    std::string filename("bucket_100million_");
//    auto maxElement = generateBinaryFileWithData(filename, N_100_million);
//
//    auto start = std::chrono::high_resolution_clock::now();
//
//    // unsync the I/O of C and C++.
//    std::ios_base::sync_with_stdio(false);
//
//    sortings::bucketSort(filename, k_thousand, maxElement);
//
//    auto end = std::chrono::high_resolution_clock::now();
//
//    // Calculating total time taken by the BM algorithm.
//    double time_taken =
//        std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
//
//    time_taken *= 1e-9;
//    std::ios_base::sync_with_stdio(true);
//
//    std::fstream resultFile(SUMMARY, std::ios::out | std::ios::app);
//    resultFile << "bucket_sort_100million_test" << "--------------------------" << std::fixed << time_taken << std::setprecision(9) << " sec" << std::endl;
//    resultFile.close();
//
//    BOOST_TEST_MESSAGE("bucket_sort_100million_test has been ended. Look for quality of sorting manually");
//}
//
////takes a very long time. Uncomment, run and makesure that you have free hour
//BOOST_AUTO_TEST_CASE(bucket_sort_billion_test)
//{
//    std::string filename("bucket_billion_");
//    auto maxElement = generateBinaryFileWithData(filename, N_billion);
//
//    auto start = std::chrono::high_resolution_clock::now();
//
//    // unsync the I/O of C and C++.
//    std::ios_base::sync_with_stdio(false);
//
//    sortings::bucketSort(filename, k_thousand, maxElement);
//
//    auto end = std::chrono::high_resolution_clock::now();
//
//    // Calculating total time taken by the BM algorithm.
//    double time_taken =
//        std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
//
//    time_taken *= 1e-9;
//    std::ios_base::sync_with_stdio(true);
//
//    std::fstream resultFile(SUMMARY, std::ios::out | std::ios::app);
//    resultFile << "bucket_sort_billion_test" << "--------------------------" << std::fixed << time_taken << std::setprecision(9) << " sec" << std::endl;
//    resultFile.close();
//
//    BOOST_TEST_MESSAGE("bucket_sort_billion_test has been ended. Look for quality of sorting manually");
//}
//
//BOOST_AUTO_TEST_CASE(count_sort_million_test)
//{
//    std::string filename("count_million_");
//    auto maxElement = generateBinaryFileWithData(filename, N_million);
//
//    auto start = std::chrono::high_resolution_clock::now();
//
//    // unsync the I/O of C and C++.
//    std::ios_base::sync_with_stdio(false);
//
//    sortings::countSort(filename);
//
//    auto end = std::chrono::high_resolution_clock::now();
//
//    // Calculating total time taken by the BM algorithm.
//    double time_taken =
//        std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
//
//    time_taken *= 1e-9;
//    std::ios_base::sync_with_stdio(true);
//
//    std::fstream resultFile(SUMMARY, std::ios::out | std::ios::app);
//    resultFile << "count_sort_million_test" << "--------------------------" << std::fixed << time_taken << std::setprecision(9) << " sec" << std::endl;
//    resultFile.close();
//
//    BOOST_TEST_MESSAGE("count_sort_million_test has been ended. Look for quality of sorting manually");
//}
//
//BOOST_AUTO_TEST_CASE(count_sort_10_million_test)
//{
//    std::string filename("count_10_million_");
//    auto maxElement = generateBinaryFileWithData(filename, N_10_million);
//
//    auto start = std::chrono::high_resolution_clock::now();
//
//    // unsync the I/O of C and C++.
//    std::ios_base::sync_with_stdio(false);
//
//    sortings::countSort(filename);
//
//    auto end = std::chrono::high_resolution_clock::now();
//
//    // Calculating total time taken by the BM algorithm.
//    double time_taken =
//        std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
//
//    time_taken *= 1e-9;
//    std::ios_base::sync_with_stdio(true);
//
//    std::fstream resultFile(SUMMARY, std::ios::out | std::ios::app);
//    resultFile << "count_sort_10_million_test" << "--------------------------" << std::fixed << time_taken << std::setprecision(9) << " sec" << std::endl;
//    resultFile.close();
//
//    BOOST_TEST_MESSAGE("count_sort_10_million_test has been ended. Look for quality of sorting manually");
//}
//
//BOOST_AUTO_TEST_CASE(count_sort_100_million_test)
//{
//    std::string filename("count_100_million_");
//    auto maxElement = generateBinaryFileWithData(filename, N_100_million);
//    
//    auto start = std::chrono::high_resolution_clock::now();
//
//    // unsync the I/O of C and C++.
//    std::ios_base::sync_with_stdio(false);
//
//    sortings::countSort(filename);
//
//    auto end = std::chrono::high_resolution_clock::now();
//
//    // Calculating total time taken by the BM algorithm.
//    double time_taken =
//        std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
//
//    time_taken *= 1e-9;
//    std::ios_base::sync_with_stdio(true);
//
//    std::fstream resultFile(SUMMARY, std::ios::out | std::ios::app);
//    resultFile << "count_sort_100_million_test" << "--------------------------" << std::fixed << time_taken << std::setprecision(9) << " sec" << std::endl;
//    resultFile.close();
//
//    BOOST_TEST_MESSAGE("count_sort_100_million_test has been ended. Look for quality of sorting manually");
//}
//
//BOOST_AUTO_TEST_CASE(count_sort_billion_test)
//{
//    std::string filename("count_billion_");
//    auto maxElement = generateBinaryFileWithData(filename, N_billion);
//
//    auto start = std::chrono::high_resolution_clock::now();
//
//    // unsync the I/O of C and C++.
//    std::ios_base::sync_with_stdio(false);
//
//    sortings::countSort(filename);
//
//    auto end = std::chrono::high_resolution_clock::now();
//
//    // Calculating total time taken by the BM algorithm.
//    double time_taken =
//        std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
//
//    time_taken *= 1e-9;
//    std::ios_base::sync_with_stdio(true);
//
//    std::fstream resultFile(SUMMARY, std::ios::out | std::ios::app);
//    resultFile << "count_sort_billion_test" << "--------------------------" << std::fixed << time_taken << std::setprecision(9) << " sec" << std::endl;
//    resultFile.close();
//
//    BOOST_TEST_MESSAGE("count_sort_billion_test has been ended. Look for quality of sorting manually");
//}
//
////this one works for appropriate time. Rest tests - only if you have free half of day
//BOOST_AUTO_TEST_CASE(radix_sort_million_test)
//{
//    std::string filename("radix_million_");
//    auto maxElement = generateBinaryFileWithData(filename, N_million);
//
//    auto start = std::chrono::high_resolution_clock::now();
//
//    // unsync the I/O of C and C++.
//    std::ios_base::sync_with_stdio(false);
//
//    sortings::radixSort(filename, maxElement);
//
//    auto end = std::chrono::high_resolution_clock::now();
//
//    // Calculating total time taken by the BM algorithm.
//    double time_taken =
//        std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
//
//    time_taken *= 1e-9;
//    std::ios_base::sync_with_stdio(true);
//
//    std::fstream resultFile(SUMMARY, std::ios::out | std::ios::app);
//    resultFile << "radix_sort_million_test" << "--------------------------" << std::fixed << time_taken << std::setprecision(9) << " sec" << std::endl;
//    resultFile.close();
//
//    BOOST_TEST_MESSAGE("radix_sort_million_test has been ended. Look for quality of sorting manually");
//}
//
//BOOST_AUTO_TEST_CASE(radix_sort_10_million_test)
//{
//    std::string filename("radix_10_million_");
//    auto maxElement = generateBinaryFileWithData(filename, N_10_million);
//
//    auto start = std::chrono::high_resolution_clock::now();
//
//    // unsync the I/O of C and C++.
//    std::ios_base::sync_with_stdio(false);
//
//    sortings::radixSort(filename, maxElement);
//
//    auto end = std::chrono::high_resolution_clock::now();
//
//    // Calculating total time taken by the BM algorithm.
//    double time_taken =
//        std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
//
//    time_taken *= 1e-9;
//    std::ios_base::sync_with_stdio(true);
//
//    std::fstream resultFile(SUMMARY, std::ios::out | std::ios::app);
//    resultFile << "radix_sort_10_million_test" << "--------------------------" << std::fixed << time_taken << std::setprecision(9) << " sec" << std::endl;
//    resultFile.close();
//
//
//    BOOST_TEST_MESSAGE("radix_sort_10_million_test has been ended. Look for quality of sorting manually");
//}
//
//BOOST_AUTO_TEST_CASE(radix_sort_100_million_test)
//{
//    std::string filename("radix_100_million_");
//    auto maxElement = generateBinaryFileWithData(filename, N_100_million);
//
//    auto start = std::chrono::high_resolution_clock::now();
//
//    // unsync the I/O of C and C++.
//    std::ios_base::sync_with_stdio(false);
//
//    sortings::radixSort(filename, maxElement);
//
//    auto end = std::chrono::high_resolution_clock::now();
//
//    // Calculating total time taken by the BM algorithm.
//    double time_taken =
//        std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
//
//    time_taken *= 1e-9;
//    std::ios_base::sync_with_stdio(true);
//
//    std::fstream resultFile(SUMMARY, std::ios::out | std::ios::app);
//    resultFile << "radix_sort_100_million_test" << "--------------------------" << std::fixed << time_taken << std::setprecision(9) << " sec" << std::endl;
//    resultFile.close();
//
//    BOOST_TEST_MESSAGE("radix_sort_100_million_test has been ended. Look for quality of sorting manually");
//}
//
//BOOST_AUTO_TEST_CASE(radix_sort_billion_test)
//{
//    std::string filename("radix_billion_");
//    auto maxElement = generateBinaryFileWithData(filename, N_billion);
//
//    auto start = std::chrono::high_resolution_clock::now();
//
//    // unsync the I/O of C and C++.
//    std::ios_base::sync_with_stdio(false);
//
//    sortings::radixSort(filename, maxElement);
//
//    auto end = std::chrono::high_resolution_clock::now();
//
//    // Calculating total time taken by the BM algorithm.
//    double time_taken =
//        std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
//
//    time_taken *= 1e-9;
//    std::ios_base::sync_with_stdio(true);
//
//    std::fstream resultFile(SUMMARY, std::ios::out | std::ios::app);
//    resultFile << "radix_sort_billion_test" << "--------------------------" << std::fixed << time_taken << std::setprecision(9) << " sec" << std::endl;
//    resultFile.close();
//
//    BOOST_TEST_MESSAGE("radix_sort_billion_test has been ended. Look for quality of sorting manually");
//}

BOOST_AUTO_TEST_CASE(merge_sort_million_test)
{
    std::string filename("merge_million_");
    generateBinaryFileWithData(filename, N_million);

    auto start = std::chrono::high_resolution_clock::now();

    // unsync the I/O of C and C++.
    std::ios_base::sync_with_stdio(false);

    sortings::mergeSort(filename);

    auto end = std::chrono::high_resolution_clock::now();

    // Calculating total time taken by the BM algorithm.
    double time_taken =
        std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();

    time_taken *= 1e-9;
    std::ios_base::sync_with_stdio(true);

    std::fstream resultFile(SUMMARY, std::ios::out | std::ios::app);
    resultFile << "merge_sort_million_test" << "--------------------------" << std::fixed << time_taken << std::setprecision(9) << " sec" << std::endl;
    resultFile.close();

    BOOST_TEST_MESSAGE("merge_sort_million_test has been ended. Look for quality of sorting manually");
}

//BOOST_AUTO_TEST_CASE(merge_sort_10_million_test)
//{
//    std::string filename("merge_10_million_");
//    generateBinaryFileWithData(filename, N_10_million);
//
//    auto start = std::chrono::high_resolution_clock::now();
//
//    // unsync the I/O of C and C++.
//    std::ios_base::sync_with_stdio(false);
//
//    sortings::mergeSort(filename);
//
//    auto end = std::chrono::high_resolution_clock::now();
//
//    // Calculating total time taken by the BM algorithm.
//    double time_taken =
//        std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
//
//    time_taken *= 1e-9;
//    std::ios_base::sync_with_stdio(true);
//
//    std::fstream resultFile(SUMMARY, std::ios::out | std::ios::app);
//    resultFile << "merge_sort_10_million_test" << "--------------------------" << std::fixed << time_taken << std::setprecision(9) << " sec" << std::endl;
//    resultFile.close();
//
//    BOOST_TEST_MESSAGE("merge_sort_10_million_test has been ended. Look for quality of sorting manually");
//}

//these two tests takes more then hour for each. Uncomment if you have free day
//BOOST_AUTO_TEST_CASE(merge_sort_100_million_test)
//{
//    std::string filename("merge_100_million_");
//    generateBinaryFileWithData(filename, N_100_million);
//
//    auto start = std::chrono::high_resolution_clock::now();
//
//    // unsync the I/O of C and C++.
//    std::ios_base::sync_with_stdio(false);
//
//    sortings::mergeSort(filename);
//
//    auto end = std::chrono::high_resolution_clock::now();
//
//    // Calculating total time taken by the BM algorithm.
//    double time_taken =
//        std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
//
//    time_taken *= 1e-9;
//    std::ios_base::sync_with_stdio(true);
//
//    std::fstream resultFile(SUMMARY, std::ios::out | std::ios::app);
//    resultFile << "merge_sort_100_million_test" << "--------------------------" << std::fixed << time_taken << std::setprecision(9) << " sec" << std::endl;
//    resultFile.close();
//
//    BOOST_TEST_MESSAGE("merge_sort_100_million_test has been ended. Look for quality of sorting manually");
//}
//
//BOOST_AUTO_TEST_CASE(merge_sort_billion_test)
//{
//    std::string filename("merge_billion_");
//    generateBinaryFileWithData(filename, N_billion);
//
//    auto start = std::chrono::high_resolution_clock::now();
//
//    // unsync the I/O of C and C++.
//    std::ios_base::sync_with_stdio(false);
//
//    sortings::mergeSort(filename);
//
//    auto end = std::chrono::high_resolution_clock::now();
//
//    // Calculating total time taken by the BM algorithm.
//    double time_taken =
//        std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
//
//    time_taken *= 1e-9;
//    std::ios_base::sync_with_stdio(true);
//
//    std::fstream resultFile(SUMMARY, std::ios::out | std::ios::app);
//    resultFile << "merge_sort_billion_test" << "--------------------------" << std::fixed << time_taken << std::setprecision(9) << " sec" << std::endl;
//    resultFile.close();
//
//    BOOST_TEST_MESSAGE("merge_sort_billion_test has been ended. Look for quality of sorting manually");
//}
BOOST_AUTO_TEST_SUITE_END()
