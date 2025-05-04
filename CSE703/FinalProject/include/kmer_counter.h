#pragma once
#include <unordered_map>
#include <string>

void count_kmers_parallel(const std::string& sequence, int k, int num_threads,
                           std::unordered_map<std::string, int>& global_counts);

