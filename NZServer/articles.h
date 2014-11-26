//
//  articles.h
//  NZServer
//
//  Created by Maximilian Maldacker on 10/11/2014.
//  Copyright (c) 2014 Maximilian Maldacker. All rights reserved.
//

#ifndef __NZServer__articles__
#define __NZServer__articles__

#include "database.h"
#define LUAINTF_LINK_LUA_COMPILED_IN_CXX 0
#include "LuaIntf.h"

#include <vector>

class articles
{
public:
    articles(database & db, LuaIntf::LuaContext & state);

    struct article
    {
        std::string short_title;
        std::string title;
        std::string abstract;
        std::string image;
        std::string content;
    };

    article get(const std::string & name);

    class iterator : public LuaIntf::CppFunctor
    {
    public:
        int run(lua_State* L) override;

        friend class articles;
    private:
        int n = 0;
        std::vector<article> articles;
    };

    int get_all(lua_State * state);

private:
    query article_query_;
    query all_articles_query_;
};

#endif /* defined(__NZServer__articles__) */
