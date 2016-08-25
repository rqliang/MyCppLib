//
//  Biology.h
//  
//
//  Created by Ruqiang Liang on 8/23/16.
//
//

#ifndef ____Biology__
#define ____Biology__
#include <vector>
#include <initializer_list>
#include <string>
#include <iostream>

enum class NT{G,A,T,C,N,M,K};

NT complement(const NT& x);
float ntmw(const NT& x);


class DNA{
    std::vector<NT> dna;
public:
    DNA(std::initializer_list<NT> ilNT): dna{ilNT} {}
    DNA(std::vector<NT> d){dna = d;}
    DNA(std::string str){
        for (const char& x: str) {
            switch (x) {
                case 'A':
                case 'a':
                    dna.push_back(NT::A);
                    break;
                case 'G':
                case 'g':
                    dna.push_back(NT::G);
                    break;
                case 'C':
                case 'c':
                    dna.push_back(NT::C);
                    break;
                case 'T':
                case 't':
                    dna.push_back(NT::T);
                    break;
                case 'N':
                case 'n':
                    dna.push_back(NT::N);
                    break;
                case 'M':
                case 'm':
                    dna.push_back(NT::M);
                    break;
                case 'K':
                case 'k':
                    dna.push_back(NT::K);
                    break;
                default:
                    break;
            }
        }
    }
    DNA reverse_complement() const;
    inline std::string toString() const;
    float mw() const;
    DNA& operator+=(const DNA& d) {
        for (auto x: d.dna)
            dna.push_back(x);
        return *this;
    }
    
    DNA& operator+(const DNA& d) { return *this += d;}
    friend std::ostream& operator<<(std::ostream& os, const DNA& d);
};



#endif /* defined(____Biology__) */
