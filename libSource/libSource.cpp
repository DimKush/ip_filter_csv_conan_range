#include <range/v3/all.hpp>
#include "libSource.h"

#include <algorithm>
#include <iostream>
#include <fstream>
#include <regex>


namespace libSource
{
    vectStr setListOfFilesInVector(int &argc, char **argv)
    {
        vectStr bufferOfFilesNames;

        if(argc <= 1)
        {
            std::cout << "File list in command line is empty." << '\n';
            std::exit(0);
        }

        for(auto i = 1 ; i < argc; i++)
        {
            bufferOfFilesNames.emplace_back(std::string(*(argv + i)));
        }

        return bufferOfFilesNames;
    }


    void checkFilesForOpenAndFillMainContent(vectStr const & bufferOfFilesNames, std::string & mainContent)
    {
        std::ifstream file;
        std::string strTmp;

        ranges::for_each(bufferOfFilesNames , [&file, &strTmp, &mainContent](auto element)
        {
            file.open(element);

            if(!file)
                std::cout << "Cant find file : " << element;
            else
            {   
                strTmp.assign(std::istreambuf_iterator<char>(file),std::istreambuf_iterator<char>());
                mainContent += strTmp;

                file.close();
            }            
        });
    }

    void writeInFile(const vectVectInt & ipInFile)
    {
        std::ofstream file("ip_filter_csv_done.csv");

        for(auto ip = ipInFile.cbegin(); ip != ipInFile.cend(); ++ip)
        {
            for(auto ip_part = ip->cbegin(); ip_part != ip->cend(); ++ip_part)
            {
                if (ip_part != ip->cbegin())
                {
                    file << ".";
                }
                file << *ip_part;
            }
            file << "\n";
        }
    }

    vectVectInt& concatenateIp(vectVectInt &basicIp,vectVectInt &ip)
    {
        basicIp.insert(basicIp.end(), ip.begin(),ip.end());
        return basicIp;
    } 


    vectStr split(std::string const & str, char symbol)
    {
        vectStr tmpContainer;

        std::string::size_type  beginPos = 0, endPos = str.find_first_of(symbol);

        while(endPos != std::string::npos)
        {
            tmpContainer.push_back(str.substr(beginPos,endPos - beginPos));

            beginPos = endPos + 1;
            endPos = str.find_first_of(symbol, beginPos);
        }

        tmpContainer.push_back(str.substr(beginPos));

        return tmpContainer;
    }

    bool lexiCompare(const vectInt &a, const vectInt &b)
    {
        return ranges::lexicographical_compare(b,a);
    }

    void sortIp(vectVectInt & ip)
    {
        ranges::sort(ip, lexiCompare);
    }

    vectVectInt filter_any(vectVectInt & vInside, int param)
    {
        vectVectInt ipSorted;
    
        std::for_each(vInside.begin(), vInside.end(), [&ipSorted, param](const vectInt & element)
        {
            auto pos = std::any_of(element.begin(),element.end(),[=](int byteStr)
            {
                return param == byteStr;
            });
    
            if(pos)
            {
                ipSorted.emplace_back(element);
            }
        });
        
        return ipSorted;
    }

    vectVectInt convertToInt(const vectVectStr &ipSorted)
    {
        vectVectInt ip;
        vectInt ipByte; 

        ranges::for_each(ipSorted, [&ip, &ipByte](std::vector<std::string> element)
        {  
            ipByte.clear();

            ranges::for_each(element, [&ipByte](auto byteStr)
            {
                ipByte.emplace_back(std::stoi(byteStr));
            });

            ip.emplace_back(ipByte);
        });

        return ip;
    }

    vectVectInt prepareIpContainer(const vectStr &rows)
    {
        std::string element;
        vectVectStr ipBytesStr;
        
        std::regex regIp("^((25[0-5]|2[0-4][\\d]|1[\\d][\\d]|[\\d]?[\\d])[\\.,\\s]){3}(25[0-5]|2[0-4][\\d]|1[\\d][\\d]|[\\d]?[\\d])$");
        
        for(auto i = rows.begin() ; i != rows.end() ; i++)
        {
            element = split(*(i),';').at(0);

            if(std::regex_match(element, regIp))
            {
                ipBytesStr.push_back(split(element, '.'));
            }
            else
            {
                std::cout << "Elemnent : " << element << " was dropped.\n";
            }
        }

        return convertToInt(ipBytesStr);
    }
};