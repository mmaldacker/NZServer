//
//  template_handler.cpp
//  NZServer
//
//  Created by Maximilian Maldacker on 09/11/2014.
//  Copyright (c) 2014 Maximilian Maldacker. All rights reserved.
//

#include "template_handler.h"

template_handler::template_handler(const std::string & root) : root_(root)
{

}

void template_handler::handle_request(const request & req, reply & rep)
{
    rep.content = template_engine_.generate_html(root_ + req.uri);
    rep.status = reply::ok;
    rep.headers.resize(2);
    rep.headers[0].name = "Content-Length";
    rep.headers[0].value = std::to_string(rep.content.size());
    rep.headers[1].name = "Content-Type";
    rep.headers[1].value = "text/html";

}
