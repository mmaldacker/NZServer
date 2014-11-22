//
//  request_parser.cpp
//  NZServer
//
//  Created by Maximilian Maldacker on 08/11/2014.
//  Copyright (c) 2014 Maximilian Maldacker. All rights reserved.
//

#include "request_parser.h"
#include <boost/log/trivial.hpp>

request_parser::request_parser() : result_type_(indeterminate), last_was_value_(true)
{
    http_parser_init(&parser_, HTTP_REQUEST);
    parser_.data = this;

    settings_.on_header_field = [](http_parser *parser, const char *at, size_t length) -> int
    {
        request_parser * req = (request_parser*)parser->data;
        return req->on_header_field(at, length);
    };

    settings_.on_header_value = [](http_parser *parser, const char *at, size_t length) -> int
    {
        request_parser * req = (request_parser*)parser->data;
        return req->on_header_value(at, length);
    };

    settings_.on_body = [](http_parser *parser, const char *at, size_t length) -> int
    {
        request_parser * req = (request_parser*)parser->data;
        return req->on_body(at, length);
    };

    settings_.on_url = [](http_parser *parser, const char *at, size_t length) -> int
    {
        request_parser * req = (request_parser*)parser->data;
        return req->on_url(at, length);
    };

    settings_.on_message_begin = [](http_parser *parser) -> int
    {
        request_parser * req = (request_parser*)parser->data;
        return req->on_message_begin();
    };

    settings_.on_message_complete = [](http_parser *parser) -> int
    {
        request_parser * req = (request_parser*)parser->data;
        return req->on_message_complete();
    };

    settings_.on_headers_complete = [](http_parser *parser) -> int
    {
        request_parser * req = (request_parser*)parser->data;
        return req->on_headers_complete();
    };
}

request_parser::result_type request_parser::parse(const char * data, size_t length)
{
    auto nparsed = http_parser_execute(&parser_, &settings_, data, length);

    if (parser_.upgrade)
    {
        // FIXME handle new protocol
    }
    else if (nparsed != length)
    {
        return result_type::bad;
    }

    return result_type_;
}

request & request_parser::request()
{
    return request_;
}

bool request_parser::has_keepalive()
{
    for(auto && header : request_.headers)
    {
        if(header.name == "Connection" && header.value == "Keep-Alive")
        {
            return true;
        }
    }

    return false;
}

int request_parser::on_header_field(const char * at, size_t length)
{
    if(last_was_value_)
    {
        header h{std::string(at, length), std::string()};
        request_.headers.push_back(std::move(h));
    }
    else
    {
        request_.headers.back().name += std::string(at, length);
    }

    last_was_value_ = false;

    return 0;
}

int request_parser::on_header_value(const char * at, size_t length)
{
    request_.headers.back().value += std::string(at, length);

    last_was_value_ = true;

    return 0;
}

int request_parser::on_url(const char * at, size_t length)
{
    request_.uri += std::string(at, length);
    return 0;
}

int request_parser::on_body(const char * at, size_t length)
{
    request_.content += std::string(at, length);
    return 0;
}

int request_parser::on_message_begin()
{
    last_was_value_ = true;
    request_.clear();
    result_type_ = result_type::indeterminate;
    return 0;
}

int request_parser::on_message_complete()
{
    BOOST_LOG_TRIVIAL(info) << request_;

    result_type_ = result_type::good;
    return 0;
}

int request_parser::on_headers_complete()
{
    request_.method = http_method_str((enum http_method)parser_.method);
    request_.http_version_major = parser_.http_major;
    request_.http_version_minor = parser_.http_minor;
    return 0;
}