/*
** EPITECH PROJECT, 2020
** CCP_plazza_2019
** File description:
** ThreadPool
*/

#include <vector>
#include <queue>
#include <thread>
#include <mutex>
#include <atomic>
#include <condition_variable>
#include <functional>

namespace Plazza {
    namespace Encapsulation {
        class ThreadPool {
            public:
                ThreadPool() = delete;
                ThreadPool(const ThreadPool &other) = delete;
                ThreadPool(std::size_t threads);
                ~ThreadPool();

                void initThreads(std::size_t threads);
                void pushOrder(const std::function<std::string()>&);
                void waitTasksEnd() const;

                std::size_t resultSize();
                void pushResult(std::string result);
                std::string popResult();
            private:
                std::function<std::string()> assignTask();
                void pushTask(const std::function<std::string()>& task);

                std::queue<std::string> _result;
                std::vector<std::thread> _workers;
                std::queue<std::function<std::string()>> _taskQueue;
                std::atomic_uint _taskCount;
                std::mutex _mutex;
                std::condition_variable _condition;
                std::atomic_bool _stop;
            };
    };
};