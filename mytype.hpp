#pragma once
#include <forward_list>
#include <string>

using TForwardListLongString = std::forward_list<std::pair<long,std::string>>;
using TForwardListLongForwardListIntString = std::forward_list<std::pair<long,std::forward_list<std::pair<int,std::string>>>>;