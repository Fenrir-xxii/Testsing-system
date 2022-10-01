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

int main()
{
    ShowConsoleCursor(false);

    ClassRoom classRoom;
    classRoom.showMenu();

    return 0;
}
