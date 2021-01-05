//Напишите программу, которая преобразовывает текст из входного текстового файла 
//в азбуку Морзе и наоборот. Полученный текст сохраняется в отдельный файл.

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
	'u', 'v', 'w', 'x', 'y', 'z', 'a', 'б', 'в', 'г',
	'д', 'е', 'ж', 'з', 'и', 'й', 'к', 'л', 'м', 'н',
	'о', 'п', 'р', 'с', 'т', 'у', 'ф', 'х', 'ц', 'ч',
	'ш', 'щ', 'ъ', 'ы', 'ь', 'э', 'ю', 'я', '1', '2',
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
		cout << "Кодирование и раскодирование сообщения с помощью азбуки Морзе" << endl;
		cout << "==================================================================" << endl << endl;
		cout << "Для текстового файла разрешены следующие символы:" << endl;
		cout << "1) Латинские символы:" << endl;
		cout << "a b c d e f g h i g k l m n o p q r s t u v w x y z" << endl;
		cout << "2) Русские символы:" << endl;
		cout << "а б в г д е ж з и й к л м н о п р с т у ф х ц ч ш щ ъ ы ь э ю я" << endl;
		cout << "3) Цифры и специальные символы:" << endl;
		cout << "1 2 3 4 5 6 7 8 9 0 . , ! ? ; : - ( ) / \" \'" << endl << endl << endl;
		cout << "Правила написания сообщения в кодах Морзе:" << endl;
		cout << "1) В качестве точки используется символ '*'" << endl;
		cout << "2) В качестве тире используется символ '-'" << endl;
		cout << "3) Символы одной буквы пишутся слитно" << endl;
		cout << "4) Между буквами оного слова ставится 1 пробел" << endl;
		cout << "5) Между словами ставится 3 пробела" << endl;
		cout << "==================================================================" << endl << endl;

		cout << "Меню:" << endl;
		cout << "1) Ввести путь до файла" << endl;
		cout << "2) Закодировать сообщение" << endl;
		cout << "3) Раскодировать сообщение" << endl;
		cout << "4) Выход" << endl;
		cout << ">> ";
		cin >> choise;
		cin.get();
		cout << endl;

		switch (choise)
		{
		case 1:
			cout << "Введите путь до файла с сообщением" << endl << ">> ";
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
				cout << "Путь до файла с результатом работы программы:" << endl;
				cout << output_file << endl;
			}
			else
			{
				is_file_open = false;
				cout << "Введен неверный путь." << endl;
			}

			system("pause");
			break;
		case 2:
			if (!is_file_open)
			{
				cout << "Входной файл не был найден." << endl;
				cout << "Сначала введите правильный путь к нему." << endl;
			}
			else if (!checkFile(ENCODING, input))
			{
				cout << "Выбрано неправильное действие для данного файла." << endl;
			}
			else
			{
				remove(output_file.c_str());
				output.open(output_file, ios_base::out);

				//encode(input, output);

				output.close();
				cout << "Кодирование завершено." << endl;
			}
			system("pause");
			break;
		case 3:
			if (!is_file_open)
			{
				cout << "Входной файл не был найден." << endl;
				cout << "Сначала введите правильный путь к файлу." << endl;
			}
			else if (!checkFile(DECODING, input))
			{
				cout << "Выбрано неправильное действие для данного файла." << endl;
			}
			else
			{	
				remove(output_file.c_str());
				output.open(output_file, ios_base::out);

				//decode(input, output);

				output.close();
				cout << "Кодирование завершено." << endl;
			}
			system("pause");
			break;
		case 4:
			work = false;
			break;
		default:
			cout << "Выбран неверный пункт меню." << endl;
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