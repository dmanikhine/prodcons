#include <random>
#include <fstream>
#include "cmdoptions.hpp"

using engine = std::mt19937;
using distribution = std::uniform_int_distribution<uint_least64_t>;

class TTestASCII
{

public:
    TTestASCII(Options &options);
    int process();

private:
    void writeToFile(long restFile, std::ofstream &ofs);
    long writeToLine(long restFile, int restLine, std::ofstream &ofs);
    
    engine m_generator;
    distribution m_ascii_distribution{32,126};
    distribution m_length_distribution{1, 100};
    const std::string o_filepathname;
    const ulong o_filelength;
    const uint o_linelength;
};