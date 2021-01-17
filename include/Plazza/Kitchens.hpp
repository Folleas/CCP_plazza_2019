/*
** EPITECH PROJECT, 2020
** CCP_plazza_2019
** File description:
** Kitchenss
*/

#ifndef KITCHENS_HPP_
#define KITCHENS_HPP_

#include <iostream>
#include <fstream>
#include "Encapsulation/ThreadPool.hpp"
#include "Encapsulation/IPC.hpp"
#include "Plazza/Pizza.hpp"
#include "Core/Utils.hpp"
#include <string>
#include <memory>
#include <chrono>

typedef std::chrono::high_resolution_clock Clock;

namespace Plazza {
    class Kitchens {
        public:
            Kitchens() = delete;
            Kitchens(const Kitchens &other) = delete;
            Kitchens(std::size_t nbCooks, std::size_t kitchenID, std::size_t cookingTimeMultiplier, std::size_t timeToRestock); //init thread pool
            ~Kitchens();

            void runKitchens();
            void displayStatus();
            void checkDestroyKitchen();

            std::size_t findAssignedKitchen(std::string &order);
            bool isOrderAssignedHere(std::string &order);
            bool isKitchenWorking();

            std::vector<std::string> readIPC(std::string nameFile);
            std::vector<std::shared_ptr<Pizza>> getOrderFromReception(std::vector<std::string> &allOrders);
            std::vector<std::string> getCookedOrders();

            void sendOrderToCooks(std::vector<std::shared_ptr<Pizza>> kitchenOrder);
            void sendReceipt(std::vector<std::string> &cookedOrders);
        private:
            Encapsulation::ThreadPool _cooks;
            std::vector<bool> _cooksWorking;
            std::size_t _kitchenID;
            std::size_t _cookingTimeMultiplier;
            std::size_t _doe;
            std::size_t _timeToRestock;
            IPC _ipc;
    };
};

#endif /* !KITCHENS_HPP_ */
