//
//  database.h
//  NZServer
//
//  Created by Maximilian Maldacker on 09/11/2014.
//  Copyright (c) 2014 Maximilian Maldacker. All rights reserved.
//

#ifndef __NZServer__database__
#define __NZServer__database__

#include <sqlite3.h>
#include <string>
#include "query.h"

class database
{
public:
    database(const std::string & name);
    ~database();

    query exec(const std::string & sql);

private:
    sqlite3 * handle_;
};

#endif /* defined(__NZServer__database__) */
