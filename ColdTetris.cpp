// ColdTetris.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <conio.h>
#include <windows.h>

using namespace std;


bool game = true;
int mapWidth = 21;
int mapHeight = 21;
int spawnXCoord = 0;
int spawnYCoord = 10;
int timer = 60;
int barrierXPos[400];
int barrierYPos[400];
int lockedCount = 0;
int mapLockedCount = 0;
int innerTimer = 0;
int cellFillX[400];
int cellFillY[400];
char wall = (char) 186;
char brick = (char) 219;
char leftCorner = (char) 200;
char rightCorner = (char) 188;
char tetrisFloor = (char) 205;
int score = 0;
int brickCheck = 0;
int lowBorder = 20;
int spawnClearXCoord = 0;
int spawnClearYCoord = 0;
int spawnTimeXCoord = 0;
int spawnTimeYCoord = 0;

void chooseBonus() {
	srand(time(0));
	int choose = 0;
	choose = rand() % 2;
	switch (choose) {
	  case 0:
	    spawnClearXCoord = (rand() % mapWidth) - 1;
			spawnClearYCoord = (rand() % mapHeight) - 1;
		case 1:
			spawnTimeXCoord = (rand() % mapWidth) - 1;
			spawnTimeYCoord = (rand() % mapHeight) - 1;
	}
}

void map() {
  system("cls");
  srand(time(0));
  for (int mapIndex = 0; mapIndex < mapHeight; ++mapIndex) {
	  for (int cellIndex = 0; cellIndex < mapWidth; ++cellIndex) {
      if (cellIndex == 0 || cellIndex == mapWidth - 1) {
	      cout << wall;
	    } else if (cellIndex == mapWidth && mapIndex == mapHeight) {
		    cout << wall;
	    } else if (cellIndex == spawnYCoord && mapIndex == spawnXCoord) {
				cout << brick;
			} else if (cellIndex == spawnClearYCoord && mapIndex == spawnClearXCoord) {
				cout << "C";
			} else if (cellIndex == spawnTimeYCoord && mapIndex == spawnTimeXCoord) {
				cout << "T";
			} else {
				for (int lockedBlockIndex = 0; lockedBlockIndex <= lockedCount; ++lockedBlockIndex) {
					if (cellIndex == barrierYPos[lockedBlockIndex] && mapIndex == barrierXPos[lockedBlockIndex] ) {
						cout << brick;
						++mapLockedCount;
						cellFillX[lockedBlockIndex] = barrierXPos[lockedBlockIndex];
						cellFillY[lockedBlockIndex] = barrierYPos[lockedBlockIndex];
					}
				}

				if (mapLockedCount == 0) {
					cout << " ";
				} else {
					--mapLockedCount;
				}
		    
	    }

	  }
    cout  << endl;
  }
  for (int borderIndex = 0; borderIndex < mapWidth; ++borderIndex) {
	  if (borderIndex == 0) {
	    cout << leftCorner;
	  } else if (borderIndex == mapWidth - 1) {
	    cout << rightCorner;
	  } else {
	    cout << tetrisFloor;
	  }
	
  }
  cout << endl;
	cout << "Time left: " << timer << endl;
	cout << "Game score: " << score << endl;
}

void controls() {
	if (_kbhit()) { //проверка нажатия на кнопку
		switch (_getch()) { //ловим нажатую кнопку
		  case 'd':
				++spawnYCoord;
			  break;
		  case 'a':
				--spawnYCoord;
			  break;
		}
	}

}

void clear() {
	for (int clearIndex = 0; clearIndex <= lowBorder; ++clearIndex) {
		barrierXPos[clearIndex] = 0;
		barrierYPos[clearIndex] = 0;
		cellFillX[clearIndex] = 0;
		cellFillY[clearIndex] = 0;
	}
}

int brickCollision() {
	int findBrick = 0;
	while (findBrick == 0) {
		for (int checkFloorIndex = 0; checkFloorIndex <= sizeof(cellFillX); ++checkFloorIndex) {
			if (spawnXCoord + 1 == cellFillX[checkFloorIndex] && spawnYCoord == cellFillY[checkFloorIndex] ) {
				findBrick = 1;
				break;
			} else if (checkFloorIndex == sizeof(cellFillX)) {
				findBrick = 2;
			}
		}
	}
	return findBrick;
}
void logic() {
	int check = 10;
	if (spawnYCoord == 0 || spawnYCoord >= mapHeight - 1) {
		spawnYCoord = mapHeight / 2;
	}
	if (spawnXCoord == spawnClearXCoord && spawnYCoord == spawnClearYCoord) {
		clear();
		++score;
		spawnClearXCoord = 0;
		spawnClearYCoord = 0;
	}
	if (spawnXCoord == spawnTimeXCoord && spawnYCoord == spawnTimeYCoord) {
		++score;
		timer += 10;
		spawnTimeXCoord = 0;
		spawnTimeYCoord = 0;
	}
	if (spawnXCoord == mapWidth - 1) {
		barrierXPos[lockedCount] = spawnXCoord;
		barrierYPos[lockedCount] = spawnYCoord;
		spawnXCoord = 0;
		spawnYCoord = (rand() % mapHeight) - 1;
		++lockedCount;
		++innerTimer;
		if (innerTimer == check) {
			--timer;
			innerTimer = 0;
		}
	} else {
		brickCheck = brickCollision();
		if (brickCheck == 1) {
			barrierXPos[lockedCount] = spawnXCoord;
			barrierYPos[lockedCount] = spawnYCoord;
			spawnXCoord = 0;
			spawnYCoord = rand() % mapHeight - 1;
			++lockedCount;
			++innerTimer;
			if (innerTimer == check) {
				--timer;
				innerTimer = 0;
			}
		} else {
			++spawnXCoord;
			++innerTimer;
			if (innerTimer == check) {
				--timer;
				innerTimer = 0;
			}
		}
		
	}

}

int main() {
	int sleepTime = 100;
	int time = 0;
	char playerName[20];
	int gameDifficulty = 0;
	bool spawnBonus = true;

	cout << "Enter your name: ";
	cin >> playerName;

	cout << endl;

	cout << "Enter the number of points required to win: ";
	cin >> gameDifficulty;

	if (gameDifficulty <= 0) {
		gameDifficulty = 1;
	}

	cout << "Press any button to start.";

	if (_getch()) {
		game = true;
	}

  while (game && timer > 0) {
		controls();
		logic();
		spawnBonus = true;
		if (timer % 5 == 0 && timer != 60 && spawnBonus) {
			chooseBonus();
			spawnBonus = false;
		}
	  map();
	  Sleep(sleepTime);
		if (score == gameDifficulty) {
			game = false;
			cout << playerName << ", you won! Congratulations!";
		}

  }

}
