//
//  printVariant.hpp
//  PrintVariant
//
//  Created by Ruqiang Liang on 8/12/16.
//  Copyright © 2016 Ruqiang Liang. All rights reserved.
//

#ifndef printVariant_hpp
#define printVariant_hpp
#include <string>
#include <vector>
//#include <fstream>
//#include <iostream>

struct fasta{
    std::string name;
  std::string seq; /// without checking the fidelity of the sequnce.
};

struct retMatrix{
    std::vector<unsigned> pos;
    std::vector<fasta> seqs;
};

/// Read a fasta file into a vector of single fasta records.
std::vector<fasta> getSeqs(const std::string& fn);

/// Print a vector of fasta records into string.
std::string  printSeqs(const std::vector<fasta>& seqs);

/// write a vector of fasta records to a file.
void writeSeqs(const std::vector<fasta>& seqs, const std::string& fn);

/// Returns a retMatrix with position info and the mutant info.
retMatrix getMatrix (const std::vector<fasta>& seqs);

#endif /* printVariant_hpp */
