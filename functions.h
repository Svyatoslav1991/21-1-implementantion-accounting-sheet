#pragma once
#ifndef FUNCTION_H
#define FUNCTION_H

#include <iostream>
#include <vector>
#include "employer.h"

//variable value input function
template <typename T>
T myCin() noexcept
{
    bool good = true;

    T variable;

    do
    {
        std::cout << "Enter the value of the variable: ";
        std::cin >> variable;

        good = std::cin.good();

        if (!good)
        {
            std::cout << "You entered something wrong\n";
        }
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    } while (!good);

    return variable;
}

//Check the entered name for correctness
bool isNormalName(std::string name) noexcept;

//Check date
bool isCorrectDate(std::string date) noexcept;

//Check pay
bool isCorrectPay(std::string pay) noexcept;

//choose a command
std::string chooseCommand() noexcept;

//command processing
void commandProcessing(const std::string COMMAND);

//Handling the "add" command
void commandProcessingAdd();

//create a worker
Employer createEmployer() noexcept;

//Handling the "list" command
void commandProcessingList();

//Display the workers on the screen
void printEmployers(std::vector<Employer> vEmployers) noexcept;


#endif // FUNCTION_H
