#pragma once
#include <vector>
#include "Test.h"
#include "Student.h"
#include "EnumMenu.h"
#include "DataBase.h"

class ClassRoom
{
private:
	DataBase dataBase;
	std::vector <Test> tests;
	std::vector <std::string> students;
	fs::path testsPath = fs::current_path().string() + "\\Tests";
	fs::path studentsPath = fs::current_path().string() + "\\Users";
	FileCryptor cryptor;
	void loadTests();
	void loadUsersLogins();
public:
	ClassRoom() 
	{
		loadTests();
		loadUsersLogins();
	};

	void init();
	void studentRegistration(std::string login, std::string password);
	void studentRegistrationMenu();
	void studentLogIn();
	bool isLoginUnique(std::string login);
	void createHomeDirectory(std::string login);
	void showMenu();
};
