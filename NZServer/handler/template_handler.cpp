//
//  template_handler.cpp
//  NZServer
//
//  Created by Maximilian Maldacker on 09/11/2014.
//  Copyright (c) 2014 Maximilian Maldacker. All rights reserved.
//

#include "template_handler.h"
#include <boost/algorithm/string.hpp>

template_handler::template_handler(file_store & store)
    : db_(store.get_root() + "/db/test.db")
    , articles_(db_, state_)
    , session_(state_)
    , template_engine_(state_, store)
    , file_store_(store)
{
    state_.importLibs();
}

void template_handler::handle_request(const request & req, reply & rep)
{
    std::deque<std::string> keys;
    boost::split(keys,req.uri,boost::is_any_of("/"));
    keys.pop_front();

    assert(keys.size());

    auto name = keys.front(); keys.pop_front();

    if(template_engine_.run_template(name, {std::begin(keys), std::end(keys)}, req, rep.content, rep.headers))
    {
        rep.status = reply::ok;
        rep.headers.push_back({"Content-Length", std::to_string(rep.content.size())});
        rep.headers.push_back({"Content-Type", "text/html"});
    }
    else
    {
        rep = reply::stock_reply(reply::internal_server_error);
    }
}
