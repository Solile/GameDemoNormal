// Game BlackJacket
#include <iostream>
#include <string>
#include <cstdlib>
#include <algorithm>
#include <cmath>
#include <vector>
#include <locale>
using namespace std;
/*
** Ŀ�꣺��ҵ�Ŀ����ʹ���е��Ƶ��������ܽӽ������21�㣬�����ܳ�����������е��Ƶ�������21�㣬���Ϊ���ƣ�Bust������ҽ�����þ֡�
** ����������˿���2-10�ĵ�������������ʾ��������ͬ��J��Q��K�ĵ���Ϊ10��A�ĵ������������Ϊ1��11��
** ��Ϸ���̣�
* 1.ÿ����Һ�ׯ�ң��ɹ٣����ȷֱ������ơ�
* 2.��ҿ���ѡ��Ҫ�ƣ�Hit����ͣ�ƣ�Stand����Ҫ�ƾ����ٳ�һ���ƣ�ͣ�����ʾ���ٳ��ơ�
* 3.��ҿ��Ը��������Ƶĵ���ѡ���Ƿ�Ҫ�ƣ��Խӽ�21��ΪĿ�ꡣ
* 4.���ͣ�ƺ�ׯ�һ����γ��ƣ�ͨ��ֱ�������Ƶ����ﵽ17�������Ϊֹ��ׯ��ÿ��Ҫ�����³�����ơ�
** �ж�ʤ����
* 1.�����ҵ����Ƶ�������21�㣨��һ��A��һ��10�������ɣ������ʤ����Ϊ���ڽܿˡ���Blackjack����
* 2.�����һ�õĵ�����ׯ�Ҹߵ�û�б��ƣ�����һ�ʤ��Ӯ��ׯ����ע��һ���ĳ��롣
* 3.�����ұ��ƻ��������ׯ�ң�����������ע�ĳ��롣
* 4.������Ƶ�����ͬ�����Ϊ���;֡���Push������ұ�����ע�ĳ��롣
*/
class Card
{
public:
	enum rank {
		ACE = 1, TWO, THREE, FOUR, FIVE, SIX,
		SEVEN, EIGHT, NINE, TEN, JACK, QUEEN, KING
	};
	enum suit { CLUBS, DIAMONDS, HEARTS, SPADES };
	friend ostream& operator<<(ostream& os, const Card& aCard);
	Card(rank r = ACE, suit s = SPADES, bool ifu = true);
	int getValue() const;
	void flip();
private:
	rank m_Rank;
	suit m_Suit;
	bool m_IsFaceUp;
};
Card::Card(rank r, suit s, bool ifu) :m_Rank(r), m_Suit(s), m_IsFaceUp(ifu) { }
// �õ������С
int Card::getValue() const
{
	int value = 0;
	if (m_IsFaceUp)
	{
		value = m_Rank;
		if (value > 10)
		{
			value = 10;
		}
	}
	return value;
}
// ���� ����
void Card::flip()
{
	m_IsFaceUp = !(m_IsFaceUp);
}

class Hand
{
public:
	Hand();
	virtual ~Hand();
	void add(Card* pCard);
	void clear();
	int getTotal() const;
protected:
	vector<Card*>m_Cards;
};
Hand::Hand()
{
	// Ԥ��7��Ԫ�ظ�m_Cards
	m_Cards.reserve(7);
}
Hand::~Hand()
{
	clear();
}
// ����һ����
void Hand::add(Card* pCard)
{
	m_Cards.push_back(pCard);
}
// ������е���
void Hand::clear()
{
	vector<Card*>::iterator iter = m_Cards.begin();
	for (iter = m_Cards.begin(); iter != m_Cards.end(); ++iter)
	{
		delete* iter;
		*iter = 0;
	}
	m_Cards.clear();
}
// ��ȡ���������Ƶ�����
int Hand::getTotal() const
{
	if (m_Cards.empty())
	{
		return 0;
	}
	if (m_Cards[0]->getValue() == 0)
	{
		return 0;
	}
	int total = 0;
	vector<Card*>::const_iterator iter;
	for (iter = m_Cards.begin(); iter != m_Cards.end(); ++iter)
	{
		total += (*iter)->getValue();
	}
	// �����ж� �������Ƿ���Ace,�����ݾ������ ��1 --> 11
	bool containsAce = false;
	for (iter = m_Cards.begin(); iter != m_Cards.end(); ++iter)
	{
		if ((*iter)->getValue() == Card::ACE)
		{
			containsAce = true;
		}
	}
	if (containsAce && total < 11)
	{
		total += 10;
	}
	return total;

}
class GenericPlayer :public Hand
{
	friend ostream& operator<<(ostream& os, const GenericPlayer& aGenericPlayer);
public:
	GenericPlayer(const string& name = "");
	virtual ~GenericPlayer();
	virtual bool isHitting() const = 0;
	bool isBusted() const;
	void bust() const;
protected:
	string m_Name;
};
GenericPlayer::GenericPlayer(const string& name) :m_Name(name) { }
GenericPlayer::~GenericPlayer() { }
// �Ƿ�>21��
bool GenericPlayer::isBusted() const
{
	return(getTotal() > 21);
}
// >21 ��ը
void GenericPlayer::bust() const
{
	cout << m_Name << "�ĵ�������21�㣬��ը�������̻�...\n";
}
class Player :public GenericPlayer
{
public:
	Player(const string& name = "");
	virtual ~Player();
	virtual bool isHitting() const;
	void win() const;
	void lose() const;
	void push() const;
};
Player::Player(const string& name) :GenericPlayer(name) {}
Player::~Player() {}
// ����Ƿ�Ҫ����
bool Player::isHitting() const
{
	cout << m_Name << "������Ҫһ�������(y/N)";
	char response;
	cin >> response;
	return (response == 'y' || response == 'Y');
}
// ���Ӯ
void Player::win() const
{
	cout << m_Name << "��������յ�ʤ���������ǹ�ϲ��������\n";
}
// �����
void Player::lose() const
{
	cout << m_Name << "��Ȼһ��Ϳ�أ��������ź���~\n";
}
// ���ƽ��
void Player::push() const
{
	cout << m_Name << "������һ��û����˼��ƽ�֡�\n";
}
class House :public GenericPlayer
{
public:
	House(const string& name = "ׯ��");
	virtual ~House();
	virtual bool isHitting() const;
	void flipFirstCard();
};
House::House(const string& name):GenericPlayer(name) {}
House::~House() {}
// ׯ���Ƿ�<16
bool House::isHitting() const
{
	return(getTotal() <= 16);
}
// ׯ�ҷ���
void House::flipFirstCard()
{
	if (!(m_Cards.empty()))
	{
		m_Cards[0]->flip();
	}
	else
	{
		cout << "ׯ����Ĳ��ܱ��������� = ��=\n";
	}
}
// �ƶ�
class Deck :public Hand
{
public:
	Deck();
	virtual ~Deck();
	void populate();
	void shuffle();
	void deal(Hand& aHand);	// �ַ���
	void additionalCards(GenericPlayer& aGenericPlayer);
};
Deck::Deck()
{
	m_Cards.reserve(52);
	populate();
}
Deck::~Deck() {}
// ����һ����
void Deck::populate()
{
	clear();
	for (int s = Card::CLUBS; s <= Card::SPADES; ++s)
	{
		for (int r = Card::ACE; r <= Card::KING; ++r)
		{
			add(new Card(static_cast<Card::rank>(r), static_cast<Card::suit>(s)));
		}
	}
}
// ϴ��
void Deck::shuffle()
{
	random_shuffle(m_Cards.begin(), m_Cards.end());
}
// ����
void Deck::deal(Hand& aHand)
{
	if (!m_Cards.empty())
	{
		aHand.add(m_Cards.back());
		m_Cards.pop_back();
	}
	else
	{
		cout << "��Ŷ���ƶ����Ѿ�û�������� 0-0\n";
	}
}
// ���������
void Deck::additionalCards(GenericPlayer& aGenericPlayer)
{
	cout << endl;
	while (!(aGenericPlayer.isBusted()) && aGenericPlayer.isHitting())
	{
		deal(aGenericPlayer);
		cout << aGenericPlayer << endl;
		if (aGenericPlayer.isBusted())
		{
			aGenericPlayer.bust();
		}
	}
}
class Game
{
public:
	Game(const vector<string>& names);
	~Game();
	void play();
private:
	Deck m_Deck;
	House m_House;
	vector<Player> m_Players;
};
Game::Game(const vector<string>& names)
{
	vector<string>::const_iterator pName;
	for (pName = names.begin(); pName != names.end(); ++pName)
	{
		m_Players.push_back(Player(*pName));
	}
	srand(static_cast<unsigned int>(time(0)));
	m_Deck.populate();
	m_Deck.shuffle();
}
Game::~Game() {}
void Game::play()
{
	vector<Player>::iterator pPlayer;
	for (int i = 0; i < 2; ++i)
	{
		for (pPlayer = m_Players.begin(); pPlayer != m_Players.end(); ++pPlayer)
		{
			m_Deck.deal(*pPlayer);
		}
		m_Deck.deal(m_House);
	}
	m_House.flipFirstCard();
	for (pPlayer = m_Players.begin(); pPlayer != m_Players.end(); ++pPlayer)
	{
		cout << *pPlayer << endl;
	}
	cout << m_House << endl;
	for (pPlayer = m_Players.begin(); pPlayer != m_Players.end(); ++pPlayer)
	{
		m_Deck.additionalCards(*pPlayer);
	}
	m_House.flipFirstCard();
	cout << endl << m_House;
	m_Deck.additionalCards(m_House);
	if (m_House.isBusted())
	{
		for (pPlayer = m_Players.begin(); pPlayer != m_Players.end(); ++pPlayer)
		{
			if (!(pPlayer->isBusted()))
			{
				pPlayer->win();
			}
		}
	}
	else
	{
		for (pPlayer = m_Players.begin(); pPlayer != m_Players.end(); ++pPlayer)
		{
			if (!(pPlayer->isBusted()))
			{
				if (pPlayer->getTotal() > m_House.getTotal())
				{
					pPlayer->win();
				}
				else if (pPlayer->getTotal() < m_House.getTotal())
				{
					pPlayer->lose();
				}
				else
				{
					pPlayer->push();
				}
			}
		}
	}
	for (pPlayer = m_Players.begin(); pPlayer != m_Players.end(); ++pPlayer)
	{
		pPlayer->clear();
	}
	m_House.clear();
}
ostream& operator<<(ostream& os, const Card& aCard);
ostream& operator<<(ostream& os, const GenericPlayer& aGenericPlayer);
int main()
{
	cout << "\t\t��ӭ�����ڽܿ���Ϸ 0v0\n\n";
	int numPlayers = 0;
	while (numPlayers < 1 || numPlayers > 7)
	{
		cout << "������1-7֮������֣���ѡ���м����˲μӺڽܿ���Ϸ > w <\n";
		cin >> numPlayers;
	}
	vector<string> names;
	string name;
	for (int i = 0; i < numPlayers; i++)
	{
		cout << "���������" << i+1 << "������ѽ~\n";
		cin >> name;
		names.push_back(name);
	}
	cout << endl;
	Game aGame(names);
	char again = 'y';
	while (again != 'n' && again != 'N')
	{
		aGame.play();
		cout << "\nһ����Ϸ�Ѿ������ˣ���������һ����=w= (y/N)";
		cin >> again;
	}
	return 0;
}
ostream& operator<<(ostream& os, const Card& aCard)
{
	const string RANKS[] = { "0","A","2","3","4","5","6","7",
	"8","9","10","J","Q","K" };
	const string SUITS[] = { "÷��","����","����","����" };
	if (aCard.m_IsFaceUp)
	{
		os << SUITS[aCard.m_Suit] << RANKS[aCard.m_Rank];
	}
	else
	{
		os << "XX";
	}
	return os;
}
ostream& operator<<(ostream& os, const GenericPlayer& aGenericPlayer)
{
	os << aGenericPlayer.m_Name << ":\t";
	vector<Card*>::const_iterator pCard;
	if (!aGenericPlayer.m_Cards.empty())
	{
		for (pCard = aGenericPlayer.m_Cards.begin();
			pCard != aGenericPlayer.m_Cards.end(); pCard++)
		{
			os << *(*pCard) << "\t";
		}
		if (aGenericPlayer.getTotal() != 0)
		{
			cout << "(" << aGenericPlayer.getTotal() << ")";
		}
	}
	else
	{
		os << "<�տ���Ҳ>";
	}
	return os;
}