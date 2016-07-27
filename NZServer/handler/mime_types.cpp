//
//  mime_types.cpp
//  NZServer
//
//  Created by Maximilian Maldacker on 08/11/2014.
//  Copyright (c) 2014 Maximilian Maldacker. All rights reserved.
//

#include "mime_types.h"

namespace mime_types
{

struct mapping
{
    const char* extension;
    const char* mime_type;
} mappings[] =
{
    { "gif", "image/gif" },
    { "htm", "text/html" },
    { "html", "text/html" },
    { "jpg", "image/jpeg" },
    { "png", "image/png" },
    { "css", "text/css" },
    { "js", "text/javascript" }
};

std::string extension_to_type(const std::string& extension)
{
    for (mapping m: mappings)
    {
        if (m.extension == extension)
        {
            return m.mime_type;
        }
    }
    
    return "text/plain";
}

}
