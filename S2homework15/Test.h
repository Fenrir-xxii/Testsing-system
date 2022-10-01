#pragma once
#include <iostream>
#include <filesystem>
#include <string>
#include <vector>
#include <chrono>
#include <thread>
#include <future>
#include <fstream>
#include "menu.h"
#include "struct.h"
#include "EnumMenu.h"
#include "FileCryptor.h"

namespace fs = std::filesystem;

class Test
{
private:
	std::vector<Question> questions;
	int timeDurSec;
	fs::path homePath = fs::current_path().string() + "\\Tests";
	std::string delimiter = "-|-";
	std::string testName = "test.txt";
	FileCryptor cryptor;
public:
	Test() {}
	Test(std::vector<Question> questions)
	{
		this->questions = questions;
	}
	void init();
	void createTest();
	void setTime(int seconds);
	double getScore(std::vector<Answer> results);
	void addQuestion();
	Question& getQuestion(int idx);
	std::vector<Question> getQuestions();
	void readTestFile(std::string name);
	void writeTestFile();
	std::string getTestName();
	void setTestName(std::string name);
	void clearArea(int x, int y);

};