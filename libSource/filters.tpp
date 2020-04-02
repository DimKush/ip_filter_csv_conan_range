#pragma once
#include <algorithm>
#include <range/v3/all.hpp>

namespace libSource
{
    template<typename ... Args>
    [[deprecated]]
    vectVectInt filter(vectVectInt & ipBytes, const Args ... args)
    {
        vectVectInt ipSorted;
        
        vectInt forSearch;
            
        (forSearch.emplace_back(args),...);
        
        std::for_each(ipBytes.begin(), ipBytes.end(), [&ipSorted,&forSearch](const vectInt & element)
        {
            bool pos = std::equal(forSearch.begin(), forSearch.end(), element.begin());

            if(pos)
            {
                ipSorted.emplace_back(element);
            }
        });

        return ipSorted;
    }

    template<typename ... Args>
    vectVectInt filterRange(vectVectInt & ipBytes, const Args ... args)
    {
        vectVectInt ipSorted;
        
        vectInt forSearch;
            
        (forSearch.emplace_back(args),...);
        
        ranges::for_each(ipBytes | ranges::view::filter([&forSearch](auto element){ return std::equal(forSearch.begin(), forSearch.end(), element.begin());}),
                                                         [&ipSorted](auto doneElement){ ipSorted.push_back(doneElement); });
    }

};