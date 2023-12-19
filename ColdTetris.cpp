// ColdTetris.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <conio.h>
#include <windows.h>

using namespace std;

struct shape {
  int shapeWidth;
  int shapeHeight;
};

bool game = true;
int mapWidth = 21;
int mapHeight = 21;
int spawnXCoord = 0;
int spawnYCoord = 10;
shape spawnShape;

void map() {
  system("cls");
  srand(time(0));
  for (int mapIndex = 0; mapIndex < mapHeight; ++mapIndex) {
	for (int cellIndex = 0; cellIndex < mapWidth; ++cellIndex) {
      if (cellIndex == 0 || cellIndex == mapWidth - 1) {
	    cout << (char)186;
	  } else if (cellIndex == mapWidth && mapIndex == mapHeight) {
		cout << (char)186;
	  } else {
		cout << " ";
	  }

	}
   cout  << endl;
  }
  
  for (int borderIndex = 0; borderIndex < mapWidth; ++borderIndex) {
	if (borderIndex == 0) {
	  cout << (char)200;
	} else if (borderIndex == mapWidth - 1) {
	  cout << (char)188;
	} else {
	  cout << (char)205;
	}
	
  }
  cout << endl;
}


int main() {
 int timer = 0;
  while (game && timer < 5) {
	map();
	Sleep(200);
	++spawnXCoord;
	++timer;
  }
}

