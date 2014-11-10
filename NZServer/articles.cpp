//
//  articles.cpp
//  NZServer
//
//  Created by Maximilian Maldacker on 10/11/2014.
//  Copyright (c) 2014 Maximilian Maldacker. All rights reserved.
//

#include "articles.h"

articles::articles(database & db, sel::State & state) : db_(db)
{
    state["article"].SetClass<article>("title", &article::title);
    state["article"].SetClass<article>("content", &article::content);
    state["articles"].SetObj(*this, "get", &articles::get);
}

articles::article * articles::get(const std::string name)
{
    auto q = db_.exec("select long_title, content from articles where short_title = '" + name + "'");

    if(q.step())
    {
        current_article_ = {q.at<std::string>(0), q.at<std::string>(1)};
    }

    return &current_article_;
}
