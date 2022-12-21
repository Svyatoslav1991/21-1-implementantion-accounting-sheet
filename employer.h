#pragma once
#ifndef EMPLOYER_H
#define EMPLOYER_H
#include <string>

struct Employer
{
	std::string name;
	std::string surname;
	int64_t pay;
	std::string date;//XX.XX.XXXX
};

#endif // EMPLOYER_H