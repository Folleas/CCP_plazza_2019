/*
** EPITECH PROJECT, 2020
** ccp_plazza_2019
** File description:
** Main
*/

#include <iostream>
#include "Core/ErrorHandling.hpp"
#include "Core/Shell.hpp"
#include "Core/Parser.hpp"

using namespace Plazza;

int main(int ac, char **av)
{
    if (ErrorHandling::errorHandling(ac, av) == false) {
        std::cout << "You are not using the arguments correctly!\n";
        return (84);
    }
    Shell shell(av);
    shell.runShell();
    return (0);
}