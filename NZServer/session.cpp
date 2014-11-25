//
//  session.cpp
//  NZServer
//
//  Created by Maximilian Maldacker on 22/11/2014.
//  Copyright (c) 2014 Maximilian Maldacker. All rights reserved.
//

#include "session.h"
#include <vector>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <boost/log/trivial.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/algorithm/string.hpp>

session::session(LuaIntf::LuaContext & state)
{
    LuaBinding(state)
    .beginModule("session")
    .addFunction("login", [&](const std::string & name, const std::string password) { return login(name, password); })
    .addFunction("get_session_cookie", [&](const std::string & name){ return get_session_cookie(name); })
    .addFunction("is_logged_in", [&](const std::string & cookie) { return is_logged_in(cookie); })
    .endModule();
}

bool session::login(const std::string name, const std::string password)
{
    auto uuid = boost::uuids::random_generator()();
    sessions_[name] = boost::lexical_cast<std::string>(uuid);

    return true;
}

std::string session::get_session_cookie(const std::string name)
{
    return "sid=" + sessions_[name] + "; path=/";
}

bool session::is_logged_in(const std::string cookie)
{
    std::vector<std::string> pairs;
    boost::split(pairs,cookie,boost::is_any_of(";"));
    for(auto && pair : pairs)
    {
        auto eq = pair.find('=');
        auto key = pair.substr(0, eq);
        auto value = pair.substr(eq+1);

        if(key == "sid")
        {
            for(auto && s : sessions_) if(s.second == value) return true;
        }
    }

    return false;
}