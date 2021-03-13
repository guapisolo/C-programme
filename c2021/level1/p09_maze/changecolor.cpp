#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include <windows.h>
#include <algorithm>
#define dd double
#define ll long long 
#define ull unsigned long long 


int main()
{
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	WORD wOldColorAttrs;
	CONSOLE_SCREEN_BUFFER_INFO csbiInfo;
 
	// Save the current color
	GetConsoleScreenBufferInfo(h, &csbiInfo);
	wOldColorAttrs = csbiInfo.wAttributes;
 
	// Set the new color
	SetConsoleTextAttribute(h, FOREGROUND_RED | FOREGROUND_INTENSITY | BACKGROUND_GREEN);
	printf("This is a test\n");
 
	// Restore the original color
	SetConsoleTextAttribute(h, wOldColorAttrs);
	printf("This is a test\n");
}