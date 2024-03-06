#include "cmdoptions.hpp"
#include "iostream"

using Todsc = boost::program_options::options_description;
namespace bpo = boost::program_options;

Todsc makeDescription(Options &options)
{
    Todsc odsc("\n"
               "How to use:\n"
               "mtfind [Options] [-v] \n"
               "mtfind [-h|--help]  \n"
               " \n"
               "Options");

    odsc.add_options()
    ("verbose,v", bpo::bool_switch(&options.verbose)->default_value(false), "verbose (print command line options values)")
    ("filepathname,f", bpo::value<std::string>(&options.mainOptions["filepathname"]), "path and name of output file")
    ("searchmask,s", bpo::value<std::string>(&options.mainOptions["searchmask"]), "search mask '?' mean any symbol, not forget to use double \\\\ for \\ symbol")
    

    ("help,h", "Print help mesage");
    

    Todsc example("Example:\n"
                  "mtfind --verbose --filepathname testfile --searchmask \"?ad\" \n"
                  "\n");
    odsc.add(example);
    return odsc;
}

std::pair<Options, ErrorCode> cmdOptionsParse(int argc, char *argv[])
{
    Options options;
    Todsc odsc = makeDescription(options);
    bpo::variables_map vm;
    try {
    bpo::store(bpo::parse_command_line(argc, argv, odsc), vm);
    bpo::notify(vm);
    }
    catch (bpo::error &e) {
         /* Invalid options */
        std::cerr << "ERROR: " << e.what() << std::endl << std::endl;
        return {options, ErrorCode::Failure};
    }
    if (vm.count("help"))
    {
        std::cout << odsc << "\n";
        return {options, ErrorCode::Help};
    }
    

    auto [optionName, error] =options.check(options.mainOptions);
    if (error){
        std::cerr << "Error! Command line have no value for option: " << optionName;
        std::cout << std::endl;
        std::cout << odsc << "\n";
        return {options, ErrorCode::Failure};
    }

    return {options, ErrorCode::Success};
}

void printVerbose(Options &options)
{    
    std::cout << "====================" << std::endl;
    std::cout << "filepathname: " << options.mainOptions["filepathname"] << std::endl;
    std::cout << "serachmask: " << options.mainOptions["searchmask"] << std::endl;
    std::cout << "====================" << std::endl;
    std::cout << std::endl;
}


