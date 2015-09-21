#include <iostream>
#include "window.h"

using namespace std;

int main() {
  Xwindow w;

    w.fillRectangle(50 , 200, 50, 250, 2);

  w.drawString(50, 50, "Hello!");

  char c;
  cin >> c;
}

