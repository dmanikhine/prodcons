#include "transformline.hpp"
#include <utility>
#include <iostream>
#include <algorithm>
#include <execution>
#include <regex>

TVectorLongVectorIntString TTransformLine::operator()(TVectorLongString &inVec)
{
    TVectorLongVectorIntString resVec(inVec.size());

    std::transform(std::execution::par, inVec.cbegin(), inVec.cend(),
                   resVec.begin(),
                   [&lambda_rgx = m_rgx](std::pair<long, std::string> x)
                   {
                       std::vector<std::pair<int,std::string>> matches;
                       std::regex rx(lambda_rgx);
                       for (auto it = std::sregex_iterator(x.second.begin(), x.second.end(), rx);
                            it != std::sregex_iterator();
                            ++it)
                       {
                           matches.push_back(std::pair{(it->position())+1, it->str()});
                       }
                       return std::pair(x.first, matches);
                   });
    return resVec;
}