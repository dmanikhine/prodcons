#include "transformline.hpp"
#include <utility>
#include <iostream>
#include <algorithm>
#include <execution>
#include <regex>

TForwardListLongForwardListIntString TTransformLine::operator()(TForwardListLongString &inList)
{
    TForwardListLongForwardListIntString resList;

    std::transform(std::execution::par_unseq, inList.cbegin(), inList.cend(),
                   resList.begin(),
                   [&lambda_rgx = m_rgx](std::pair<long, std::string> x)
                   {
                       std::forward_list<std::pair<int,std::string>> matches;
                       std::regex rx(lambda_rgx);
                       for (auto it = std::sregex_iterator(x.second.begin(), x.second.end(), rx);
                            it != std::sregex_iterator();
                            ++it)
                       {
                           matches.push_front(std::pair{(it->position())+1, it->str()});
                       }
                       matches.reverse();
                       return std::pair(x.first, matches);
                   });
    return resList;
}