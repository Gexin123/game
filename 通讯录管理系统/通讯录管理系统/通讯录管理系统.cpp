#include<iostream>
#include<string>
using namespace std;
#define MAX 1000

//�˵�ҳ��
void showmenu()
{
	cout << "***********************" << endl;
	cout << "*****1�������ϵ��*****" << endl;
	cout << "*****2����ʾ��ϵ��*****" << endl;
	cout << "*****3��ɾ����ϵ��*****" << endl;
	cout << "*****4��������ϵ��*****" << endl;
	cout << "*****5���޸���ϵ��*****" << endl;
	cout << "*****6�������ϵ��*****" << endl;
	cout << "*****0���˳�ͨѶ¼*****" << endl;
	cout << "***********************" << endl;
}

struct Person
{
	string m_name;
	int m_sex;
	int m_age;
	string m_phone;
	string m_addr;
};
struct Addressbooks
{
	struct Person personarray[MAX];
	int m_size;
};

//�����ϵ��
void addperson(Addressbooks* abs)
{
	if (abs->m_size == MAX)
	{
		cout << "full" << endl;
		return;
	}
	else
	{
		string name;
		cout << "����������" << endl;
		cin >> name;
		abs->personarray[abs->m_size].m_name = name;
		
		cout << "�������Ա�" << endl;
		int sex = 0;
		cin >> sex;
		abs->personarray[abs->m_size].m_sex = sex;

		cout << "���������" << endl;
		int age = 0;
		cin >> age;
		abs->personarray[abs->m_size].m_age = age;

		cout << "��������ϵ�绰" << endl;
		string phone = "";
		cin >> phone;
		abs->personarray[abs->m_size].m_phone = phone;

		cout << "�������ͥסַ" << endl;
		string address;
		cin >> address;
		abs->personarray[abs->m_size].m_addr = address;

		abs->m_size++;

		system("pause");
		system("cls");
	}
}

//��ʾ��ϵ��
void showperson(Addressbooks* abs)
{
	if (abs->m_size == 0)
	{
		cout << "��ʱû����ϵ��" << endl;
	}
	else
	{
		for (auto& p : abs->personarray)
		{
			cout << "������" << p.m_name << "\t";
			cout << "�Ա�" << (p.m_sex == 1 ? "man" : "woman") << "\t";
			cout << "סַ��" << p.m_addr << endl;
		}
	}
	system("pause");
	system("cls");
}


int isexist(Addressbooks* abs, string name)
{
	for (int i = 0; i < abs->m_size; i++)
	{
		if (abs->personarray[i].m_name == name)
		{
			return i;
		}
	}
	return -1;
}
//ɾ����ϵ��
void deleteperson(Addressbooks* abs)
{
	cout << "ѡ��Ҫɾ������ϵ��" << endl;
	string name;
	cin >> name;

	int ret = isexist(abs, name);
	if (ret != -1)
	{
		for (int i = ret; i < abs->m_size; i++)
		{
			abs->personarray[i] = abs->personarray[i++];
		}
		abs->m_size--;
		cout << "ɾ���ɹ�" << endl;
	}
	else
	{
		cout << "���޴���" << endl;
	}
	system("pause");
	system("cls");
}

//������ϵ��
void findperson(Addressbooks* abs)
{
	cout << "������Ҫ�ҵ���ϵ��" << endl;
	string name;
	cin >> name;
	int ret = isexist(abs,name);
	if (ret != -1)
	{
		cout << "������" << abs->personarray[ret].m_name << "\t";
		cout << "�Ա�" << abs->personarray[ret].m_sex << endl;
	}
	else
	{
		cout << "���޴���" << endl;
	}
	system("pause");
	system("cls");
}

//�޸���ϵ��
void xiugaiperson(Addressbooks* abs)
{
	cout << "������Ҫ�޸ĵ���" << endl;
	string name;
	cin >> name;
	int ret = isexist(abs, name);
	if (ret != -1)
	{
		cout << "������������" << endl;
		string name;
		cin >> name;
		abs->personarray[ret].m_name = name;
		cout << "�޸ĳɹ�" << endl;
	}
	else
	{
		cout << "���޴���" << endl;
	}
	system("pause");
	system("cls");
}

//�����ϵ��
void clearperson(Addressbooks* abs)
{
	abs->m_size = 0;
	system("pause");
	system("cls");
}


int main()
{
	int select;

	Addressbooks abs;
	abs.m_size = 0;
	while (true)
	{
		showmenu();
		cin >> select;
		switch (select)
		{
		case 1:
			addperson(&abs);
			break;
		case 2:
			showperson(&abs);
			break;
		case 3:
			deleteperson(&abs);
			break;
		case 4:
			findperson(&abs);
			break;
		case 5:
			xiugaiperson(&abs);
			break;
		case 6:
			clearperson(&abs);
			break;
		case 0:
			cout << "��ӭ�´�ʹ��" << endl;
			system("pause");
			system("cls");
			return 0;
			break;
		default:
			break;
		}
	}
	system("pause");
	return 0;
}