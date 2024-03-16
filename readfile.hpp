#pragma once
#include <fstream>
#include "mytype.hpp"

class TReadFile
{
    public:
    TReadFile(std::ifstream &ifs)
        : m_ifs{ifs}{}
    TReadFile(const TReadFile &src) = delete;
    TReadFile &operator=(const TReadFile &rhs) =delete;

    std::pair<bool, TForwardListLongString> operator()();    
    virtual void printResultVector(TForwardListLongString &localVector);  
private:
    std::ifstream &m_ifs;
    long m_lineCounter=0;    
};