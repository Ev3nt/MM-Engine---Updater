#include <Windows.h>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#pragma comment(lib, "urlmon.lib")
//#pragma comment(lib, "Version.lib")

// #include "GHRD.h"

template <class T>
void print_colored(const int color_flags, const T& arg)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	SetConsoleTextAttribute(hConsole, color_flags);
	std::cout << arg;
	SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);//back to normal
}


BOOL main()
{
	// DWORD dwHandle;
	// DWORD size = GetFileVersionInfoSize("MM Engine.exe", &dwHandle);
	// 
	// LPSTR buffer = new char[size];
	// GetFileVersionInfo("MM Engine.exe", dwHandle, size, buffer);
	// 
	// VS_FIXEDFILEINFO* verInfo;
	// size = sizeof(VS_FIXEDFILEINFO);
	// VerQueryValue(buffer, "\\", (LPVOID*)&verInfo, (UINT*)&size);
	// 
	// printf("File Version: %d.%d.%d.%d\n",
	// 	(verInfo->dwFileVersionMS >> 16) & 0xffff,
	// 	(verInfo->dwFileVersionMS >> 0) & 0xffff,
	// 	(verInfo->dwFileVersionLS >> 16) & 0xffff,
	// 	(verInfo->dwFileVersionLS >> 0) & 0xffff
	// );

	print_colored(FOREGROUND_RED, "stuff");//this will be red
	print_colored(FOREGROUND_GREEN, "boy");//this will be red

	// GitHub::Releases releases("https://github.com/Ev3nt/MM-Engine");
	// 
	// for (int i = 0; i < releases.GetSize(); i++)
	// 	printf("--------------------------------\nVersion: %s\nDescription: %s\n", releases[i].version.c_str(), releases[i].comment.c_str());

	return FALSE;
}