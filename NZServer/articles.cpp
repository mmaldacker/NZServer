//
//  articles.cpp
//  NZServer
//
//  Created by Maximilian Maldacker on 10/11/2014.
//  Copyright (c) 2014 Maximilian Maldacker. All rights reserved.
//

#include "articles.h"

articles::articles(database & db, LuaIntf::LuaContext & state)
    : article_query_(db.exec("select long_title, content from articles where short_title = ?"))
    , all_articles_query_(db.exec("select long_title, short_title, image from articles"))
{
    LuaIntf::LuaBinding(state)
    .beginClass<article>("article")
    .addVariable("short_title", &article::short_title)
    .addVariable("title", &article::title)
    .addVariable("content", &article::content)
    .addVariable("image", &article::image)
    .addVariable("abstract", &article::abstract)
    .addStaticFunction("get_for", [&](const std::string & name) { return get(name); })
    .addStaticFunction("get_all", [&](lua_State * state) { return get_all(state); })
    .endClass();
}

articles::article articles::get(const std::string & name)
{
    article_query_.reset();
    article_query_.bind(name);

    if(article_query_.step())
    {
        article a;

        a.title = article_query_.at<std::string>(0);
        a.content = article_query_.at<std::string>(1);
        a.short_title = name;

        return a;
    }

    return {};
}

int articles::iterator::run(lua_State* state)
{
    if(n < articles.size())
    {
        LuaIntf::LuaType<article*>::push(state, &articles[n++]);
        return 1;
    }
    else
    {
        return 0;
    }

}

int articles::get_all(lua_State * state)
{
    iterator * iterator_ = new iterator();
    iterator_->n = 0;

    all_articles_query_.reset();
    while(all_articles_query_.step())
    {
        article a;
        a.title = all_articles_query_.at<std::string>(0);
        a.short_title = all_articles_query_.at<std::string>(1);
        a.image = all_articles_query_.at<std::string>(2);

        iterator_->articles.push_back(a);
    }

    LuaIntf::CppFunctor::pushToStack(state, iterator_);
    return 1;
}
