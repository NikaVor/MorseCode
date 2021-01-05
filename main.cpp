//�������� ���������, ������� ��������������� ����� �� �������� ���������� ����� 
//� ������ ����� � ��������. ���������� ����� ����������� � ��������� ����.

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

#define ENCODING 1
#define DECODING 2

bool checkFile(int mode, ifstream& file);
void encode(ifstream& in, ofstream& out);
void decode(ifstream& in, ofstream& out);

const char alphabet[80] =
{
	'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j',
	'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't',
	'u', 'v', 'w', 'x', 'y', 'z', 'a', '�', '�', '�',
	'�', '�', '�', '�', '�', '�', '�', '�', '�', '�',
	'�', '�', '�', '�', '�', '�', '�', '�', '�', '�',
	'�', '�', '�', '�', '�', '�', '�', '�', '1', '2',
	'3', '4', '5', '6', '7', '8', '9', '0', '.', ',',
	'!', '?', ';', ':', '-', '(', ')', '/', '\"', '\''
};

const string morse_code[80] = 
{
	"*-",		"-***",		"-*-*",		"-**",		"*",		"**-*",		"--*",		"****",		"**",		"*---",
	"-*-",		"*-**",		"--",		"-*",		"---",		"*--*",		"--*-",		"*-*",		"***",		"-",
	"**-",		"***-",		"*--",		"-**-",		"-*--",		"--**",		"*-",		"-***",		"*--",		"--*",
	"-**",		"*",		"***-",		"--**",		"**",		"*---",		"-*-",		"*-**",		"--",		"-*",
	"---",		"*--*",		"*-*",		"***",		"-",		"**-",		"**-*",		"****",		"-*-*",		"---*",
	"----",		"--*-",		"--*--",	"-*--",		"-**-",		"**-**",	"**--",		"*-*-",		"*----",	"**---",
	"***--",	"****-",	"*****",	"-****",	"--***",	"---**",	"----*",	"-----",	"******",	"*-*-*-",
	"--**--",	"**--**",	"-*-*-*",	"---***",	"*-**-*",	"*----*",	"-****-",	"-*--*",	"-*--*-",	"-**-*"
};

int main()
{
	system("chcp 1251 > 0");

	int choise = 0;
	bool work = true;
	bool is_file_open = false;
	
	ifstream input;
	ofstream output;
	
	string input_file;
	string output_file;


	while (work)
	{
		system("cls");
		cout << "����������� � �������������� ��������� � ������� ������ �����" << endl;
		cout << "==================================================================" << endl << endl;
		cout << "��� ���������� ����� ��������� ��������� �������:" << endl;
		cout << "1) ��������� �������:" << endl;
		cout << "a b c d e f g h i g k l m n o p q r s t u v w x y z" << endl;
		cout << "2) ������� �������:" << endl;
		cout << "� � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � �" << endl;
		cout << "3) ����� � ����������� �������:" << endl;
		cout << "1 2 3 4 5 6 7 8 9 0 . , ! ? ; : - ( ) / \" \'" << endl << endl << endl;
		cout << "������� ��������� ��������� � ����� �����:" << endl;
		cout << "1) � �������� ����� ������������ ������ '*'" << endl;
		cout << "2) � �������� ���� ������������ ������ '-'" << endl;
		cout << "3) ������� ����� ����� ������� ������" << endl;
		cout << "4) ����� ������� ����� ����� �������� 1 ������" << endl;
		cout << "5) ����� ������� �������� 3 �������" << endl;
		cout << "==================================================================" << endl << endl;

		cout << "����:" << endl;
		cout << "1) ������ ���� �� �����" << endl;
		cout << "2) ������������ ���������" << endl;
		cout << "3) ������������� ���������" << endl;
		cout << "4) �����" << endl;
		cout << ">> ";
		cin >> choise;
		cin.get();
		cout << endl;

		switch (choise)
		{
		case 1:
			cout << "������� ���� �� ����� � ����������" << endl << ">> ";
			getline(cin, input_file);
			
			if (input.is_open())
				input.close();
			input.open(input_file, ios_base::in);

			if (input.is_open())
			{
				output_file = input_file;

				if (output_file.find_last_of("\\") != string::npos)
				{
					output_file.erase(output_file.find_last_of("\\"));
					output_file.append("\\Result.txt");
				}
				else
				{
					output_file = "Result.txt";
				}
				
				is_file_open = true;
				cout << "���� �� ����� � ����������� ������ ���������:" << endl;
				cout << output_file << endl;
			}
			else
			{
				is_file_open = false;
				cout << "������ �������� ����." << endl;
			}

			system("pause");
			break;
		case 2:
			if (!is_file_open)
			{
				cout << "������� ���� �� ��� ������." << endl;
				cout << "������� ������� ���������� ���� � ����." << endl;
			}
			else if (!checkFile(ENCODING, input))
			{
				cout << "������� ������������ �������� ��� ������� �����." << endl;
			}
			else
			{
				remove(output_file.c_str());
				output.open(output_file, ios_base::out);

				//encode(input, output);

				output.close();
				cout << "����������� ���������." << endl;
			}
			system("pause");
			break;
		case 3:
			if (!is_file_open)
			{
				cout << "������� ���� �� ��� ������." << endl;
				cout << "������� ������� ���������� ���� � �����." << endl;
			}
			else if (!checkFile(DECODING, input))
			{
				cout << "������� ������������ �������� ��� ������� �����." << endl;
			}
			else
			{	
				remove(output_file.c_str());
				output.open(output_file, ios_base::out);

				//decode(input, output);

				output.close();
				cout << "����������� ���������." << endl;
			}
			system("pause");
			break;
		case 4:
			work = false;
			break;
		default:
			cout << "������ �������� ����� ����." << endl;
			system("pause");
			break;
		}
	}

	input.close();

	system("pause");
	return 0;
}

bool checkFile(int mode, ifstream& file)
{
	string message;
	file.seekg(0, ios::beg);

	while (!file.eof())
	{
		getline(file, message);

		for (int i = 0; i < message.size(); i++)
		{
			if (message[i] != '-' && message[i] != '*' && message[i] != ' ')
				if (mode == ENCODING)
					return true;
				else
					return false;
		}
	}

	if (mode == ENCODING)
		return false;
	else
		return true;
}

void encode(ifstream& in, ofstream& out)
{
	in.seekg(0, ios::beg);
}

void decode(ifstream& in, ofstream& out)
{
	in.seekg(0, ios::beg);
}