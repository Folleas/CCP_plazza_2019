/*
** EPITECH PROJECT, 2020
** CCP_plazza_2019
** File description:
** Thread
*/

#include "Thread.hpp"

Plazza::Encapsulation::Thread::Thread(void *(function)(void *), void *param)
{
    createThread(function, param);
}

void Plazza::Encapsulation::Thread::createThread(void *(function)(void *), void *param)
{
    pthread_create(&_threadID, NULL, function, param);
}

void Plazza::Encapsulation::Thread::joinThread()
{
    pthread_join(this->_threadID, &this->_returnValue);
}

void *Plazza::Encapsulation::Thread::getReturnValue()
{
    return (this->_returnValue);
}

Plazza::Encapsulation::Thread::~Thread()
{
}