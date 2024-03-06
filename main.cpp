#include <boost/thread/thread.hpp>
#include <boost/lockfree/spsc_queue.hpp>
#include <boost/atomic.hpp>

#include <iostream>
#include <algorithm>
#include "cmdoptions.hpp"
#include "readfile.hpp"
#include "transformline.hpp"
#include "smalltools.hpp"


boost::lockfree::spsc_queue<TVectorLongString, boost::lockfree::capacity<1024>> spsc_queue;

void producer(TReadFile &readFile)
{
    while (true)
    {
        std::pair<bool, TVectorLongString> result = readFile();
        while (!spsc_queue.push(std::move(result.second)))
            ;
        if (!result.first)
            break;
    }
}

boost::atomic_bool done(false);

void consumer(TTransformLine &transformLine)
{
    long match_counter{0};
    TVectorLongVectorIntString finalVec;

    TVectorLongString vectorLongString;
    while (!done)
    {
        while (spsc_queue.pop(vectorLongString))
        {
            TVectorLongVectorIntString transformVec = transformLine(vectorLongString);
            TVectorLongVectorIntString endVec = removeEmptyLine(std::move(transformVec));
            match_counter += getMatchCount(endVec);
            finalVec.insert(
                finalVec.end(),
                std::make_move_iterator(endVec.begin()),
                std::make_move_iterator(endVec.end()));
        }
    }

    while (spsc_queue.pop(vectorLongString))
    {
        TVectorLongVectorIntString transformVec = transformLine(vectorLongString);
        TVectorLongVectorIntString endVec = removeEmptyLine(std::move(transformVec));
        match_counter += getMatchCount(endVec);
        finalVec.insert(
            finalVec.end(),
            std::make_move_iterator(endVec.begin()),
            std::make_move_iterator(endVec.end()));
    }

    std::cout<<std::endl<< match_counter<< std::endl; 
    printTVectorLongVectorIntString(finalVec);
}

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

    std::string inputFile = options.mainOptions["filepathname"];
    std::ifstream ifs(inputFile);
    if (ifs.fail())
    {
        std::cerr << "Failed to open file: " << inputFile << std::endl;
        return 1;
    }

    TReadFile rf{ifs};
    boost::thread producer_thread(producer, std::ref(rf));
    
    std::string mask=escapeRegexWithoutQuestionSymbol(options.mainOptions["searchmask"]);
    std::replace(mask.begin(), mask.end(), '?', '.');

    TTransformLine tl{mask};
    boost::thread consumer_thread(consumer, std::ref(tl));

    producer_thread.join();
    done = true;
    consumer_thread.join();
}
