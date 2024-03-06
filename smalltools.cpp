#include "smalltools.hpp"
#include <algorithm>
#include <execution>
#include <iostream>

TVectorLongVectorIntString removeEmptyLine(TVectorLongVectorIntString inVec)
{
    inVec.erase(std::remove_if(std::execution::par, begin(inVec), end(inVec), [](std::pair<long, std::vector<std::pair<int, std::string>>> i)
                               { return i.second.size() == 0; }),
                end(inVec));
    return inVec;
}

auto accumulate_func = [](long accumulator, const std::pair<long, std::vector<std::pair<int, std::string>>> &el)
{
    return accumulator + el.second.size();
};

long getMatchCount(TVectorLongVectorIntString inVec)
{
    return std::accumulate(inVec.begin(), inVec.end(), 0, accumulate_func);
}

void printTVectorLongVectorIntString(TVectorLongVectorIntString &inVec)
{
    for (const auto &i : inVec)
    {        
        for (const auto [column, match] : i.second)
        {
            std::cout << i.first << " " << column << " " << match << std::endl;
        }
        
    }
}

std::string escapeRegexWithoutQuestionSymbol(const std::string &input)
{
    // Characters that need to be escaped in a regex pattern    
    const std::string specialChars = "\\^$|*+()[]{}"; // without symbol ?

    std::string escaped;
    for (char c : input)
    {
        if (specialChars.find(c) != std::string::npos)
        {
            escaped += '\\';
        }
        escaped += c;
    }
    return escaped;
}