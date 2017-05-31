// DisksInfo.cpp: ���������� ����� ����� ��� ����������� ����������.
//

#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable : 4996) // ����� ���������� �� ��������������, ���������� �� ����������� ����������.

#include <stdio.h>
#include <iostream>
#include <Windows.h>
#include <locale>
#include <TCHAR.H> // Unicode - wchar_t, Multi-byte - char
using namespace std;

int _tmain(int argc, _TCHAR* argv[])
{
	setlocale(LC_ALL, "rus");
	cout << "���������� � ������ : " << endl;
	int k = 0;
	int sz = GetLogicalDriveStrings(NULL, 0); // ���������� ������� ���� ���������� ����� �� ���������� � ��������� �� �������� �������� ��������� � ������
	TCHAR* szLogicalDrives = new TCHAR[sz];
	GetLogicalDriveStrings(sz, szLogicalDrives);
	while (*szLogicalDrives)
	{
		TCHAR szDisk[80];
		lstrcpy(szDisk, szLogicalDrives);
		UINT uDriveType = GetDriveType(szDisk);
		if (uDriveType == DRIVE_FIXED)	// ������� ����
		{
			k = k + 1;					// ������� ���-�� ������� ������
			wcout << szDisk << endl;	// ������� ��������
			_int64 Free, Total;
			Free = 0;
			Total = 0;
			//���������� ����� 
			GetDiskFreeSpaceEx(szDisk, NULL, (PULARGE_INTEGER)&Total, (PULARGE_INTEGER)&Free);
			cout << "����� ����� : \t\t" << Total / (1024 * 1024 * 1024) << " ��" << endl;
			cout << "�������� : \t\t" << Free / (1024 * 1024 * 1024) << " ��" << endl;
			cout << "������ : \t\t" << (Total - Free) / (1024 * 1024 * 1024) << " ��\n" << endl;
		}
		while (*szLogicalDrives) szLogicalDrives++;
		szLogicalDrives++;
	}
	std::wcout << L"����� ����� ������:\t" << k << std::endl;

	system("pause");
	return 0;
}

