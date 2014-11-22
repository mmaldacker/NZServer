//
//  template.h
//  NZServer
//
//  Created by Maximilian Maldacker on 09/11/2014.
//  Copyright (c) 2014 Maximilian Maldacker. All rights reserved.
//

#ifndef __NZServer__template__
#define __NZServer__template__

#include "selene.h"
#include <vector>
#include "file_service.h"
#include "request.h"

struct template_structure
{
    std::string code;
    std::vector<std::string> blocks;
    std::string name;

    void clear()
    {
        code.clear();
        blocks.clear();
    }
};

class template_engine
{
public:
    template_engine(sel::State & state, file_store &);

    bool run_template(const std::string & file,
                      const std::vector<std::string> & arguments,
                      const request & req,
                      std::string & content,
                      std::vector<header> & headers);

private:
    bool run_template(const template_structure & structure,
                      const std::vector<std::string> & arguments,
                      const request & req,
                      std::string & content,
                      std::vector<header> & headers);

    void parse_file(const std::string & file);
    void parse_file(const std::string & file, template_structure & structure);

    void gather(int x, const std::string data);
    void set_header(const std::string key, const std::string value);

    sel::State & state_;
    std::map<std::string, template_structure> templates_;
    std::map<int, std::string> computed_data_;
    std::vector<header> * extra_headers_;
    file_store & file_store_;
};

#endif /* defined(__NZServer__template__) */
