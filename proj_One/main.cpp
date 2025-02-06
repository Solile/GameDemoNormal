#include <iostream>
#include <string>
#include <cstdlib>
#include <algorithm>
#include <cmath>
#include <vector>
#include <cctype>
#include <locale>

using namespace std;

int main()
{
	wcout.imbue(locale("")); // ���ñ��ػ�֧��
	wcout << L"��ã����磡\n"; // ǰ���L��ʾ���ַ�������
	vector<string> inventory = {"apple","banana","orange","peach","cherry"};
	// random number
	srand(static_cast<unsigned int>(time(0)));	// seed random number generator
	int randomNumber = rand();	// generate random number
	// random_shuffle(A.begin(), A.end()); // ��Ԫ�ؽ�������
	int die = (randomNumber % 6) + 1; // get a number between 1 and 6; 

	// ������
	vector<string>::iterator myIterator;
	vector<string>::const_iterator iter;	// �����޸������õ�Ԫ��(only-read) ���������� ���� i

	for (iter = inventory.begin(); iter != inventory.end(); ++iter)
	{
		// �������Ľ����� ��ʾ���õ�Ԫ��
		cout << *iter << endl;
	}

	int a = 10;
	int& b = a;
	int* c = &b;

	cout << &a << endl;
	cout << &b << endl;
	cout << &(*c) << endl;

	// ��������Ϸ
	const int ROWS = 3;
	const int COLUMNS = 3;
	char board[ROWS][COLUMNS] = { 
		{'O','X','O'},
		{' ','X','X'},
		{'X','O','O'} };
	cout << "Here's the tic-tac-toe board:\n";
	for (int i = 0; i < ROWS; i++)
	{
		for (int j = 0; j < COLUMNS; j++)
		{
			cout << board[i][j];
		}
		cout << endl;
	}
	cout << "\n'X' moves to the empty location.\n\n";
	board[1][0] = 'X';
	cout << "Now the tic-tac-toe board is:\n";
	for (int i = 0; i < ROWS; i++)
	{
		for (int j = 0; j < COLUMNS; j++)
		{
			cout << board[i][j];
		}
		cout << endl;
	}
	cout << "\n'X' wins!";

	return 0;
}