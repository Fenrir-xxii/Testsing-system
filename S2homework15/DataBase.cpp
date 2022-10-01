#include "DataBase.h"

void DataBase::loadTests()
{
    std::vector <std::string> testsNames;
    std::string name;
    for (auto const& dirEntry : fs::directory_iterator{ this->testsPath })
    {
        if (dirEntry.is_regular_file())
        {
            name = dirEntry.path().filename().string();
            testsNames.push_back(name);
        }
    }

    for (int i = 0; i < testsNames.size(); i++)
    {
        Test newTest;
        newTest.readTestFile(testsNames[i]);
        this->tests.push_back(newTest);
    }
}

void DataBase::loadUsers()
{
    std::string name;
    Student student;
    std::string text;
    this->cryptor.decrypt(this->studentsCredentialsPath);
    std::ifstream ifs(this->studentsCredentialsPath);
    int counter = 0;

	if (ifs.is_open())
	{
		while (getline(ifs, text))
		{
			size_t pos = 0;
			std::string data;
            counter = 0;
			while ((pos = text.find(this->delimiter)) != std::string::npos)
			{
				data = text.substr(0, pos);
                if (!counter)
                {
                    student.setLogin(data);
                }
                else
                {
                    student.setPassword(data);
                }
				text.erase(0, pos + this->delimiter.length());
                counter++;
			}
            this->students.push_back(student);
		}
		ifs.close();
        this->cryptor.crypt(this->studentsCredentialsPath);
	}
	else
	{
		std::cout << "Unable to open file" << std::endl;
	}
}

std::vector <std::string> DataBase::getLogins()
{
    std::vector<std::string> logins;

    for (int i = 0; i < students.size(); i++)
    {
        logins.push_back(students[i].getLogin());
    }
    return logins;
}

std::vector <Test> DataBase::getTests()
{
    return this->tests;
}

Student& DataBase::getStudent(std::string login)
{
    for (int i = 0; i < students.size(); i++)
    {
        if (login == students[i].getLogin())
        {
            return students[i];
        }
    }
}

void DataBase::refresh()
{
    loadTests();
    loadUsers();
}