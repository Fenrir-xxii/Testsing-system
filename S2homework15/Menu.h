#pragma once
#include <iostream>
#include <vector>
#include <string>
#include "console.h"
#include "struct.h"


class Menu {
private:
	int activeOption = 0;
	std::vector<std::string> options;
	size_t getMaxItemSize() const;
	size_t getFrameWidth() const;
	size_t getFrameHeight() const;
public:
	Menu(const std::vector<std::string>& options);
	Menu(std::vector<Question> options);
	Menu() {};
	void drawFrame();

	void drawFrame(int cX, int xY);

	void drawFrame(std::string header);

	void drawOptions();

	void drawOptions(int cX, int cY);

	void drawQuestion(Question q);

	//void drawQuestion(std::string question);

	void down();

	void up();

	int getSelectedOption() const;

	void setActiveOption(int idx);

	void drawMessageFrame(std::string message);
};