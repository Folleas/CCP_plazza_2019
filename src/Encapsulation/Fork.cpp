/*
** EPITECH PROJECT, 2020
** undefined
** File description:
** Fork
*/

#include "../../include/Encapsulation/Fork.hpp"

pid_t Plazza::Fork::addFork(void)
{
    pid_t pid = fork();

    if (pid == -1) {
        std::cerr << "Error: fork failed.\n";
        return (-1);
    } _pid.push_back(pid);
    return pid;
}

void Plazza::Fork::delFork(pid_t curr)
{
    kill(curr, SIGKILL);
}

bool waitPid(pid_t pid)
{
    if (waitpid(pid, 0, 0) == -1)
        return false;
    return true;
}