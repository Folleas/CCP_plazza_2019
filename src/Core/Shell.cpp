/*
** EPITECH PROJECT, 2020
** ccp_plazza_2019
** File description:
** Shell
*/

#include "../../include/Core/Shell.hpp"
#include "../../include/Core/Parser.hpp"
#include "../../include/Plazza/Reception.hpp"

Plazza::Shell::Shell(char **av)
{
    this->initShell(av);
}

void Plazza::Shell::deleteTmpFiles()
{
    DIR *dir;
    struct dirent *ent;
    std::string tmp;

    if ((dir = opendir ("./res/")) != NULL) {
        while ((ent = readdir (dir)) != NULL) {
            tmp.assign(ent->d_name);
            if (tmp.size() > 3 && !(tmp.substr(0, 3).compare(".to"))) {
                remove(("./res/" + tmp).c_str());
            }
        }
        closedir (dir);
    }
    else {
        std::cerr << "Couldn't open ressource directory";
        exit (84);
    }
}


void Plazza::Shell::runShell()
{
    Reception reception;
    std::string input;
    std::vector<std::string> command;
    std::vector<std::string> parsedInput;
    bool isRunning = true;

    reception.setCookingTime(atoi(args.at(0).c_str()));
    reception.setNbCooksPerKitchen(atoi(args.at(1).c_str()));
    reception.setTimeReplaceIngredient(atoi(args.at(2).c_str()));
    this->deleteTmpFiles();
    while(isRunning) {
        if(!(getline(std::cin, input))) {
            isRunning = false;
        }
        if(input == "exit") {
            isRunning = false;
        }
        else {
            parsedInput = reception.splitInput(input);
            for (int i = 0; i < parsedInput.size(); i++) {
                command = reception.parseInput(parsedInput.at(i));
                if (!reception.checkParser(command))
                    std::cout << "Your order isn't with the good format.\n";
                else {
                    reception.runReception(command);
                }
            }
        }
    }
    return;
}

void Plazza::Shell::initShell(char **av)
{
    args.push_back(av[1]);
    args.push_back(av[2]);
    args.push_back(av[3]);
}