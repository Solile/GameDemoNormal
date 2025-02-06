// 继承
#include <iostream>
using namespace std;

class Enemy
{
public:
	Enemy(int damage = 10);
	void virtual Taunt() const;
	void virtual Attack() const;
protected:
	int m_Damage;
};
Enemy::Enemy(int damage) :m_Damage(damage) { }
void Enemy::Taunt() const
{
	cout << "敌人说他将会与你决斗！！！\n";
}
void Enemy::Attack() const
{
	cout << "被攻击！受到" << m_Damage << "点伤害！\n";
}
// Enemy类派生boss类
/*
* 基类的一些成员函数不能被派生类继承(以Enemy为例)
* 1.构造函数
*	Enemy();
* 2.拷贝构造函数
*	Enemy(const Enemy& e)
* 3.析构函数
*	~Enemy();
* 4.重载赋值运算符
*	Enemy& operator = (const Enemy & e);
* 
* Boss中定义的重载赋值运算符↓
* Boss& operator = (const Boss & b)
* {
*	Enemy::operator = (b);
*	//now take care of data members defined in Boss
* ...
* Boss中定义的拷贝构造函数↓
* Boss(const Boss& b)
* {
*	//now take care of data members defined in Boss
* ...
*/

class Boss :public Enemy
{
public:
	Boss(int damage = 30);
	void virtual Taunt() const;
	void virtual Attack() const;
//private:
//	int m_DamageMultiplier;
};
//Boss::Boss(int damage) :m_DamageMultiplier(damage) { }
Boss::Boss(int damage) :Enemy(damage) { }
void Boss::Taunt() const
{
	cout << "敌人头领说他将抹杀掉你的存在！！！\n";
}
void Boss::Attack() const
{
	Enemy::Attack();
	cout << "敌人头领大声地嘲笑你的存在！！！\n";
}
int main()
{
	cout << "敌人的行动：\n";
	Enemy anEnemy;
	anEnemy.Taunt();
	anEnemy.Attack();
	cout << "\n敌人头领的行动：\n";
	Boss aBoss;
	aBoss.Taunt();
	aBoss.Attack();
	return 0;
}