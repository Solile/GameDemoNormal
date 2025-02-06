// �����ࣺ���ĳ�������кܶ������൫�ǲ�����ʵ��������
#include <iostream>
using namespace std;
class Creature	// abstract class
{
public:
	Creature(int health = 100);
	virtual void Greet() const = 0;
	virtual void DisplayHealth() const;
protected:
	int m_Health;
};
Creature::Creature(int health) :m_Health(health) { }
void Creature::DisplayHealth() const
{
	cout << "����ֵΪ��" << m_Health << endl;
}
class Orc :public Creature
{
public:
	Orc(int health = 120);
	virtual void Greet() const;
};
Orc::Orc(int health) :Creature(health) {}
void Orc::Greet() const
{
	cout << "��������Ϊū������\n";
}
int main()
{
	Creature* pCreature = new Orc();
	pCreature->Greet();
	pCreature->DisplayHealth();
	return 0;
}