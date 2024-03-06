#include <boost/thread/thread.hpp>

#include <iostream>
#include "cmdoptions.hpp"
#include "readfile.hpp"
#include "smalltools.hpp"
#include "concurrency.hpp"


int main(int argc, char *argv[])
{
    //get command line options
    auto [options, error] = cmdOptionsParse(argc, argv);
    if (error == ErrorCode::Help)
        return 0;
    if (error == ErrorCode::Failure)
        return 1;
    if (options.verbose)
    {
        printVerbose(options);
    }

    //open test file
    std::string inputFile = options.mainOptions["filepathname"];
    std::ifstream ifs(inputFile);
    if (ifs.fail())
    {
        std::cerr << "Failed to open file: " << inputFile << std::endl;
        return 1;
    }

    TReadFile rf{ifs}; 
    boost::thread producer_thread(producer, std::ref(rf));
    
    // make regex string
    std::string mask=escapeRegexWithoutQuestionSymbol(options.mainOptions["searchmask"]);
    std::replace(mask.begin(), mask.end(), '?', '.');
    TTransformLine tl{mask};

    boost::thread consumer_thread(consumer, std::ref(tl));

    producer_thread.join();
    done = true;
    consumer_thread.join();
}
