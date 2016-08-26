//
//  main.cpp
//  CleanPDB
//
//  Created by Ruqiang Liang on 8/24/16.
//  Copyright © 2016 Ruqiang Liang. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <string>
using namespace std;
/// This program copy the PDB file and remove any other lines than ATOM and HETATM.
/// It accepts a input.pdb and output a input.pdb_out.pdb file.

int main(int argc, const char * argv[]) {
    // insert code here...
    //std::cout << "Hello, World!\n";
    string fn = argv[1];
    ifstream file(fn);
    ofstream fo(fn + "_out.pdb");
    string ln;
    if (argc < 2) {
        cerr << "Usage: " + string(argv[0]) + " input.pdb";
        return -1;
    }
    while(getline(file, ln)){
        if (ln.find("ATOM") == 0)
            fo << ln + '\n';
        else if (ln.find("HETATM") == 0)
            fo << ln + '\n';
        else
            continue;
    }
    return 0;
}
