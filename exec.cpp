#include "exec.h"
#include <Windows.h>

exec::exec(QObject *parent)
    : QObject{parent}
{
    //hide cursor
    HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE); CONSOLE_CURSOR_INFO cursorInfo; GetConsoleCursorInfo(out, &cursorInfo); cursorInfo.bVisible = false; SetConsoleCursorInfo(out, &cursorInfo);

    gif = new QMovie(":/samples/gif.gif");
    gif->setSpeed(3000);
    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &exec::DrawScreen);
    connect(gif, &QMovie::frameChanged, this, &exec::DrawScreen);
    gif->start();
    //timer->start(1000/framerate);
    //TimedEvent();
}
void exec::DrawScreen()
{
    //system("cls");
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos = {0, 0};
    SetConsoleCursorPosition(hConsole, pos);


    //currentImage.load(":/samples/rofl4.jpg");
    //QImage _currentImage = gif->currentImage();//currentImage.toImage();//currentImage.toImage();
    QImage scaledImage = gif->currentImage().scaled(screen_width,screen_height);
    for (int y = 0; y < screen_height; y++)
    {
        for (int x = 0; x < screen_width; x++)
        {
            QColor col = scaledImage.pixel(x,y);
            charBuffer[x][y] = gradient[(col.red()+col.blue()+col.green())/(26*3)];
            WriteConsoleA(hConsole, &charBuffer[x][y], 1, NULL, NULL);
        }
    }
}

