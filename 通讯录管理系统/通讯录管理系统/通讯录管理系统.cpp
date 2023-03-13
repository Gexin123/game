#include<iostream>
#include<string>
using namespace std;
#define MAX 1000

//菜单页面
void showmenu()
{
	cout << "***********************" << endl;
	cout << "*****1、添加联系人*****" << endl;
	cout << "*****2、显示联系人*****" << endl;
	cout << "*****3、删除联系人*****" << endl;
	cout << "*****4、查找联系人*****" << endl;
	cout << "*****5、修改联系人*****" << endl;
	cout << "*****6、清空联系人*****" << endl;
	cout << "*****0、退出通讯录*****" << endl;
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

//添加联系人
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
		cout << "请输入姓名" << endl;
		cin >> name;
		abs->personarray[abs->m_size].m_name = name;
		
		cout << "请输入性别" << endl;
		int sex = 0;
		cin >> sex;
		abs->personarray[abs->m_size].m_sex = sex;

		cout << "请输入年纪" << endl;
		int age = 0;
		cin >> age;
		abs->personarray[abs->m_size].m_age = age;

		cout << "请输入联系电话" << endl;
		string phone = "";
		cin >> phone;
		abs->personarray[abs->m_size].m_phone = phone;

		cout << "请输入家庭住址" << endl;
		string address;
		cin >> address;
		abs->personarray[abs->m_size].m_addr = address;

		abs->m_size++;

		system("pause");
		system("cls");
	}
}

//显示联系人
void showperson(Addressbooks* abs)
{
	if (abs->m_size == 0)
	{
		cout << "暂时没有联系人" << endl;
	}
	else
	{
		for (auto& p : abs->personarray)
		{
			cout << "姓名：" << p.m_name << "\t";
			cout << "性别：" << (p.m_sex == 1 ? "man" : "woman") << "\t";
			cout << "住址：" << p.m_addr << endl;
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
//删除联系人
void deleteperson(Addressbooks* abs)
{
	cout << "选择要删除的联系人" << endl;
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
		cout << "删除成功" << endl;
	}
	else
	{
		cout << "查无此人" << endl;
	}
	system("pause");
	system("cls");
}

//查找联系人
void findperson(Addressbooks* abs)
{
	cout << "请输入要找的联系人" << endl;
	string name;
	cin >> name;
	int ret = isexist(abs,name);
	if (ret != -1)
	{
		cout << "姓名：" << abs->personarray[ret].m_name << "\t";
		cout << "性别：" << abs->personarray[ret].m_sex << endl;
	}
	else
	{
		cout << "查无此人" << endl;
	}
	system("pause");
	system("cls");
}

//修改联系人
void xiugaiperson(Addressbooks* abs)
{
	cout << "请输入要修改的人" << endl;
	string name;
	cin >> name;
	int ret = isexist(abs, name);
	if (ret != -1)
	{
		cout << "请输入姓名：" << endl;
		string name;
		cin >> name;
		abs->personarray[ret].m_name = name;
		cout << "修改成功" << endl;
	}
	else
	{
		cout << "查无此人" << endl;
	}
	system("pause");
	system("cls");
}

//清空联系人
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
			cout << "欢迎下次使用" << endl;
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