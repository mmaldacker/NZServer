//
//  file_service.h
//  NZServer
//
//  Created by Maximilian Maldacker on 11/11/2014.
//  Copyright (c) 2014 Maximilian Maldacker. All rights reserved.
//

#ifndef __NZServer__file_service__
#define __NZServer__file_service__

#include <string>
#include <fstream>
#include <vector>
#include <map>

// FIXME not thread safe!
class file_store
{
public:
    file_store(const std::string & root);

    bool get_file(const std::string & file, std::string & content);
    std::vector<std::string> get_files(const std::string & dir);
    bool is_modified(const std::string & file) const;
    const std::string & get_root() const;

private:
    std::string root_;
    std::map<std::string, std::time_t> modified_;
    std::map<std::string, std::string> files_;

};
#endif /* defined(__NZServer__file_service__) */
