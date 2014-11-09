//
//  template.cpp
//  NZServer
//
//  Created by Maximilian Maldacker on 09/11/2014.
//  Copyright (c) 2014 Maximilian Maldacker. All rights reserved.
//

#include "template.h"
#include <fstream>
#include <boost/log/trivial.hpp>

void template_engine::parse_file(const std::string &file)
{
    std::ifstream is(file, std::ifstream::binary);
    if (is)
    {
        // get length of file:
        is.seekg(0, is.end);
        long long length = is.tellg();
        is.seekg(0, is.beg);

        std::string str;
        str.resize(length, ' '); // reserve space
        char* begin = &str[0];

        is.read(begin, length);
        is.close();

        std::string luaCode;

        std::string::size_type codeLoc = 0, varLoc = 0;
        while(codeLoc != std::string::npos && varLoc != std::string::npos)
        {
            codeLoc = str.find("{%");
            varLoc = str.find("{{");

            if(codeLoc < varLoc)
            {
                auto end = str.find("%}");
                luaCode += str.substr(codeLoc, end);
            }
            else
            {
                auto end = str.find("}}");
            }
        }

        BOOST_LOG_TRIVIAL(info) << "Lua code is " << luaCode;
    }
    else
    {
    }
}