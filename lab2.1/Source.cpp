#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include <string.h>
#include <locale.h>
#include <iostream>

using namespace std;

class Plenty {
private:
	int size;
	int *data;
public:
	Plenty() : data(nullptr), size(0) {}
	Plenty(int size) : data(new int[size]), size(size) {}
	Plenty(const Plenty& second);
	~Plenty();

	int operator[](const int index);

	Plenty operator+(const Plenty& second);
	Plenty operator-(const Plenty& second);

	Plenty& operator+(int num);
	Plenty& operator-(int num);

	Plenty& operator+=(int num);
	Plenty& operator-=(int num);

	Plenty intersection(const Plenty& second);
	Plenty ungeneral(const Plenty& second);

	bool check_num(int num);

	bool operator==(const Plenty& second);

	friend std::ostream& operator<<(std::ostream& s, const Plenty& set);
};


Plenty:: Plenty(const Plenty& second) {
	size = second.size;
	data = second.data;
}

Plenty:: ~Plenty() {
	if (!data)
		delete[] data;
}
int Plenty:: operator[](const int index){
	if (!data)
		throw std::logic_error("arr == nullptr");
	if (index > size - 1 || index < 0)
		throw std::logic_error("invalide index");
	return data[index];
	}
Plenty Plenty:: operator+(const Plenty& second){
	Plenty tmp(size + second.size);
	tmp.size = 0;
	for (int i = 0; i < size; i++) {
		tmp.data[i] = data[i];
		tmp.size++;
	}
	for (int i = 0; i < second.size; i++) {
		if (check_num(second.data[i]) == false)
		{
			tmp.data[tmp.size] = second.data[i];
			tmp.size++;
		}
	}
	return tmp;
}
Plenty Plenty:: operator-(const Plenty& second){ 
	Plenty tmp(size);
	tmp.size = 0;
	bool flag = false;
	for (int i = 0; i < size; i++) {
		flag = false;
		for (int j = 0; j < second.size; j++) {
			if (data[i] == second.data[j])
			{
				flag = true;
				break;
			}
		}
		if (flag == false)
		{
			tmp.data[tmp.size] = data[i];
			tmp.size++;
		}
	}
	return tmp;
}
Plenty& Plenty:: operator+(int num){
	if (!data)
	{
		Plenty tmp(size);
		tmp.data[0] = num;
		data = tmp.data;
		size++;
	}
	if (check_num(num) == false)
	{
		Plenty tmp(size);
		for (int i = 0; i < size; i++) {
			tmp.data[i] = data[i];
		}
		tmp.data[tmp.size] = num;
		data = tmp.data;
		size++;
	}
	return *this;
}
Plenty& Plenty:: operator-(int num){
	if (check_num(num) == false)
		throw std::logic_error("Set have not got this num");
	for (int i = 0; i < size; i++) {
		if (data[i] == num)
		{
			for (int j = i; j < size - 1; j++) {
				data[j] = data[j + 1];
			}
			size--;
			break;
		}
	}
	return *this;
}

Plenty& Plenty::operator+=(int num)
{
	if (!data)
	{
		Plenty tmp(size);
		tmp.data[0] = num;
		data = tmp.data;
		size++;

	}
	if (check_num(num) == false) {
		Plenty tmp(size);
		for (int i = 0; i < size; i++) {
			tmp.data[i] = data[i];
		}
		tmp.data[tmp.size] = num;
		data = tmp.data;
		size++;
	}
	return *this;
}

Plenty& Plenty:: operator-=(int num){
	if (check_num(num) == false)
		throw std::logic_error("Set have not got this num");
	for (int i = 0; i < size; i++) {
		if (data[i] == num)
		{
			for (int j = i; j < size - 1; j++) {
				data[j] = data[j + 1];
			}
			size--;
			break;
		}
	}
	return *this;
} 
Plenty Plenty:: intersection(const Plenty& second){
	Plenty tmp(size);
	tmp.size = 0;
	bool flag = false;
	for (int i = 0; i < size; i++) {
		flag = false;
		for (int j = 0; j < second.size; j++) {
			if (data[i] == second.data[j])
			{
				flag = true;
				break;
			}
		}
		if (flag == true)
		{
			tmp.data[tmp.size] = data[i];
			tmp.size++;
		}
	}
	return tmp;
}
bool Plenty:: check_num(int num){
	if (!data)
		throw std::logic_error("data == nullptr in check_num");
	for (int i = 0; i < size; i++) {
		if (num == data[i])
			return true;
	}
	return false;
}
bool Plenty:: operator==(const Plenty& second){
	if (second.size != size)
		return false;
	else
	{
		bool flag = false;
		for (int i = 0; i < size; i++)
		{
			flag = false;
			for (int j = 0; j < second.size; j++) {
				if (data[i] == second.data[j]) {
					flag = true;
				}
			}
			if (flag == false)
				return false;
		}
		return true;
	}
}
std::ostream& operator<<(std::ostream& s, const Plenty& plenty){
	for (int i = 0; i < plenty.size; i++) {
		s << plenty.data[i] << " ";
	}
	return s;
}

void menu() {
	cout << "1.Add elements" << endl;
	cout << "2.Delete elements" << endl;
	cout << "3.Sum plenty" << endl;
	cout << "4.Div plenty" << endl;
	cout << "5.Element by index" << endl;
	cout << "6.Intersection" << endl;
	cout << "7.Find num in plenty" << endl;
	cout << "8.Ungeneral" << endl;
}
void menu_2() {
	cout << "1.plenty" << endl;
	cout << "2.plenty" << endl;
}
void menu_3() {
	cout << "1.p1-p2" << endl;
	cout << "2.p2-p1" << endl;
}

int main() {
	Plenty p1;
	Plenty p2;
	Plenty p3;

	while (true)
	{
		system("cls");
		menu();
		size_t flag;
		cin >> flag;
		switch (flag)
		{
		case 1:
		{
			bool fg = true;
			while (fg) {
				system("cls");
				menu_2();
				size_t flag_2;
				cin >> flag_2;
				switch (flag_2)
				{
				case 1:
				{
					int i;
					cout << "i=";
					cin >> i;
					p1 += i;
					cout << "p1= " << p1 << endl;
					system("pause");
					fg = false;
					break;
				}
				case 2:
				{
					int i;
					cout << "i=";
					cin >> i;
					p2 + i;
					cout << "p2= " << p2 << endl;
					system("pause");
					fg = false;
					break;
				}
				}
			} break;
		}
		case 2:
		{
			bool fg2 = true;
			while (fg2) {
				system("cls");
				menu_2();
				size_t flag_2;
				cin >> flag_2;
				switch (flag_2)
				{
				case 1:
				{
					int i;
					cout << "i=";
					cin >> i;
					p1 -= i;
					cout << "p1= " << p1 << endl;
					system("pause");
					fg2 = false;
					break;
				}
				case 2:
				{
					int i;
					cout << "i=";
					cin >> i;
					p2 - i;
					cout << "p2= " << p2 << endl;
					system("pause");
					fg2 = false;
					break;
				}
				}

			} break;
		}
		case 3:
		{
			cout << "p3= " << p1 + p2 << endl;
			system("pause");
			break;
		}
		case 4:
		{
			bool fg3 = true;
			while (fg3) {
				system("cls");
				menu_3();
				size_t flag_2;
				cin >> flag_2;
				switch (flag_2)
				{
				case 1:
				{
					cout << "p3= " << p1 - p2 << endl;
					system("pause");
					fg3 = false;
					break;
				}
				case 2:
				{
					cout << "p3= " << p2 - p1 << endl;
					system("pause");
					fg3 = false;
					break;
				}
				}

			} break;
		}
		case 5:
		{
			bool fg4 = true;
			while (fg4) {
				system("cls");
				menu_2();
				size_t flag_2;
				cin >> flag_2;
				switch (flag_2)
				{
				case 1:
				{
					int i;
					cout << "i=";
					cin >> i;
					cout << "p1[i]= " << p1[i] << endl;
					system("pause");
					fg4 = false;
					break;
				}
				case 2:
				{
					int i;
					cout << "i=";
					cin >> i;
					cout << "p2= " << p2[i] << endl;
					system("pause");
					fg4 = false;
					break;
				}
				}

			} break;
		}
		case 6:
		{
			cout << "intersection : " << p1.intersection(p2) << endl;
			system("pause");
			break;
		}
		case 7:
		{
			bool fg7 = true;
			while (fg7) {
				system("cls");
				menu_2();
				size_t flag_2;
				cin >> flag_2;
				switch (flag_2)
				{
				case 1:
				{
					int i;
					cout << "i=";
					cin >> i;
					bool p = p1.check_num(i);
					if (p == true) {
						cout << "plenty has num" << endl;
					}
					else {
						cout << "plenty has not num" << endl;
					}
					system("pause");
					fg7 = false;
					break;
				}
				case 2:
				{
					int i;
					cout << "i=";
					cin >> i;
					bool p = p2.check_num(i);
					if (p == true) {
						cout << "plenty has num" << endl;
					}
					else {
						cout << "plenty has not num" << endl;
					}
					system("pause");
					fg7 = false;
					break;
				}
				}

			} break;
		}
		case 8:
		{
			cout << "ungeneral: " << (p1 - p2) + (p2 - p1) << endl;
			system("pause");
			break;
		}

		}
	}
}
	