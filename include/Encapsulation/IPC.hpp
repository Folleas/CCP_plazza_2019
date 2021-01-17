/*
** EPITECH PROJECT, 2020
** CCP_plazza_2019
** File description:
** IPC
*/

#ifndef IPC_HPP_
#define IPC_HPP_

#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "Core/Utils.hpp"
#include "Encapsulation/Mutex.hpp"

namespace Plazza {
    class IPC {
        public:
            IPC() = default;
            ~IPC() = default;

            void writeMessage(std::string message, std::string path);
            void deleteMessage(size_t line, std::string path);
            void deleteFile(std::string fileName);
            void manageMessage(std::vector<std::string> &order, std::vector<std::string> lineVector, std::pair<std::size_t, std::size_t> stat, std::pair<std::string, std::string> statString);
            std::vector<std::string> readIPC(std::string nameFile, std::size_t kitchenID);

        private:
    };
}

#endif /* !IPC_HPP_ */
