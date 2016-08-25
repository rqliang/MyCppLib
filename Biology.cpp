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

float DNA::mw() const {
    float sum=0;
    for (const NT& n: dna)
        sum += ntmw(n);
    return sum;
}

inline std::string DNA::toString() const{
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