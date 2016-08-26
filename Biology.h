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

/// enum class for nucleotides, including N, M, and K other than regulars
enum class NT{G,A,T,C,N,M,K};

/// enum class for amino acid residues with one letter symbol, with an extra X stands for anything else.
enum class AA1{A,C,D,E,F,G,H,I,K,L,M,N,P,Q,R,S,T,V,W,Y,X};

/// enum class for amino acid residues with three letter symbol.
enum class AA3{Ala,Cys,Asp,Glu,Phe,Gly,His,Ile,Lys,Leu,Met,Asn,Pro,Gln,Arg,Ser,Thr,Val,Trp,Tyr,Any};

/// Translates one letter symbol amino acid residue into three letter symbol
AA3 AA123(AA1 x);

/// Translates three letter symbol into one letter symbol
AA1 AA321(AA3 x);

/// Translate one letter symbol amino acid residue into printable char
char AA1toChar(AA1 x);

/// Translate 3-letter symbol into one printable char
char AA3toChar(AA3 x);

/// Translate 3-letter symbol into 3-letter string.
std::string AA3toStr(AA3 x);

/// Translates 1-letter symbol into 3-letter string.
std::string AA1toStr(AA1 x);

/// Return complementary nucleotide 
NT complement(const NT& x);

/// Return molecular weight of a nucleotide
float ntmw(const NT& x);


/// A simple class definition for protein.
class Protein{
  std::vector<AA1> prot; /// a vector of 1-letter amino acid symbol
public:
 Protein(std::initializer_list<AA1> ilAA1): prot{ilAA1} {} /// standard initializer_list construction.
 Protein(std::vector<AA1> x): prot{x}{} /// Constructor with a vector of 1-letter amino acid residue.

  /// Constructor using a string, ignoring any other nonstandard amino acids.
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

    /// print the protein sequence into 1-letter symbol string.
    std::string toString1() const {
        std::string str = "";
        for (const AA1& x: prot) {
            str += AA1toChar(x);
        }
        return str;
    }
    /// alias of toString1    
    std::string toString() const {
        return toString1();
    }
    
    /// Print protein sequence into 3-letter symbol separated by space
    std::string toString3() const {
        std::string str = "";
        for (const AA1& x: prot) {
            str += AA1toStr(x)+' ';
        }
        return str;
    }
    
    /// Concatenate protein sequnce
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

/// A simple class for DNA sequence.
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

    /// Return the reverse complementary sequence of a DNA
    DNA reverse_complement() const;

    /// Print the DNA sequence into a string
    std::string toString() const;

    /// Return the molecular weight of this single strand DNA.
    float mw() const;

    /// Concatenate DNA sequence.
    DNA& operator+=(const DNA& d) {
        for (auto x: d.dna)
            dna.push_back(x);
        return *this;
    }
    
    DNA& operator+(const DNA& d) { return *this += d;}
    friend std::ostream& operator<<(std::ostream& os, const DNA& d);
};

/// A template for Record either protein or DNA
template <typename T>
struct Record{
    std::string name;
    T seq;
};


/// A template class for Fasta file, either protein or DNA
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

    /// Return number of sequences in the fasta record.
    size_t size() const { return records.size();}

    /// Concatenate two fasta records.
    Fasta& operator+=(const Fasta& a) {
        for (auto x: a.records){
            records.push_back(x);
        }
        return *this;
    }

    /// Add one record onto the fasta
    Fasta& operator+=(const Record<T>& a) {
        records.push_back(a);
        return *this;
    }

    /// Return fasta records into string.
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
