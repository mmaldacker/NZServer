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
#include "utils.h"

template_engine::template_engine(sel::State & state) : state_(state)
{
    using namespace std::placeholders;
    std::function<void(int,const std::string)> gather_function = std::bind(&template_engine::gather, this, _1, _2);
    state_["display"] = gather_function;
}

std::string template_engine::generate_html(const std::string & file)
{
    if(templates_.find(file) == templates_.end())
    {
        parse_file(file);
    }

    return run_template(templates_[file]);
}

// FIXME reload file if it has changed!
void template_engine::parse_file(const std::string &file)
{
    std::string content;
    if(!load_file(file, content))
    {
        return;
    }

    template_structure & structure = templates_[file];

    // FIXME more solid parsing!

    int variableCall = 0;
    std::string::size_type loc = 0, end = 0;
    while((loc = content.find("{", loc+2)) != std::string::npos)
    {
        if(content[loc+1] == '%')
        {
            structure.blocks.push_back(content.substr(end, loc - end));
            end = content.find("%}", loc) + 2;
            structure.code += content.substr(loc + 2, end - loc - 4) + "\n";
            variableCall++;
        }
        else if(content[loc+1] == '{')
        {
            structure.blocks.push_back(content.substr(end, loc - end));
            end = content.find("}}", loc) + 2;
            structure.code += "display(" + std::to_string(variableCall) + ", " + content.substr(loc + 2, end - loc - 4) + ")\n";
            variableCall++;
        }
    }

    structure.blocks.push_back(content.substr(end));

    BOOST_LOG_TRIVIAL(info) << "Loaded template file " << file;
}

void template_engine::gather(int n, const std::string data)
{
    computed_data_[n].append(data);
}

std::string template_engine::run_template(const template_structure & structure)
{
    computed_data_.clear();
    if(!state_(structure.code.c_str()))
    {
        BOOST_LOG_TRIVIAL(error) << "Error running template:\n" << structure.code << "Error: " << state_;
    }

    std::string content;
    content += structure.blocks[0];
    for(int i = 1 ; i < structure.blocks.size() ; ++i)
    {
        if(computed_data_.find(i-1) != computed_data_.end())
        {
            content += computed_data_[i-1];
        }

        content += structure.blocks[i];
    }

    return content;
}