#include <stdio.h>
#include <iostream>
#include <vector>
#include <cmath>
#include "numbers.dat"


using namespace std;

const int Simple317[66] =
{ 2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73,
79, 83, 89, 97, 101, 103, 107, 109, 113, 127, 131, 137, 139, 149, 151, 157, 163,
167, 173, 179, 181, 191, 193, 197, 199, 211, 223, 227, 229, 233, 239, 241, 251,
257, 263, 269, 271, 277, 281, 283, 293, 307, 311, 313, 317}; 
//��������� ������ �� ���� ������������ ������� ����� [0, sqrt(100000)] 
//������������ ��� �������� ���������, ��������� ������ �� ���� ������� ��������� ���������.

void SearchArray(int head, int tail); //����� ���������� � ������� �� ��������� [head, tail]
bool CheckSimple(int n); //�������� �������� ����� (����� �������� ������� ��������� �� sqrt[n])
int GetUpperSimple(int n); //��������� ������� ������������� �������� �������� n �� Simple317

int main(int argc, char* argv[])
{
	if (argc % 2 == 0||argc==1) //��������� ������������ �����
	{
		return -1;//������� ������
	}

	int head, tail; //�������� ������ � ����� ���������� ������, -1 ���� ����������.
	head = tail = -1;

	for (int i = 1; i < argc; ++i) //�������� ���������
	{
		if (head == -1) //��������� ������� ������ ����������
		{
			head= std::atoi(argv[i]); //��� ���������� ���������� ������� - ������
		}
		else
		{
			tail = std::atoi(argv[i]); //����� ��� �����

			if (head <= tail)//�������� ������ <=�����
			{
				SearchArray(head, tail);
			}
			else
			{
				cout << 0;
			}

			head = tail = -1; //����������� �������� �� ���������
		}
	}

	return 0;
}

void SearchArray(int head, int tail)
{
	int count = 0; //���������� ��������� ������� �����
	bool flag = false; //���� ���������� ������ ����������

	for (int i = 0; i < Size; i++)
	{
		if (Data[i] < head) //�� ����� �� ������ ����������
		{
			continue;
		}
		else if (Data[i] == head) //��������� �������� ����������� � ���������
		{
			flag = true;
			if (CheckSimple(Data[i]))
			{
				count++;
			}
		}
		else if (Data[i] == tail && flag)//��������� �������� ����������� � ��������
		{
			if (CheckSimple(Data[i]))
			{
				count++;
			}
		}
		else if (Data[i] > tail && flag) //��������� ���� � ������ ����������
		{
			flag = false;
		}
		else if (flag) //��������� �������� ������ ����������
		{
			if (CheckSimple(Data[i]))
			{
				count++;
			}
		}
		else //����������� �������� ����� ��������� ��� ��� ���������� ���������
		{
			if (flag) //���� ������ ��������� � ���� �� ������, �� ��������� �������� ���
			{
				count = 0;
			}
			flag = false;
			break;
		}
	}
	cout << count <<"\n"; //����� ���������� ������� ����� � ����������
};

bool CheckSimple(int n)
{
	if (n == 2) //�������� �� ����������� 2
	{
		return true;
	}
	int upperSimple = GetUpperSimple(n); //�������� ������ �� ������� �������
	for (int i = 0; i <= upperSimple; i++)
	{
		if (n%Simple317[i] == 0||n==1) //��������� ��������� �� ������� �����, ����������� �� 1
		{
			return false; //���� ������� - ����� �� �������
		}
	}
	return true; //����� - �������
}

int GetUpperSimple(int n)
{
	for (int i = 0; i < 66; i++)
	{
		if (Simple317[i] > sqrt(n))
		{
			return i;
		}
	}
	return 65;
}