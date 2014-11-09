//
//  mime_types.h
//  NZServer
//
//  Created by Maximilian Maldacker on 08/11/2014.
//  Copyright (c) 2014 Maximilian Maldacker. All rights reserved.
//

#ifndef __NZServer__mime_types__
#define __NZServer__mime_types__

#include <string>

namespace mime_types
{

/// Convert a file extension into a MIME type.
std::string extension_to_type(const std::string& extension);

}

#endif /* defined(__NZServer__mime_types__) */
