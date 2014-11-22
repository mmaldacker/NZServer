//
//  query.h
//  NZServer
//
//  Created by Maximilian Maldacker on 22/11/2014.
//  Copyright (c) 2014 Maximilian Maldacker. All rights reserved.
//

#ifndef __NZServer__query__
#define __NZServer__query__

#include <sqlite3.h>
#include <string>

class database;

class query
{
public:
    ~query();

    bool step();

    void reset();

    template<typename ... Args>
    query & bind(Args &&... args);

    template<typename T>
    T at(int column);

private:
    friend class database;

    query(sqlite3_stmt * statement);
    sqlite3_stmt * statement_;
};

namespace
{

inline void bind_dispatch(sqlite3_stmt * stmt, int index, const std::string & val)
{
    sqlite3_bind_text(stmt,index,val.c_str(),-1,nullptr);
}

inline void bind_helper(sqlite3_stmt*, int)
{
}

template<typename T, typename ... Args>
inline void bind_helper(sqlite3_stmt * stmt, int index, T && val, Args &&... args)
{
    bind_dispatch(stmt, index, std::forward<T>(val));
    bind_helper(stmt, index+1, std::forward<Args>(args)...);
}

}

template<typename ... Args>
query & query::bind(Args &&... args)
{
    bind_helper(statement_, 1, std::forward<Args>(args)...);
    return *this;
}

template<>
inline std::string query::at(int column)
{
    return reinterpret_cast<const char*>(sqlite3_column_text(statement_, column));
}

#endif /* defined(__NZServer__query__) */
