#include "classRoom.h"

void ClassRoom::loadTests()
{
    //this->dataBase.init();
    this->tests = this->dataBase.getTests();
    
    /*std::vector <std::string> testsNames;
    std::string name;
    for (auto const& dirEntry : fs::directory_iterator{ this->testsPath })
    {
        if (dirEntry.is_regular_file())
        {
            name = dirEntry.path().filename().string();
            testsNames.push_back(name);
        }
    }
    Test newTest;

    for (int i = 0; i < testsNames.size(); i++)
    {
        newTest.readTestFile(testsNames[i]);
        this->tests.push_back(newTest);
    }*/

    /*for (int i = 0; i < tests.size(); i++)
    {
        std::cout << "Test name: " << this->tests[i].getQuestion(i).text << std::endl;
    }*/

}

void ClassRoom::loadUsersLogins()
{
    //this->dataBase.init();
    this->students = this->dataBase.getLogins();
    
    /*std::string name;
    for (auto const& dirEntry : fs::directory_iterator{ this->studentsPath })
    {
        if (dirEntry.is_directory())
        {
            name = dirEntry.path().filename().string();
            students.push_back(name);
        }
    }*/

    /*for (int i = 0; i < students.size(); i++)
    {
        std::cout << "Student name: " << students[i] << std::endl;
    }*/
}

void ClassRoom::init()
{
    loadTests();
    loadUsersLogins();
}

void ClassRoom::studentRegistration(std::string login, std::string password)
{
    if (isLoginUnique(login))
    {
        students.push_back(login);
        createHomeDirectory(login);

        std::string name = "Credentials.txt";
        fs::path path = this->studentsPath;
        fs::current_path(path);
        path /= name;
        std::ofstream ofs;
        ofs.open(name, std::ios::app);

        ofs << login << "-|-" << password << "-|-" << std::endl;

        ofs.close();
    }
}

void ClassRoom::studentRegistrationMenu()
{
    Menu menu;
    menu.drawMessageFrame("Create your login");
    std::string login;
    std::string password;
    std::string passwordConfirm;
    std::getline(std::cin, login);
    if (isLoginUnique(login))
    {
        do
        {
            menu.drawMessageFrame("Create your password");
            std::getline(std::cin, password);
            menu.drawMessageFrame("Repeat your password");
            std::getline(std::cin, passwordConfirm);
            if (password != passwordConfirm)
            {
                menu.drawMessageFrame("Passwords don't match. Try again");
                system("pause");
            }
        } while (password != passwordConfirm);
        studentRegistration(login, password);
    }
    else
    {
        SetCursorPosition(1, 5);
        SetColor(ConsoleColor::RED_FADE, ConsoleColor::BLACK);
        std::cout << "Such login is already registered\n";
        SetCursorPosition(1, 6);
        SetColor(ConsoleColor::WHITE, ConsoleColor::BLACK);
        system("pause");
    }
    system("cls");
}

void ClassRoom::studentLogIn()
{
     //menu log-in
     Menu menu;
     menu.drawMessageFrame("Enter your login");
     std::string login;
     std::string password;
     std::getline(std::cin, login);
     int key = 0;
     int selection = 0;
     if (!isLoginUnique(login))
     {
         Student student = this->dataBase.getStudent(login);
         menu.drawMessageFrame("Enter your password");
         std::getline(std::cin, password);
         if (student.passValidation(password))
         {
             // show tests
             std::vector<std::string> testNames;
             for (int i = 0; i < this->tests.size(); i++)
             {
                 testNames.push_back(tests[i].getTestName());
             }
             Menu subMenu(testNames);
             system("cls");

             while (key != ESC)
             {
                 subMenu.drawFrame();
                 subMenu.drawOptions();
                 key = getKey();

                 switch (key)
                 {
                 case UP_ARROW:
                     subMenu.up();
                     break;
                 case DOWN_ARROW:
                     subMenu.down();
                     break;
                 case ENTER:
                     selection = subMenu.getSelectedOption();
                     system("cls");
                     tests[selection].init();
                     break;
                 default:
                     break;
                 }


             }
         }
         else
         {
             menu.drawMessageFrame("Wrong password");
             system("pause");
             system("cls");
         }
     }
     else
     {
         std::cout << "Such login is not registered";
     }
    
}

bool ClassRoom::isLoginUnique(std::string login)
{
    if (!students.size())
    {
        return true;
    }

    for (int i = 0; i < students.size(); i++)
    {
        if (students[i] == login)
        {
            return false;
        }
    }
    return true;
}

void ClassRoom::createHomeDirectory(std::string login)
{
	fs::path path = this->studentsPath;
	path /= login;
	fs::create_directory(path);
}

void ClassRoom::showMenu()
{
    std::vector<std::string> mainMenuOptions({"Student", "Teacher", "Exit"});
    Menu menu(mainMenuOptions);
    int key = -1;
    int selection = -1;
    
    while (key!=ESC)
    {
        menu.drawFrame();
        menu.drawOptions();
        key = getKey();
        
        switch (key)
        {
        case UP_ARROW:
            menu.up();
            break;
        case DOWN_ARROW:
            menu.down();
            break;
        case ENTER:
            selection = menu.getSelectedOption();
            if (selection == MAIN_MENU::STUDENT)
            {
                std::vector<std::string> subMenuOptions({ "Log in", "Register", "Go back" });
                Menu subMenu(subMenuOptions);
                subMenu.drawFrame();
                subMenu.drawOptions();
                int key2 = -1;
                selection = -1;

                while (key2 != ESC)
                {
                    key2 = getKey();
                    subMenu.drawFrame();
                    subMenu.drawOptions();

                    switch (key2)
                    {
                    case UP_ARROW:
                        subMenu.up();
                        //subMenu.drawOptions();
                        break;
                    case DOWN_ARROW:
                        subMenu.down();
                        //subMenu.drawOptions();
                        break;
                    case ENTER:
                        selection = subMenu.getSelectedOption();
                        if (selection == STUDENT_MENU::LOGIN)
                        {
                            studentLogIn();
                        }
                        else if (selection == STUDENT_MENU::REGISTER)
                        {
                            studentRegistrationMenu();
                        }
                        else if (selection == STUDENT_MENU::GO_BACK)
                        {
                            key2 = ESC;
                            system("cls");
                        }
                        break;
                    default:
                        break;
                    }
                }
            }
            else if (selection == MAIN_MENU::TEACHER)
            {
                //TO-DO
            }
            else if (selection == MAIN_MENU::EXIT)
            {
                key = ESC;
                system("cls");
            }
            break;
        default:
            break;
        }
    }

}