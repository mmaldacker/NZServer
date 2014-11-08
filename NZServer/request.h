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

    void clear()
    {
        method.clear();
        uri.clear();
        http_version_major = 0;
        http_version_minor = 0;
        headers.clear();
    }
};

inline std::ostream & operator<<(std::ostream & o, const request & req)
{
    o << "URI " << req.uri << " METHOD " << req.method << " | ";
    for(auto && h : req.headers)
    {
        o << h.name << "=" << h.value << " | ";
    }

    return o;
}

#endif /* defined(__NZServer__request__) */
