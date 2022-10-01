#pragma once
#include <string>
#include <filesystem>
#include "struct.h"

namespace fs = std::filesystem;

class Student
{
private:
	Credentials credentials;
public:

	Student() {};
	Student(Credentials credentials) 
	{ 
		this->credentials = credentials; 
	};
	Student(std::string login, std::string password) 
	{
		this->credentials.login = login;
		this->credentials.password = password;
	};

	void setPassword(std::string password);
	void setLogin(std::string login);
	std::string getLogin();
	bool passValidation(std::string password);

};
