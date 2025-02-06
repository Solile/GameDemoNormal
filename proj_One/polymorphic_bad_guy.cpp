// 多态
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
	cout << "在敌人的世界，删除m_pDamage指针。\n";
	delete m_pDamage;
	m_pDamage = 0;
}
void Enemy::Attack() const
{
	cout << "被攻击！受到" << *m_pDamage << "点伤害！\n";
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
	cout << "在敌人的世界，删除m_pMultiplier指针。\n";
	delete m_pMultiplier;
	m_pMultiplier = 0;
}
void Boss::Attack() const
{
	cout << "被强烈攻击！受到" << (*m_pDamage)*(*m_pMultiplier)
		<< "点伤害！\n";
}
/*
* Enemy* pBadGuy = new Boss();
* Enemy* pBadGuy = new Enemy();
* ↑因为Attack() 为虚函数
* 虚函数通过指针和引用来产生多态行为
* 
*/
int main()
{
	cout << "敌人的行动：\n";
	Enemy* pBadGuy = new Boss();
	pBadGuy->Attack();
	cout << "\n\n删除指向敌人的指针:\n";
	delete pBadGuy;
	pBadGuy = 0;
	return 0;
}
