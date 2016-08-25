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
enum class AA1{A,C,D,E,F,G,H,I,K,L,M,N,P,Q,R,S,T,V,W,Y,X};
enum class AA3{Ala,Cys,Asp,Glu,Phe,Gly,His,Ile,Lys,Leu,Met,Asn,Pro,Gln,Arg,Ser,Thr,Val,Trp,Tyr,Any};
AA3 AA123(AA1 x);
AA1 AA321(AA3 x);
char AA1toChar(AA1 x);
char AA3toChar(AA3 x);
std::string AA3toStr(AA3 x);
std::string AA1toStr(AA1 x);

NT complement(const NT& x);
float ntmw(const NT& x);

class Protein{
    std::vector<AA1> prot;
public:
    Protein(std::initializer_list<AA1> ilAA1): prot{ilAA1} {}
    Protein(std::vector<AA1> x): prot{x}{}
    Protein(std::string str) {
        for (const char& x: str) {
            switch (x) {
                case 'A':
                case 'a':
                    prot.push_back(AA1::A);
                    break;
                case 'C':
                case 'c':
                    prot.push_back(AA1::C);
                    break;
                case 'D':
                case 'd':
                    prot.push_back(AA1::D);
                    break;
                case 'E':
                case 'e':
                    prot.push_back(AA1::E);
                    break;
                case 'F':
                case 'f':
                    prot.push_back(AA1::F);
                    break;
                case 'G':
                case 'g':
                    prot.push_back(AA1::G);
                    break;
                case 'H':
                case 'h':
                    prot.push_back(AA1::H);
                    break;
                case 'I':
                case 'i':
                    prot.push_back(AA1::I);
                    break;
                case 'K':
                case 'k':
                    prot.push_back(AA1::K);
                    break;
                case 'L':
                case 'l':
                    prot.push_back(AA1::L);
                    break;
                case 'M':
                case 'm':
                    prot.push_back(AA1::M);
                    break;
                case 'N':
                case 'n':
                    prot.push_back(AA1::N);
                    break;
                case 'P':
                case 'p':
                    prot.push_back(AA1::P);
                    break;
                case 'Q':
                case 'q':
                    prot.push_back(AA1::Q);
                    break;
                case 'R':
                case 'r':
                    prot.push_back(AA1::R);
                    break;
                case 'S':
                case 's':
                    prot.push_back(AA1::S);
                    break;
                case 'T':
                case 't':
                    prot.push_back(AA1::T);
                    break;
                case 'V':
                case 'v':
                    prot.push_back(AA1::V);
                    break;
                case 'W':
                case 'w':
                    prot.push_back(AA1::W);
                    break;
                case 'X':
                case 'x':
                    prot.push_back(AA1::X);
                    break;
                case 'Y':
                case 'y':
                    prot.push_back(AA1::Y);
                    break;
            }
        }
    }
    std::string toString1() const {
        std::string str = "";
        for (const AA1& x: prot) {
            str += AA1toChar(x);
        }
        return str;
    }
    
    std::string toString() const {
        return toString1();
    }
    
    std::string toString3() const {
        std::string str = "";
        for (const AA1& x: prot) {
            str += AA1toStr(x)+' ';
        }
        return str;
    }
    
    Protein& operator+=(const Protein& p) {
        for (AA1 x: p.prot) {
            prot.push_back(x);
        }
        return *this;
    }
    
    Protein& operator+(const Protein& p) {
        return *this += p;
    }
    
    friend std::ostream& operator<<(std::ostream& os, const Protein& p) {
        os << p.toString1();
        return os;
    }
};


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
    std::string toString() const;
    float mw() const;
    DNA& operator+=(const DNA& d) {
        for (auto x: d.dna)
            dna.push_back(x);
        return *this;
    }
    
    DNA& operator+(const DNA& d) { return *this += d;}
    friend std::ostream& operator<<(std::ostream& os, const DNA& d);
};

template <typename T>
struct Record{
    std::string name;
    T seq;
};

template <typename T>
class Fasta{
    std::vector<Record<T>> records;
public:
    Fasta(Record<T> a) {
        records.push_back(a);
    }
    Fasta(std::string s, T a) {
        Record<T> t{s,a};
        records.push_back(t);
    }
    size_t size() const { return records.size();}
    Fasta& operator+=(const Fasta& a) {
        for (auto x: a.records){
            records.push_back(x);
        }
        return *this;
    }
    Fasta& operator+=(const Record<T>& a) {
        records.push_back(a);
        return *this;
    }
    std::string toString() const {
        std::string str{""};
        for (auto x: records){
            str += '>' + x.name + '\n';
            str += x.seq.toString() + '\n';
        }
        return str;
    }
    
};

#endif /* defined(____Biology__) */
