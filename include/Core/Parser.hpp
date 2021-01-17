/*
** EPITECH PROJECT, 2020
** ccp_plazza_2019
** File description:
** Parser
*/

#ifndef PARSER_HPP_
#define PARSER_HPP_

#include <string>
#include <iostream>
#include <vector>

namespace Plazza {
    class Parser {
        public:
            Parser() = default;
            ~Parser() = default;

            std::vector<std::string> splitInput(std::string input);
            std::vector<std::string> parseInput(std::string str);
            bool checkParser(std::vector<std::string> vec);

            float getCookingTime(void);
            int getNbCooksPerKitchen(void);
            int getTimeGetIngredient(void);

        private:

    };
};

#endif /* !PARSER_HPP_ */