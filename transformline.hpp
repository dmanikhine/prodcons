#pragma once
#include <fstream>
#include "mytype.hpp"

class TTransformLine
{
public:
    TTransformLine(std::string rgx)
        : m_rgx{rgx} {}
    TTransformLine(const TTransformLine &src) = delete;
    TTransformLine &operator=(const TTransformLine &rhs) = delete;

    TVectorLongVectorIntString operator()(TVectorLongString &inVec);

private:
    std::string m_rgx;
};