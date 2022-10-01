#include "Student.h"

void Student::setPassword(std::string password)
{
	this->credentials.password = password;
}

void Student::setLogin(std::string login)
{
	this->credentials.login = login;
}

bool Student::passValidation(std::string password)
{
	return this->credentials.password == password;
}

std::string Student::getLogin()
{
	return this->credentials.login;
}