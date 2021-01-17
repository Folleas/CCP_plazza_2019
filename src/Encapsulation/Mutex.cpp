/*
** EPITECH PROJECT, 2020
** CCP_plazza_2019
** File description:
** Mutex
*/

#include "Encapsulation/Mutex.hpp"

Plazza::Encapsulation::Mutex::Mutex()
{
    pthread_mutex_init(&this->_mutexID, NULL);
}

Plazza::Encapsulation::Mutex::~Mutex()
{
    pthread_mutex_destroy(&this->_mutexID);
}

int Plazza::Encapsulation::Mutex::mutexLock()
{
    return (pthread_mutex_lock(&this->_mutexID));
}

int Plazza::Encapsulation::Mutex::mutexUnlock()
{
    return (pthread_mutex_unlock(&this->_mutexID));
}

int Plazza::Encapsulation::Mutex::mutexTrylock()
{
    return (pthread_mutex_trylock(&this->_mutexID));
}

pthread_mutex_t Plazza::Encapsulation::Mutex::getMutexID()
{
    return (this->_mutexID);
}