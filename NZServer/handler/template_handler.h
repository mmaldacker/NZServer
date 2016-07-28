//
//  template_handler.h
//  NZServer
//
//  Created by Maximilian Maldacker on 09/11/2014.
//  Copyright (c) 2014 Maximilian Maldacker. All rights reserved.
//

#ifndef __NZServer__template_handler__
#define __NZServer__template_handler__

#include "network/request.h"
#include "network/reply.h"
#define LUAINTF_LINK_LUA_COMPILED_IN_CXX 0
#include "LuaIntf/LuaIntf.h"
#include "db/database.h"
#include "service/articles.h"
#include "service/session.h"
#include "template/template.h"
#include "utils/file_service.h"

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
