//
//  file_service.cpp
//  NZServer
//
//  Created by Maximilian Maldacker on 11/11/2014.
//  Copyright (c) 2014 Maximilian Maldacker. All rights reserved.
//

#include "file_service.h"
#include <boost/filesystem.hpp>
#include <boost/log/trivial.hpp>

file_store::file_store(const std::string & root) : root_(root)
{

}

bool file_store::get_file(const std::string & file, std::string & content)
{
    if(!is_modified(file))
    {
        BOOST_LOG_TRIVIAL(info) << "File from cache " << file;

        content = files_[file];
        return true;
    }

    BOOST_LOG_TRIVIAL(info) << "Loading file " << file;

    std::string filename = root_ + file;
    std::ifstream is(filename.c_str(), std::ios::in | std::ios::binary);
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

        files_[file] = content;
        modified_[file] = boost::filesystem::last_write_time({filename});
        
        return true;
    }
    else
    {
        return false;
    }
}

std::vector<std::string> file_store::get_files(const std::string & dir)
{
    std::vector<std::string> files;

    using namespace boost::filesystem;
    path p(root_ + dir);

    if (exists(p) && is_directory(p))
    {
        std::vector<path> paths;
        std::copy(directory_iterator(p), directory_iterator(), std::back_inserter(paths));

        for(auto && p : paths)
        {
            auto filename = dir + "/" + p.filename().string();
            files.push_back(filename);
        }
    }

    return files;
}

bool file_store::is_modified(const std::string &file) const
{
    using namespace boost::filesystem;

    std::string filename = root_ + file;
    path p(filename);

    auto m = modified_.find(file);
    if(m != modified_.end())
    {
        return last_write_time(p) > m->second;
    }

    return true;
}

const std::string & file_store::get_root() const
{
    return root_;
}
