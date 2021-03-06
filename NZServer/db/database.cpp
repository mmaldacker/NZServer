//
//  database.cpp
//  NZServer
//
//  Created by Maximilian Maldacker on 09/11/2014.
//  Copyright (c) 2014 Maximilian Maldacker. All rights reserved.
//

#include "database.h"

database::database(const std::string & name)
{
    if(sqlite3_open(name.c_str(), &handle_) != SQLITE_OK)
    {
        sqlite3_close(handle_);
        throw std::runtime_error("Could not open DB");
    }
}

database::~database()
{
    sqlite3_close(handle_);
}

query database::exec(const std::string & sql)
{
    sqlite3_stmt * statement;
    sqlite3_prepare(handle_, sql.c_str(), -1, &statement, NULL);

    return query(statement);
}
