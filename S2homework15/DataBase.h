#pragma once
#include "Student.h"
#include "Test.h"

class DataBase
{
private:
	std::vector<Student> students;
	std::vector<Test> tests;
	fs::path testsPath = fs::current_path().string() + "\\Tests";
	fs::path studentsPath = fs::current_path().string() + "\\Users";
	fs::path studentsCredentialsPath = fs::current_path().string() + "\\Users\\Credentials.txt";
	std::string delimiter = "-|-";
	FileCryptor cryptor;
	void loadTests();
	void loadUsers();
public:
	//DataBase() {};
	DataBase() 
	{
		loadTests();
		loadUsers();
	};

	std::vector < std::string> getLogins();
	std::vector <Test> getTests();
	Student& getStudent(std::string login);
	void refresh();

};