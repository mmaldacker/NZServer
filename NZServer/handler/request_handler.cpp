//
//  request_handler.cpp
//  NZServer
//
//  Created by Maximilian Maldacker on 08/11/2014.
//  Copyright (c) 2014 Maximilian Maldacker. All rights reserved.
//

#include "request_handler.h"
#include <boost/log/trivial.hpp>

request_handler::request_handler()
: file_store_("/Users/mmaldacker/NZServer")
, file_handler_(file_store_)
, template_handler_(file_store_)
{
    
}

void request_handler::handle_request(const request & req, reply & rep)
{
    BOOST_LOG_TRIVIAL(info) << "Handling request " << req.uri;

    const std::string file_request = "/file";

    if (req.uri.compare(0, file_request.length(), file_request) == 0)
    {
        file_handler_.handle_request(req, rep);
    }
    else
    {
        template_handler_.handle_request(req, rep);
    }

    compressor_handler_.handle_request(req, rep);
}
