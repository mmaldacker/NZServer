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

class template_engine
{
public:

    void parse_file(const std::string & file);
};

struct template_structure
{
    std::vector<std::string> blocks;
};

#endif /* defined(__NZServer__template__) */
