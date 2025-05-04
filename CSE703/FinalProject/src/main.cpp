#include <iostream>
#include <unordered_map>
#include <omp.h>
#include "../include/fasta_parser.h"
#include "../include/kmer_counter.h"
#include "../include/heap.h"

int main() {
    std::string filename = "data/ncbi_dataset/data/GCF_000001405.40/chr22.fna"; // <-- correct path
    int k = 7;                  // k-mer size
    int top_k = 20;              // find top 20 most frequent k-mers
    int num_threads = 8;         // number of threads

    // Load sequence
    std::string sequence = load_fasta_sequence(filename);
    std::cout << "✅ Sequence loaded: " << sequence.length() << " bases." << std::endl;

    // Global k-mer counts
    std::unordered_map<std::string, int> global_counts;

    // Start timer
    double start = omp_get_wtime();
    count_kmers_parallel(sequence, k, num_threads, global_counts);
    double end = omp_get_wtime();
    std::cout << "✅ K-mer counting completed in " << (end - start) << " seconds." << std::endl;

    // Find top-k frequent k-mers
    auto top_k_kmers = find_top_k_kmers(global_counts, top_k);

    // Output results
    std::cout << "\nTop " << top_k << " most frequent k-mers:" << std::endl;
    for (const auto& kv : top_k_kmers) {
        std::cout << kv.first << " : " << kv.second << std::endl;
    }

    return 0;
}

