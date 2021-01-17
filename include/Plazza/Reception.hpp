/*
** EPITECH PROJECT, 2020
** CCP_plazza_2019
** File description:
** Reception
*/

#ifndef RECEPTION_HPP_
#define RECEPTION_HPP_

#include "../Core/Parser.hpp"
#include "../Encapsulation/Fork.hpp"
#include "../Encapsulation/IPC.hpp"
#include "../Plazza/Pizza.hpp"
#include "../Plazza/Kitchens.hpp"

namespace Plazza {
    class Reception : public Parser {
        public:
            Reception() = default;
            ~Reception() = default;

            void runReception(std::vector<std::string> &);
            std::size_t checkInputStatus(std::string command);

            std::string formatCommand(std::vector<std::string> &command, std::size_t chosenKitchenID);
            void displayReceipts(std::vector<std::string> receipts);
            void manageReceipt();
            std::vector<std::string> manageCommands(std::vector<std::string> &command);
            std::size_t createKitchen();
            std::size_t assignKitchenID();
            std::size_t chooseBestFittedKitchen();
            void checkWorkingKitchen();
            void updateKitchens(std::vector<std::string> receipts);

            void addKitchenStat(std::size_t kitchenID);

            void setCookingTime(std::size_t newValue);
            void setNbCooksPerKitchen(std::size_t newValue);
            void setTimeReplaceIngredient(std::size_t newValue);

            std::size_t getNbCooks(void) const {return _nbCooksPerKitchen;}
            void deleteKitchen(pid_t pid);

            void deleteFile(std::string fileName);

        private:
            std::size_t _cookingTimeMultiplier;
            std::size_t _nbCooksPerKitchen;
            std::size_t _timeReplaceIngredient;
            Fork _proc;
            IPC _ipc;

            std::unordered_map<std::size_t, std::pair<pid_t, std::size_t>> _kitchenStats;
    };
};

#endif /* !RECEPTION_HPP_ */
