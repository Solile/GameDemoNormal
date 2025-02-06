#include <iostream>
#include <string>
#include <locale>

using namespace std;

class Player
{
public:
	Player(const string& name = "");
	string GetName() const;
	Player* GetNext() const;
	void SetNext(Player* next);
private:
	string m_Name;
	Player* m_pNext;
};
Player::Player(const string& name) :m_Name(name), m_pNext(0){ }
string Player::GetName() const
{
	return m_Name;
}
Player* Player::GetNext() const
{
	return m_pNext;
}
void Player::SetNext(Player* next)
{
	m_pNext = next;
}

class Lobby
{
	friend ostream& operator<<(ostream& os, const Lobby& aLobby);
public:
	Lobby();
	~Lobby();
	void AddPlayer();
	void RemovePlayer();
	void Clear();
private:
	Player* m_pHead;
};
Lobby::Lobby() :m_pHead(0) { }
Lobby::~Lobby()
{
	Clear();
}
void Lobby::AddPlayer()
{
	wcout << L"请输入用户的新名字：";
	string name;
	cin >> name;
	Player* pNewPlayer = new Player(name);
	if (m_pHead == 0)
	{
		m_pHead = pNewPlayer;
	}
	else
	{
		Player* pIter = m_pHead;
		while (pIter->GetNext() != 0)
		{
			pIter = pIter->GetNext();
		}
		pIter->SetNext(pNewPlayer);
	}
}
void Lobby::RemovePlayer()
{
	if (m_pHead == 0)
	{
		wcout << L"游戏大厅里没有游戏玩家，没有可以删除的用户.\n";
	}
	else
	{
		Player* pTemp = m_pHead;
		m_pHead = m_pHead->GetNext();
		delete pTemp;
	}
}
void Lobby::Clear()
{
	while (m_pHead != 0) 
	{
		RemovePlayer();
	}
	wcout << L"已经清除了游戏大厅里所有的用户数据\n";
}
ostream& operator<<(ostream& os, const Lobby& aLobby)
{
	Player* pIter = aLobby.m_pHead;
	os << "\n让我们看看，谁在游戏大厅呢-v-\n";
	if (pIter == 0)
	{
		os << "游戏大厅空无一人！\n";
	}
	else
	{
		while (pIter != 0)
		{
			os << pIter->GetName() << endl;
			pIter = pIter->GetNext();
		}
	}
	return os;
}
int main()
{
	wcout.imbue(locale(""));
	Lobby myLobby;
	int choice;
	do
	{
		cout << myLobby;
		wcout << L"\n游戏大厅\n";
		wcout << L"0 - 退出程序\n";
		wcout << L"1 - 添加新用户到游戏大厅里\n";
		wcout << L"2 - 从游戏大厅里删除用户（头用户）\n";
		wcout << L"3 - 清除整个游戏大厅\n";
		wcout << L"\n请输入您的选择：";
		cin >> choice;
		switch (choice)
		{
		case 0:
			wcout << L"再见，感谢游玩\n"; break;
		case 1:
			myLobby.AddPlayer(); break;
		case 2:
			myLobby.RemovePlayer(); break;
		case 3:
			myLobby.Clear(); break;
		default:
			wcout << L"小可爱呀，你填错选项啦.\n";
		}
	} while (choice != 0);

	return 0;
}