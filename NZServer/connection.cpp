//
//  connection.cpp
//  NZServer
//
//  Created by Maximilian Maldacker on 08/11/2014.
//  Copyright (c) 2014 Maximilian Maldacker. All rights reserved.
//

#include "connection.h"
#include <utility>
#include <vector>
#include <boost/log/trivial.hpp>

connection::connection(boost::asio::ip::tcp::socket socket, request_handler & handler)
: socket_(std::move(socket))
, request_handler_(handler)
{

}

connection::connection(connection && other) : connection(std::move(other.socket_), other.request_handler_)
{

}

void connection::start()
{
    do_read();
}

void connection::stop()
{
    socket_.close();
}

void connection::do_read()
{
    socket_.async_read_some(boost::asio::buffer(buffer_),
    [this](boost::system::error_code ec, std::size_t bytes_transferred)
    {
        if (!ec)
        {
            BOOST_LOG_TRIVIAL(debug) << "Reading " << bytes_transferred << " bytes";

            request_parser::result_type result = request_parser_.parse(request_, buffer_.data(), bytes_transferred);

            if (result == request_parser::good)
            {
                request_handler_.handle_request(request_, reply_);
                do_write();
            }
            else if (result == request_parser::bad)
            {
                reply_ = reply::stock_reply(reply::bad_request);
                do_write();
            }
            else
            {
                do_read();
            }
        }
        else if (ec != boost::asio::error::operation_aborted)
        {
            // stop
        }
    });
}

void connection::do_write()
{
    boost::asio::async_write(socket_, reply_.to_buffers(),
    [this](boost::system::error_code ec, std::size_t)
    {
        if (!ec)
        {
            // Initiate graceful connection closure.
            boost::system::error_code ignored_ec;
            socket_.shutdown(boost::asio::ip::tcp::socket::shutdown_both, ignored_ec);
        }

        if (ec != boost::asio::error::operation_aborted)
        {
            // stop
        }
    });
}



