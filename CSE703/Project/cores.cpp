#include <omp.h>
#include <iostream>

int main() {
    int num_cores = omp_get_num_procs(); // Get number of available cores
    std::cout << "Number of CPU cores available: " << num_cores << std::endl;
    return 0;
}

