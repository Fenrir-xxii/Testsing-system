#include "Test.h"

bool timeInit(int seconds, std::atomic_bool& run)
{
	auto start = std::chrono::system_clock::now();
	auto end = start + std::chrono::seconds(seconds);

	for (int i = 0; i < seconds + 1; ++i)
	{
		if (!run)
		{
			throw std::runtime_error("timeout");
		}
		
		SetCursorPosition(0, 12);
		std::cout << "                    ";
		SetCursorPosition(0, 12);
		std::cout << "Time until end: ";
		if ((seconds - i) <= 5)
		{
			SetColor(ConsoleColor::RED_FADE, ConsoleColor::BLACK);
		}
		std::cout << (seconds - i) << '\n';
		std::this_thread::sleep_for(std::chrono::seconds(1));
		SetColor(ConsoleColor::WHITE, ConsoleColor::BLACK);
	}


	while (true)
	{
		if (std::chrono::system_clock::now() > end)
		{
			return false;
		}
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}

	SetCursorPosition(0, 13);
	std::cout << "Times up";
	SetColor(ConsoleColor::WHITE, ConsoleColor::BLACK);
	return run ? true : false;
}

void Test::init()
{
	std::vector<std::string> options ({ "Start test" , "Exit" });
	Menu menu(options);
	menu.drawOptions();
	int key;
	int selection = -1;
	while (selection == -1)
	{
		menu.drawFrame();

		key = getKey();
		if (key == -1) {
			Sleep(100);
			continue;
		}

		switch (key)
		{
		case UP_ARROW:
			menu.up();
			menu.drawOptions();
			break;
		case DOWN_ARROW:
			menu.down();
			menu.drawOptions();
			break;
		case ENTER:
			selection = menu.getSelectedOption();
			break;
		default:
			break;
		}
		Sleep(100);
	}
	system("cls");
	bool work = true;
	Menu menuTest(getQuestions());
	std::atomic_bool run;
	run = true;
	auto future = std::async(timeInit, this->timeDurSec, std::ref(run));
	auto start = std::chrono::system_clock::now();
	auto end = start + std::chrono::seconds(this->timeDurSec);
	auto nowTime = std::chrono::system_clock::now();
	int keyTest = 0;
	int num = 0;
	double result = 0;
	bool answered = false;
	bool t = true;
	std::vector<Answer> studentAnswers;

	while (work)
	{
		switch (selection)
		{
		case TestMenuOptions::START_TEST:
			selection = -1;
			for (int counter = 0; counter < questions.size(); counter++)
			{
				clearArea(60, 11); // cls clears all console including countdown
				menuTest.setActiveOption(0);
				menuTest.drawQuestion(getQuestion(counter));
				answered = false;
				while (!answered)
				{
					if (std::chrono::system_clock::now() > end)
					{
						run = false;
						break;
					}

					keyTest = getKey();
					if (keyTest == -1) {
						Sleep(100);
						continue;
					}

					switch (keyTest)
					{
					case UP_ARROW:
						menuTest.up();
						menuTest.drawOptions();
						break;
					case DOWN_ARROW:
						menuTest.down();
						menuTest.drawOptions();
						break;
					case ENTER:
						num = menuTest.getSelectedOption();
						studentAnswers.push_back(questions[counter].answers[num]);
						answered = true;
						break;
					default:
						break;
					}
				}
			}
			system("cls");
			SetColor(ConsoleColor::WHITE, ConsoleColor::BLACK);
			result = getScore(studentAnswers);
			std::cout << result << "%" << std::endl;
			nowTime = std::chrono::system_clock::now();
			std::chrono::duration<double> diff = nowTime - start;
			SetCursorPosition(0, 1);
			std::cout << "Time: " << diff.count() << " s." << std::endl;
			//std::this_thread::sleep_for(std::chrono::milliseconds(3000));
			work = false;
			run = false;
			try
			{
				t = future.get();
			}
			catch (const std::runtime_error& ex)
			{
				std::cout << "You've finish the test\n\n";
				system("pause");
			}
			break;
		case TestMenuOptions::EXIT_TEST:
			work = false;
			break;
		default:
			break;
		}
	}
}

void Test::createTest()
{
	Menu m;
	m.drawMessageFrame("Enter test's name:");
	std::string newTestName;
	std::getline(std::cin, newTestName);
	newTestName += ".txt";
	this->testName = newTestName;
	bool enoughtQuestions = false;
	std::vector <std::string> v({"Yes", "No"});
	Menu yesNo(v);
	int key = 0;
	bool work = true;
	int num = -1;
	do
	{
		addQuestion();
		m.drawMessageFrame("Add another question for this test?");
		yesNo.drawFrame(1, 1);
		yesNo.drawOptions(3, 3);
		work = true;
		do
		{
			key = getKey();
			switch (key)
			{
			case UP_ARROW:
				yesNo.up();
				yesNo.drawOptions(3, 3);
				break;
			case DOWN_ARROW:
				yesNo.down();
				yesNo.drawOptions(3, 3);
				break;
			case ENTER:
				num = yesNo.getSelectedOption();
				if (num == YES_NO_MENU::NO) 
				{
					enoughtQuestions = true;
				}
				system("cls");
				work = false;
				break;
			default:
				break;
			}

		} while (work);

	} while (!enoughtQuestions);
	m.drawMessageFrame("Enter test's duration (in seconds):");
	int seconds = 0;
	do
	{
		try
		{
			while (true)
			{
				std::cin >> seconds;
				if (std::cin.fail()) {
					std::cin.clear();
					std::cin.ignore(256, '\n');
					system("cls");
					throw "Error: wrong input type. Input must be number (integer)\nTry again\n";
				}
				if (seconds <= 0) {
					system("cls");
					std::cout << "Number is less than or equal to 0\nTry again\n" << std::endl;
				}
				else
				{
					break;
				}
			}
		}
		catch (const char* error)
		{
			std::cout << error << std::endl;
		}
	} while (seconds <= 0);
	std::cin.clear();
	std::cin.ignore(256, '\n');
	setTime(seconds);
	writeTestFile();
}

void Test::setTime(int seconds)
{
	this->timeDurSec = seconds;
}

double Test::getScore(std::vector<Answer> results)
{
	int correctAnswerCount = 0;
	double score = 0;

	
	for (int i = 0; i < results.size(); i++)
	{
		if (results[i].correct)
		{
			correctAnswerCount++;
		}
	}

	score = (double)correctAnswerCount / questions.size() * 100;
	return score;
}

void Test::addQuestion()
{
	Question newQuestion;
	Menu m;
	std::vector <std::string> v;
	v.push_back("Yes");
	v.push_back("No");
	Menu yesNo(v);
	m.drawMessageFrame("Enter question's text:");
	std::getline(std::cin, newQuestion.text);
	int answerCount = 0;
	Answer answer;
	int key = 0;
	bool enoughAnswers = false;
	bool work = true;
	int num = 0;
	do
	{
		if (answerCount >= 2)
		{
			system("cls");
			m.drawMessageFrame("Add another answer?");
			yesNo.drawFrame(1, 1);
			yesNo.drawOptions(3, 3);
			work = true;
			do
			{
				key = getKey();
				switch (key)
				{
				case UP_ARROW:
					yesNo.up();
					yesNo.drawOptions(3, 3);
					break;
				case DOWN_ARROW:
					yesNo.down();
					yesNo.drawOptions(3, 3);
					break;
				case ENTER:
					num = yesNo.getSelectedOption();
					if (num == YES_NO_MENU::NO) 
					{
						enoughAnswers = true;
					}
					system("cls");
					work = false;
					break;
				default:
					break;
				}

			} while (work);
		}
		if (!enoughAnswers)
		{
			m.drawMessageFrame("Enter answer: #" + std::to_string(answerCount + 1));
			std::getline(std::cin, answer.text);
			answer.correct = false;
			newQuestion.answers.push_back(answer);
			answerCount++;
		}

	} while (!enoughAnswers);

	std::vector<std::string> answersText;
	for (int i = 0; i < newQuestion.answers.size(); i++)
	{
		answersText.push_back(newQuestion.answers[i].text);
	}

	m.drawMessageFrame("Pick correct answer");
	Menu menuTest(answersText);

	work = true;
	do
	{
		menuTest.drawFrame(1, 1);
		menuTest.drawOptions(3, 3);

		key = getKey();
		switch (key)
		{
		case UP_ARROW:
			menuTest.up();
			menuTest.drawOptions(3, 3);
			break;
		case DOWN_ARROW:
			menuTest.down();
			menuTest.drawOptions(3, 3);
			break;
		case ENTER:
			num = menuTest.getSelectedOption();
			newQuestion.answers[num].correct = true;
			system("cls");
			work = false;
			break;
		default:
			break;
		}

	} while (work);
	this->questions.push_back(newQuestion);

	system("cls");
}

Question& Test::getQuestion(int idx)
{
	return questions[idx];
}

std::vector<Question> Test::getQuestions()
{
	return questions;
}

void Test::writeTestFile()
{
	fs::path path = this->homePath;
	fs::path mainPath = fs::current_path();
	fs::current_path(path);
	std::string name = this->testName;
	path /= name;
	std::ofstream ofs;
	ofs.open(name, std::ios::out);

	for (int i = 0; i < questions.size(); ++i)
	{
		ofs << questions[i].text;

		for (int j = 0; j < questions[i].answers.size(); j++)
		{
			ofs << this->delimiter << questions[i].answers[j].text << this->delimiter << (std::boolalpha) << questions[i].answers[j].correct;
		}
		ofs << this->delimiter << std::endl;
	}
	ofs << "TestDuration:" << this->timeDurSec << std::endl;
	ofs.close();
	cryptor.crypt(name);
	fs::current_path(mainPath);
}

void Test::readTestFile(std::string name)
{
	fs::path path = this->homePath;
	path /= name;
	cryptor.decrypt(path);
	std::string timeDuration = "TestDuration:";
	std::string text;
	std::ifstream ifs(path);
	bool foundDurationTimeLine = false;
	if (ifs.is_open())
	{
		while (getline(ifs, text))
		{
			size_t pos = 0;
			std::string data;
			Question q;
			Answer a;
			int counter = 0;
			bool hasAnswerValidation = false;
			if (text.substr(0, 13) == timeDuration)
			{
				this->timeDurSec = stoi(text.substr(13));
				foundDurationTimeLine = true;
			}

			while ((pos = text.find(this->delimiter)) != std::string::npos)
			{
				data = text.substr(0, pos);
				hasAnswerValidation = false;
				if (!counter)
				{
					q.text = data;
				}
				else
				{
					if (counter % 2 != 0)
					{
						a.text = data;
					}
					else
					{
						if (data == "true")
						{
							a.correct = true;
						}
						else
						{
							a.correct = false;
						}
						hasAnswerValidation = true;
					}
					if (hasAnswerValidation)
					{
						q.answers.push_back(a);
					}
				}
				text.erase(0, pos + this->delimiter.length());
				counter++;
			}
			if (!foundDurationTimeLine)  // last row (line) is Duration Time not a Question
			{
				this->questions.push_back(q);
			}
		}
		ifs.close();
		cryptor.crypt(path);
	}
	else
	{
		std::cout << "Unable to open file" << std::endl;
	}
	this->testName = name;
}

std::string Test::getTestName()
{
	return this->testName;
}

void Test::setTestName(std::string name)
{
	this->testName = name;
}

void Test::clearArea(int x, int y)  // to clear certain area (for countdown time)
{
	for (int i = 0; i < y; i++)
	{
		for (int j = 0; j < x; j++)
		{
			SetCursorPosition(j, i);
			std::cout << " ";
		}
	}
}