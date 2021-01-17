/*
** EPITECH PROJECT, 2020
** undefined
** File description:
** condVar
*/

#ifndef CONDVAR_HPP_
#define CONDVAR_HPP_

#include <pthread.h>
#include <mutex>
#include <condition_variable>

namespace Plazza {
    class condVar {
        public:
            condVar() = default;
            ~condVar() = default;

            void setLock(std::mutex tmp);

            void notifyOne(void);
            void notifyAll(void);

            bool waitLock(void);
        private:
            std::unique_lock<std::mutex> _lock;
            std::mutex _mu;
            std::condition_variable _cond;
    };
};

#endif /* !CONDVAR_HPP_ */
