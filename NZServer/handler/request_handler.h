//
//  request_handler.h
//  NZServer
//
//  Created by Maximilian Maldacker on 08/11/2014.
//  Copyright (c) 2014 Maximilian Maldacker. All rights reserved.
//

#ifndef __NZServer__request_handler__
#define __NZServer__request_handler__

#include "network/request.h"
#include "network/reply.h"
#include "file_handler.h"
#include "template_handler.h"
#include "utils/file_service.h"
#include "compressor_handler.h"

class request_handler
{
public:
    request_handler();

    void handle_request(const request & req, reply & rep);

private:
    file_store file_store_;
    file_handler file_handler_;
    template_handler template_handler_;
    compressor_handler compressor_handler_;
};

#endif /* defined(__NZServer__request_handler__) */
