#include "utils/io_testing.hpp"

/*
std::vector<uint> numToDisp(const std::vector<uint>& outs, char in)
{
    std::vector<uint> result;
    for(int i =0; i < 1<<outs.size(); i = i <<1)
    {
        if(in & i)
        {
            result.push_back(outs.at(i));
        }
    }
    return result;
}*/