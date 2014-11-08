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
    BOOST_LOG_TRIVIAL(info) << "Handling request";
    rep = reply::stock_reply(reply::ok);
}