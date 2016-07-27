//
//  request.h
//  NZServer
//
//  Created by Maximilian Maldacker on 08/11/2014.
//  Copyright (c) 2014 Maximilian Maldacker. All rights reserved.
//

#ifndef __NZServer__request__
#define __NZServer__request__

#include <string>
#include <vector>
#include <ostream>
#include "header.h"

/// A request received from a client.
struct request
{
    std::string method;
    std::string uri;
    int http_version_major;
    int http_version_minor;
    std::vector<header> headers;
    std::string content;

    void clear()
    {
        method.clear();
        uri.clear();
        http_version_major = 0;
        http_version_minor = 0;
        headers.clear();
        content.clear();
    }
};

#endif /* defined(__NZServer__request__) */
