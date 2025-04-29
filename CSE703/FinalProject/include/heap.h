#pragma once
#include <vector>
#include <string>
#include <unordered_map>

std::vector<std::pair<std::string, int>> find_top_k_kmers(
    const std::unordered_map<std::string, int>& counts, int top_k);

