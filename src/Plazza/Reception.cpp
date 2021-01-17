/*
** EPITECH PROJECT, 2020
** CCP_plazza_2019
** File description:
** Reception
*/

#include "../../include/Plazza/Reception.hpp"
#include <iostream>

std::size_t Plazza::Reception::assignKitchenID()
{
    std::size_t chosenID = 0;

    if (this->_kitchenStats.empty())
        return (0);
    for (std::pair<std::size_t, std::pair<pid_t, std::size_t>> element : this->_kitchenStats) {
        if (element.first >= chosenID)
            chosenID = element.first;
    }
    chosenID++;
    return (chosenID);
}

std::size_t Plazza::Reception::chooseBestFittedKitchen()
{
    int chosenKitchenID = -1;
    std::size_t chosenKitchenSize = this->_nbCooksPerKitchen * 2;

    for (std::pair<std::size_t, std::pair<pid_t, std::size_t>> element : this->_kitchenStats) {
        if (chosenKitchenSize > element.second.second) {
            chosenKitchenID = element.first;
            chosenKitchenSize = element.second.second;
        }
    }
    return (chosenKitchenID);
}

std::size_t Plazza::Reception::checkInputStatus(std::string command)
{
    if (!command.compare("status")) {
        for (std::size_t i = 0; i != this->_kitchenStats.size(); i++) {
            auto clock = Clock::now();
            _ipc.writeMessage("status: :" + std::to_string(i), "./res/.toKitchen" + std::to_string(i));
            while (std::chrono::duration_cast<std::chrono::milliseconds>(Clock::now() - clock).count() <= 500);
        }
        return (1);
    }
    return (0);
}

std::size_t Plazza::Reception::createKitchen()
{
    std::size_t kitchenID = assignKitchenID();
    pid_t curr_pid;

    curr_pid = this->_proc.addFork();
    switch (curr_pid) {
        case -1: std::cerr << "Error: Fork failed.\n"; return (-1);
        case 0:
            Kitchens current((std::size_t)this->getNbCooks(), (std::size_t)kitchenID, this->_cookingTimeMultiplier, this->_timeReplaceIngredient);
            this->addKitchenStat(kitchenID);
            current.runKitchens();
            break;
    }
    return (kitchenID);
}

void Plazza::Reception::checkWorkingKitchen()
{

}

void Plazza::Reception::addKitchenStat(std::size_t kitchenID)
{
    std::unordered_map<std::size_t, std::pair<pid_t, std::size_t>> tmp = _kitchenStats;

    tmp[kitchenID].second = 0;
    _kitchenStats = tmp;
}

std::vector<std::string> Plazza::Reception::manageCommands(std::vector<std::string> &command)
{
    std::vector<std::string> commands;
    std::size_t chosenKitchenID;

    command.at(2).erase(0, 1);
    for (std::size_t i = 0; i != std::stoi(command.at(2)); i++) {
        chosenKitchenID = this->chooseBestFittedKitchen();
        if (chosenKitchenID == -1)
            chosenKitchenID = createKitchen();
        this->_kitchenStats[chosenKitchenID].second += 1;
        commands.push_back(this->formatCommand(command, chosenKitchenID));
        this->_ipc.writeMessage(this->formatCommand(command, chosenKitchenID), "./res/.toKitchen" + std::to_string(chosenKitchenID));
    }
    return (commands);
}

void Plazza::Reception::displayReceipts(std::vector<std::string> receipts)
{
    Utils utils;

    for (std::string receipt : receipts) {
        std::vector<std::string> receiptVector = utils.stringToVector(receipt);
        std::string receiptLog;
        receiptLog += utils.getTypeMapString()[PizzaType(std::atoi(receiptVector.at(0).c_str()))] + " " + utils.getSizeMapString()[PizzaSize(std::atoi(receiptVector.at(1).c_str()))];
        _ipc.writeMessage(receiptLog, "./res/PizzaLog");
        std::cout << receiptLog << " Ready !" << std::endl;
    }
}

void Plazza::Reception::updateKitchens(std::vector<std::string> receipts)
{
    Utils utils;
    std::vector<std::string> kitchenInfo;

    for (std::string receipt : receipts) {
        kitchenInfo = utils.stringToVector(receipt);
        if (kitchenInfo.size() == 3) {
            this->_kitchenStats[std::atoi(kitchenInfo.at(2).c_str())].second -= 1;
        }
        else if (kitchenInfo.size() == 2) {
            std::cout << "Destroy kitchen " << kitchenInfo.at(2) << std::endl;
        }
    }
}

void Plazza::Reception::manageReceipt()
{
    std::vector<std::string> receipts = _ipc.readIPC("./res/.toReception", 1000);
    this->_ipc.deleteFile("./res/.toReception");

    this->updateKitchens(receipts);
    // this->displayReceipts(receipts);
}

void Plazza::Reception::runReception(std::vector<std::string> &command)
{
    this->manageReceipt();
    if (!this->checkInputStatus(command.at(0)))
        std::vector<std::string> formatedCommand = manageCommands(command);
    // this->sendCommandToKitchens();
    // this->manageKitchens();
}

std::string Plazza::Reception::formatCommand(std::vector<std::string> &command, std::size_t chosenKitchenID)
{
    Utils utils;

    Pizza tmpPizza(utils.getTypeMap()[command.at(0)], utils.getSizeMap()[command.at(1)], this->_cookingTimeMultiplier);
    std::string formatedCommand = tmpPizza.serialize();

    formatedCommand += std::to_string(chosenKitchenID);
    formatedCommand += "\n";
    return (formatedCommand);
}

void Plazza::Reception::setCookingTime(std::size_t newValue)
{
    this->_cookingTimeMultiplier = newValue;
}

void Plazza::Reception::setNbCooksPerKitchen(std::size_t newValue)
{
    this->_nbCooksPerKitchen = newValue;
}

void Plazza::Reception::setTimeReplaceIngredient(std::size_t newValue)
{
    this->_timeReplaceIngredient = newValue;
}

void Plazza::Reception::deleteFile(std::string fileName)
{
    this->_ipc.deleteFile(fileName);
}