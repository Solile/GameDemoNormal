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
** 目标：玩家的目标是使手中的牌点数尽可能接近或等于21点，但不能超过。如果手中的牌点数超过21点，则称为爆牌（Bust），玩家将输掉该局。
** 牌面点数：扑克牌2-10的点数与牌面上显示的数字相同，J、Q、K的点数为10，A的点数可以视情况为1或11。
** 游戏流程：
* 1.每个玩家和庄家（荷官）会先分别发两张牌。
* 2.玩家可以选择要牌（Hit）或停牌（Stand）。要牌就是再抽一张牌，停牌则表示不再抽牌。
* 3.玩家可以根据手中牌的点数选择是否要牌，以接近21点为目标。
* 4.玩家停牌后，庄家会依次抽牌，通常直到手中牌点数达到17点或以上为止，庄家每轮要亮出新抽出的牌。
** 判定胜负：
* 1.如果玩家的手牌点数等于21点（由一张A和一张10点的牌组成），则获胜，称为“黑杰克”（Blackjack）。
* 2.如果玩家获得的点数比庄家高但没有爆牌，则玩家获胜，赢得庄家下注的一倍的筹码。
* 3.如果玩家爆牌或点数低于庄家，则玩家输掉下注的筹码。
* 4.如果手牌点数相同，则称为“和局”（Push），玩家保留下注的筹码。
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
// 得到牌面大小
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
// 牌面 翻面
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
	// 预留7个元素给m_Cards
	m_Cards.reserve(7);
}
Hand::~Hand()
{
	clear();
}
// 增加一张牌
void Hand::add(Card* pCard)
{
	m_Cards.push_back(pCard);
}
// 清空所有的牌
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
// 获取手上所有牌的总数
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
	// 用于判断 卡牌中是否有Ace,并根据具体情况 由1 --> 11
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
// 是否>21点
bool GenericPlayer::isBusted() const
{
	return(getTotal() > 21);
}
// >21 爆炸
void GenericPlayer::bust() const
{
	cout << m_Name << "的点数超过21点，爆炸成漫天烟火...\n";
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
// 玩家是否还要新牌
bool Player::isHitting() const
{
	cout << m_Name << "，您还要一张新牌嘛？(y/N)";
	char response;
	cin >> response;
	return (response == 'y' || response == 'Y');
}
// 玩家赢
void Player::win() const
{
	cout << m_Name << "获得了最终的胜利，让我们恭喜他！！！\n";
}
// 玩家输
void Player::lose() const
{
	cout << m_Name << "竟然一败涂地，真让人遗憾呢~\n";
}
// 玩家平局
void Player::push() const
{
	cout << m_Name << "，真是一场没有意思的平局。\n";
}
class House :public GenericPlayer
{
public:
	House(const string& name = "庄家");
	virtual ~House();
	virtual bool isHitting() const;
	void flipFirstCard();
};
House::House(const string& name):GenericPlayer(name) {}
House::~House() {}
// 庄家是否<16
bool House::isHitting() const
{
	return(getTotal() <= 16);
}
// 庄家翻牌
void House::flipFirstCard()
{
	if (!(m_Cards.empty()))
	{
		m_Cards[0]->flip();
	}
	else
	{
		cout << "庄家真的不能被翻牌了呢 = 、=\n";
	}
}
// 牌堆
class Deck :public Hand
{
public:
	Deck();
	virtual ~Deck();
	void populate();
	void shuffle();
	void deal(Hand& aHand);	// 分发牌
	void additionalCards(GenericPlayer& aGenericPlayer);
};
Deck::Deck()
{
	m_Cards.reserve(52);
	populate();
}
Deck::~Deck() {}
// 创建一副牌
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
// 洗牌
void Deck::shuffle()
{
	random_shuffle(m_Cards.begin(), m_Cards.end());
}
// 发牌
void Deck::deal(Hand& aHand)
{
	if (!m_Cards.empty())
	{
		aHand.add(m_Cards.back());
		m_Cards.pop_back();
	}
	else
	{
		cout << "哇哦，牌堆里已经没有牌了呦 0-0\n";
	}
}
// 发额外的牌
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
	cout << "\t\t欢迎来到黑杰克游戏 0v0\n\n";
	int numPlayers = 0;
	while (numPlayers < 1 || numPlayers > 7)
	{
		cout << "请输入1-7之间的数字，来选择有几个人参加黑杰克游戏 > w <\n";
		cin >> numPlayers;
	}
	vector<string> names;
	string name;
	for (int i = 0; i < numPlayers; i++)
	{
		cout << "请输入玩家" << i+1 << "的名字呀~\n";
		cin >> name;
		names.push_back(name);
	}
	cout << endl;
	Game aGame(names);
	char again = 'y';
	while (again != 'n' && again != 'N')
	{
		aGame.play();
		cout << "\n一局游戏已经结束了，还想再来一局嘛=w= (y/N)";
		cin >> again;
	}
	return 0;
}
ostream& operator<<(ostream& os, const Card& aCard)
{
	const string RANKS[] = { "0","A","2","3","4","5","6","7",
	"8","9","10","J","Q","K" };
	const string SUITS[] = { "梅花","方块","红心","黑桃" };
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
		os << "<空空如也>";
	}
	return os;
}