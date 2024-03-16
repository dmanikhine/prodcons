#include "readfile.hpp"
#include "mytype.hpp"
#include <iostream>

const long LENGTH_OF_BUFFER = 100'000;

std::pair<bool, TForwardListLongString> TReadFile::operator()()
{
    std::string inLine;
    TForwardListLongString localVector;    
    std::cout << "Read File" << std::endl;
    for (int i = 1; i <= LENGTH_OF_BUFFER; i++)
    {
        if (std::getline(m_ifs, inLine))
        {
            localVector.push_front(std::pair{++m_lineCounter, inLine});
        }
        else
        {
            return std::pair{false, localVector};
        }
    }
    return std::pair{true, localVector};
}

void TReadFile::printResultVector(TForwardListLongString &localVector)
{
    for (const auto &i : localVector)
        std::cout << i.first << ' ' << i.second << std::endl;
}