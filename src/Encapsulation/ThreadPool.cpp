/*
** EPITECH PROJECT, 2020
** CCP_plazza_2019
** File description:
** ThreadPool
*/

#include "Encapsulation/ThreadPool.hpp"
#include <chrono>
#include <iostream>

Plazza::Encapsulation::ThreadPool::ThreadPool(std::size_t threads) :    _workers(),
                                                                _taskQueue(),
                                                                _taskCount(0u),
                                                                _mutex(),
                                                                _condition(),
                                                                _stop(false)
{
    initThreads(threads);
}

Plazza::Encapsulation::ThreadPool::~ThreadPool()
{
    _stop = true;
    _condition.notify_all();
    for (auto &worker: _workers) {
        worker.join();
    }
}

std::function<std::string()> Plazza::Encapsulation::ThreadPool::assignTask()
{
    std::unique_lock<std::mutex> lock(_mutex);
    std::function<std::string()> newTask;

    _condition.wait(lock, [this]() -> bool { return !_taskQueue.empty() || _stop;});
    if (_stop && _taskQueue.empty()) {
        newTask = nullptr;
        return (newTask);
    }
    newTask = std::move(_taskQueue.front());
    _taskQueue.pop();
    return (newTask);
}

std::size_t Plazza::Encapsulation::ThreadPool::resultSize()
{
    return (this->_result.size());
}

std::string Plazza::Encapsulation::ThreadPool::popResult()
{
    std::unique_lock<std::mutex> lock(_mutex);
    std::string tmp;

    if (!this->_result.empty()) {
        tmp.assign(this->_result.front());
        this->_result.pop();
    }
    else {
        tmp = "";
    }

    return(tmp);
}

void Plazza::Encapsulation::ThreadPool::pushResult(std::string newResult)
{
    std::unique_lock<std::mutex> lock(_mutex);
    this->_result.push(newResult);
}

void Plazza::Encapsulation::ThreadPool::initThreads(std::size_t threads)
{
    for (size_t i = 0; i < threads; i++) {
        _workers.emplace_back([this]() -> void {
            while (true) {
                std::function<std::string()> task = assignTask();
                if (task == nullptr)
                    return;
                std::string tmp = (task());
                this->pushResult(tmp);
                _taskCount--;
            }
        });
    }
}

void Plazza::Encapsulation::ThreadPool::pushTask(const std::function<std::string()>& task)
{
    std::unique_lock<std::mutex> lock(_mutex);
    _taskQueue.push(task);
}

void Plazza::Encapsulation::ThreadPool::pushOrder(const std::function<std::string()>& task)
{
    this->pushTask(task);
    _taskCount++;
    _condition.notify_one();
}

void Plazza::Encapsulation::ThreadPool::waitTasksEnd() const
{
    while (_taskCount != 0u) {
        std::this_thread::yield();
    }
}