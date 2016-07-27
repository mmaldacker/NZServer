//
//  compressor_handler.cpp
//  NZServer
//
//  Created by Maximilian Maldacker on 12/11/2014.
//  Copyright (c) 2014 Maximilian Maldacker. All rights reserved.
//

#include "compressor_handler.h"

std::string deflate(const std::string & data)
{
    z_stream zs{0};

    if (deflateInit(&zs, Z_BEST_COMPRESSION) != Z_OK)
        throw(std::runtime_error("deflateInit failed while compressing."));


    zs.next_in = (Bytef*)data.data();
    zs.avail_in = (unsigned int)data.size();

    int ret;
    char outbuffer[32768];
    std::string compressed_data;

    // retrieve the compressed bytes blockwise
    do
    {
        zs.next_out = reinterpret_cast<Bytef*>(outbuffer);
        zs.avail_out = sizeof(outbuffer);

        ret = deflate(&zs, Z_FINISH);

        compressed_data.append(outbuffer, sizeof(outbuffer) - zs.avail_out);

    }while (ret == Z_OK);

    deflateEnd(&zs);

    if (ret != Z_STREAM_END)
    {
        std::ostringstream oss;
        oss << "Exception during zlib compression: (" << ret << ") " << zs.msg;
        throw(std::runtime_error(oss.str()));
    }

    return compressed_data;
}

void compressor_handler::handle_request(const request &req, reply &rep)
{
    // FIXME verify that deflate is available in request!

    rep.content = deflate(rep.content);
    rep.headers.push_back({"Content-Encoding", "deflate"});
    for(auto & h : rep.headers)
    {
        if(h.name == "Content-Length")
        {
            h.value = std::to_string(rep.content.size());
            break;
        }
    }
}