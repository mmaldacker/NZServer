//
//  request_handler.cpp
//  NZServer
//
//  Created by Maximilian Maldacker on 08/11/2014.
//  Copyright (c) 2014 Maximilian Maldacker. All rights reserved.
//

#include "request_handler.h"
#include <boost/log/trivial.hpp>

void request_handler::handle_request(const request & req, reply & rep)
{
    BOOST_LOG_TRIVIAL(info) << "Handling request " << req.uri;

    const std::string file_request = "/file";
    const std::string template_request = "/template";

    if (req.uri.compare(0, file_request.length(), file_request) == 0)
    {
        file_handler_.handle_request(req, rep);
    }
    else if(req.uri.compare(0, template_request.length(), template_request) == 0)
    {
        template_handler_.handle_request(req, rep);
    }
    else
    {
        rep = reply::stock_reply(reply::not_found);
    }
}