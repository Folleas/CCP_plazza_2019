/*
** EPITECH PROJECT, 2020
** undefined
** File description:
** main
*/

#include "Encapsulation/ThreadPool.hpp"
#include <iostream>

std::mutex mutex;

void printFunction()
{
    mutex.lock();
    static std::size_t pars = 0;

    std::cout << 150 * pars++ << std::endl;
    mutex.unlock();
}

int main()
{
    Plazza::Encapsulation::ThreadPool pool(4);

    pool.pushOrder(printFunction);
    pool.pushOrder(printFunction);
    pool.pushOrder(printFunction);
    pool.waitAll();
    return (1);
}