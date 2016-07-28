//
//  file_handler.h
//  NZServer
//
//  Created by Maximilian Maldacker on 08/11/2014.
//  Copyright (c) 2014 Maximilian Maldacker. All rights reserved.
//

#ifndef __NZServer__file_handler__
#define __NZServer__file_handler__

#include "network/request.h"
#include "network/reply.h"
#include "utils/file_service.h"

class file_handler
{
public:
    file_handler(file_store &);
    void handle_request(const request & req, reply & rep);

private:

    file_store & file_store_;
};

#endif /* defined(__NZServer__file_handler__) */
