#include "data_processor.h"
#include "hash_utils.h"  // Подключаем модуль безопасности для хеширования
#include <algorithm>  // For data transformations
#include <xmmintrin.h>  // For SIMD prefetching
#include <immintrin.h>  // For AVX instructions
#include <iostream>

// Process the raw data by first filtering, then transforming each data point, and optionally hashing.
// The processed data is returned as a vector of strings.
std::vector<std::string> DataProcessor::process(const std::vector<std::string>& rawData) {
    std::vector<std::string> processedData;
    processedData.reserve(rawData.size());  // Reserve memory to avoid reallocations
    
    // Prefetch the first block of data
    _mm_prefetch(rawData.data(), _MM_HINT_T0);

    // Use standard algorithms for efficiency
    std::transform(rawData.begin(), rawData.end(), std::back_inserter(processedData),
                   [this](const std::string& data) {
                       std::string filtered = filterData(data);
                       std::string transformed = transformData(filtered);
                       
                       // Хешируем трансформированные данные для проверки целостности
                       hash_result_t hash_result;
                       int ret = hash_data((const uint8_t*)transformed.c_str(), transformed.size(), HASH_ALG_SHA256, &hash_result);
                       
                       if (ret == 0) {
                           std::cout << "Hash of data: ";
                           for (size_t i = 0; i < hash_result.hash_len; ++i) {
                               printf("%02x", hash_result.hash[i]);
                           }
                           std::cout << std::endl;
                       } else {
                           std::cerr << "Error hashing data!" << std::endl;
                       }

                       hash_result_free(&hash_result);  // Очистка после хеширования
                       
                       return transformed;
                   });

    return processedData;
}

// Filter the data to remove or modify unwanted elements.
std::string DataProcessor::filterData(const std::string& data) {
    // Potentially add SIMD optimization here if more complex filtering is needed
    return data;  // No filtering applied in this simple example
}

// Transform the data, for example by normalizing or formatting it.
std::string DataProcessor::transformData(const std::string& data) {
    // Example SIMD usage for more complex transformations (if necessary)
    return "Transformed: " + data;
}
