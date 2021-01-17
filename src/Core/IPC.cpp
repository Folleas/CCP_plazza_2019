/*
** EPITECH PROJECT, 2020
** CCP_plazza_2019
** File description:
** IPC
*/

#include "../../include/Encapsulation/IPC.hpp"

void Plazza::IPC::writeMessage(std::string message, std::string path)
{
    std::ofstream myFile;

    myFile.open(path, std::ios::app);
    myFile << message;
    myFile.close();
}

void Plazza::IPC::deleteMessage(size_t posLine, std::string path)
{
    size_t i = 0;
    std::ifstream sup(path);
    std::fstream temp;
    std::string line;

    temp.open("./res/.temp", std::ios::app);
    while (getline(sup, line))
    {
        if (i != posLine)
            temp << line << std::endl;
        i = i + 1;
    }
    temp.close();
    sup.close();
    remove(path.c_str());
    rename("./res/.temp",path.c_str());
}

void Plazza::IPC::manageMessage(std::vector<std::string> &order, std::vector<std::string> lineVector, std::pair<std::size_t, std::size_t> stat, std::pair<std::string, std::string> statString)
{
    if (lineVector.size() == 3) {
        if (std::atoi(lineVector.at(2).c_str()) == stat.first) {
            order.push_back(statString.first);
            this->deleteMessage(stat.second, statString.second);
        }
        else if (stat.first == 1000) {
            order.push_back(statString.first);
            this->deleteMessage(stat.second, statString.second);
        }
    }
}

std::vector<std::string> Plazza::IPC::readIPC(std::string nameFile, std::size_t ID)
{
    std::vector<std::string> order;
    std::string line;
    std::ifstream myfile(nameFile);
    Utils utils;

    if (myfile.is_open()) {
        for (std::size_t i = 0; getline (myfile,line); i++) {
            std::vector<std::string> lineVector = utils.stringToVector(line);
            manageMessage(order, lineVector, std::make_pair(ID, i), std::make_pair(line, nameFile));
        }
        myfile.close();
    }
    return (order);
}

void Plazza::IPC::deleteFile(std::string fileName)
{
    remove(fileName.c_str());
}