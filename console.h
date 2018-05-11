// console header
#define     KEY_LEFT    VK_LEFT
#define     KEY_RIGHT   VK_RIGHT
#define     KEY_UP      VK_UP
#define     KEY_DOWN    VK_DOWN
#define     KEY_ESC     VK_ESCAPE
#include<windows.h>
void gotoXY(int x, int y)           // dua con tro den vi tri (x,y) tren man hinh console (copy)
{
  static HANDLE h = NULL;  
  if(!h)
    h = GetStdHandle(STD_OUTPUT_HANDLE);
  COORD c = { x, y };  
  SetConsoleCursorPosition(h,c);
}

bool checkKey(int key)              // kiem tra phim duoc nhap vao tu ban phim (copy)
{
    return GetAsyncKeyState(key);
}
 void SetColor(int ForgC)			// hien thi mau (copy)
 {
     WORD wColor;

      HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
      CONSOLE_SCREEN_BUFFER_INFO csbi;
     if(GetConsoleScreenBufferInfo(hStdOut, &csbi))
     {
          wColor = (csbi.wAttributes & 0xF0) + (ForgC & 0x0F);
          SetConsoleTextAttribute(hStdOut, wColor);
     }
     return;
 }
