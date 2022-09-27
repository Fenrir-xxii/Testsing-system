#pragma once
#include <string>
#include <filesystem>

namespace fs = std::filesystem;

struct Credentials
{
	std::string login;
	std::string password;
};

class Student
{
private:
	Credentials credentials;
	//fs::path homePath = fs::current_path().string() + "\\Users";
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
	//void createHomeDirectory();

};
