#include <iostream>
#include <future>
#include "Test.h"
#include "Menu.h"
#include "Student.h"
#include "classRoom.h"
#include "DataBase.h"

void ShowConsoleCursor(bool showFlag)
{
    HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);

    CONSOLE_CURSOR_INFO     cursorInfo;

    GetConsoleCursorInfo(out, &cursorInfo);
    cursorInfo.bVisible = showFlag; // set the cursor visibility
    SetConsoleCursorInfo(out, &cursorInfo);
}

//void timeInit(int seconds)
//{
//    auto start = std::chrono::system_clock::now();
//    auto end = start + std::chrono::seconds(seconds);
//
//    for (int i = 0; i < seconds+1; ++i)
//    {
//        SetCursorPosition(0, 10);
//        std::cout << "Time until end: " << (seconds - i) << '\n';
//        std::this_thread::sleep_for(std::chrono::seconds(1));
//    }
//
//
//    while (true)
//    {
//        //std::this_thread::sleep_for(std::chrono::milliseconds(100));
//        if (std::chrono::system_clock::now() > end)
//        {
//            break;
//        }
//        std::this_thread::sleep_for(std::chrono::milliseconds(100));
//    }
//    //system("cls");
//    SetCursorPosition(0, 11);
//    std::cout << "Times up";
//}

//int timeInit2(int seconds)
//{
//    auto start = std::chrono::system_clock::now();
//    auto end = start + std::chrono::seconds(seconds);
//
//    for (int i = 0; i < seconds + 1; ++i)
//    {
//        SetCursorPosition(0, 10);
//        std::cout << "Time until end: " << (seconds - i) << '\n';
//        std::this_thread::sleep_for(std::chrono::seconds(1));
//    }
//
//
//    while (true)
//    {
//        //std::this_thread::sleep_for(std::chrono::milliseconds(100));
//        if (std::chrono::system_clock::now() > end)
//        {
//            break;
//        }
//        std::this_thread::sleep_for(std::chrono::milliseconds(100));
//    }
//    //system("cls");
//    SetCursorPosition(0, 11);
//    std::cout << "Times up";
//    return 0;
//}

//bool hasTime(std::chrono::system_clock startTime, std::chrono::seconds duration)
//{
//    auto end = startTime + std::chrono::seconds(duration);
//    return 
//}

//int main()
//{
//    ShowConsoleCursor(false);
//    
//    std::vector<Question> questions;
//    Question q1;
//    q1.text = "Question1";
//    Answer a1;
//    a1.text = "Answer1";
//    a1.correct = false;
//    Answer a2;
//    a2.text = "Answer2";
//    a2.correct = true;
//    Answer a3;
//    a3.text = "Answer3";
//    a3.correct = false;
//    std::vector<Answer> answers;
//    answers.push_back(a1);
//    answers.push_back(a2);
//    answers.push_back(a3);
//    q1.answers = answers;
//    questions.push_back(q1);
//
//    Question q2;
//    q2.text = "Question2";
//    Answer a11;
//    a11.text = "Answer1-2";
//    a11.correct = false;
//    Answer a21;
//    a21.text = "Answer2-2";
//    a21.correct = true;
//    Answer a31;
//    a31.text = "Answer3-2";
//    a31.correct = false;
//    std::vector<Answer> answers2;
//    answers2.push_back(a11);
//    answers2.push_back(a21);
//    answers2.push_back(a31);
//    q2.answers = answers2;
//
//    questions.push_back(q2);
//
//    // answer choosed by student
//
//    std::vector<Answer> studentAnswers;
//    studentAnswers.push_back(a2);
//
//    Test test(questions);
//    //test.addQuestion();
//
//    std::vector <std::string> options;
//    for (int i = 0; i < answers.size(); i++)
//    {
//        options.push_back(answers[i].text);
//    }
//
//    //Menu menu(options);
//    Menu menu(test.getQuestions());
//
//    //menu.drawOptions();
//    //menu.drawFrame(q1.text);
//    menu.drawQuestion(test.getQuestion(1));
//
//    int key = 0;
//    int num = 0;
//    double result = 0;
//
//    //test.setTime(5);
//    auto future = std::async(timeInit, 7);
//
//    auto start = std::chrono::system_clock::now();
//    auto end = start + std::chrono::seconds(7);
//
//    auto nowTime = std::chrono::system_clock::now();
//    //SetCursorPosition(20, 0);
//    //std::cout << "1. " << future.valid() << std::endl;
//    //auto future2 = std::async(timeInit2, 5);;
//    //int t = timeInit2(5);
//    //bool t = future.valid();
//
//    while (key!=ESC)
//    {
//        if (std::chrono::system_clock::now() > end)
//        {
//            break;
//        }
//        
//        key = getKey();
//        if (key == -1) {
//            Sleep(100);
//            continue;
//        }
//
//        switch (key)
//        {
//        case UP_ARROW:
//            menu.up();
//            menu.drawOptions();
//            break;
//        case DOWN_ARROW:
//            menu.down();
//            menu.drawOptions();
//            break;
//        case ENTER:
//            //system("cls");
//            num = menu.getSelectedOption();
//            studentAnswers.push_back(answers[num]);
//            system("cls");
//            result = test.getScore(studentAnswers);
//            std::cout << result << "%" << std::endl;
//            nowTime = std::chrono::system_clock::now();
//            std::chrono::duration<double> diff = nowTime - start;
//            SetCursorPosition(0, 1);
//            std::cout << "Time: " << diff.count() << " s." << std::endl;
//            std::this_thread::sleep_for(std::chrono::milliseconds(2000));
//            break;
//        default:
//            break;
//        }
//        //Sleep(100);
//    }
//    system("cls");
//    std::cout << "EXIT";
//
//}


int main2()
{
    ShowConsoleCursor(false);
    std::vector<Question> questions;
   /* Question q1;
    q1.text = "Question1";
    Answer a1;
    a1.text = "Answer1-1";
    a1.correct = false;
    Answer a2;
    a2.text = "Answer2-1";
    a2.correct = true;
    Answer a3;
    a3.text = "Answer3-1";
    a3.correct = false;
    std::vector<Answer> answers;
    answers.push_back(a1);
    answers.push_back(a2);
    answers.push_back(a3);
    q1.answers = answers;
    questions.push_back(q1);

    Question q2;
    q2.text = "Question2";
    Answer a11;
    a11.text = "Answer1-2";
    a11.correct = false;
    Answer a21;
    a21.text = "Answer2-2";
    a21.correct = false;
    Answer a31;
    a31.text = "Answer3-2";
    a31.correct = true;
    std::vector<Answer> answers2;
    answers2.push_back(a11);
    answers2.push_back(a21);
    answers2.push_back(a31);
    q2.answers = answers2;
    questions.push_back(q2);

    Question q3;
    q3.text = "Question3";
    Answer a12;
    a12.text = "Answer1-3";
    a12.correct = true;
    Answer a22;
    a22.text = "Answer2-3";
    a22.correct = false;
    Answer a32;
    a32.text = "Answer3-3";
    a32.correct = false;
    std::vector<Answer> answers3;
    answers3.push_back(a12);
    answers3.push_back(a22);
    answers3.push_back(a32);
    q3.answers = answers3;
    questions.push_back(q3);*/

    Test test(questions);
    //test.init();


    //test.writeTestFile("test1.txt");
    test.readTestFile("test1.txt");
    test.init();

    //test.addQuestion();
    return 0;
}


int main()
{
    ShowConsoleCursor(false);
    ClassRoom classRoom;
    //classRoom.init();

    //Student student;
    Credentials cred;
    cred.login = "user1";
    cred.password = "102030";
    //Student student(cred);
    
    //classRoom.studentRegistration(cred.login);
    classRoom.showMenu();
    //classRoom.init();


    //DataBase db;
    ////db.init();
    //Student stud = db.getStudent("user1");
    //std::cout << stud.getLogin() << std::endl;
    //db.init();
}