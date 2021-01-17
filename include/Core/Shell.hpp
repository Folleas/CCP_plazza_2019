/*
** EPITECH PROJECT, 2020
** ccp_plazza_2019
** File description:
** Shell
*/

#ifndef SHELL_HPP_
#define SHELL_HPP_

#include <iostream>
#include <string>
#include <stdlib.h>
#include <dirent.h>

#include "Core/Parser.hpp"
#include "Plazza/Reception.hpp"

namespace Plazza {
    class Shell {
        public:
            Shell(char **av);
            ~Shell() = default;

            void deleteTmpFiles();
            void initShell(char **args);
            void runShell();

        private:
            std::vector<std::string> args;
    };
};

#endif /* !SHELL_HPP_ */
