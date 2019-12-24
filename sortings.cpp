#include "sortings.h"
#include <algorithm>

using Buckets_t = std::vector<std::vector<unsigned short>>;

void sortings::bucketSort(std::vector<unsigned short> &buff, int k)
{
    Buckets_t buckets;
    buckets.resize(static_cast<size_t>(k));

    const auto it_max = std::max_element(std::begin(buff), std::end(buff));

    for(auto& item: buff)
        buckets[static_cast<size_t>(k * item /(*it_max))].push_back(item);

    for(auto& bucket: buckets)
        std::sort(bucket.begin(), bucket.end());

    size_t j = 0;
    for(auto& bucket: buckets)
        for(auto& item: bucket)
            buff[j++] = item;
}
