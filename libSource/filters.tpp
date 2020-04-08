#pragma once
#include <algorithm>
#include <range/v3/all.hpp>
#include <iostream>

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

        ranges::for_each(ipBytes | ranges::view::filter([&forSearch](auto intVal){ return std::equal(forSearch.begin(), forSearch.end(),intVal.begin());}),
                                                        [&ipSorted] (auto element){ipSorted.emplace_back(element);});

        return ipSorted; 
    
    }

    template<typename Type>
    void show(std::vector<Type> const& showing)
    {
       int val = 0; 
       
       ranges::for_each(showing, [&val](auto element)
       {
           char symbol = ' ';

           if(val < 3) symbol = '.'; 
           else { symbol = ' '; }
           
           val++;
           std::cout << element << symbol;
           

       });
    }

    template<typename Type>
    void show(Type const& showing)
    {
        std::cout << showing << '\n';
    }

    template<typename Type>
    void showAllContainer(std::vector<std::vector<Type>> container)
    {
       ranges::for_each(container, 
       [](auto element)
       {
           show(element);
           std::cout << '\n';
       });
    }
};