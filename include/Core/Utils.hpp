/*
** EPITECH PROJECT, 2020
** CCP_plazza_2019
** File description:
** Utils
*/

#ifndef UTILS_HPP_
#define UTILS_HPP_

#include <vector>
#include <string>
#include <unordered_map>

namespace Plazza {
    enum PizzaType
    {
        Regina = 1,
        Margarita = 2,
        Americana = 4,
        Fantasia = 8
    };

    enum PizzaSize
    {
        S = 1,
        M = 2,
        L = 4,
        XL = 8,
        XXL = 16
    };
    class Utils {
        public:
            Utils();
            ~Utils() = default;

            std::vector<std::string> stringToVector(std::string line);
            std::unordered_map<std::string, PizzaType> getTypeMap() const {return (_typeMap);};
            std::unordered_map<std::string, PizzaSize> getSizeMap() const {return (_sizeMap);};
            std::unordered_map<PizzaType, std::string> getTypeMapString() const {return (_typeMapString);};
            std::unordered_map<PizzaSize, std::string> getSizeMapString() const {return (_sizeMapString);};

        private:
            std::unordered_map<std::string, PizzaType> _typeMap;
            std::unordered_map<std::string, PizzaSize> _sizeMap;
            std::unordered_map<PizzaType, std::string> _typeMapString;
            std::unordered_map<PizzaSize, std::string> _sizeMapString;
    };
};

#endif /* !UTILS_HPP_ */
