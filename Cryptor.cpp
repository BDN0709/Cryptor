#include <iostream>
#include <Windows.h>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

enum ModeOfProgram : UINT  // перерахування можливих типів роботи програми
{	Encrypt = 1, Decrypt	};

inline string ToUpperCase(const string&);
inline string ToLowerCase(const string&);
inline void PrintAndWriteText(const vector <string>&, const bool&, const string&, const string&);

#include "Cryptor.h"  // підключаємо опис шифровальщика
													// B2 = 2
int main(const ModeOfProgram _Mode, const char** _DecryptionKey)
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	string OpenTextPath = "OpenText.txt";  // шлях до відкритого тексту
	string EncryptedTextPath = "Output.txt";  // шлях до зашифрованого тексту
	string DecryptedTextPath = "DecryptedText.txt";  // шлях до розшифрованого тексту

	Cryptor* cryptor = new Cryptor();  // створення нового об'єкту для шифрування / дешифрування

	if (_Mode == Decrypt)  // якщо працюємо на розшифровку
	{
		if (!cryptor->GetText(EncryptedTextPath))  // якщо не вдалося отримати зашифрований текст з файлу
		{
			cout << "Помилка під час відкриття / читання файлу з зашифрованим текстом!" << endl;
			return -1;  // перериваємо виконання програми
		}

		string _KeyForDecryption = _DecryptionKey[1];  // отримуємо ключ для розшифровки

		cryptor->ProcessText(_KeyForDecryption, _Mode);  // розшифровуємо текст

						  // отримуємо розшифрований текст
		PrintAndWriteText(cryptor->GetProcessedText(), true, DecryptedTextPath, "Розшифрований текст:");  // виводимо розшифрований текст

	}
	else if (_Mode == Encrypt)  // якщо працюємо на шифрацію
	{
		// B1 = 1
		string EncryptionKey = "";
		cout << "Введіть ключ для шифрації тексту: ";
		getline(cin, EncryptionKey);
		// end

		if (!cryptor->GetText(OpenTextPath))  // якщо не вдалося зчитати відкритий текст з файлу
		{
			cout << "Помилка під час відкриття / читання файлу з вихідним текстом!" << endl;
			return -2;  // перериваємо виконання програми
		}

		cryptor->ProcessText(EncryptionKey, _Mode);  // шифруємо текст

						// отримуємо зашифрований текст
		PrintAndWriteText(cryptor->GetProcessedText(), true, EncryptedTextPath, "Зашифрований текст:");  // виводимо зашифрований текст

	}

	delete cryptor;  // звільнюємо ресурси з-під об'єкта для шифрування / дешифрування

	return 0;  // успішно завершуємо програму
}

inline string ToUpperCase(const string& _Str)
{  // функція, що повертає строку із заголовними літерами

	string NewString = "";  // нова строка, у яку запишемо той самий текст, тільки заголовними літерами

	for (UINT i = 0; i < _Str.size(); i++)  // ітеруємось переданою строкою
	{
		if (isalpha(_Str.at(i)) || isspace(_Str.at(i))) // якщо символ - буква (не знак) або пробіл
			NewString += toupper(_Str.at(i));  // змінюємо символ на заголовний та записуємо його у "нашу" строку
		else if (ispunct(_Str.at(i)))  // якщо символ - розділовий знак
			NewString += _Str.at(i);  // просто заносимо його у "нашу" строку
	}

	return NewString;  // повертаємо "нашу" строку тільки із заголовними символами
}

inline string ToLowerCase(const string& _Str)
{  // функція, що повертає строку зі строчними літерами

	string NewString = "";  // нова строка, у яку запишемо той самий текст, тільки строчними літерами

	for (UINT i = 0; i < _Str.size(); i++)  // ітеруємось переданою строкою
	{
		if (isalpha(_Str.at(i)) || isspace(_Str.at(i)))  // якщо символ - буква (не знак) або пробіл
			NewString += tolower(_Str.at(i));  // змінюємо символ на строчний та записуємо його у "нашу" строку
		else if (ispunct(_Str.at(i)))  // якщо символ - розділовий знак
			NewString += _Str.at(i);  // просто заносимо його у "нашу" строку
	}

	return NewString;  // повертаємо "нашу" строку тільки зі строчними символами
}

inline void PrintAndWriteText(const vector <string>& _Text, const bool& _Write = false, const string& _Filename = "", const string& _Message = "")
{  // функція, що виводить в консоль та за бажанням в файл переданий текст та повідомлення

	system("cls");  // очищуємо консоль

	cout << _Message << endl << endl;  // виводимо передане повідомлення

	if (!_Write || _Filename == "")  // якщо не потрібно записувати у файл або шлях до фалу пустий
	{  // просто виводимо текст на консоль
		for (UINT i = 0; i < _Text.size(); i++)
			cout << _Text.at(i) << endl;
	}
	else
	{  // інакше (якщо потрібно записувати у файл та шлях до фалу не пустий)

		fstream fout(_Filename, fstream::out);  // виділяємо ресурси для запису в файл

		for (UINT i = 0; i < _Text.size(); i++)
		{
			fout << _Text.at(i) << '\n';  // записуємо у файл

			cout << _Text.at(i) << endl;  // виводимо на консоль
		}

		fout.close();  // звільнюємо ресурси з-під запису у файл
	}

	return;  // повертаємо "успіх"
}