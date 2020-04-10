/*
** EPITECH PROJECT, 2020
** CPP_plazza_2019
** File description:
** TODO: add description
*/

#include "Reception/Reception.hpp"
#include "Socket/Client.hpp"

#include <iostream>
#include <sys/ipc.h>
#include <sys/msg.h>

using namespace Plazza;

Reception::Reception(float cookingMultiplier, int cooksPerKitchen, float regenerateTime) :
    _cookingMultiplier(cookingMultiplier),
    _cooksPerKitchen(cooksPerKitchen),
    _regenerateTime(regenerateTime),
    _shell(std::make_unique<UserShell>()),
    _server(std::make_unique<Server>()),
    _running(true)
{

}

void Reception::run()
{
    std::string command;
    fd_set writefs;
    fd_set readfs;

    while (!std::cin.eof()) {
        resetFdSet(&readfs, &writefs);
        FD_SET(1, &readfs);
        _server->setFdSet(&readfs, &writefs);
        if (select(FD_SETSIZE, &readfs, &writefs, NULL, NULL) < 0)
            throw ReceptionError("Select fail", "Select");
        translateSelect(readfs, writefs);
    }
}

void Reception::translateSelect(const fd_set &readfs, const fd_set &writefs)
{
    if (FD_ISSET(1, &readfs)) {
        std::string command;

        std::getline(std::cin, command);
        if (!command.empty())
            translateCommand(command);
    }
    _server->translateSelect(readfs, writefs);
}

void Reception::resetFdSet(fd_set *readfs, fd_set *writefs)
{
    FD_ZERO(readfs);
    FD_ZERO(writefs);
}

void Reception::translateCommand(const std::string &command)
try {
    std::unique_ptr<Order> order = std::make_unique<Order>(command);
    int child = fork();

    if (child == 0) {

        exit(0);
    } else {
    }
} catch (const ParserError &e) {
    std::cout << "Invalid command" << std::endl;
}

float Reception::getCookingMultiplier() const
{
    return _cookingMultiplier;
}

int Reception::getCooksPerKitchen() const
{
    return _cooksPerKitchen;
}

float Reception::getRegenerateTime() const
{
    return _regenerateTime;
}

void Reception::setCookingMultiplier(float cookingMultiplier)
{
    _cookingMultiplier = cookingMultiplier;
}

void Reception::setCooksPerKitchen(int cooksPerKitchen)
{
    _cooksPerKitchen = cooksPerKitchen;
}

void Reception::setRegenerateTime(float regenerateTime)
{
    _regenerateTime = regenerateTime;
}