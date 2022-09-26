#pragma once
#include <string>
#include <vector>


struct Answer
{
	std::string text;
	bool correct;
};

struct Question
{
	std::string text;
	std::vector<Answer> answers;
};