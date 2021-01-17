/*
** EPITECH PROJECT, 2020
** CCP_plazza_2019
** File description:
** Utils
*/

#include "Core/Utils.hpp"

Plazza::Utils::Utils()
{
    std::unordered_map<std::string, PizzaType> typeMap;
    std::unordered_map<std::string, PizzaSize> sizeMap;
    std::unordered_map<PizzaType, std::string> typeMapString;
    std::unordered_map<PizzaSize, std::string> sizeMapString;

    typeMap["regina"] = PizzaType::Regina;
    typeMap["margarita"] = PizzaType::Margarita;
    typeMap["americana"] = PizzaType::Americana;
    typeMap["fantasia"] = PizzaType::Fantasia;
    this->_typeMap = typeMap;

    sizeMap["S"] = PizzaSize::S;
    sizeMap["M"] = PizzaSize::M;
    sizeMap["L"] = PizzaSize::L;
    sizeMap["XL"] = PizzaSize::XL;
    sizeMap["XXL"] = PizzaSize::XXL;
    this->_sizeMap = sizeMap;

    typeMapString[PizzaType::Regina] = "regina";
    typeMapString[PizzaType::Margarita] = "margarita";
    typeMapString[PizzaType::Americana] = "americana";
    typeMapString[PizzaType::Fantasia] = "fantasia";
    this->_typeMapString = typeMapString;

    sizeMapString[PizzaSize::S] = "S";
    sizeMapString[PizzaSize::M] = "M";
    sizeMapString[PizzaSize::L] = "L";
    sizeMapString[PizzaSize::XL] = "XL";
    sizeMapString[PizzaSize::XXL] = "XXL";
    this->_sizeMapString = sizeMapString;
}

std::vector<std::string> Plazza::Utils::stringToVector(std::string line)
{
    std::vector<std::string> tokens;
    std::size_t pos = 0;
    std::string tmpToken;

    while ((pos = line.find(":")) != std::string::npos) {
        tmpToken = line.substr(0, pos);
        tokens.push_back(tmpToken);
        line.erase(0, pos + 1);
    }
    tmpToken = line.substr(0, pos);
    tokens.push_back(tmpToken);
    return (tokens);
}