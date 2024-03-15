#include "concurrency.hpp"
#include "smalltools.hpp"
#include "iostream"



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

void consumer(TTransformLine &transformLine)
{
    long match_counter{0};
    TVectorLongVectorIntString finalVec;

    TVectorLongString vectorLongString;
    while (!done)
    {
        while (spsc_queue.pop(vectorLongString))
        {
            std::cout << "consummer" << std::endl;
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