//
//  Biology.cpp
//  
//
//  Created by Ruqiang Liang on 8/23/16.
//
//

#include "Biology.h"
NT complement(const NT& x) {
    switch (x) {
        case NT::G: return NT::C;
        case NT::A: return NT::T;
        case NT::T: return NT::A;
        case NT::C: return NT::G;
        case NT::N: return NT::N;
        case NT::M: return NT::K;
        case NT::K: return NT::M;
    }
}

AA3 AA123(AA1 x) {
    switch (x) {
        case AA1::A:
            return AA3::Ala;
        case AA1::C:
            return AA3::Cys;
        case AA1::D:
            return AA3::Asp;
        case AA1::E:
            return AA3::Glu;
        case AA1::F:
            return AA3::Phe;
        case AA1::G:
            return AA3::Gly;
        case AA1::H:
            return AA3::His;
        case AA1::I:
            return AA3::Ile;
        case AA1::K:
            return AA3::Lys;
        case AA1::L:
            return AA3::Leu;
        case AA1::M:
            return AA3::Met;
        case AA1::N:
            return AA3::Asn;
        case AA1::P:
            return AA3::Pro;
        case AA1::Q:
            return AA3::Gln;
        case AA1::R:
            return AA3::Arg;
        case AA1::S:
            return AA3::Ser;
        case AA1::T:
            return AA3::Thr;
        case AA1::V:
            return AA3::Val;
        case AA1::W:
            return AA3::Trp;
        case AA1::Y:
            return AA3::Tyr;
        case AA1::X:
            return AA3::Any;
    }
}

AA1 AA321(AA3 x) {
    switch (x) {
        case AA3::Ala :
            return AA1::A;
        case AA3::Cys :
            return AA1::C;
        case AA3::Asp :
            return AA1::D;
        case AA3::Glu :
            return AA1::E;
        case AA3::Phe :
            return AA1::F;
        case AA3::Gly :
            return AA1::G;
        case AA3::His :
            return AA1::H;
        case AA3::Ile :
            return AA1::I;
        case AA3::Leu :
            return AA1::L;
        case AA3::Lys :
            return AA1::K;
        case AA3::Met :
            return AA1::M;
        case AA3::Asn :
            return AA1::N;
        case AA3::Pro :
            return AA1::P;
        case AA3::Gln :
            return AA1::Q;
        case AA3::Arg :
            return AA1::R;
        case AA3::Ser :
            return AA1::S;
        case AA3::Thr :
            return AA1::T;
        case AA3::Val :
            return AA1::V;
        case AA3::Trp :
            return AA1::W;
        case AA3::Any :
            return AA1::X;
        case AA3::Tyr :
            return AA1::Y;
    }
}

char AA1toChar(AA1 x) {
    switch (x) {
        case AA1::A:
            return 'A';
        case AA1::C:
            return 'C';
        case AA1::D:
            return  'D';
        case AA1::E:
            return 'E';
        case AA1::F:
            return 'F';
        case AA1::G:
            return 'G';
        case AA1::H:
            return 'H';
        case AA1::I:
            return 'I';
        case AA1::K:
            return 'K';
        case AA1::L:
            return 'L';
        case AA1::M:
            return 'M';
        case AA1::N:
            return 'N';
        case AA1::P:
            return 'P';
        case AA1::Q:
            return 'Q';
        case AA1::R:
            return 'R';
        case AA1::S:
            return 'S';
        case AA1::T:
            return 'T';
        case AA1::V:
            return 'V';
        case AA1::W:
            return 'W';
        case AA1::Y:
            return 'Y';
        case AA1::X:
            return 'X';
    }
}

char AA3toChar(AA3 x) {
    AA1 y = AA321(x);
    return AA1toChar(y);
}

std::string AA3toStr(AA3 x){
    switch (x) {
        case AA3::Ala :
            return "Ala";
        case AA3::Cys :
            return "Cys";
        case AA3::Asp :
            return "Asp";
        case AA3::Glu :
            return "Glu";
        case AA3::Phe :
            return "Phe";
        case AA3::Gly :
            return "Gly";
        case AA3::His :
            return "His";
        case AA3::Ile :
            return "Ile";
        case AA3::Leu :
            return "Leu";
        case AA3::Lys :
            return "Lys";
        case AA3::Met :
            return "Met";
        case AA3::Asn :
            return "Asn";
        case AA3::Pro :
            return "Pro";
        case AA3::Gln :
            return "Gln";
        case AA3::Arg :
            return "Arg";
        case AA3::Ser :
            return "Ser";
        case AA3::Thr :
            return "Thr";
        case AA3::Val :
            return "Val";
        case AA3::Trp :
            return "Trp";
        case AA3::Any :
            return "Any";
        case AA3::Tyr :
            return "Tyr";
    }
}

std::string AA1toStr(AA1 x) {
    AA3 y = AA123(x);
    return AA3toStr(y);
}

/// This version of the molecular weight is not accurate.
float ntmw(const NT& x){
    switch (x) {
        case NT::G: return 347.2;
        case NT::A: return 331.2;
        case NT::T: return 322.2;
        case NT::C: return 307.2;
        case NT::N: return 327.0;
        case NT::M: return (ntmw(NT::A) + ntmw(NT::C))/2;
        case NT::K: return (ntmw(NT::G) + ntmw(NT::T))/2;
    }
}

std::ostream& operator<<(std::ostream& os, const DNA& d) {
    os << d.toString();
    return os;
}

/// This version of molecular weight is not correct.
float DNA::mw() const {
    float sum=0;
    for (const NT& n: dna)
        sum += ntmw(n);
    return sum;
}

std::string DNA::toString() const{
    std::string res;
    for (const NT& x: dna) {
        switch (x) {
            case NT::G:
                res.append("G");
                break;
            case NT::A:
                res.append("A");
                break;
            case NT::T:
                res.append("T");
                break;
            case NT::C:
                res.append("C");
                break;
            case NT::N:
                res.append("N");
                break;
            case NT::M:
                res.append("M");
                break;
            case NT::K:
                res.append("K");
                break;
            default:
                break;
        }
    }
    return res;
}

DNA DNA::reverse_complement() const {
    std::vector<NT> res;
    std::vector<NT> res2;
    for (const NT& x: dna)
        res.push_back(complement(x));
    for (auto i = res.rbegin(); i != res.rend(); ++i)
        res2.push_back(*i);
    return DNA{res2};
}
