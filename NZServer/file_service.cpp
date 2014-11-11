//
//  file_service.cpp
//  NZServer
//
//  Created by Maximilian Maldacker on 11/11/2014.
//  Copyright (c) 2014 Maximilian Maldacker. All rights reserved.
//

#include "file_service.h"

file_store::file_store(const std::string & root) : root_(root)
{

}

bool file_store::get_file(const std::string & file, std::string & content)
{
    std::ifstream is((root_ + file).c_str(), std::ios::in | std::ios::binary);
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

const std::string & file_store::get_root() const
{
    return root_;
}
