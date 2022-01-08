#include <iostream.h>
#include <conio.h>
#include <string.h>
#include <fstream.h>

class element
{
	int ano;
	float amass;
	char symbol[3];
	char name[50];

public:
	void input();
	void display();
	int get_ano()
	{
		return ano;
	}
	float get_amass()
	{
		return amass;
	}
	char* get_symbol()
	{
		return symbol;
	}
	char* get_name()
	{
		return name;
	}
};

void modify();
void search();
void del();
void add();

void element::input()
{
	cout << "Input Element Symbol:\n";
	cin.getline(symbol, 3);
	cout << "Input Element Name:\n";
	cin.getline(name, 50);
	cout << "Input Element Atomic Number: \n";
	cin >> ano;
	cout << "Input Element Atomic Mass: \n";
	cin >> amass;
}

void add()
{
	ofstream file("base.dat", ios::out | ios::binary | ios::app);
	element obj;
	obj.input();
	file.write((char*)obj, sizeof(obj));
	file.close();
}

void search()
{
	int flag = 0;
	ifstream file("base.dat", ios::in | ios::binary );
	cout << "Search by:\n1 = Symbol\n2 = Name\n3 = Atomic Number\n4 = Atomic Mass\n";
	int ch;
	cin >> ch;
	switch(ch)
	{
		case 1:
			char arg[3];
			cout << "Input Element Symbol:\n";
			cin.getline(arg, 3);
			while(!file.eof())
			{
				element t;
				file.read((char*)t, sizeof(t));
				if(!strcmp(t.get_symbol(),arg))
				{
					cout << "Element Found!\n";
					t.display();
					flag = 1;
					break;
				}
			}
			break;
		case 2:
			char arg[50];
			cout << "Input Element Name:\n";
			cin.getline(arg, 50);
			while(!file.eof())
			{
				element t;
				file.read((char*)t, sizeof(t));
				if(!strcmp(t.get_name(),arg))
				{
					cout << "Element Found!\n";
					t.display();
					flag = 1;
					break;
				}
			}
			break;
		case 3:
			int arg;
			cout << "Input Element Atomic Number: \n";
			cin >> arg;
			while(!file.eof())
			{
				element t;
				file.read((char*)t, sizeof(t));
				if(t.get_ano() == arg)
				{
					cout << "Element Found!\n";
					t.display();
					flag = 1;
					break;
				}
			}
			break;
		case 4:
			float arg;
			cout << "Input Element Atomic Mass: \n";
			cin >> arg;
			while(!file.eof())
			{
				element t;
				file.read((char*)t, sizeof(t));
				if(t.get_amass() == arg)
				{
					cout << "Element Found!\n";
					t.display();
					flag = 1;
					break;
				}
			}
			break;
		default:
			search();
	}
	if(!flag)
		cout << "Element was not found\n";
	file.close();
}
