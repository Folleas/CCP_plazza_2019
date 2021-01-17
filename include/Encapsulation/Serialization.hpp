/*
** EPITECH PROJECT, 2020
** CCP_plazza_2019
** File description:
** Serialization
*/

#ifndef SERIALIZATION_HPP_
#define SERIALIZATION_HPP_

#include <string>
#include <iostream>
#include <sstream>
#include <memory>

namespace Plazza {
    class ASerialization {
        public:
            ASerialization();
            ~ASerialization();

            template<typename First, typename... Atrs>
            std::string serializeObject(First first, Atrs... attributes);
            template<typename Atr>
            std::string serializeObject(Atr attribute);

            virtual std::shared_ptr<ASerialization> unserializeObject(std::string serializedObject) = 0;
        protected:
    };

    template<typename Atr>
    std::string ASerialization::serializeObject(Atr attribute)
    {
        std::stringstream stringStream;

        stringStream << attribute << ":";
        return (stringStream.str());
    }

    template<typename First, typename... Atrs>
    std::string ASerialization::serializeObject(First first, Atrs... attributes)
    {
        std::string serialized = "";

        serialized += this->serializeObject(first);
        serialized += this->serializeObject(attributes...);
        return (serialized);
    }
};


#endif /* !SERIALIZATION_HPP_ */
