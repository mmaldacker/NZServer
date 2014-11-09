//
//  request_handler.h
//  NZServer
//
//  Created by Maximilian Maldacker on 08/11/2014.
//  Copyright (c) 2014 Maximilian Maldacker. All rights reserved.
//

#ifndef __NZServer__request_handler__
#define __NZServer__request_handler__

#include "request.h"
#include "reply.h"
#include "file_handler.h"
#include "template_handler.h"

class request_handler
{
public:
    void handle_request(const request & req, reply & rep);

private:
    file_handler file_handler_;
    template_handler template_handler_;
};

#endif /* defined(__NZServer__request_handler__) */
