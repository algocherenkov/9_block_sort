#pragma once
#include <vector>

namespace sortings {
    void bucketSort(std::vector<unsigned short>& buff, int k);
    void countSort(std::vector<int>& buff);
    void radixSort(std::vector<int>& buff);
}
