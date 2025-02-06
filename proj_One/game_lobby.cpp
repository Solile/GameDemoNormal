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
	wcout << L"�������û��������֣�";
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
		wcout << L"��Ϸ������û����Ϸ��ң�û�п���ɾ�����û�.\n";
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
	wcout << L"�Ѿ��������Ϸ���������е��û�����\n";
}
ostream& operator<<(ostream& os, const Lobby& aLobby)
{
	Player* pIter = aLobby.m_pHead;
	os << "\n�����ǿ�����˭����Ϸ������-v-\n";
	if (pIter == 0)
	{
		os << "��Ϸ��������һ�ˣ�\n";
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
		wcout << L"\n��Ϸ����\n";
		wcout << L"0 - �˳�����\n";
		wcout << L"1 - ������û�����Ϸ������\n";
		wcout << L"2 - ����Ϸ������ɾ���û���ͷ�û���\n";
		wcout << L"3 - ���������Ϸ����\n";
		wcout << L"\n����������ѡ��";
		cin >> choice;
		switch (choice)
		{
		case 0:
			wcout << L"�ټ�����л����\n"; break;
		case 1:
			myLobby.AddPlayer(); break;
		case 2:
			myLobby.RemovePlayer(); break;
		case 3:
			myLobby.Clear(); break;
		default:
			wcout << L"С�ɰ�ѽ�������ѡ����.\n";
		}
	} while (choice != 0);

	return 0;
}