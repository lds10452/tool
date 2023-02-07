#include <iostream>
#include <fstream>
#include <string>
using namespace std;

#define FOURTH
void rTextFile()//��ѡ������
{
	ifstream ifs;
	ifs.open("TEXT.txt", ios::in);
	if (!ifs.is_open())
	{
		cout << "file open failed!" << endl;
		return;
	}
	int i = 0;
#ifdef FIRST
	char buff[640] = { 0 };
	while (ifs>>buff)//���ո񡢻��ж�ȡ���������Ŷ�ȡ��һ�У�����ʾ���кͿո�
	{
		cout << "-----" << i++ << "-----" << endl;
		cout << buff << endl;
	}
#elif defined SECOND
	char buff[1500] = { 0 };
	while (ifs.getline(buff,sizeof(buff))) //һ��һ�ж���������һ�з���false
	{
		cout << "-----" << i++ << "-----" << endl;
		cout << buff << endl;
	}
#elif defined THIRD
	string buff;
	while (getline(ifs,buff))
	{
		cout << "-----" << i++ << "-----" << endl;
		cout << buff << endl;
	}
#elif defined FOURTH
	char c;
	while ((c=ifs.get())!=EOF)//һ���ַ���ȡ,����ʾ���кͿո�
	{
		cout << c ;
	}
#endif 
	ifs.close();
}
void wTextFile()
{
	ofstream ofs;
	ofs.open("TEXT.txt", ios::out | ios::app);
	ofs << "11111";
	ofs.close();
}

class Person
{
public:
	char m_cName[64];
	int m_nAge;
};
void rBinFile()
{
	ifstream ifs("BIN.txt", ios::in | ios::binary);
	if (!ifs.is_open())
	{
		cout << "open file failed!";
	}
	Person p;
	ifs.read((char*)&p, sizeof(p));
	cout << p.m_cName << "----" << p.m_nAge << endl;
	ifs.close();
}
void wBinFile()
{
	ofstream ofs("BIN.txt", ios::out | ios::binary);
	//ofs.open("BIN.txt", ios::out | ios::binary);
	Person p = { "����",20 };
	ofs.write((const char*)&p, sizeof(p));
	ofs.close();
}
int main()
{
	rTextFile();
	//wTextFile();
	//rBinFile();
	//wBinFile();
	system("pause");
	return 0;
}