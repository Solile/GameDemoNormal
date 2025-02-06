// ��̬
#include <iostream>
using namespace std;
class Enemy
{
public:
	Enemy(int damage = 10);
	virtual ~Enemy();
	void virtual Attack() const;
protected:
	int* m_pDamage;
};
Enemy::Enemy(int damage)
{
	m_pDamage = new int(damage);
}
Enemy::~Enemy()
{
	cout << "�ڵ��˵����磬ɾ��m_pDamageָ�롣\n";
	delete m_pDamage;
	m_pDamage = 0;
}
void Enemy::Attack() const
{
	cout << "���������ܵ�" << *m_pDamage << "���˺���\n";
}

class Boss :public Enemy
{
public:
	Boss(int multiplier = 3);
	virtual ~Boss();
	void virtual Attack() const;
private:
	int* m_pMultiplier;
};
//Boss::Boss(int damage) :m_DamageMultiplier(damage) { }
Boss::Boss(int multiplier)
{
	m_pMultiplier = new int(multiplier);
}
Boss::~Boss()
{
	cout << "�ڵ��˵����磬ɾ��m_pMultiplierָ�롣\n";
	delete m_pMultiplier;
	m_pMultiplier = 0;
}
void Boss::Attack() const
{
	cout << "��ǿ�ҹ������ܵ�" << (*m_pDamage)*(*m_pMultiplier)
		<< "���˺���\n";
}
/*
* Enemy* pBadGuy = new Boss();
* Enemy* pBadGuy = new Enemy();
* ����ΪAttack() Ϊ�麯��
* �麯��ͨ��ָ���������������̬��Ϊ
* 
*/
int main()
{
	cout << "���˵��ж���\n";
	Enemy* pBadGuy = new Boss();
	pBadGuy->Attack();
	cout << "\n\nɾ��ָ����˵�ָ��:\n";
	delete pBadGuy;
	pBadGuy = 0;
	return 0;
}
