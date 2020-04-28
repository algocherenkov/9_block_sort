#include "sortings.h"
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
constexpr int CHUNK_SIZE_RADIX_SORT = 10000; 
constexpr int CHUNK_SIZE_MERGE_SORT = 100000;

/*********************************************************BUCKET SORT****************************************************************/
void pushToBuckets(std::vector<std::fstream>& bucketFiles, std::vector<unsigned short>& numbers, int k, int max, int n)
{
    std::vector <std::vector<unsigned short>> buckets;
    buckets.resize(k + 1);
    for (int i = 0; i < n; i++)
    {
        auto bucketNumber = k * numbers[i] / max;
        buckets[bucketNumber].push_back(numbers[i]);       
    }    

    int bucketCounter = 0;
    for (const auto& bucket : buckets)
    {       
        if (!bucket.empty() && bucketFiles[bucketCounter].is_open())
            bucketFiles[bucketCounter].write((char*)(bucket.data()), bucket.size() * sizeof(unsigned short));
        
        bucketCounter++;
    }
}

void sortBuckets(std::vector<std::fstream>& bucketFiles, std::string& filename)
{
    std::vector<unsigned short> tempBuff;
    int bucketCounter = 0;
    tempBuff.resize(CHUNK_SIZE_BUCKET_SORT * sizeof(unsigned short), 0);

    for (auto& file : bucketFiles)
    {
        file.seekp(0, std::ios_base::beg);

        file.read((char*)(tempBuff.data()), sizeof(unsigned short) * CHUNK_SIZE_BUCKET_SORT * 2);
        auto readBytes = file.gcount();
        if (readBytes == sizeof(unsigned short) * CHUNK_SIZE_BUCKET_SORT * 2)
            std::cerr << "not enough space in RAM for sorting bucket. Result is not valid";

        std::vector<unsigned short> data(tempBuff.begin(), tempBuff.begin() + readBytes / sizeof(unsigned short));
        file.close();

        std::sort(data.begin(), data.end());

        file.open(filename + std::to_string(bucketCounter), std::ios::out | std::ios::in | std::ios::trunc | std::ios::binary);
        file.write((char*)(data.data()), readBytes);

        memset(tempBuff.data(), 0, CHUNK_SIZE_BUCKET_SORT * sizeof(unsigned short));
        bucketCounter++;
    }
}

void mergeBuckets(std::vector<std::fstream>& bucketFiles, std::string& filename)
{
    std::fstream unsortedFile(filename, std::ios::out | std::ios::trunc | std::ios::binary);
    std::vector<unsigned short> tempBuff;
    tempBuff.resize(CHUNK_SIZE_BUCKET_SORT, 0);

    int bucketCounter = 0;
    for (auto& sortedBucket : bucketFiles)
    {          
        sortedBucket.seekp(0, std::ios_base::beg);

        sortedBucket.read((char*)(tempBuff.data()), sizeof(unsigned short) * CHUNK_SIZE_BUCKET_SORT);
        auto bytes = sortedBucket.gcount();
        unsortedFile.write((char*)(tempBuff.data()), sortedBucket.gcount());
        sortedBucket.close();
                
        auto deleteStatus = remove(std::string(filename + std::to_string(bucketCounter)).c_str());
        if (deleteStatus)
            std::cerr << "cannot delete file " << filename + std::to_string(bucketCounter);

        memset(tempBuff.data(), 0, CHUNK_SIZE_BUCKET_SORT * sizeof(unsigned short));
        bucketCounter++;
    }

    unsortedFile.close(); //now file sorted
}

void sortings::bucketSort(std::string& filename, int k, int max)
{
    std::fstream unsortedFile(filename, std::ios::binary | std::ios::in);

    std::vector<unsigned short> numbers;
    numbers.resize(CHUNK_SIZE_BUCKET_SORT, 0);
    
    std::vector<std::fstream> bucketFiles;
    for (int i = 0; i < (k + 1); i++)
    {
        std::string fileName(filename + std::to_string(i));
        bucketFiles.emplace_back(fileName, std::ios::trunc | std::ios::binary | std::ios::out | std::ios::in);
    }

    while (true)
    {
        unsortedFile.read((char*)(numbers.data()), sizeof(unsigned short) * CHUNK_SIZE_BUCKET_SORT);   //reading chunk of data
        auto readBytes = unsortedFile.gcount();
        if (!readBytes)
            break;
        //distribute this chunk to buckets
        pushToBuckets(bucketFiles, numbers, k, max, readBytes/sizeof(unsigned short));
        memset(numbers.data(), 0, CHUNK_SIZE_BUCKET_SORT * sizeof(unsigned short));
    }
       
    unsortedFile.close();

    sortBuckets(bucketFiles, filename);
    
    mergeBuckets(bucketFiles, filename);
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

void mergeFiles(std::string& filename, std::vector<unsigned short>& elementsFromFile2, int nElementsInFile2)
{
    std::fstream file1(filename + "helper1", std::ios::in | std::ios::binary);
    std::fstream file3(filename + "helper3", std::ios::binary | std::ios::out);
    unsigned short temp = 0;
    int file2Counter = 0;

    file1.read((char*)&temp, sizeof(unsigned short));
    if (!file1.gcount())
        return;

    while (true)
    {   
        if (temp < elementsFromFile2[file2Counter])
        {            
            file3.write((char*)&temp, sizeof(unsigned short));
            
            unsigned short data = 0;
            file1.read((char*)&data, sizeof(unsigned short));
            auto readBytes = file1.gcount();
            if (!readBytes)
                break;

            temp = data;
        }
        else
        {
            file3.write((char*)&(elementsFromFile2[file2Counter++]), sizeof(unsigned short));
            if (file2Counter == nElementsInFile2)
                break;
        }
    }

    if (file2Counter < nElementsInFile2)
        file3.write((char*)&(elementsFromFile2[file2Counter]), (nElementsInFile2 - file2Counter)*sizeof(unsigned short));

    memset(elementsFromFile2.data(), 0, CHUNK_SIZE_MERGE_SORT * sizeof(unsigned short));
    while (true)
    {
        file1.read((char*)(elementsFromFile2.data()), CHUNK_SIZE_MERGE_SORT * sizeof(unsigned short));
        auto readBytes = file1.gcount();
        if (!readBytes)
            break;       

        file3.write((char*)(elementsFromFile2.data()), readBytes);
     }

    file1.close();
    file3.close();
}

void sortings::mergeSort(std::string& filename)
{
    std::fstream input(filename, std::ios::in | std::ios::out | std::ios::binary);

    std::fstream helperFile1(filename + "helper1", std::ios::out | std::ios::binary);    
    
    std::vector<unsigned short> chunkWithNumbers;
    chunkWithNumbers.resize(CHUNK_SIZE_MERGE_SORT * sizeof(unsigned short), 0);

    input.read((char*)(chunkWithNumbers.data()), CHUNK_SIZE_MERGE_SORT * sizeof(unsigned short));   //reading chunk of data
    auto readBytes = input.gcount();
    
    std::sort(chunkWithNumbers.begin(), chunkWithNumbers.begin() + readBytes / sizeof(unsigned short));

    helperFile1.write((char*)(chunkWithNumbers.data()), readBytes);
    memset(chunkWithNumbers.data(), 0, CHUNK_SIZE_MERGE_SORT * sizeof(unsigned short));

    helperFile1.close();

    while (true)
    {

        input.read((char*)(chunkWithNumbers.data()), CHUNK_SIZE_MERGE_SORT * sizeof(unsigned short));   //reading chunk of data
        auto readBytes = input.gcount();
        if (!readBytes)
            break;

        std::sort(chunkWithNumbers.begin(), chunkWithNumbers.begin() + readBytes / sizeof(unsigned short));

        //                   "file2" in RAM already
        mergeFiles(filename, chunkWithNumbers, readBytes / sizeof(unsigned short));

        remove(std::string(filename + "helper1").c_str());

        rename(std::string(filename + "helper3").c_str(), std::string(filename + "helper1").c_str());
    }

    input.close();
    remove(filename.c_str());
    rename(std::string(filename + "helper1").c_str(), filename.c_str());
}
