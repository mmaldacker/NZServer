//
//  connection.h
//  NZServer
//
//  Created by Maximilian Maldacker on 08/11/2014.
//  Copyright (c) 2014 Maximilian Maldacker. All rights reserved.
//

#ifndef __NZServer__connection__
#define __NZServer__connection__

#include <array>
#include <memory>
#include <boost/asio.hpp>
#include "request_parser.h"
#include "handler/request_handler.h"
#include "reply.h"

/// Represents a single connection from a client.
class connection
{
public:
    connection(const connection&) = delete;
    connection& operator=(const connection&) = delete;

    explicit connection(boost::asio::ip::tcp::socket socket, request_handler & handler);

    connection(connection&&);

    void start();
    void stop();

private:
    void do_read();
    void do_write(const reply & reply_, bool close_connection);

    boost::asio::ip::tcp::socket socket_;
    
    /// Buffer for incoming data.
    std::array<char, 8192> buffer_;

    request_parser request_parser_;

    request_handler & request_handler_;
};

#endif /* defined(__NZServer__connection__) */
