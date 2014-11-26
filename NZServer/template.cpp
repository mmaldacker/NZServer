//
//  template.cpp
//  NZServer
//
//  Created by Maximilian Maldacker on 09/11/2014.
//  Copyright (c) 2014 Maximilian Maldacker. All rights reserved.
//

#include "template.h"
#include <fstream>
#include <boost/log/trivial.hpp>
#include <boost/algorithm/string/trim.hpp>
#include <boost/algorithm/string.hpp>
#include "utils.h"

template_engine::template_engine(LuaIntf::LuaContext & state, file_store & store) : state_(state), file_store_(store)
{
    using namespace std::placeholders;
    std::function<void(int,const std::string)> gather_function = std::bind(&template_engine::gather, this, _1, _2);
    std::function<void(const std::string, const std::string)> set_header_function = std::bind(&template_engine::set_header, this, _1, _2);

    LuaBinding(state_).beginModule("template_engine")
    .addFunction("display", gather_function)
    .addFunction("set_header", set_header_function)
    .endModule();

    auto files = file_store_.get_files("/template");
    for(auto && file : files)
    {
        parse_file(file);
    }
}

std::string template_path(const std::string & file)
{
    return "/template/" + file + ".tpl";
}

bool template_engine::run_template(const std::string & file,
                                   const std::vector<std::string> & arguments,
                                   const request & req,
                                   std::string & content,
                                   std::vector<header> & headers)
{
    auto full_path = template_path(file);
    if(file_store_.is_modified(full_path))
    {
        parse_file(full_path);
    }

    return run_template(templates_[full_path], arguments, req, content, headers);
}

void template_engine::parse_file(const std::string &file)
{
    template_structure & structure = templates_[file];
    structure.name = file;
    structure.clear();
    parse_file(file, structure);
}

void template_engine::parse_file(const std::string & file, template_structure & structure)
{
    std::string content;
    if(!file_store_.get_file(file, content))
    {
        return;
    }

    std::string::size_type loc = 0, end = 0;
    while((loc = content.find("{", loc)) != std::string::npos && loc != content.size() - 1)
    {
        if(content[loc+1] == '%')
        {
            structure.blocks.push_back(content.substr(end, loc - end));
            end = content.find("%}", loc) + 2;

            structure.code += content.substr(loc + 2, end - loc - 4) + "\n";
            loc = end;
        }
        else if(content[loc+1] == '{')
        {
            structure.blocks.push_back(content.substr(end, loc - end));
            end = content.find("}}", loc) + 2;

            structure.code += "template_engine.display(" + std::to_string(structure.blocks.size()) + ", " + content.substr(loc + 2, end - loc - 4) + ")\n";
            loc = end;
        }
        else if(content[loc+1] == '#')
        {
            structure.blocks.push_back(content.substr(end, loc - end));
            end = content.find("#}", loc) + 2;

            auto location = content.substr(loc + 2, end - loc - 4);
            boost::trim(location);
            parse_file(template_path(location), structure);

            loc = end;
        }
    }

    structure.blocks.push_back(content.substr(end));

    BOOST_LOG_TRIVIAL(info) << "Loaded template file " << file;
}

void template_engine::gather(int n, const std::string data)
{
    computed_data_[n] += data;
}

void template_engine::set_header(const std::string key, const std::string value)
{
    extra_headers_->push_back({key, value});
}

void template_engine::set_arguments(const std::vector<std::string> & arguments, const request & req)
{
    LuaIntf::LuaRef lua_arguments = LuaIntf::LuaRef::createTable(state_);
    state_.setGlobal("arguments", lua_arguments);

    for(int i = 0 ; i < arguments.size() ; i++)
    {
        lua_arguments[i] = arguments[i];
    }

    state_.setGlobal("method", req.method);
    state_.setGlobal("uri", req.uri);

    LuaIntf::LuaRef lua_headers = LuaIntf::LuaRef::createTable(state_);
    state_.setGlobal("headers", lua_headers);

    for(auto && h : req.headers)
    {
        lua_headers[h.name.c_str()] = h.value;
    }

    LuaIntf::LuaRef lua_post = LuaIntf::LuaRef::createTable(state_);
    state_.setGlobal("post", lua_post);
    
    std::vector<std::string> pairs;
    boost::split(pairs,req.content,boost::is_any_of("&"));
    for(auto && pair : pairs)
    {
        auto eq = pair.find('=');
        std::string key, value;
        if(url_decode(pair.substr(0, eq), key) && url_decode(pair.substr(eq+1), value))
        {
            lua_post[key.c_str()] = value;
        }
    }
}

void template_engine::clear_arguments(const std::vector<std::string> & arguments, const request & req)
{
    LuaIntf::LuaRef lua_arguments(state_, "arguments");
    LuaIntf::LuaRef lua_headers(state_, "headers");
    LuaIntf::LuaRef lua_post(state_, "post");

    lua_arguments = nullptr;
    lua_headers = nullptr;
    lua_post = nullptr;
}

bool template_engine::run_template(const template_structure & structure,
                                   const std::vector<std::string> & arguments,
                                   const request & req,
                                   std::string & content,
                                   std::vector<header> & headers)
{
    BOOST_LOG_TRIVIAL(info) << "Running template " << structure.name;

    set_arguments(arguments, req);

    extra_headers_ = &headers;
    computed_data_.clear();

    state_.doString(structure.code.c_str());

    for(int i = 0 ; i < structure.blocks.size() ; ++i)
    {
        content += computed_data_[i];
        content += structure.blocks[i];
    }

    clear_arguments(arguments, req);

    return true;
}