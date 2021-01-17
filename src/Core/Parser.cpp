/*
** EPITECH PROJECT, 2020
** ccp_plazza_2019
** File description:
** Parser
*/

#include "Core/Parser.hpp"

std::vector<std::string> Plazza::Parser::splitInput(std::string input)
{
    std::string delimiter = "; ";
    size_t pos = 0;
    std::string token;
    std::vector<std::string> pizzaInfo;

    while ((pos = input.find(delimiter)) != std::string::npos) {
        token = input.substr(0, pos);
        pizzaInfo.push_back(token);
        input.erase(0, pos + delimiter.length());
    }
    pizzaInfo.push_back(input);
    return (pizzaInfo);
}

std::vector<std::string> Plazza::Parser::parseInput(std::string input)
{
    std::string delimiter = " ";
    size_t pos = 0;
    std::string token;
    std::vector<std::string> pizzaInfo;

    while ((pos = input.find(delimiter)) != std::string::npos) {
        token = input.substr(0, pos);
        pizzaInfo.push_back(token);
        input.erase(0, pos + delimiter.length());
    }
    pizzaInfo.push_back(input);
    return (pizzaInfo);
}

bool Plazza::Parser::checkParser(std::vector<std::string> vec)
{
    if (!vec.at(0).compare("status"))
        return (true);
    if (vec.size() != 3)
        return (false);
    if (vec.at(0) != "regina" && vec.at(0) != "margarita" && vec.at(0) != "americana" && vec.at(0) != "fantasia")
        return (false);
    if (vec.at(1) != "S" && vec.at(1) != "M" && vec.at(1) != "L" && vec.at(1) != "XL" && vec.at(1) != "XXL")
        return (false);
    if (vec.at(2)[0] != 'x')
        return (false);
    if (atoi(&vec.at(2).c_str()[1]) <= 0)
        return (false);
    return (true);
}