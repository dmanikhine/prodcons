#include "testascii.hpp"
#include <iostream>


TTestASCII::TTestASCII(Options &options): 
o_filepathname{options.mainOptions["filepathname"]},
o_filelength{options.filelength},
o_linelength{options.linelength}
{
    std::random_device os_seed;
    const uint_least64_t seed = os_seed();
    m_generator=engine{seed};
}

int TTestASCII::process(){
    std::ofstream tFile{o_filepathname};
    if(tFile.fail()) {
        std::cerr <<"Failed to open file testFile.txt!" << std::endl;
        return 1;
    }
    ulong restFile = o_filelength; 
    writeToFile(restFile, tFile);
    return 0;
}

void TTestASCII::writeToFile(long restFile, std::ofstream &ofs)
{
    if (restFile ==0) return;
    int restLine = m_length_distribution(m_generator)+o_linelength;
    writeToFile(writeToLine(restFile,restLine,ofs),ofs);
    
}

long TTestASCII::writeToLine(long restFile, int restLine, std::ofstream &ofs)
    {
        if (restFile == 0) return restFile;
        if (restLine == 0) {
            ofs << std::endl;
            return restFile--;
        } 

        int iASCII = m_ascii_distribution(m_generator);
        if (iASCII != 10)
        {
            ofs << (char)iASCII;
            restFile--;
            restLine--;
        }
        return writeToLine(restFile,restLine,ofs);
    }
