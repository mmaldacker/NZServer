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

class database
{
public:
    class query
    {
    public:
        ~query();
        
        bool step();

        template<typename T>
        T at(int column);

    private:
        friend class database;
        
        query(sqlite3_stmt * statement);
        sqlite3_stmt * statement_;
    };

    database(const std::string & name);
    ~database();

    query exec(const std::string & sql);

private:
    sqlite3 * handle_;
};

template<>
inline std::string database::query::at(int column)
{
    return reinterpret_cast<const char*>(sqlite3_column_text(statement_, column));
}

#endif /* defined(__NZServer__database__) */
