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
    std::string seq;
};

struct retMatrix{
    std::vector<unsigned> pos;
    std::vector<fasta> seqs;
};

std::vector<fasta> getSeqs(const std::string& fn);
void printSeqs(const std::vector<fasta>& seqs);
void writeSeqs(const std::vector<fasta>& seqs, const std::string& fn);
retMatrix getMatrix (const std::vector<fasta>& seqs);

#endif /* printVariant_hpp */
