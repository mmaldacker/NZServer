//
//  request_parser.h
//  NZServer
//
//  Created by Maximilian Maldacker on 08/11/2014.
//  Copyright (c) 2014 Maximilian Maldacker. All rights reserved.
//

#ifndef __NZServer__request_parser__
#define __NZServer__request_parser__

#include "http_parser.h"
#include "request.h"

class request_parser
{
public:
    request_parser();

    enum result_type { good, bad, indeterminate };

    result_type parse(const char * data, size_t length);
    request & request();

private:
    int on_header_field(const char * at, size_t length);
    int on_header_value(const char * at, size_t length);
    int on_url(const char * at, size_t length);
    int on_body(const char * at, size_t length);
    int on_message_begin();
    int on_message_complete();
    int on_headers_complete();

    http_parser parser_;
    http_parser_settings settings_;

    result_type result_type_;

    struct request request_;

    bool last_was_value_;
};

#endif /* defined(__NZServer__request_parser__) */
