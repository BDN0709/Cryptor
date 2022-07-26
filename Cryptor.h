#pragma once

class Cryptor sealed
{
public:

	inline bool GetText(const string&);

	inline void ProcessText(string, const ModeOfProgram);

	vector <string> GetProcessedText() const
	{	return _ProcessedText;	}

private:

	vector <string> _Text;  // поле для зберігання зчитаного тексту
	vector <string> _ProcessedText;  // поле для зберігання опрацьованого тексту

};

inline bool Cryptor::GetText(const string& _Filename)
{  // функція, що отримує текст з файлу за заданим шляхом до нього

	fstream fin;

	try
	{
		fin.open(_Filename, fstream::in);  // спроба відкрити файл

		if (!fin.is_open())  // якщо не відкритий
			throw exception("Error while opening file with text!");  // прокинути виключну ситуацію, щоб опрацювати її

		if (fin.beg == fin.end)  // якщо вдалося відкрити, але він пустий
			throw exception("File is empty!");  // прокинути виключну ситуацію, щоб опрацювати її
	}
	catch (const exception& ex)  // зловити виключну ситуацію
	{
		cout << ex.what() << endl;  // вивести що сталося

		fin.close();  // звільнити ресурси

		return false;  // повернути 0, оскільки текст не вдалося зчитати
	}

	string str = "";
	while (getline(fin, str))  // якщо все ОК, то поки можемо зчитати строку - зчитуємо її з файлу у змінну str
		_Text.push_back(str);  // записуємо строку у зчитаний текст

	fin.close();  // звільнюємо ресурси

	return true;  // повертаємо 1, оскільки текст успішно зчитано
}

inline void Cryptor::ProcessText(string _Key, const ModeOfProgram _Mode)
{  // основна функція шифрації, що отримує ключ та тип роботи програми (ПШ / ПД)

	 // R = 2
		for (UINT i = 0; i < _Text.size(); i++)  // ітеруємось текстом
			if (_Mode == Encrypt)
				_Text.at(i) = ToLowerCase(_Text.at(i));  // та усі символи його строк робимо прописними

		_Key = ToUpperCase(_Key);  // символи ключа робимо заголовними 
	// end

	for (UINT i = 0; i < _Text.size(); i++)  // біжимо по всім строкам тексту
	{
		UINT KeyMove = 0;  // змінна для ітерування ключем

		string ProcessedString = "";  // строка, яку отримаємо в результаті шифрації / дешифрації

		string strText = _Text.at(i);  // зчитуємо строку з тексту

		for (UINT j = 0; j < strText.size(); j++)  // ітеруємось зчитаною строкою
		{
			if (KeyMove == _Key.size())  // якщо дійшли до кінця ключа
				KeyMove = 0;  // починаємо знову ("підписувати" ключ під текстом)

			if (_Mode == Encrypt)  // якщо працюємо на шифр
				ProcessedString += char((int)strText.at(j) - (int)_Key.at(KeyMove++) /5);  // шифруємо таким чином
			else if (_Mode == Decrypt)  // якщо розшифровуємо
				ProcessedString += char((int)strText.at(j) + (int)_Key.at(KeyMove++) / 5);  // розшифровуємо зворотнім чином
		}

		_ProcessedText.push_back(ProcessedString);  // записуємо строку в опрацьований текст
	}

	return;
}