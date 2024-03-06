#include "testascii.hpp"
#include "cmdoptions.hpp"




int main(int argc, char *argv[])
{
    auto [options, error] = cmdOptionsParse(argc, argv);
    if (error == ErrorCode::Help)
        return 0;
    if (error == ErrorCode::Failure)
        return 1;
    if (options.verbose)
    {
        printVerbose(options);
    }

    TTestASCII testascii{options};
    return testascii.process();    
}
