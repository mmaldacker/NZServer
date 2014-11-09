//
//  template_handler.h
//  NZServer
//
//  Created by Maximilian Maldacker on 09/11/2014.
//  Copyright (c) 2014 Maximilian Maldacker. All rights reserved.
//

#ifndef __NZServer__template_handler__
#define __NZServer__template_handler__

#include "request.h"
#include "reply.h"

class template_handler
{
public:
    void handle_request(const request & req, reply & rep);
};

#endif /* defined(__NZServer__template_handler__) */
