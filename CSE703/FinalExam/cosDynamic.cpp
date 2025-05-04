#include <iostream>
#include <vector>
#include <cmath>
#include <omp.h>

int main() {
    std::vector<double> A = {12.5, 11.6, 17.2, 9.9, 10.14, 17.3, 10.5, 13.8, 8.12};
    std::vector<double> B = {11.5, 17.4, 12.5, 8.8, 11.04, 14.2, 15.6, 11.9, 7.16};

    int n = A.size();

    double dot_product = 0.0;
    double norm_A = 0.0;
    double norm_B = 0.0;

    #pragma omp parallel for reduction(+:dot_product, norm_A, norm_B) num_threads(3) schedule(dynamic)
    for (int i = 0; i < n; i++) {
        int thread_id = omp_get_thread_num();
        printf("Thread %d dynamically working on index %d\n", thread_id, i);

        dot_product += A[i] * B[i];
        norm_A += A[i] * A[i];
        norm_B += B[i] * B[i];
    }

    norm_A = sqrt(norm_A);
    norm_B = sqrt(norm_B);

    double cosine_similarity = dot_product / (norm_A * norm_B);

    std::cout << "\n[DYNAMIC] Cosine Similarity: " << cosine_similarity << std::endl;

    return 0;
}

