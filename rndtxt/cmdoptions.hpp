#pragma once
#include <boost/program_options.hpp>
#include <string>

struct Options
{
    std::map<std::string, std::string> mainOptions;

    Options()
        : mainOptions({{"filepathname", ""}}) {}

    bool verbose = false;
    ulong filelength;
    uint linelength;

    std::pair<std::string, bool> check(std::map<std::string, std::string> &options) const
    {
        for (auto const &[optionName, value] : options)
        {
            if (value.empty())
                return {optionName, true};
        }
        return {"", false};
    }
};

enum class ErrorCode
{
    Success = 0,
    Help = 1,
    Failure = 2
};

std::pair<Options, ErrorCode> cmdOptionsParse(int argc, char *argv[]);

void printVerbose(Options &option);
