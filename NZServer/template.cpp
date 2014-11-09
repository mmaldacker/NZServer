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

template_engine::template_engine() : state_(true)
{
    gather_function_ = std::bind(&template_engine::gather, this, std::placeholders::_1, std::placeholders::_2);
    state_["display"] = gather_function_;
}

std::string template_engine::generate_html(const std::string & file)
{
    if(templates_.find(file) == templates_.end())
    {
        parse_file(file);
    }

    return run_template(templates_[file]);
}

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
            variableCall++;
            structure.blocks.push_back(content.substr(end, loc - end));
            end = content.find("%}", loc) + 2;
            structure.code += content.substr(loc + 2, end - loc - 4) + "\n";
        }
        else if(content[loc+1] == '{')
        {
            variableCall++;
            structure.blocks.push_back(content.substr(end, loc - end));
            end = content.find("}}", loc) + 2;
            structure.code += "display(" + std::to_string(variableCall) + ", " + content.substr(loc + 2, end - loc - 4) + ")\n";
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
    state_(structure.code.c_str());

    std::string content;
    content += structure.blocks[0];
    for(int i = 0 ; i < structure.blocks.size() ; ++i)
    {
        if(computed_data_.find(i) != computed_data_.end())
        {
            content += computed_data_[i];
        }

        content += structure.blocks[i];
    }

    return content;
}