#define _CRT_SECURE_NO_WARNINGS
#include <Windows.h>
#pragma comment(lib, "Version.lib")
#include <iostream>
#include <sstream>
#include <string>

#include "GHRD.h"
#pragma comment(lib, "GitHub Releases Downloader.lib")

#define MAJOR "1"
#define MINOR "0"
#define RELEASE "0"

#define UPDATER_VERSION MAJOR "." MINOR "." RELEASE
#define UPDATER "MM Engine - Updater Version " UPDATER_VERSION

template <class T>
void printColored(int color_flags, T arg);

bool fileExists(LPCSTR lpFileName);

//------------------------------------------------------------------------------

BOOL main()
{
	GitHub::Releases releases("https://github.com/Ev3nt/MM-Engine");

	printf("%s\n", UPDATER);

	if (fileExists("MM Engine.exe"))
	{
		DWORD handle;
		DWORD size = GetFileVersionInfoSize("MM Engine.exe", &handle);

		LPSTR buffer = new char[size];
		GetFileVersionInfo("MM Engine.exe", handle, size, buffer);

		VS_FIXEDFILEINFO* verInfo;
		size = sizeof(VS_FIXEDFILEINFO);
		VerQueryValue(buffer, "\\", (LPVOID*)&verInfo, (UINT*)&size);
		delete[] buffer;

		buffer = (LPSTR)calloc(MAX_PATH, sizeof(char));
		sprintf_s(buffer, MAX_PATH, "%d.%d.%d.%d\n",
			(verInfo->dwFileVersionMS >> 16) & 0xffff,
			(verInfo->dwFileVersionMS >> 0) & 0xffff,
			(verInfo->dwFileVersionLS >> 16) & 0xffff,
			(verInfo->dwFileVersionLS >> 0) & 0xffff
		);
		printf("Current MM Engine version: ");
		printColored(10, buffer);
		free(buffer);
	}

	printf("\n");

	for (UINT i = 0; i < releases.GetSize(); i++)
	{
		printColored(11, "--------------------------------\n");
		printColored(3, "Number: ");
		printf("%d\n", i + 1);
		printColored(3, "Version: ");
		std::string version = releases[i].version;

		int it = 0;
		while ((it = version.find('_')) != -1)
		{
			version[it] = ' ';
		}

		printf("%s\n", version.c_str());
		printColored(3, "Description: ");

		UINT end;
		for (end = 0; end < releases[i].comment.size() && releases[i].comment.substr(end, 9).compare("\nAssets:\n"); end++);

		printf("%s\n", releases[i].comment.substr(0, --end).c_str());
	}

	printColored(11, "--------------------------------\n");

	UINT num = -1;
	while (num > releases.GetSize() || !num)
	{
		printf("Type number: ");
		std::cin >> num;

		if (num > releases.GetSize() || !num)
		{
			printColored(12, "Invalid number\n");
			printf("--------------------------------\n");
		}
	}

	printColored(14, "Downloading...\n");
	std::stringstream ss(releases[--num].comment);

	bool assets = false;
	while (!ss.eof())
	{
		char buffer[512];
		ss.getline(buffer, sizeof(buffer));
		std::string line = buffer;

		if (!assets)
		{
			if (!line.compare("Assets:"))
			{
				assets = true;
			}
		}
		else
		{
			UINT i;
			for (i = 0; line.substr(i, 2).compare("//") && i < line.size(); i++);

			if (i != line.size())
			{
				line.erase(i, line.size() - i);
			}

			bool mustbe = false;
			if (line.size() > 2 && line[0] == '+' && line[1] == ' ')
			{
				line.erase(0, 2);
				mustbe = true;
			}

			for (i = 0; i < line.size() && line[i] != ':'; i++);

			std::string asset = line.substr(0, i - 1).c_str();
			std::string path = line.substr(i + 2, line.size() - i - 2).c_str();
			if (mustbe)
			{
				releases[num].Download(asset.c_str(), path.c_str());
			}
			else if (!fileExists(path.c_str()))
			{
				releases[num].Download(asset.c_str(), path.c_str());
			}
		}
	}

	printColored(10, "Successfully!\n");
	system("pause");

	return FALSE;
}

//------------------------------------------------------------------------------

template <class T>
void printColored(int color_flags, T arg)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	SetConsoleTextAttribute(hConsole, color_flags);
	std::cout << arg;
	SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
}

bool fileExists(LPCSTR lpFileName)
{
	FILE* file = fopen(lpFileName, "r");

	return file ? !fclose(file) : false;
}