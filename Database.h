#pragma once
#include "sqlite3.h"
#include <Windows.h>
#include <string>
int CreateDatabase(HWND);
int inputInfo(char* , char* , char* , char* , int , HWND);
char* outputInfoLineID(int);
char* outputInfoName(int);
char* outputInfoTemperature(int);
char* outputInfoPressure(int);
char* outputInfoMinutes(int);
void closeDatabase();