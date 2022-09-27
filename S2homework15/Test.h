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

namespace fs = std::filesystem;

//struct Answer
//{
//	std::string text;
//	bool correct;
//};
//
//struct Question
//{
//	std::string text;
//	std::vector<Answer> answers;
//};

//struct Time
//{
//	short hour;
//	short minute;
//	short second;
//};

class Test
{
private:
	std::vector<Question> questions;
	int timeDurSec;
	fs::path homePath = fs::current_path().string() + "\\Tests";
	std::string delimiter = "-|-";
	//std::string testName;
public:
	Test() {}
	Test(std::vector<Question> questions)
	{
		this->questions = questions;
	}
	void init();
	void setTime(int seconds);
	double getScore(std::vector<Answer> results);
	void addQuestion();
	Question& getQuestion(int idx);
	std::vector<Question> getQuestions();
	void readTestFile(std::string name);
	void writeTestFile(std::string name);
	//void timeInit(int seconds);
};