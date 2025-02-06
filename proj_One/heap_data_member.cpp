#include <iostream>
#include <string>
#include <locale>

using namespace std;

class Critter
{
public:
	Critter(const string& name = "", int age = 0);
	~Critter();
	Critter(const Critter& c);
	Critter& operator = (const Critter & c);
	void Greet() const;
private:
	string* m_pName;
	int m_Age;
};
Critter::Critter(const string& name, int age)
{
	wcout << L"����ָ��\n";
	m_pName = new string(name);
	m_Age = age;
}
Critter::~Critter()
{
	wcout << L"ɾ��ָ��\n";
	delete m_pName;
}
Critter::Critter(const Critter& c)
{
	wcout << L"���ƴ���ָ��\n";
	m_pName = new string(*(c.m_pName));
	m_Age = c.m_Age;
}
Critter& Critter::operator = (const Critter& c)
{
	wcout << L"����'='����\n";
	if (this != &c)// this ��ָָ������ָ��
	{
		delete m_pName;
		m_pName = new string(*(c.m_pName));
		m_Age = c.m_Age;
	}
	return *this;
}
void Critter::Greet() const
{
	wcout << L"����";
	cout << *m_pName;
	wcout << L",�ҽ���" << m_Age << L"��\n";
	cout << "&m_pName: " << &m_pName << endl;
}
void testDestructor();
void testCopyConstructor(Critter aCopy);
void testAssignmentOp();
int main()
{
	wcout.imbue(locale(""));
	testDestructor();
	cout << endl;
	Critter crit("Poochie", 5);
	crit.Greet();
	testCopyConstructor(crit);
	crit.Greet();
	cout << endl;
	testAssignmentOp();
	return 0;
}
void testDestructor()
{
	Critter toDestory("Rover", 3);
	toDestory.Greet();
}
void testCopyConstructor(Critter aCopy)
{
	aCopy.Greet();
	cout << "this is a copy\n";
}
void testAssignmentOp()
{
	Critter crit1("crit1", 7);
	Critter crit2("crit2", 9);
	crit1 = crit2;
	crit1.Greet();
	crit2.Greet();
	cout << endl;
	Critter crit3("crit3", 11);
	crit3 = crit3;
	crit3.Greet();
}