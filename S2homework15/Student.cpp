#include "Student.h"

//Student::Student(Credentials credentials)
//{
//	this->credentials = credentials;
//}

//Student::Student(std::string login, std::string password)
//{
//	this->credentials.login = login;
//	this->credentials.password = password;
//}

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

//void Student::createHomeDirectory()
//{
//	fs::path path = this->homePath;
//	path /= this->credentials.login;
//	fs::create_directory(path);
//}