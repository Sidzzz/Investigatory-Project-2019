#include <iostream>
#include <string>
#include <fstream>

using namespace std;

class element
{
public:
	int ano;
	float amass;
	string symbol;
	string name;
	void input();
	void display();
	/*int get_ano()
	{
		return ano;
	}
	float get_amass()
	{
		return amass;
	}
	string get_symbol()
	{
		return symbol;
	}
	string get_name()
	{
		return name;
	}*/
};

void element::input()
{
	cout << "Input Element Symbol:\n";
	getline(cin, symbol);
	cout << "Input Element Name:\n";
	getline(cin, name);
	cout << "Input Element Atomic Number: \n";
	cin >> ano;
	cout << "Input Element Atomic Mass: \n";
	cin >> amass;
}

void element::display()
{
	cout << "Element Symbol:\n";
	cout << symbol << endl;
	cout << "Element Name:\n";
	cout << name << endl;
	cout << "Element Atomic Number: \n";
	cout << ano << endl;
	cout << "Element Atomic Mass: \n";
	cout << amass << endl;
}

int main()
{
	ifstream info;
	ofstream file;
	info.open("element_info.txt", ios::in );
	file.open("BASE.DAT", ios::out | ios::binary | ios::app);
	if (!info)
		cout << "Error\n";
	string line;
	while (info.good())
	{
		element buf;
		float amass;
		int ano;
		string name, symbol, temp;
		info >> ano;
		buf.ano = ano;
		info >> temp;
		info >> temp;
		info >> symbol;
		buf.symbol = symbol;
		info >> name;
		buf.name = name;
		info >> amass;
		buf.amass = amass;
		buf.display();
		file.write((char*)&buf, sizeof(buf));
		getline(info, line);
		cout << line << endl;
	}
	system("pause");
}