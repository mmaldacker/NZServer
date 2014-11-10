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
#include "selene.h"

class articles
{
public:
    articles(database & db, sel::State & state);

    struct article
    {
        std::string title;
        std::string content;
    };

    article * get(const std::string name);
    
private:
    database & db_;
    article current_article_;
};

#endif /* defined(__NZServer__articles__) */
