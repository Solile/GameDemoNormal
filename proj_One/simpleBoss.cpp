// �̳�
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
	cout << "����˵�������������������\n";
}
void Enemy::Attack() const
{
	cout << "���������ܵ�" << m_Damage << "���˺���\n";
}
// Enemy������boss��
/*
* �����һЩ��Ա�������ܱ�������̳�(��EnemyΪ��)
* 1.���캯��
*	Enemy();
* 2.�������캯��
*	Enemy(const Enemy& e)
* 3.��������
*	~Enemy();
* 4.���ظ�ֵ�����
*	Enemy& operator = (const Enemy & e);
* 
* Boss�ж�������ظ�ֵ�������
* Boss& operator = (const Boss & b)
* {
*	Enemy::operator = (b);
*	//now take care of data members defined in Boss
* ...
* Boss�ж���Ŀ������캯����
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
	cout << "����ͷ��˵����Ĩɱ����Ĵ��ڣ�����\n";
}
void Boss::Attack() const
{
	Enemy::Attack();
	cout << "����ͷ������س�Ц��Ĵ��ڣ�����\n";
}
int main()
{
	cout << "���˵��ж���\n";
	Enemy anEnemy;
	anEnemy.Taunt();
	anEnemy.Attack();
	cout << "\n����ͷ����ж���\n";
	Boss aBoss;
	aBoss.Taunt();
	aBoss.Attack();
	return 0;
}