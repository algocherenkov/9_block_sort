#pragma once
#include <vector>
#include <string>

namespace sortings {
    void bucketSort(std::string& filename, int k, int max);
    void countSort(std::string& filename);
    void radixSort(std::string& filename, int maxValue);
    void mergeSort(std::string& filename);
}
