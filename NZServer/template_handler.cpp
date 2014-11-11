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
    std::vector<std::string> keys;
    boost::split(keys,req.uri,boost::is_any_of("/"));

    assert(keys.size() > 3);

    if(keys[2] == "articles")
    {
        state_["article_name"] = keys[3];
        rep.content = template_engine_.generate_html("articles.tpl");
    }

    rep.status = reply::ok;
    rep.headers.resize(2);
    rep.headers[0].name = "Content-Length";
    rep.headers[0].value = std::to_string(rep.content.size());
    rep.headers[1].name = "Content-Type";
    rep.headers[1].value = "text/html";
}
