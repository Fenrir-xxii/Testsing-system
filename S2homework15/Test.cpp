#include "Test.h"

enum TestMenuOptions { START_TEST, EXIT };

void timeInit(int seconds);

void Test::init()
{
	std::vector<std::string> options ({ "Start test" , "Exit" });
	//options.push_back("Start test");
	//options.push_back("Exit");
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
	auto future = std::async(timeInit, this->timeDurSec);
	auto start = std::chrono::system_clock::now();
	auto end = start + std::chrono::seconds(this->timeDurSec);
	auto nowTime = std::chrono::system_clock::now();
	int counter = 0;
	int keyTest = 0;
	int num = 0;
	double result = 0;
	bool answered = false;
	std::vector<Answer> studentAnswers;
	//system("cls");

	while (work)
	{
		switch (selection)
		{
		case TestMenuOptions::START_TEST:
			selection = -1;
			for (int counter = 0; counter < questions.size(); counter++)
			{
				//system("cls");
				clearArea(60, 11);
				/*if (counter == questions.size() - 1)
					work = false;*/
				menuTest.setActiveOption(0);
				menuTest.drawQuestion(getQuestion(counter));
				answered = false;
				while (!answered)
				{
					if (std::chrono::system_clock::now() > end)
					{
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
						//system("cls");
						answered = true;
						break;
					default:
						break;
					}
					//Sleep(100);
				}
			}
			system("cls");
			result = getScore(studentAnswers);
			std::cout << result << "%" << std::endl;
			nowTime = std::chrono::system_clock::now();
			std::chrono::duration<double> diff = nowTime - start;
			SetCursorPosition(0, 1);
			std::cout << "Time: " << diff.count() << " s." << std::endl;
			std::this_thread::sleep_for(std::chrono::milliseconds(2000));
			//std::cout << "EXIT";
			break;
		case TestMenuOptions::EXIT:
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
	addQuestion();
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
					if (num != 0) // 0 - 'Yes', 1 - 'No'
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


	system("cls");
}

//void Test::addQuestion()
//{
//	Question newQuestion;
//	Menu m;
//	//std::vector <std::string> v("Yes", "No");
//	std::vector <std::string> v;
//	v.push_back("Yes");
//	v.push_back("No");
//	Menu yesNo(v);
//	m.drawMessageFrame("Enter question's text:");
//	//std::cout << "Enter question's text:\n";
//	//std::cin << m;
//	std::getline(std::cin, newQuestion.text);
//	int answerCount = 0;
//	Answer answer;
//	//char correct;
//	int key = 0;
//	bool enoughAnswers = false;
//	bool work = true;
//	int num = 0;
//	do
//	{
//		if (answerCount >= 2)
//		{
//			m.drawMessageFrame("Add another answer?");
//			yesNo.drawFrame();
//			yesNo.drawOptions();
//			do
//			{
//				key = getKey();
//				switch (key)
//				{
//				case UP_ARROW:
//					yesNo.up();
//					yesNo.drawOptions();
//					break;
//				case DOWN_ARROW:
//					yesNo.down();
//					yesNo.drawOptions();
//					break;
//				case ENTER:
//					num = yesNo.getSelectedOption();
//					if (num != 0)
//					{
//						enoughAnswers = true;
//					}
//					system("cls");
//					work = false;
//					break;
//				default:
//					break;
//				}
//
//			} while (work);
//
//			//std::cout << "Add another answer? Y/N\n";
//			/*std::cin >> correct;
//			std::cin.ignore(256, '\n');
//			if (correct == 'n' or correct == 'N')
//			{
//				enoughAnswers = true;
//				break;
//			}*/
//		}
//		//std::string n = "Enter answer: #" +  std::to_string(answerCount + 1);
//		//m.drawMessageFrame("Enter answer: #" + answerCount + 1);
//		m.drawMessageFrame("Enter answer: #" + std::to_string(answerCount + 1));
//		//std::cout << "Enter answer: # " << answerCount +1 << '\n';
//		std::getline(std::cin, answer.text);
//		m.drawMessageFrame("Is this answer correct?");
//		yesNo.drawFrame();
//		yesNo.drawOptions();
//		do
//		{
//			key = getKey();
//			switch (key)
//			{
//			case UP_ARROW:
//				yesNo.up();
//				yesNo.drawOptions();
//				break;
//			case DOWN_ARROW:
//				yesNo.down();
//				yesNo.drawOptions();
//				break;
//			case ENTER:
//				num = yesNo.getSelectedOption();
//				if (num == 0)
//				{
//					answer.correct = true;
//				}
//				else
//				{
//					answer.correct = false;
//				}
//				system("cls");
//				work = false;
//				break;
//			default:
//				break;
//			}
//
//		} while (work);
//		//std::cout << "Is this answer correct? Y/N\n";
//		//std::cin.ignore(256, '\n');
//		/*std::cin >> correct;
//		std::cin.ignore(256, '\n');
//		if (correct == 'y' or correct == 'Y')
//		{
//			answer.correct = true;
//		}
//		else
//		{
//			answer.correct = false;
//		}*/
//		newQuestion.answers.push_back(answer);
//		answerCount++;
//	} while (!enoughAnswers);
//	system("cls");
//}

Question& Test::getQuestion(int idx)
{
	return questions[idx];
}

std::vector<Question> Test::getQuestions()
{
	return questions;
}

void timeInit(int seconds)
{
	auto start = std::chrono::system_clock::now();
	auto end = start + std::chrono::seconds(seconds);

	for (int i = 0; i < seconds + 1; ++i)
	{
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
		//std::this_thread::sleep_for(std::chrono::milliseconds(100));
		if (std::chrono::system_clock::now() > end)
		{
			break;
		}
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}
	//system("cls");
	SetCursorPosition(0, 13);
	std::cout << "Times up";
}

void Test::writeTestFile()
{
	fs::path path = this->homePath;
	//fs::current_path(path);
	std::string name = this->testName;
	path /= name;
	std::ofstream ofs;
	ofs.open(name, std::ios::out);
	//std::string divider = "-|-";

	for (int i = 0; i < questions.size(); ++i)
	{
		ofs << questions[i].text;// << divider;

		for (int j = 0; j < questions[i].answers.size(); j++)
		{
			ofs << this->delimiter << questions[i].answers[j].text << this->delimiter << (std::boolalpha) << questions[i].answers[j].correct;
		}
		ofs << this->delimiter << std::endl;
	}
	ofs << "TestDuration:" << this->timeDurSec << std::endl;
	ofs.close();

}

void Test::readTestFile(std::string name)
{
	fs::path path = this->homePath;
	//fs::current_path(path);
	path /= name;
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

void Test::clearArea(int x, int y)
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