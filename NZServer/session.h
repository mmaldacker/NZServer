//
//  session.h
//  NZServer
//
//  Created by Maximilian Maldacker on 22/11/2014.
//  Copyright (c) 2014 Maximilian Maldacker. All rights reserved.
//

#ifndef __NZServer__session__
#define __NZServer__session__

#include "selene.h"

#include <map>

class session
{
public:
    session(sel::State & state);

    bool login(const std::string name, const std::string password);
    std::string get_session_cookie(const std::string name);
    bool is_logged_in(const std::string cookie);

private:
    std::map<std::string, std::string> sessions_;
};

#endif /* defined(__NZServer__session__) */
