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

void modify()
{
	int flag = 0;
	element x;
	ifstream file("base.dat", ios::in | ios::binary | ios::nocreate );
	if(!file)
	{
		cout << "Error: Base file does not exist, please add some elements first\n";
		menu();
	}
	else
	{
		ofstream file_temp("base_temp.dat", ios::out | ios::binary);
		cout << "Search for element to be modified by:\n1 = Symbol\n2 = Name\n3 = Atomic Number\n4 = Atomic Mass\n";
		int ch;
		cin >> ch;
		switch (ch)
		{
		case 1:
			char arg[3];
			cout << "Input Element Symbol:\n";
			gets(arg);
			while (!file.eof())
			{
				element t;
				file.read((char*)&t, sizeof(t));
				if (!strcmp(t.get_symbol(), arg))
				{
					cout << "Element Found!\n\n";
					t.display();
					flag = 1;
					cout << "Input revised Element info:\n";
					x.input();
					file_temp.write((char*)&x, sizeof(x));
					break;
				}
				else
					file_temp.write((char*)&t, sizeof(t));
			}
			break;
		case 2:
			char arg1[50];
			cout << "Input Element Name:\n";
			gets(arg1);
			while (!file.eof())
			{
				element t;
				file.read((char*)&t, sizeof(t));
				if (!strcmp(t.get_name(), arg1))
				{
					cout << "Element Found!\n\n";
					t.display();
					flag = 1;
					cout << "Input revised Element info:\n";
					x.input();
					file_temp.write((char*)&x, sizeof(x));
					break;
				}
				else
					file_temp.write((char*)&t, sizeof(t));
			}
			break;
		case 3:
			int arg2;
			cout << "Input Element Atomic Number: \n";
			cin >> arg2;
			while (!file.eof())
			{
				element t;
				file.read((char*)&t, sizeof(t));
				if (t.get_ano() == arg2)
				{
					cout << "Element Found!\n\n";
					t.display();
					flag = 1;
					cout << "Input revised Element info:\n";
					x.input();
					file_temp.write((char*)&x, sizeof(x));
					break;
				}
				else
					file_temp.write((char*)&t, sizeof(t));
			}
			break;
		case 4:
			float arg3;
			cout << "Input Element Atomic Mass: \n";
			cin >> arg3;
			while (!file.eof())
			{
				element t;
				file.read((char*)&t, sizeof(t));
				if (t.get_amass() == arg3)
				{
					cout << "Element Found!\n\n";
					t.display();
					flag = 1;
					cout << "Input revised Element info:\n";
					x.input();
					file_temp.write((char*)&x, sizeof(x));
					break;
				}
				else
					file_temp.write((char*)&t, sizeof(t));
			}
			break;
		default:
			modify();
		}
		if (!flag)
			cout << "Element was not found\n";
		file.close();
		file_temp.close();
		rename("base.dat", "base2.dat");
		rename("base_temp.dat", "base.dat");
		remove("base2.dat");
	}
	file.close();
}

void del()
{
	int flag = 0;
	ifstream file("base.dat", ios::in | ios::binary | ios::nocreate );
	if(!file)
	{
		cout << "Error: Base file does not exist, please add some elements first\n";
	}
	else
	{
		ofstream file_temp("base_temp.dat", ios::out | ios::binary);
		cout << "Search for element to be deleted by:\n1 = Symbol\n2 = Name\n3 = Atomic Number\n4 = Atomic Mass\n";
		int ch;
		cin >> ch;
		switch (ch)
		{
		case 1:
			char arg[3];
			cout << "Input Element Symbol:\n";
			gets(arg);
			while (!file.eof())
			{
				element t;
				file.read((char*)&t, sizeof(t));
				if (!strcmp(t.get_symbol(), arg))
				{
					cout << "Element Found! Deleting\n\n";
					t.display();
					flag = 1;
					break;
				}
				else
					file_temp.write((char*)&t, sizeof(t));
			}
			break;
		case 2:
			char arg1[50];
			cout << "Input Element Name:\n";
			gets(arg1);
			while (!file.eof())
			{
				element t;
				file.read((char*)&t, sizeof(t));
				if (!strcmp(t.get_name(), arg1))
				{
					cout << "Element Found! Deleting\n\n";
					t.display();
					flag = 1;
					break;
				}
				else
					file_temp.write((char*)&t, sizeof(t));
			}
			break;
		case 3:
			int arg2;
			cout << "Input Element Atomic Number: \n";
			cin >> arg2;
			while (!file.eof())
			{
				element t;
				file.read((char*)&t, sizeof(t));
				if (t.get_ano() == arg2)
				{
					cout << "Element Found! Deleting\n\n";
					t.display();
					flag = 1;
					break;
				}
				else
					file_temp.write((char*)&t, sizeof(t));
			}
			break;
		case 4:
			float arg3;
			cout << "Input Element Atomic Mass: \n";
			cin >> arg3;
			while (!file.eof())
			{
				element t;
				file.read((char*)&t, sizeof(t));
				if (t.get_amass() == arg3)
				{
					cout << "Element Found! Deleting\n\n";
					t.display();
					flag = 1;
					break;
				}
				else
					file_temp.write((char*)&t, sizeof(t));
			}
			break;
		default:
			del();
		}
		if (!flag)
			cout << "Element was not found\n";
		file.close();
		file_temp.close();
		rename("base.dat", "base2.dat");
		rename("base_temp.dat", "base.dat");
		remove("base2.dat");
	}
	file.close();
}

void menu()
{
	cout << "Menu:\n1 = Search for Element in File\n2 = Modify Existing Element in File\n3 = Delete Existing Element in File\n4 = Add Element to File\n5 = Exit\n"; 
	int ch;
	cin >> ch;
	switch(ch)
	{
		case 1:
			search();
			menu();
			break;
		case 2:
			modify();
			menu();
			break;
		case 3:
			del();
			menu();
			break;
		case 4:
			add();
			menu();
			break;
		case 5:
			break;
		default:
			menu();
	}
}

void main()
{
	menu();
}
