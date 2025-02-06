#include <iostream>
#include <string>
using namespace std;
void instruction();
char askYesNo(string question);
int askNumber(int high, int low = 1);
int triple(int number);
string triple(string text);
int radiation(int health);
string askText(string prompt);
int askNumber(string prompt);
void tellStory(string name, string noun, int number, string bodyPart, string verb);
int main()
{
	//cout << "Tripling 5:" << triple(5) << "\n\n";
	//cout << "Tripling 'game':" << triple("game");
	instruction();
	string name = askText("Please enter a name: ");
	string noun = askText("Please enter a plural noun: ");
	int number = askNumber("Please enter a number: ");
	string bodyPart = askText("Please enter a body part: ");
	string verb = askText("Please enter a verb: ");
	tellStory(name, noun, number, bodyPart, verb);
	return 0;
}
void instruction()
{
	cout << "Welcome to Mad Lib.\n\n";
	cout << "Answer the following questions to help create a new story.\n";
}
char askYesNo(string question)
{
	char response;
	do
	{
		cout << question << "(y/N):";
		cin >> response;
	} while (response != 'y' && response != 'n');
	return response;
}
int askNumber(int high, int low)
{
	int num;
	do {
		cout << "Please enter a number" << "(" << low << "-" << high << "):";
		cin >> num;
	} while (num > high || num < low);
	return num;
}
// 重载
int triple(int number)
{
	return number * 3;
}
string triple(string text)
{
	return(text + text + text);
}
// 内联 适合较小的函数 反复使用(可以带来性能提升)
inline int radiation(int health)
{
	return health / 2;
}
string askText(string prompt)
{
	string text;
	cout << prompt;
	cin >> text;
	return text;
}
int askNumber(string prompt)
{
	int number;
	cout << prompt;
	cin >> number;
	return number;
}
void tellStory(string name, string noun, int number, string bodyPart, string verb)
{
	cout << "\nHere's your story:\n";
	cout << "The famous explorer ";
	cout << name;
	cout << " had nearly given up a life-long quest to find\n";
	cout << "The Lost City of ";
	cout << noun;
	cout << " when one day, the ";
	cout << noun;
	cout << " found the explorer.\n";
	cout << "Surrounded by ";
	cout << number;
	cout << " " << noun;
	cout << ", a tear came to ";
	cout << name << "'s ";
	cout << bodyPart << ".\n";
	cout << "After all this time, the quest was finaly over. ";
	cout << "And then, the ";
	cout << noun << "\n";
	cout << "promptly devoured ";
	cout << name << ". ";
	cout << "The moral of the the story? Be careful what you ";
	cout << verb;
	cout << " for.";
}