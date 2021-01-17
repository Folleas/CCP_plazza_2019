/*
** EPITECH PROJECT, 2020
** CCP_plazza_2019
** File description:
** Mutex
*/

#ifndef MUTEX_HPP_
#define MUTEX_HPP_

#include <pthread.h>

namespace Plazza {
    namespace Encapsulation {
        class Mutex {
            public:
                Mutex();
                ~Mutex();

                int mutexLock();
                int mutexUnlock();
                int mutexTrylock();

                pthread_mutex_t getMutexID();
            private:
                pthread_mutex_t _mutexID;
        };
    };
};

#endif /* !MUTEX_HPP_ */
