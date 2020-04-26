#include "sortings.h"
#include "sortings.h"
#include "sortings.h"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <conio.h>
#include <stdio.h>
#include <iterator>

constexpr int CHUNK_SIZE_BUCKET_SORT = 100000;
constexpr int CHUNK_SIZE_COUNT_SORT = 10000;
constexpr int CHUNK_SIZE_RADIX_SORT = 10000; //number of elements

/*********************************************************BUCKET SORT****************************************************************/
void pushToBuckets(std::string filename, unsigned short* numbers, int k, int max, int n)
{
    std::vector < std::vector<unsigned short>> buckets;
    buckets.resize(k + 1);
    for (int i = 0; i < n; i++)
    {
        auto bucketNumber = k * numbers[i] / max;
        buckets[bucketNumber].push_back(numbers[i]);       
    }    

    int bucketCounter = 0;
    for (const auto& bucket : buckets)
    {
        if (!bucket.empty())
        {
            std::string bucketName(filename + std::to_string(bucketCounter));
            std::ofstream bucketFile(bucketName, std::ios::app | std::ios::binary);
            bucketFile.write((char*)(bucket.data()), bucket.size() * sizeof(unsigned short));
            bucketFile.close();
        }
        bucketCounter++;
    }
}

void sortBucket(std::string filename, int n)
{
    filename += std::to_string(n);

    unsigned short tempBuff[CHUNK_SIZE_BUCKET_SORT] = { 0 };
    std::fstream bucket(filename, std::ios::binary | std::ios::in);

    bucket.read((char*)&tempBuff, sizeof(unsigned short) * CHUNK_SIZE_BUCKET_SORT);
    auto readBytes = bucket.gcount();
    std::vector<unsigned short> data(tempBuff, tempBuff + readBytes/sizeof(unsigned short));
    bucket.close();

    std::sort(data.begin(), data.end());
    
    bucket.open(filename, std::ios::out | std::ios::trunc | std::ios::binary);
    bucket.write((char*)(data.data()), readBytes);
    bucket.close();
}

void mergeBuckets(std::string filename, int k)
{
    std::fstream unsortedFile(filename, std::ios::out | std::ios::trunc | std::ios::binary);

    for (int i = 0; i <= k; i++)
    {
        unsigned short tempBuff[CHUNK_SIZE_BUCKET_SORT] = { 0 };
        auto bucketName = filename + std::to_string(i);
        std::fstream sortedBucket(bucketName, std::ios::binary | std::ios::in);
        
        sortedBucket.read((char*)&tempBuff, sizeof(tempBuff));
        unsortedFile.write((char*)&tempBuff, sortedBucket.gcount());
        sortedBucket.close();
        auto deleteStatus = remove(bucketName.c_str());
        if (deleteStatus)
            std::cerr << "cannot delete file " << bucketName;
    }

    unsortedFile.close(); //now file sorted
}

void sortings::bucketSort(std::string& filename, int k, int max)
{
    std::fstream unsortedFile(filename, std::ios::binary | std::ios::in);
    unsigned short numbers[CHUNK_SIZE_BUCKET_SORT] = { 0 };
    
    while (true)
    {
        unsortedFile.read((char*)&numbers, sizeof(numbers));   //reading chunk of data
        auto readBytes = unsortedFile.gcount();
        if (!readBytes)
            break;
        //distribute this chink to buckets
        pushToBuckets(filename, numbers, k, max, readBytes/sizeof(unsigned short));
        memset(numbers, 0, CHUNK_SIZE_BUCKET_SORT * sizeof(unsigned short));
    }
       
    unsortedFile.close();

    for (int i = 0; i <= k; i++)
        sortBucket(filename, i);
    
    mergeBuckets(filename, k);
}

/*********************************************************COUNT SORT****************************************************************/

void sortings::countSort(std::string& filename)
{
    std::fstream input(filename, std::ios::binary | std::ios::in);
    
    std::vector<unsigned short> numbers;
    numbers.resize(CHUNK_SIZE_COUNT_SORT, 0 );
    
    std::vector<int> countingBuff;
    countingBuff.resize(UINT16_MAX, 0);

    while (true)
    {
        input.read((char*)(numbers.data()), CHUNK_SIZE_COUNT_SORT * sizeof(unsigned short));   //reading chunk of data
        auto readBytes = input.gcount();
        if (!readBytes)
            break;
        //fill counting buffer
        for (int i = 0; i < readBytes / sizeof(unsigned short); i++)
            countingBuff[numbers[i]]++;

        memset(numbers.data(), 0, CHUNK_SIZE_COUNT_SORT * sizeof(unsigned short));
    }
    numbers.clear();
    input.close();

    std::fstream output(filename, std::ios::out | std::ios::trunc | std::ios::binary);
    
    int eachNPush = 10;
    for (int i = 0; i < UINT16_MAX; i++)
    {
        for (int j = 0; j < countingBuff[i]; j++)
            numbers.push_back(i);
     
        output.write((char*)(numbers.data()), numbers.size() * sizeof(unsigned short));
        numbers.clear();
    }

    output.close();
}

/*********************************************************RADIX SORT****************************************************************/

void sortings::radixSort(std::string& filename, int maxValue)
{
    std::vector<unsigned short> chunkWithNumbers;
    chunkWithNumbers.resize(CHUNK_SIZE_RADIX_SORT * sizeof(unsigned short), 0);
           
    for (int exp = 1; maxValue / exp > 0; exp *= 10)
    {
        std::fstream input(filename, std::ios::binary | std::ios::in);

        //create helper files. Creation is need to be because creation clears the file
        std::vector<std::fstream> radixFiles;
        for (int i = 0; i < 10; i++)
        {
            std::string radixFileName(filename + "digit_" + std::to_string(i));
            radixFiles.emplace_back(radixFileName, std::ios::trunc | std::ios::binary | std::ios::out | std::ios::in);
        }

        while (true)
        {
            input.read((char*)(chunkWithNumbers.data()), CHUNK_SIZE_RADIX_SORT * sizeof(unsigned short));   //reading chunk of data
            auto readBytes = input.gcount();
            if (!readBytes)
                break;
            
            //fill radix files
            for (int i = 0; i < readBytes / sizeof(unsigned short); i++)
                radixFiles[(chunkWithNumbers[i] / exp) % 10].write((char*)&chunkWithNumbers[i], sizeof(unsigned short));
            
            memset(chunkWithNumbers.data(), 0, CHUNK_SIZE_RADIX_SORT * sizeof(unsigned short));
        }

        memset(chunkWithNumbers.data(), 0, CHUNK_SIZE_RADIX_SORT * sizeof(unsigned short));

        input.close();
  
        //clear input file
        std::fstream output(filename, std::ios::trunc | std::ios::binary | std::ios::out);
        //set reading position to the begining of helper files
        for (auto& file: radixFiles)        
            file.seekp(0, std::ios_base::beg);

        //merge radix files
        for (int i = 0; i < 10; i++)
        {            
            while (true)
            {
                radixFiles[i].read((char*)(chunkWithNumbers.data()), CHUNK_SIZE_RADIX_SORT * sizeof(unsigned short));   //reading chunk of data
                auto readBytes = radixFiles[i].gcount();
                if (!readBytes)
                    break;

                output.write((char*)(chunkWithNumbers.data()), readBytes);
                memset(chunkWithNumbers.data(), 0, CHUNK_SIZE_RADIX_SORT * sizeof(unsigned short));
            }
            radixFiles[i].close();

        }

        output.close();
        radixFiles.clear();
    }

    //remove helper files after sort
    for (int i = 0; i < 10; i++)
    {
        std::string radixFileName(filename + "digit_" + std::to_string(i));
        auto deleteStatus = remove(radixFileName.c_str());
        if (deleteStatus) {
            std::cerr << "cannot delete file " << radixFileName; std::cerr << "\n";
        }
    }
}
