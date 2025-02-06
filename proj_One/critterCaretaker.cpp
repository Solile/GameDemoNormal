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
	wcout << L"С�������ڸо�";
	int mode = GetMode();
	if (mode > 15)
	{
		wcout << L"ŭ�����\n";
	}
	else if (mode > 10)
	{
		wcout << L"ʮ�ֽ���\n";
	}
	else if (mode > 5)
	{
		wcout << L"ƽƽ����\n";
	}
	else
	{
		wcout << L"��Ȼ�Ե�\n";
	}
	PassTime();
}
void Critter::Eat(int food)
{
	wcout << L"�Զ���ing...";
	m_Hunger -= food;
	if (m_Hunger < 0)
	{
		m_Hunger = 0;
	}
	PassTime();
}
void Critter::Play(int fun)
{
	wcout << L"����Ϸing...";
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
		wcout << L"����ι�������\n";
		wcout << L"0--�˳�\n";
		wcout << L"1--��ѯ�����״̬\n";
		wcout << L"2--ι������\n";
		wcout << L"3--������ˣ\n";
		wcout << L"���ѡ���ǣ�";
		cin >> choice;
		switch (choice)
		{
		case 0:
			wcout << L"��Ϸ��������л����!\n";
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
			wcout << L"\n�Բ�������ѡ��" << choice << L"��������������ѡһ�Ρ�\n";
		}
	} while (choice != 0);
	return 0;
}