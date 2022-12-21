#include "functions.h"

int main() {
	std::cout << "\tTask number 1\n";
	std::cout << "\tImplementation of the accounting sheet\n\n";
	
	std::string command;

	try
	{
		do
		{
			command = chooseCommand();
			commandProcessing(command);

		} while (command != "exit");
	}
	catch (const std::exception& ex)
	{
		std::cout << ex.what() << "\n";
	}
	catch (...)
	{
		std::cout << "Something went wrong\n";
	}
	

	return 0;
}