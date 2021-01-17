/*
** EPITECH PROJECT, 2020
** CCP_plazza_2019
** File description:
** Pizza
*/

#ifndef PIZZA_HPP_
#define PIZZA_HPP_

#include <memory>
#include <vector>
#include <fstream>
#include <iostream>
#include <unordered_map>

#include "Core/Utils.hpp"
#include "../Encapsulation/Serialization.hpp"

namespace Plazza {
    class Pizza : public ASerialization {
        public:
            Pizza(PizzaType type, PizzaSize size, std::size_t cookingTimeMultiplicator);
            Pizza(const Pizza &other);
            ~Pizza();

            void setReciepe();
            void fillAttributes(std::string line);

            std::vector<std::string> getRecipe() const;

            std::string serialize();
            std::shared_ptr<ASerialization> unserializeObject(std::string serializeObject) final;

            std::size_t getBakeTime() const;
            std::size_t getCookingTimeMultiplier() const;
            bool getCooked() const;
            void setCooked(bool isCooked);
        private:
            bool isCooked;
            PizzaSize _size;
            PizzaType _type;
            std::vector<std::string> _recipe;
            std::size_t _bakeTime;
            std::size_t _cookingTimeMultiplier;
    };
    std::string operator<<(std::string &, Pizza &);
    std::shared_ptr<Pizza> operator<<(std::shared_ptr<Pizza> &, std::string &);
};

#endif /* !PIZZA_HPP_ */
