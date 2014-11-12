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
    : state_(true)
    , db_(store.get_root() + "/db/test.db")
    , articles_(db_, state_)
    , template_engine_(state_, store)
    , file_store_(store)
{

}

void template_handler::handle_request(const request & req, reply & rep)
{
    std::deque<std::string> keys;
    boost::split(keys,req.uri,boost::is_any_of("/"));
    keys.pop_front();

    assert(keys.size());

    auto name = keys.front(); keys.pop_front();

    rep.content = template_engine_.run_template(name, {std::begin(keys), std::end(keys)});

    rep.status = reply::ok;
    rep.headers.resize(2);
    rep.headers[0].name = "Content-Length";
    rep.headers[0].value = std::to_string(rep.content.size());
    rep.headers[1].name = "Content-Type";
    rep.headers[1].value = "text/html";
}
