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
#include "utils.h"

template_engine::template_engine(sel::State & state, file_store & store) : state_(state), file_store_(store)
{
    using namespace std::placeholders;
    std::function<void(int,const std::string)> gather_function = std::bind(&template_engine::gather, this, _1, _2);
    state_["display"] = gather_function;

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

std::string template_engine::generate_html(const std::string & file)
{
    auto full_path = template_path(file);
    if(file_store_.is_modified(full_path))
    {
        parse_file(full_path);
    }

    return run_template(templates_[full_path]);
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
    while((loc = content.find("{", loc+1)) != std::string::npos && loc != content.size() - 1)
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

            structure.code += "display(" + std::to_string(structure.blocks.size()) + ", " + content.substr(loc + 2, end - loc - 4) + ")\n";
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

std::string template_engine::run_template(const template_structure & structure)
{
    BOOST_LOG_TRIVIAL(error) << "Running template " << structure.name;

    computed_data_.clear();
    if(!state_(structure.code.c_str()))
    {
        BOOST_LOG_TRIVIAL(error) << "Error running template:\n" << structure.code << "Error: " << state_;
    }

    std::string content;
    for(int i = 0 ; i < structure.blocks.size() ; ++i)
    {
        content += computed_data_[i];
        content += structure.blocks[i];
    }

    return content;
}