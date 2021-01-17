/*
** EPITECH PROJECT, 2020
** undefined
** File description:
** Fork
*/

#ifndef FORK_HPP_
#define FORK_HPP_

#include <list>
#include <unistd.h>
#include <iostream>
#include <sys/types.h>
#include <sys/wait.h>

namespace Plazza {
    class Fork {
        public:
            Fork() = default;
            ~Fork() = default;

            pid_t addFork(void);
            void delFork(pid_t curr);

            bool waitPid(void);
        protected:
        private:
            std::list<pid_t> _pid;
    };
};

#endif /* !FORK_HPP_ */
