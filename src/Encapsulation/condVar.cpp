/*
** EPITECH PROJECT, 2020
** undefined
** File description:
** condVar
*/

#include "../../include/Encapsulation/condVar.hpp"

void Plazza::condVar::notifyOne(void)
{
    _cond.notify_one();
}

void Plazza::condVar::notifyAll(void)
{
    _cond.notify_all();
}

void Plazza::condVar::setLock(std::mutex tmp)
{
    std::unique_lock<std::mutex> fnl(tmp);

    this->_lock = std::unique_lock<std::mutex> (tmp);
}

bool Plazza::condVar::waitLock(void)
{
    _cond.wait(_lock);
    return true;
}