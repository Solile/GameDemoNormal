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
	wcout.imbue(locale("")); // 设置本地化支持
	wcout << L"你好，世界！\n"; // 前面加L表示宽字符字面量
	vector<string> inventory = {"apple","banana","orange","peach","cherry"};
	// random number
	srand(static_cast<unsigned int>(time(0)));	// seed random number generator
	int randomNumber = rand();	// generate random number
	// random_shuffle(A.begin(), A.end()); // 对元素进行乱序
	int die = (randomNumber % 6) + 1; // get a number between 1 and 6; 

	// 迭代器
	vector<string>::iterator myIterator;
	vector<string>::const_iterator iter;	// 不能修改其引用的元素(only-read) 常量迭代器 代替 i

	for (iter = inventory.begin(); iter != inventory.end(); ++iter)
	{
		// 迭代器的解引用 显示引用的元素
		cout << *iter << endl;
	}

	int a = 10;
	int& b = a;
	int* c = &b;

	cout << &a << endl;
	cout << &b << endl;
	cout << &(*c) << endl;

	// 井字棋游戏
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