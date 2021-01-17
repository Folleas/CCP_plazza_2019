/*
** EPITECH PROJECT, 2020
** CCP_plazza_2019
** File description:
** Thread
*/

#ifndef THREAD_HPP_
#define THREAD_HPP_

#include <pthread.h>

namespace Plazza {
    namespace Encapsulation {
        class Thread {
            public:
                Thread() = default;
                Thread(void *(function)(void *), void *param = NULL);
                ~Thread();

                void createThread(void *(function)(void *), void *param = NULL);
                void joinThread();
                void *getReturnValue();
            private:
                pthread_t _threadID;
                void *_returnValue;
        };
    };
};

#endif /* !THREAD_HPP_ */
