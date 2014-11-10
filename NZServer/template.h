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

struct template_structure
{
    std::string code;
    std::vector<std::string> blocks;
};

class template_engine
{
public:
    template_engine(sel::State & state);

    std::string generate_html(const std::string & file);
    void parse_file(const std::string & file);

private:
    std::string run_template(const template_structure & structure);
    void gather(int x, const std::string data);

    sel::State & state_;
    std::map<std::string, template_structure> templates_;
    std::map<int, std::string> computed_data_;
};

#endif /* defined(__NZServer__template__) */
