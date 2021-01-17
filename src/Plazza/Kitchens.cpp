/*
** EPITECH PROJECT, 2020
** CCP_plazza_2019
** File description:
** Kitchen
*/

#include "../../include/Plazza/Kitchens.hpp"

std::string Plazza::operator<<(std::string &str, Plazza::Pizza &pizza)
{
    str = pizza.serialize();
    return (str);
}

Plazza::Kitchens::Kitchens(std::size_t nbCooks, std::size_t kitchenID, std::size_t cookingTimeMultiplier, std::size_t timeToRestock) : _cooks(nbCooks)
{
    this->_kitchenID = kitchenID;
    this->_cookingTimeMultiplier = cookingTimeMultiplier;
    this->_cooksWorking.resize(nbCooks);
    this->_timeToRestock = timeToRestock;
    this->_doe = 5;
}

Plazza::Kitchens::~Kitchens()
{

}

void Plazza::Kitchens::displayStatus()
{
    std::size_t cooksCount = 0;

    std::cout << "\tKitchen ID\t:\t" << this->_kitchenID << std::endl;
    std::cout << "\tDoe stock\t:\t" << this->_doe << std::endl;
    for (bool status : this->_cooksWorking) {
        std::cout << "\tCook n°" << cooksCount++ << " " << "status\t: ";
        if (status)
            std::cout << "\tWorking";
        else
            std::cout << "\tNot Working";
        std::cout << std::endl << std::endl;
    }
}

void Plazza::Kitchens::runKitchens()
{
    std::vector<std::string> allOrders;
    std::vector<std::string> cookedOrders;
    std::vector<std::shared_ptr<Pizza>> kitchenOrders;

    bool isRunning = true;
    auto t1 = Clock::now();
    auto t2 = Clock::now();

    while (isRunning) {
        allOrders = this->_ipc.readIPC("./res/.toKitchen" + std::to_string(this->_kitchenID), this->_kitchenID);
        // this->_ipc.deleteFile("./res/.toKitchen" + std::to_string(this->_kitchenID));
        kitchenOrders = getOrderFromReception(allOrders);
        if (kitchenOrders.size() != 0) {
            t1 = Clock::now();
            sendOrderToCooks(kitchenOrders);
        }
        cookedOrders = getCookedOrders();
        if (cookedOrders.size() != 0) {
            t1 = Clock::now();
            sendReceipt(cookedOrders);
        }
        if (std::chrono::duration_cast<std::chrono::milliseconds>(Clock::now() - t2).count() > _timeToRestock) {
            t2 = Clock::now();
            if (_doe < 5)
                _doe++;
        }
        // if (std::chrono::duration_cast<std::chrono::seconds>(Clock::now() - t1).count() > 5) {
        //     checkDestroyKitchen();
        // }
    }
}

void Plazza::Kitchens::checkDestroyKitchen()
{
    if (!isKitchenWorking()) {
        this->_ipc.writeMessage("destroy:" + std::to_string(this->_kitchenID) + "\n", "./res/.toReception");
        exit(0);
    }
}

bool Plazza::Kitchens::isKitchenWorking()
{
    bool isWorking = false;

    for (bool tmp : this->_cooksWorking)
        isWorking = tmp;
    return (isWorking);
}

std::string preparePizza(Plazza::Pizza pizza, std::size_t doe, std::size_t timeToRestock)
{
    auto t2 = Clock::now();
    if (doe < 0)
        while (std::chrono::duration_cast<std::chrono::milliseconds>(Clock::now() - t2).count() <= timeToRestock);
    auto t1 = Clock::now();
    while (std::chrono::duration_cast<std::chrono::seconds>(Clock::now() - t1).count() <= pizza.getBakeTime() * pizza.getCookingTimeMultiplier());
    return (pizza.serialize());
}

void Plazza::Kitchens::sendOrderToCooks(std::vector<std::shared_ptr<Pizza>> kitchenOrder)
{
    for (std::size_t i = 0; i != kitchenOrder.size(); i++) {
        if (kitchenOrder.at(i) == nullptr)
            std::cout << "null" << std::endl;
        std::function<std::string()> orderFunction = std::bind(preparePizza, *(kitchenOrder.at(i)), this->_doe, this->_timeToRestock);
        this->_cooks.pushOrder(orderFunction);
        for (std::size_t i = 0; i != this->_cooksWorking.size(); i++) {
            if (this->_cooksWorking.at(i) == false) {
                this->_cooksWorking.at(i) = true;
                break;
            }
        }
        this->_doe--;
    }
}

void Plazza::Kitchens::sendReceipt(std::vector<std::string> &cookedOrders)
{
    std::vector<std::string> stringVectorTemp;
    std::string receiptLog;
    Utils utils;

    for (std::string cookedOrder : cookedOrders) {
        for (std::size_t i = 0; i != this->_cooksWorking.size(); i++) {
            if (this->_cooksWorking.at(i) == true)
                this->_cooksWorking.at(i) = false;
        }
        this->_ipc.writeMessage(cookedOrder + std::to_string(this->_kitchenID) + "\n", "./res/.toReception");
        stringVectorTemp = utils.stringToVector(cookedOrder);
        _ipc.writeMessage(cookedOrder + "\n", "./res/PizzaLog");
        receiptLog = utils.getTypeMapString()[(PizzaType)(std::atoi(stringVectorTemp.at(0).c_str()))] + " " + utils.getSizeMapString()[(PizzaSize)(std::atoi(stringVectorTemp.at(1).c_str()))] + stringVectorTemp.at(2) + " from kitchen " + std::to_string(this->_kitchenID);
        std::cout << std::endl << receiptLog << " Ready !" << std::endl;
    }
}

std::vector<std::string> Plazza::Kitchens::getCookedOrders()
{
    std::vector<std::string> cookedOrders;
    std::string tmp;

    while ((tmp = this->_cooks.popResult()) != "") {
        cookedOrders.push_back(tmp);
    }
    return (cookedOrders);
}

std::size_t Plazza::Kitchens::findAssignedKitchen(std::string &order)
{
    std::size_t pos = 0;

    if (order.size() == 0)
        return (-1);
    for (std::size_t i = 0; i != order.size(); i++) {
        if (order.at(i) == ':') {
            pos = i;
        }
    }
    return (std::atoi(order.substr(pos + 1).c_str()));
}

bool Plazza::Kitchens::isOrderAssignedHere(std::string &order)
{
    std::size_t orderID = findAssignedKitchen(order);

    if (orderID == this->_kitchenID)
        return (true);
    return (false);
}

std::vector<std::shared_ptr<Plazza::Pizza>> Plazza::Kitchens::getOrderFromReception(std::vector<std::string> &allOrders)
{
    Utils utils;
    std::vector<std::shared_ptr<Pizza>> kitchenOrders;
    std::shared_ptr<Pizza> pizzaOrder;
    std::vector<std::string> orderVector;

    for (std::string &order : allOrders) {
        if (!order.substr(0, 6).compare("status")) {
            displayStatus();
        }
        else if (isOrderAssignedHere(order)) {
            orderVector = utils.stringToVector(order);
            pizzaOrder = std::make_shared<Pizza>((PizzaType)std::atoi(orderVector.at(0).c_str()), (PizzaSize)std::atoi(orderVector.at(1).c_str()), this->_cookingTimeMultiplier);
            kitchenOrders.emplace_back(pizzaOrder);
        }
    }
    return (kitchenOrders);
}
