#pragma once

class Cryptor sealed
{
public:

	inline bool GetText(const string&);

	inline void ProcessText(string, const ModeOfProgram);

	vector <string> GetProcessedText() const
	{	return _ProcessedText;	}

private:

	vector <string> _Text;  // ���� ��� ��������� ��������� ������
	vector <string> _ProcessedText;  // ���� ��� ��������� ������������� ������

};

inline bool Cryptor::GetText(const string& _Filename)
{  // �������, �� ������ ����� � ����� �� ������� ������ �� �����

	fstream fin;

	try
	{
		fin.open(_Filename, fstream::in);  // ������ ������� ����

		if (!fin.is_open())  // ���� �� ��������
			throw exception("Error while opening file with text!");  // ��������� �������� ��������, ��� ���������� ��

		if (fin.beg == fin.end)  // ���� ������� �������, ��� �� ������
			throw exception("File is empty!");  // ��������� �������� ��������, ��� ���������� ��
	}
	catch (const exception& ex)  // ������� �������� ��������
	{
		cout << ex.what() << endl;  // ������� �� �������

		fin.close();  // �������� �������

		return false;  // ��������� 0, ������� ����� �� ������� �������
	}

	string str = "";
	while (getline(fin, str))  // ���� ��� ��, �� ���� ������ ������� ������ - ������� �� � ����� � ����� str
		_Text.push_back(str);  // �������� ������ � �������� �����

	fin.close();  // ��������� �������

	return true;  // ��������� 1, ������� ����� ������ �������
}

inline void Cryptor::ProcessText(string _Key, const ModeOfProgram _Mode)
{  // ������� ������� ��������, �� ������ ���� �� ��� ������ �������� (�� / ��)

	 // R = 2
		for (UINT i = 0; i < _Text.size(); i++)  // ��������� �������
			if (_Mode == Encrypt)
				_Text.at(i) = ToLowerCase(_Text.at(i));  // �� �� ������� ���� ����� ������ ����������

		_Key = ToUpperCase(_Key);  // ������� ����� ������ ����������� 
	// end

	for (UINT i = 0; i < _Text.size(); i++)  // ����� �� ��� ������� ������
	{
		UINT KeyMove = 0;  // ����� ��� ���������� ������

		string ProcessedString = "";  // ������, ��� �������� � ��������� �������� / ����������

		string strText = _Text.at(i);  // ������� ������ � ������

		for (UINT j = 0; j < strText.size(); j++)  // ��������� �������� �������
		{
			if (KeyMove == _Key.size())  // ���� ����� �� ���� �����
				KeyMove = 0;  // �������� ����� ("����������" ���� �� �������)

			if (_Mode == Encrypt)  // ���� �������� �� ����
				ProcessedString += char((int)strText.at(j) - (int)_Key.at(KeyMove++) /5);  // ������� ����� �����
			else if (_Mode == Decrypt)  // ���� ������������
				ProcessedString += char((int)strText.at(j) + (int)_Key.at(KeyMove++) / 5);  // ������������ �������� �����
		}

		_ProcessedText.push_back(ProcessedString);  // �������� ������ � ������������ �����
	}

	return;
}