/*
** EPITECH PROJECT, 2020
** ccp_plazza_2019
** File description:
** ErrorHandling
*/

#include "Core/ErrorHandling.hpp"

bool Plazza::ErrorHandling::errorHandling(int ac, char **av)
{
    if (ac != 4)
        return (false);
    if (atof(av[1]) < 0)
        return (false);
    if (atoi(av[2]) <= 0)
        return (false);
    if (atoi(av[3]) < 0)
        return (false);
    return (true);
}