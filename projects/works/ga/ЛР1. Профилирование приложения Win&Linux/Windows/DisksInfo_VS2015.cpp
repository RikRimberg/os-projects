// DisksInfo.cpp: определяет точку входа для консольного приложения.
//

#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable : 4996) // чтобы избавиться от предупреждений, выдаваемых на стандартные библиотеки.

#include <stdio.h>
#include <iostream>
#include <Windows.h>
#include <locale>
#include <TCHAR.H> // Unicode - wchar_t, Multi-byte - char
using namespace std;

int _tmain(int argc, _TCHAR* argv[])
{
	setlocale(LC_ALL, "rus");
	cout << "Информация о дисках : " << endl;
	int k = 0;
	int sz = GetLogicalDriveStrings(NULL, 0); // определяет имеющие силу логические диски на компьютере и размещает их названия корневых каталогов в строку
	TCHAR* szLogicalDrives = new TCHAR[sz];
	GetLogicalDriveStrings(sz, szLogicalDrives);
	while (*szLogicalDrives)
	{
		TCHAR szDisk[80];
		lstrcpy(szDisk, szLogicalDrives);
		UINT uDriveType = GetDriveType(szDisk);
		if (uDriveType == DRIVE_FIXED)	// жесткий диск
		{
			k = k + 1;					// считаем кол-во жестких дисков
			wcout << szDisk << endl;	// выводим название
			_int64 Free, Total;
			Free = 0;
			Total = 0;
			//определяем объем 
			GetDiskFreeSpaceEx(szDisk, NULL, (PULARGE_INTEGER)&Total, (PULARGE_INTEGER)&Free);
			cout << "Объем диска : \t\t" << Total / (1024 * 1024 * 1024) << " ГБ" << endl;
			cout << "Свободно : \t\t" << Free / (1024 * 1024 * 1024) << " ГБ" << endl;
			cout << "Занято : \t\t" << (Total - Free) / (1024 * 1024 * 1024) << " ГБ\n" << endl;
		}
		while (*szLogicalDrives) szLogicalDrives++;
		szLogicalDrives++;
	}
	std::wcout << L"Итого число дисков:\t" << k << std::endl;

	system("pause");
	return 0;
}

