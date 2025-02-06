#include <iostream>
#include <string>
#include <locale>

using namespace std;

class Critter
{
public:
	Critter(int hunger = 0, int boredom = 0);
	void Talk();
	void Eat(int food = 4);
	void Play(int fun = 4);
private:
	int m_Hunger;
	int m_Boredom;
	int GetMode() const;
	void PassTime(int time = 1);
};
Critter::Critter(int hunger, int boredom) :m_Hunger(hunger), m_Boredom(boredom) { }
inline int Critter::GetMode() const
{
	return (m_Hunger + m_Boredom);
}
void Critter::PassTime(int time)
{
	m_Hunger += time;
	m_Boredom += time;
}
void Critter::Talk()
{
	wcout << L"小动物现在感觉";
	int mode = GetMode();
	if (mode > 15)
	{
		wcout << L"怒火冲天\n";
	}
	else if (mode > 10)
	{
		wcout << L"十分焦躁\n";
	}
	else if (mode > 5)
	{
		wcout << L"平平淡淡\n";
	}
	else
	{
		wcout << L"怡然自得\n";
	}
	PassTime();
}
void Critter::Eat(int food)
{
	wcout << L"吃东西ing...";
	m_Hunger -= food;
	if (m_Hunger < 0)
	{
		m_Hunger = 0;
	}
	PassTime();
}
void Critter::Play(int fun)
{
	wcout << L"做游戏ing...";
	m_Boredom -= fun;
	if (m_Boredom < 0)
	{
		m_Boredom = 0;
	}
	PassTime();
}

int main()
{
	wcout.imbue(locale(""));
	Critter crit;
	crit.Talk();
	int choice;
	do {
		wcout << L"快来喂养动物吧\n";
		wcout << L"0--退出\n";
		wcout << L"1--查询动物的状态\n";
		wcout << L"2--喂养动物\n";
		wcout << L"3--和它玩耍\n";
		wcout << L"你的选择是：";
		cin >> choice;
		switch (choice)
		{
		case 0:
			wcout << L"游戏结束，感谢游玩!\n";
			break;
		case 1:
			crit.Talk();
			break; 
		case 2:
			crit.Eat();
			break;
		case 3:
			crit.Play();
			break;
		default:
			wcout << L"\n对不起，您的选择" << choice << L"不被允许，请重新选一次。\n";
		}
	} while (choice != 0);
	return 0;
}