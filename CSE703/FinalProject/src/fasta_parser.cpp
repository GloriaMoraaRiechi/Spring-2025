#include "fasta_parser.h"
#include <iostream>
#include <fstream>

std::string load_fasta_sequence(const std::string& filename) {
    std::ifstream infile(filename);
    if (!infile.is_open()) {
        std::cerr << "Error opening file: " << filename << std::endl;
        exit(1);
    }

    std::string first_line;
    std::getline(infile, first_line);

    if (first_line.empty() || first_line[0] != '>') {
        std::cerr << "Error: File does not appear to be a FASTA format." << std::endl;
        exit(1);
    }

    infile.clear();
    infile.seekg(0, std::ios::beg);

    std::string sequence = "", line;
    while (std::getline(infile, line)) {
        if (line.empty() || line[0] == '>') continue;
        sequence += line;
    }

    infile.close();
    return sequence;
}
