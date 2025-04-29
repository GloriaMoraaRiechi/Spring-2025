#include "kmer_counter.h"
#include <omp.h>
#include <iostream>

void count_kmers_parallel(const std::string& sequence, int k, int num_threads,
                           std::unordered_map<std::string, int>& global_counts) {
    
    int chunk_size = 100000; // ~100,000 bases per task
    int n = sequence.length();

    #pragma omp parallel num_threads(num_threads)
    {
        std::unordered_map<std::string, int> local_counts;

        #pragma omp single
        {
            for (int start = 0; start <= n - k; start += chunk_size) {
                int end = std::min(start + chunk_size, n - k + 1);

                #pragma omp task firstprivate(start, end) shared(sequence, k, local_counts)
                {
                    for (int i = start; i < end; ++i) {
                        std::string kmer = sequence.substr(i, k);
                        #pragma omp atomic
                        local_counts[kmer]++;
                    }
                }
            }
        }

        #pragma omp barrier

        // Merge local counts into global
        #pragma omp critical
        {
            for (const auto& kv : local_counts) {
                global_counts[kv.first] += kv.second;
            }
        }
    }
}

