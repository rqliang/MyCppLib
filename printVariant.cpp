//
//  printVariant.cpp
//  PrintVariant
//
//  Created by Ruqiang Liang on 8/12/16.
//  Copyright © 2016 Ruqiang Liang. All rights reserved.
//

#include "printVariant.hpp"
//#include <string>
//#include <vector>
#include <iostream>
#include <fstream>

std::vector<fasta> getSeqs(const std::string& fn) {
    std::vector<fasta> seqs;
    std::string str;
    fasta af;
    std::ifstream file(fn);
    while (std::getline(file, str)) {
        if (str == "") {continue;}
        else if (str.at(0) == '>') {
            if (af.name.length() != 0 && af.seq.length() != 0) {
                seqs.push_back(af);
            }
            af.name = str;
            af.seq = "";
        } else {
            af.seq += str;
        }
    }
    seqs.push_back(af);
    return seqs;
}

void printSeqs(const std::vector<fasta>& seqs) {
    for (auto& x: seqs)
        std::cout << x.name << '\t' << x.seq.length() << '\t' << x.seq << '\n';
}

void writeSeqs(const std::vector<fasta>& seqs, const std::string& fn) {
    std::ofstream file(fn);
    for (auto& x: seqs) {
        file << x.name << std::endl;
        file << x.seq << std::endl;
    }
}

retMatrix getMatrix (const std::vector<fasta>& seqs) {
    retMatrix matrix;
    fasta t;
    std::vector<bool> bTag;
    std::vector<unsigned> uPos;
    std::vector<fasta> inmat;
    std::vector<size_t> seqlen;
    
    for (auto& f: seqs) {
        seqlen.push_back(f.seq.size());
    }
    
    for (size_t i=1; i != seqlen.size(); ++i) {
        if (seqlen[0] != seqlen[i])
            std::cerr << "The " << i << "th sequences is length is different" << std::endl;
    }
    
    for (unsigned i=0; i != seqs[0].seq.size(); ++i) {
        bool isMutated = false;
        for (unsigned j=1; j != seqs.size(); ++j) {
            if (seqs[0].seq[i] != seqs[j].seq[i])
                isMutated = isMutated || true;
        }
        bTag.push_back(isMutated);
        if (isMutated) uPos.push_back(i);
    }
    
    matrix.pos = uPos;
    for (unsigned i = 0; i != seqs.size(); ++i){
        t.name = seqs[i].name;
        for (auto x: uPos){
            t.seq += seqs[i].seq[x];
        }
        inmat.push_back(t);
        t.seq="";
    }
    matrix.seqs = inmat;
    
    return matrix;
}
