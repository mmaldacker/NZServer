//
//  template_handler.h
//  NZServer
//
//  Created by Maximilian Maldacker on 09/11/2014.
//  Copyright (c) 2014 Maximilian Maldacker. All rights reserved.
//

#ifndef __NZServer__template_handler__
#define __NZServer__template_handler__

#include "request.h"
#include "reply.h"
#define LUAINTF_LINK_LUA_COMPILED_IN_CXX 0
#include "LuaIntf.h"
#include "database.h"
#include "articles.h"
#include "session.h"
#include "template.h"
#include "file_service.h"

class template_handler
{
public:
    template_handler(file_store &);
    void handle_request(const request & req, reply & rep);

private:
    LuaIntf::LuaContext state_;
    database db_;
    articles articles_;
    session session_;
    template_engine template_engine_;
    file_store & file_store_;
};

#endif /* defined(__NZServer__template_handler__) */
