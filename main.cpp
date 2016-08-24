//
//  main.cpp
//  PrintVariant
//
//  Created by Ruqiang Liang on 8/12/16.
//  Copyright © 2016 Ruqiang Liang. All rights reserved.
//


//#include <fstream>
//#include <string>
//#include <vector>
#include "printVariant.hpp"
#include <iostream>
using namespace std;

int main(int argc, const char * argv[]) {
    // insert code here...
    //cout << "Hello, World!\n";
    if (argc < 3) {
        cerr << "Usage: " << argv[0] << " input.fa output.fa\n";
        return -1;
    }
    string file = argv[1];
    
    vector<fasta> seqs = getSeqs(file);
    retMatrix matrix = getMatrix(seqs);
    for (auto x: matrix.pos)
        cout<< x+1 << ',';
    cout<<endl;
    //printSeqs(matrix.seqs);
    vector<fasta>& test = matrix.seqs;
    printSeqs(test);
    writeSeqs(test, argv[2]);
    return 0;
}
