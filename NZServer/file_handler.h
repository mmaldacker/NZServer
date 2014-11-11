//
//  file_handler.h
//  NZServer
//
//  Created by Maximilian Maldacker on 08/11/2014.
//  Copyright (c) 2014 Maximilian Maldacker. All rights reserved.
//

#ifndef __NZServer__file_handler__
#define __NZServer__file_handler__

#include "request.h"
#include "reply.h"
#include "file_service.h"

class file_handler
{
public:
    file_handler(file_store &);
    void handle_request(const request & req, reply & rep);

private:
    bool url_decode(const std::string& in, std::string& out);

    file_store & file_store_;
};

#endif /* defined(__NZServer__file_handler__) */
