#include <stdio.h>
#include <iostream>
#include <vector>
#include <cmath>
#include "numbers.dat"

using namespace std;

void SearchArray(int head, int tail, vector<int> &simple);
void Seive(vector<int> &simple);

const int Max = 100000;

int main(int argc, char* argv[])
{
	if (argc % 2 == 0 || argc == 1) //��������� ������������ �����
	{
		return -1;//������� ������
	}

	vector<int> simple; //��������� ������� �����

	Seive(simple);

	int head, tail; //�������� ������ � ����� ���������� ������, -1 ���� ����������.
	head = tail = -1;

	for (int i = 1; i < argc; ++i) //�������� ���������
	{
		if (head == -1) //��������� ������� ������ ����������
		{
			head = std::atoi(argv[i]); //��� ���������� ���������� ������� - ������
		}
		else
		{
			tail = std::atoi(argv[i]); //����� ��� �����

			if (head <= tail)//�������� ������ <=�����
			{
				SearchArray(head, tail, simple);
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

void SearchArray(int head, int tail, vector<int> &simple)
{
	int count = 0; //���������� ��������� ������� �����
	bool flag = false; //���� ���������� ������ ����������

	for (int i = 0, j = 0; i < Size; i++)
	{
		while (Data[i] > simple[j] && j < simple.size() - 1) //�������� >= ������� �����.
		{
			j++;
		}
		if (Data[i] < head) //�� ����� �� ������ ����������
		{
			continue;
		}
		else if (Data[i] == head) //��������� �������� ����������� � ���������
		{
			flag = true;
			if (Data[i] == simple[j])
			{
				count++;
			}
		}
		else if (Data[i] == tail && flag)//��������� �������� ����������� � ��������
		{
			if (Data[i] == simple[j])
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
			if (Data[i] == simple[j])
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
	cout << count << "\n"; //����� ���������� ������� ����� � ����������
};

void Seive(vector<int> &simple)
{
	int div[Max + 1]; //����������� ������� ��������
	memset(div, 0, (Max + 1) * sizeof(int));
	for (int i = 2; i <= Max; ++i) //������ ������ ���������� �� �������� �����
	{
		if (div[i] == 0)
		{
			div[i] = i;
			simple.push_back(i);
		}
		for (int j = 0; j < (int)simple.size() && simple[j] <= div[i] && i * simple[j] <= Max; ++j)
		{
			div[i*simple[j]] = simple[j];
		}
	}
};

