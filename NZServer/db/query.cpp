//
//  query.cpp
//  NZServer
//
//  Created by Maximilian Maldacker on 22/11/2014.
//  Copyright (c) 2014 Maximilian Maldacker. All rights reserved.
//

#include "query.h"

query::query(sqlite3_stmt * statement) : statement_(statement)
{

}

query::~query()
{
    sqlite3_finalize(statement_);
}

bool query::step()
{
    // FIXME have to handle error, done and busy!!
    int status = sqlite3_step(statement_);
    return status == SQLITE_ROW;
}

void query::reset()
{
    sqlite3_reset(statement_);
}
