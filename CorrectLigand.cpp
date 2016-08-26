//
//  main.cpp
//  CorrectLigand
//
//  Created by Ruqiang Liang on 8/12/16.
//  Copyright © 2016 Ruqiang Liang. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <map>
using namespace std;

static const string HETATM = "HETATM";

/// A ligand.def file is made up of lines separated by tab.
/// this program basically replate the first entity before the tab with the one
/// after the tab.
map<string, string> makeDict(const string& fn) {
    map<string, string> atomPairs;
    ifstream ligand(fn);
    string str, key, value;
    size_t pos;
    while (getline(ligand, str)) {
        if (str[0] == '#') continue;
        pos = str.find('\t');
        key = str.substr(0,pos);
        value = str.substr(pos+1,str.size());
        atomPairs.insert(pair<string, string>(key, value));
    }
    return atomPairs;
}

int main(int argc, const char * argv[]) {
    // insert code here...
    if (argc < 3){
        cerr << "Usage: " << argv[0] << " ligand.def input.pdb output.pdb" << endl;
        return -1;
    }
    string ligand = argv[1];
    string inPDB = argv[2];
    string outPDB = argv[3];
    string line;
    //string nline;
    size_t pos;
    ofstream myWrite(outPDB);
    ifstream inputFile(inPDB);
    map<string, string> atomPairs = makeDict(ligand);
    while (getline(inputFile, line)) {
        if (line.find(HETATM)==0) {
            map<string, string>::iterator it;
            for (it = atomPairs.begin(); it != atomPairs.end(); ++it) {
                if ((pos = line.find(it->first)) != string::npos) {
                    line.replace(pos, (it -> first).size(), it->second);
                    //myWrite << line << endl;
                    break;
                }
            }
            myWrite << line << endl;
        } else {
            myWrite << line << endl;
        }
    }
    return 0;
}
