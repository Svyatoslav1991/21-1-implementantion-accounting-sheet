#include "functions.h"

#include <fstream>
#include <string>

//Check the entered name for correctness
bool isNormalName(std::string name) noexcept
{
	if (name.size() == 0)
	{
		std::cout << "It can't be empty. Try again\n";
		return false;
	}
	else if ((name[0] < 65) || (name[0] > 90))
	{
		std::cout << "Name must start from big letter. Try again\n";
		return false;
	}
	else
	{
		for (int64_t i = 1; i < name.size(); ++i)
		{
			if ((name[i] < 97) || (name[i] > 122))
			{
				std::cout << "The rest must contain only small letters. Try again\n";
				return false;
			}
		}
	}

	return true;
}

////////////////////////////////////////////////////////////////////////////////////////

//Check date
bool isCorrectDate(std::string date) noexcept
{
	if (date.size() != 10)
	{
		std::cout << "Wrong date size. Try again\n";
		return false;
	}
	else
	{
		for (int64_t i = 0; i < date.size(); ++i)
		{
			if (i == 2 || i == 5)
			{
				if (date[i] != '.')
				{
					std::cout << "The date is in the wrong format. Try again\n";
					return false;
				}
			}
			else
			{
				if ((date[i] < '0') || (date[i] > '9'))
				{
					std::cout << "Date entered incorrectly. Try again.\n";
					return false;
				}

				if (i == 1 || i == 4)
				{
					std::string value;
					value.push_back(date[i - 1]);
					value.push_back(date[i]);

					int64_t number = std::atoi(value.c_str());

					if (i == 1)
					{
						if (number < 1 || number > 31)
						{
							std::cout << "The day was entered incorrectly. Try again\n";
							return false;
						}
					}
					else
					{
						if (number < 1 || number > 12)
						{
							std::cout << "The month was entered incorrectly. Try again\n";
							return false;
						}
					}
				}
				else if (i == 9)
				{
					std::string value;
					value.push_back(date[i - 3]);
					value.push_back(date[i - 2]);
					value.push_back(date[i - 1]);
					value.push_back(date[i]);

					int year = std::atoi(value.c_str());

					if (year < 2000)
					{
						std::cout << "The year was entered too early. Try again\n";
						return false;
					}
					else if (year > 2022)
					{
						std::cout << "We can't use future. Try again\n";
						return false;
					}
				}
			}
		}
	}

	return true;
}

////////////////////////////////////////////////////////////////////////////////////////

//Check pay
bool isCorrectPay(std::string pay) noexcept
{
	for (int64_t i = 0; i < pay.size(); ++i)
	{
		if ((pay[i] < '0') || (pay[i] > '9'))
		{
			std::cout << "Pay must contein only numbers. Try again.\n";
			return false;
		}
	}

	return true;
}

//////////////////////////////////////////////////////////////////////////////////////////

std::string chooseCommand() noexcept
{
	std::string command;

	do
	{
		std::cout << "\nEnter \"add\" to add new employer\nEnter \"list\" to print a list of employers\nEnter \"exit\" to quit a programm\n";
		command = myCin<decltype(command)>();
	} while (!(command == "add" || command == "list" || command == "exit"));

	return command;
}

//////////////////////////////////////////////////////////////////////////////////////////

void commandProcessing(const std::string COMMAND)
{
	if (COMMAND == "add")
	{
		commandProcessingAdd();
	}
	else if (COMMAND == "list")
	{
		commandProcessingList();
	}
	else if (COMMAND != "exit")
	{
		throw std::exception("Wrong command");
	}
}

//////////////////////////////////////////////////////////////////////////////////////////

void commandProcessingAdd()
{
	std::string path = "statement.txt";
	std::ofstream statement(path, std::ios::app);

	if (statement.is_open())
	{
		Employer employer = createEmployer();

		std::string data = employer.name + " " + employer.surname + " " + std::to_string(employer.pay) + " " + employer.date + "\n";

		statement << data;

		statement.close();
	}
	else
	{
		throw std::exception("Can't open file");
	}
}

//////////////////////////////////////////////////////////////////////////////////////////

//create a worker
Employer createEmployer() noexcept
{
	Employer employer;

	std::cout << "\n";

	do
	{
		std::cout << "Name from capitalized letter\n";
		employer.name = myCin<decltype(employer.name)>();
	} while (!isNormalName(employer.name));

	do
	{
		std::cout << "Surname from capitalized letter\n";
		employer.surname = myCin<decltype(employer.surname)>();
	} while (!isNormalName(employer.surname));

	do
	{
		std::cout << "Pay (only numbers)\n";
		employer.pay = myCin<decltype(employer.pay)>();
	} while (!isCorrectPay(std::to_string(employer.pay)));

	do
	{
		std::cout << "Date (XX.XX.XXXX)\n";
		employer.date = myCin<decltype(employer.date)>();
	} while (!isCorrectDate(employer.date));

	return employer;
}

//////////////////////////////////////////////////////////////////////////////////////////

//Handling the "list" command
void commandProcessingList()
{
	std::string str;
	std::string path = "statement.txt";

	std::ifstream statement(path);
	if (statement.is_open())
	{
		std::vector<Employer> vEmployers;

		while (true)
		{
			Employer employer;
			
			statement >> employer.name >> employer.surname >> employer.pay >> employer.date;

			if (statement.eof() || employer.name.empty())
			{
				break;
			}

			vEmployers.push_back(employer);
		}
		statement.close();

		printEmployers(vEmployers);
	}
	else
	{
		throw std::exception("Can't open file");
	}
}

//////////////////////////////////////////////////////////////////////////////////////////

//Display the workers on the screen
void printEmployers(std::vector<Employer> vEmployers) noexcept
{
	std::cout << "\n";

	for (const auto& eployer : vEmployers)
	{
		std::cout << eployer.name << "\t" << eployer.surname << "\t" << eployer.pay << "\t" << eployer.date << "\n";
	}

	std::cout << "\n";
}
