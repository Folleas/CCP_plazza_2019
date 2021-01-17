/*
** EPITECH PROJECT, 2020
** CCP_plazza_2019
** File description:
** Queue
*/

#ifndef QUEUE_HPP_
#define QUEUE_HPP_

#include <queue>

namespace Plazza {
    template <typename Type>
    class Queue {
        public:
            Queue(const Queue &other);
            ~Queue();

            void push(Type newValue);
            void pop(void);
            bool empty();
            size_t size();
            void swap(Queue<Type> &first, Queue<Type> &second);
            void swap(std::queue<Type> &first, std::queue<Type> &second);
            void emplace(Type newValue);
            Type &front(void);
            Type &queue(void);
        private:
            std::queue<T> _queue;
    };
};

#endif /* !QUEUE_HPP_ */