//
//  utils.h
//  NZServer
//
//  Created by Maximilian Maldacker on 09/11/2014.
//  Copyright (c) 2014 Maximilian Maldacker. All rights reserved.
//

#ifndef NZServer_utils_h
#define NZServer_utils_h

#include <fstream>

static bool load_file(const std::string & file, std::string & content)
{
    std::ifstream is(file.c_str(), std::ios::in | std::ios::binary);
    if (is)
    {
        // get length of file:
        is.seekg(0, is.end);
        long long length = is.tellg();
        is.seekg(0, is.beg);

        content.resize(length, ' '); // reserve space
        char* begin = &content[0];

        is.read(begin, length);
        is.close();

        return true;
    }
    else
    {
        return false;
    }
}

#endif
