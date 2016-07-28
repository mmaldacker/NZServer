//
//  server.h
//  NZServer
//
//  Created by Maximilian Maldacker on 08/11/2014.
//  Copyright (c) 2014 Maximilian Maldacker. All rights reserved.
//

#ifndef __NZServer__server__
#define __NZServer__server__

#include <boost/asio.hpp>
#include <string>
#include "connection.h"
#include "handler/request_handler.h"

class server
{
public:
    server(const server&) = delete;
    server& operator=(const server&) = delete;

    server(const std::string& address, const std::string& port);

    /// Run the server's io_service loop.
    void run();

private:
    /// Perform an asynchronous accept operation.
    void do_accept();

    /// Wait for a request to stop the server.
    void do_await_stop();

    /// The io_service used to perform asynchronous operations.
    boost::asio::io_service io_service_;

    /// Acceptor used to listen for incoming connections.
    boost::asio::ip::tcp::acceptor acceptor_;

    /// The next socket to be accepted.
    boost::asio::ip::tcp::socket socket_;

    std::vector<connection> connections_;

    request_handler request_handler_;
};


#endif /* defined(__NZServer__server__) */
