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
#include "reply.h"
#include "request_parser.h"
#include "request_handler.h"

/// Represents a single connection from a client.
class connection
{
public:
    connection(const connection&) = delete;
    connection& operator=(const connection&) = delete;

    /// Construct a connection with the given socket.
    explicit connection(boost::asio::ip::tcp::socket socket, request_handler & handler);

    connection(connection&&);

    /// Start the first asynchronous operation for the connection.
    void start();

    /// Stop all asynchronous operations associated with the connection.
    void stop();

private:
    /// Perform an asynchronous read operation.
    void do_read();

    /// Perform an asynchronous write operation.
    void do_write();

    /// Socket for the connection.
    boost::asio::ip::tcp::socket socket_;
    
    /// Buffer for incoming data.
    std::array<char, 8192> buffer_;

    request request_;
    reply reply_;

    request_parser request_parser_;

    request_handler & request_handler_;
};

#endif /* defined(__NZServer__connection__) */
