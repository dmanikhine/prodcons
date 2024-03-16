#include "concurrency.hpp"
#include "smalltools.hpp"
#include "iostream"



void producer(TReadFile &readFile)
{
    while (true)
    {
        std::pair<bool, TForwardListLongString> result = readFile();
        while (!spsc_queue.push(std::move(result.second)))
            ;
        if (!result.first)
            break;
    }
}

void consumer(TTransformLine &transformLine)
{
    long match_counter{0};
    TForwardListLongForwardListIntString finalList;

    TForwardListLongString listLongString;
    while (!done)
    {
        while (spsc_queue.pop(listLongString))
        {
            std::cout << "consummer" << std::endl;
            TForwardListLongForwardListIntString transformList = transformLine(listLongString);
            TForwardListLongForwardListIntString endList = removeEmptyLine(std::move(transformList));
            match_counter += getMatchCount(endList);
            finalList.splice_after(finalList.cbefore_begin(), endList);            
        }
    }

    while (spsc_queue.pop(listLongString))
    {
        TForwardListLongForwardListIntString transformVec = transformLine(listLongString);
        TForwardListLongForwardListIntString endList = removeEmptyLine(std::move(transformVec));
        match_counter += getMatchCount(endList);
        finalList.splice_after(finalList.cbefore_begin(), endList);            
    }

    std::cout<<std::endl<< match_counter<< std::endl; 
    printTForwardListLongForwardListIntString(finalList);
}