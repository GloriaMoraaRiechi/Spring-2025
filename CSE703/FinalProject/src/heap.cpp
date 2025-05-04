#include "heap.h"
#include <queue>
#include <algorithm>

std::vector<std::pair<std::string, int>> find_top_k_kmers(
    const std::unordered_map<std::string, int>& counts, int top_k) {

    using Pair = std::pair<int, std::string>;
    std::priority_queue<Pair, std::vector<Pair>, std::greater<Pair>> min_heap;

    for (const auto& kv : counts) {
        min_heap.push({kv.second, kv.first});
        if (min_heap.size() > top_k) {
            min_heap.pop();
        }
    }

    std::vector<std::pair<std::string, int>> result;
    while (!min_heap.empty()) {
        result.push_back({min_heap.top().second, min_heap.top().first});
        min_heap.pop();
    }

    std::reverse(result.begin(), result.end());
    return result;
}

