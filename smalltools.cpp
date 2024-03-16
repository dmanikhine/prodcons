#include "smalltools.hpp"
#include <algorithm>
#include <execution>
#include <iostream>

TForwardListLongForwardListIntString removeEmptyLine(TForwardListLongForwardListIntString inList)
{
    inList.remove_if([](std::pair<long, std::forward_list<std::pair<int, std::string>>> i)
                               { return i.second.empty();});
                
    return inList;
}

auto accumulate_func = [](long accumulator, const std::pair<long, std::forward_list<std::pair<int, std::string>>> &el)
{
    return accumulator + 1; //todo denis refactor it, it is just for test. accumulate_func workins not wright.
};

long getMatchCount(TForwardListLongForwardListIntString inList)
{
    return std::accumulate(inList.begin(), inList.end(), 0, accumulate_func);
}

void printTForwardListLongForwardListIntString(TForwardListLongForwardListIntString &inList)
{
    for (const auto &i : inList)
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