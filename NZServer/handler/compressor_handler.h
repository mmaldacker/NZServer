//
//  compressor_handler.h
//  NZServer
//
//  Created by Maximilian Maldacker on 12/11/2014.
//  Copyright (c) 2014 Maximilian Maldacker. All rights reserved.
//

#ifndef __NZServer__compressor_handler__
#define __NZServer__compressor_handler__

#include <zlib.h>
#include "network/reply.h"
#include "network/request.h"

class compressor_handler
{
public:
    void handle_request(const request & req, reply & rep);
};

#endif /* defined(__NZServer__compressor_handler__) */
