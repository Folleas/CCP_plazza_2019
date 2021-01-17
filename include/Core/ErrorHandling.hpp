/*
** EPITECH PROJECT, 2020
** ccp_plazza_2019
** File description:
** ErrorHandling
*/

#ifndef ERRORHANDLING_HPP_
#define ERRORHANDLING_HPP_

#include <stdio.h>
#include <stdlib.h>

namespace Plazza {
    class ErrorHandling {
        public:
            ErrorHandling() = default;
            ~ErrorHandling() = default;

            static bool errorHandling(int ac, char **av);

        private:
    };
};

#endif /* !ERRORHANDLING_HPP_ */
